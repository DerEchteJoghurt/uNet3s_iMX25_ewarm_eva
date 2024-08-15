/***********************************************************************
    Micro C Cube Standard, DEVICE DRIVER
    Interval Timer code for Freescale i.MX25

    Copyright (c)  2010, eForce Co., Ltd. All rights reserved.

    Version Information
            2010.10.26: Created.
 ***********************************************************************/


#include "uC3sys.h"
#include "imx25.h"

#include "DDR_FS_MX25EPIT_cfg.h"

#if 0
/***********  DDR_FS_MX25EPIT_cfg.h �̒�`���e  ************************/

/* �����g���M��̎��g�� */

#define CLKIH       24000000

/* ����g���M��̎��g�� */

#define CLKIL       32768

/* �����^�C�}�����݂̗D��x�i0�`15�j */

#define IPL_EPIT 0

/* �����^�C�}�̃`���l���ԍ��i1�`2�j */

#define CH_EPIT  1

/***********  DDR_FS_MX25EPIT_cfg.h �̒�`���e�͂����܂�  **************/
#endif

#if CH_EPIT==1
  #define REG_EPIT      REG_EPIT1
  #define INT_EPIT      INT_EPIT1
  #define IPG_CLK       0x00000400
#elif CH_EPIT==2
  #define REG_EPIT      REG_EPIT2
  #define INT_EPIT      INT_EPIT2
  #define IPG_CLK       0x00000800
#else
  #error invalid chanel number!
#endif

UW _ddr_fs_mx25epit_systim;
UW _ddr_fs_mx25epit_rate;
UW _ddr_fs_mx25epit_tick = 0;


/*******************************
      PLCLK�o�͎��g���̎擾
 *******************************/

UW _ddr_fs_mx25epit_pclk(UW PCTL)
{
    UW pd;
    UW mfd;
    UW mfi;
    W mfn;
    UW pll;

    pd = ((PCTL >> 26) & 0x0F) + 1;
    mfd = ((PCTL >> 16) & 0x03FF) + 1;
    mfi = ((PCTL >> 10) & 0x0F);
    if (mfi < 5) {
        mfi = 5;
    }
    mfn = (PCTL & 0x03FF);
    if (mfn > 511) {
        mfn -= 1024;
    }

    pll = (CLKIH * 2) / (pd * mfd);
    pll *= (mfi * mfd) + mfn;
    return pll;
}


/*******************************
      per_clk�̕�����̎擾
 *******************************/

UW _ddr_fs_mx25epit_get_perdiv(UW perclk_id)
{
    UW per_div;

    switch(perclk_id & 0xFFFFFFFC) {
        case 0x00000000:
            per_div = (REG_CCM.PCDR0 >> ((perclk_id & 0x00000003) * 8)) & 0x000000FF;
            break;
        case 0x00000004:
            per_div = (REG_CCM.PCDR1 >> ((perclk_id & 0x00000003) * 8)) & 0x000000FF;
            break;
        case 0x00000008:
            per_div = (REG_CCM.PCDR2 >> ((perclk_id & 0x00000003) * 8)) & 0x000000FF;
            break;
        case 0x0000000C:
            per_div = (REG_CCM.PCDR3 >> ((perclk_id & 0x00000003) * 8)) & 0x000000FF;
            break;
        default:
            per_div = 0;
            break;
    }
    return (per_div + 1);
}


/*******************************
      per_clk�̕�����̐ݒ�
 *******************************/

void _ddr_fs_mx25epit_set_perdiv(UW perclk_id, UW per_div)
{
    BOOL state;
    UW pcdr;

    per_div -= 1;
    state = sns_loc();
    if (state == FALSE) {
        loc_cpu();
    }
    switch(perclk_id & 0xFFFFFFFC) {
        case 0x00000000:
            pcdr = REG_CCM.PCDR0 & ~(0x000000FF << ((perclk_id & 0x00000003) * 8));
            REG_CCM.PCDR0 = (per_div << ((perclk_id & 0x00000003) * 8)) | pcdr;
            break;
        case 0x00000004:
            pcdr = REG_CCM.PCDR1 & ~(0x000000FF << ((perclk_id & 0x00000003) * 8));
            REG_CCM.PCDR1 = (per_div << ((perclk_id & 0x00000003) * 8)) | pcdr;
            break;
        case 0x00000008:
            pcdr = REG_CCM.PCDR2 & ~(0x000000FF << ((perclk_id & 0x00000003) * 8));
            REG_CCM.PCDR2 = (per_div << ((perclk_id & 0x00000003) * 8)) | pcdr;
            break;
        case 0x0000000C:
            pcdr = REG_CCM.PCDR3 & ~(0x000000FF << ((perclk_id & 0x00000003) * 8));
            REG_CCM.PCDR3 = (per_div << ((perclk_id & 0x00000003) * 8)) | pcdr;
            break;
        default:
            break;
    }
    if (state == FALSE) {
        unl_cpu();
    }
}


/***********************************
      hclk���g���̎擾
 ***********************************/

UW _ddr_fs_mx25epit_hclk(void)
{
    UW pclk;

    if ((REG_CCM.CCTL & 0x00004000) == 0) {
        pclk = 532000000;
    } else {
        pclk = 399000000;
    }
    pclk /= ((REG_CCM.CCTL >> 30) & 0x00000003) + 1;
    pclk /= ((REG_CCM.CCTL >> 28) & 0x00000003) + 1;
    return pclk;
}


/***********************************
      ipg_clk���g���̎擾
 ***********************************/

UW _ddr_fs_mx25epit_ipgclk(void)
{
    return (_ddr_fs_mx25epit_hclk() / 2);
}


/***********************************
      per_clk���g���̐ݒ�Ǝ擾
 ***********************************/

UW _ddr_fs_mx25epit_perclk(UW perclk_id, UW max_frq)
{
    BOOL state;
    UINT i;
    UW pclk;
    UW per_clk;
    UW per_div;
    UW perclk_ptn;

    perclk_ptn = 0x00000001 << perclk_id;
    if ((REG_CCM.MCR & perclk_ptn) == 0) {
        pclk =_ddr_fs_mx25epit_hclk();
    } else {
        pclk = _ddr_fs_mx25epit_pclk(REG_CCM.UPCTL);
    }

    if ((REG_CCM.CGCR0 & perclk_ptn) == 0) {
        per_div = 0;
        for(i = 1; i <= 64; i++) {
            if ((pclk / i) <= max_frq) {
                if ((pclk % i) == 0) {
                    per_div = i;
                    break;
                } else {
                    if (per_div == 0) {
                        per_div = i;
                    }
                }
            }
        }
        per_clk = pclk / per_div;
        state = sns_loc();
        if (state == FALSE) {
            loc_cpu();
        }
        _ddr_fs_mx25epit_set_perdiv(perclk_id, per_div);
        REG_CCM.CGCR0 |= perclk_ptn;
        if (state == FALSE) {
            unl_cpu();
        }
    } else {
        per_clk = pclk / _ddr_fs_mx25epit_get_perdiv(perclk_id);
    }
    return per_clk;
}


/*******************************
      �����^�C�}�̋N��
 *******************************/

void _ddr_fs_mx25epit_isr(void)
{
    loc_cpu();
    REG_EPIT.SR= 0x00000001;
    _ddr_fs_mx25epit_systim += _ddr_fs_mx25epit_tick;
    unl_cpu();
    isig_tim();
}

/*******************************
  �@    ���������[�`��
 *******************************/

T_CISR const _ddr_fs_mx25epit_cisr = {TA_NULL, (VP_INT)0, INT_EPIT, _ddr_fs_mx25epit_isr, IPL_EPIT};

void _ddr_fs_mx25epit_init(UINT tick)
{
    BOOL state;
    UW ipg_clk;

    if (acre_isr((T_CISR *)&_ddr_fs_mx25epit_cisr) >= E_OK) {

        ipg_clk = _ddr_fs_mx25epit_ipgclk();
        state = sns_loc();
        if (state == FALSE) {
            loc_cpu();
        }
        REG_CCM.CGCR1 |= IPG_CLK;
        if (state == FALSE) {
            unl_cpu();
        }

        REG_EPIT.CR = 0x00010000;
        _ddr_fs_mx25epit_tick = (tick * 1000);
        _ddr_fs_mx25epit_rate = ((ipg_clk / 1000) * tick);
        REG_EPIT.LR = _ddr_fs_mx25epit_rate-1;
        REG_EPIT.CMPR = 0;
        REG_EPIT.CR = 0x0108000E;
        ena_int(INT_EPIT);
        REG_EPIT.CR = 0x0108000F;
    }
}


/*******************************************
        �}�C�N���b�̃V�X�e�������擾
 *******************************************/

UW _kernel_micro_systim(void)
{
    UW clk = 0;
    UW tcn;

    if (_ddr_fs_mx25epit_tick != 0) {
        if ((REG_EPIT.SR & 0x00000001) != 0) {
            clk = _ddr_fs_mx25epit_systim + _ddr_fs_mx25epit_tick;
            tcn = _ddr_fs_mx25epit_rate - REG_EPIT.CNR;
        } else {
            clk = _ddr_fs_mx25epit_systim;
            tcn = _ddr_fs_mx25epit_rate - REG_EPIT.CNR;
            if ((REG_EPIT.SR & 0x00000001) != 0) {
                clk += _ddr_fs_mx25epit_tick;
                tcn = _ddr_fs_mx25epit_rate - REG_EPIT.CNR;
            }
        }
        clk += ((tcn * _ddr_fs_mx25epit_tick) / _ddr_fs_mx25epit_rate);
    }
    return clk;
}


/*******************************************
        �V�X�e�������̈ꎞ��~
 *******************************************/

void _kernel_micro_systim_stop(void)
{
    REG_EPIT.CR &= ~0x00000003;
}


/*******************************************
        �V�X�e�������̍ĊJ
 *******************************************/

void _kernel_micro_systim_start(void)
{
    REG_EPIT.CR |= 0x00000001;
}
