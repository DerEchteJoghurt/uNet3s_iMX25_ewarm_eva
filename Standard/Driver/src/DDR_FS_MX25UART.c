/***************************************************************************
    Micro C Cube Standard, DEVICE DRIVER
    Serial Interface for Freescale i.MX25

    Copyright (c)  2010-2011, eForce Co.,Ltd.  All rights reserved.

    Version Information
            2010.11.04: Created.
            2011.02.21: Mofified for RVDS warning.
 ***************************************************************************/

#include "kernel.h"

#include "imx25.h"

#include "DDR_COM.h"
#include "DDR_FS_MX25UART_cfg.h"
#include "DDR_FS_MX25UART.h"

#include <string.h>

#if 0
/******  DDR_FS_MX25UART_cfg.h の定義内容  *********************************/

/* UARTチャネルnの設定値 */

#define UART_n                  /* 未使用の場合はコメントアウト         */

#define TXBUF_SZn   1024        /* 送信バッファサイズ                   */
#define RXBUF_SZn   1024        /* 受信バッファサイズ                   */
#define XOFF_SZn    512         /* XOFF送出受信バッファデータ数トリガ   */
#define XON_SZn     128         /* XON送出受信バッファデータ数トリガ    */
                                /* レシーブFIFOデータ数トリガ           */
#define RXTL_n      24          /* 0～32                                */
                                /* トランスミットFIFOデータ数トリガ     */
#define TXTL_n      8           /* 2～32                                */
                                /* RTS出力アクティブトリガ              */
#define RTSTL_n     24          /* 0～32                                */
                                /* 割込みレベル                         */
#define DCEDTE_n    1           /* DCE(0)/DTE(1)の選択                  */
#define IPL_UARTn   2           /* 0(Lowest)～15(Highest)               */

/******  DDR_FS_MX25UART_cfg.h の定義内容はここまで  ***********************/
#endif


#ifdef UART_1
#if (RTSTL_1 > 32)
#error Invalid RTSTL Value
#endif

#if (RXTL_1 > 32)
#error Invalid RXTL Value
#endif

#if ((TXTL_1 < 2) || (TXTL_1 > 32))
#error Invalid TXTL Value
#endif

#if (TXBUF_SZ1==0)
#define _ddr_mx25uart_tbuf1  0
#else
VB  _ddr_mx25uart_tbuf1[TXBUF_SZ1];
#endif
VB  _ddr_mx25uart_rbuf1[RXBUF_SZ1];
UB  _ddr_mx25uart_sbuf1[RXBUF_SZ1];
T_MX25UART_MNG _ddr_mx25uart_data1;

void _ddr_mx25uart_intr(T_MX25UART_MNG *);
ER _ddr_mx25uartdrv(ID, VP, T_MX25UART_MNG *);

T_CDEV const _ddr_mx25uart_cdev1 = {&_ddr_mx25uart_data1, (FP)_ddr_mx25uartdrv};
T_CFLG const _ddr_mx25uart_cflg1 = {TA_TFIFO|TA_WMUL, 0x00000000};
T_CISR const _ddr_mx25uart_cisr1 = {TA_HLNG, (VP_INT)&_ddr_mx25uart_data1, INT_UART1, (FP)_ddr_mx25uart_intr, IPL_UART1};
#endif

#ifdef UART_2
#if (RTSTL_2 > 32)
#error Invalid RTSTL Value
#endif

#if (RXTL_2 > 32)
#error Invalid RXTL Value
#endif

#if ((TXTL_2 < 2) || (TXTL_2 > 32))
#error Invalid TXTL Value
#endif

#if (TXBUF_SZ2==0)
#define _ddr_mx25uart_tbuf2  0
#else
VB  _ddr_mx25uart_tbuf2[TXBUF_SZ2];
#endif
VB  _ddr_mx25uart_rbuf2[RXBUF_SZ2];
UB  _ddr_mx25uart_sbuf2[RXBUF_SZ2];
T_MX25UART_MNG _ddr_mx25uart_data2;

void _ddr_mx25uart_intr(T_MX25UART_MNG *);
ER _ddr_mx25uartdrv(ID, VP, T_MX25UART_MNG *);

T_CDEV const _ddr_mx25uart_cdev2 = {&_ddr_mx25uart_data2, (FP)_ddr_mx25uartdrv};
T_CFLG const _ddr_mx25uart_cflg2 = {TA_TFIFO|TA_WMUL, 0x00000000};
T_CISR const _ddr_mx25uart_cisr2 = {TA_HLNG, (VP_INT)&_ddr_mx25uart_data2, INT_UART2, (FP)_ddr_mx25uart_intr, IPL_UART2};
#endif

#ifdef UART_3
#if (RTSTL_3 > 32)
#error Invalid RTSTL Value
#endif

#if (RXTL_3 > 32)
#error Invalid RXTL Value
#endif

#if ((TXTL_3 < 2) || (TXTL_3 > 32))
#error Invalid TXTL Value
#endif

#if (TXBUF_SZ3==0)
#define _ddr_mx25uart_tbuf3  0
#else
VB  _ddr_mx25uart_tbuf3[TXBUF_SZ3];
#endif
VB  _ddr_mx25uart_rbuf3[RXBUF_SZ3];
UB  _ddr_mx25uart_sbuf3[RXBUF_SZ3];
T_MX25UART_MNG _ddr_mx25uart_data3;

void _ddr_mx25uart_intr(T_MX25UART_MNG *);
ER _ddr_mx25uartdrv(ID, VP, T_MX25UART_MNG *);

T_CDEV const _ddr_mx25uart_cdev3 = {&_ddr_mx25uart_data3, (FP)_ddr_mx25uartdrv};
T_CFLG const _ddr_mx25uart_cflg3 = {TA_TFIFO|TA_WMUL, 0x00000000};
T_CISR const _ddr_mx25uart_cisr3 = {TA_HLNG, (VP_INT)&_ddr_mx25uart_data3, INT_UART3, (FP)_ddr_mx25uart_intr, IPL_UART3};
#endif

#ifdef UART_4
#if (RTSTL_4 > 32)
#error Invalid RTSTL Value
#endif

#if (RXTL_4 > 32)
#error Invalid RXTL Value
#endif

#if ((TXTL_4 < 2) || (TXTL_4 > 32))
#error Invalid TXTL Value
#endif

#if (TXBUF_SZ4==0)
#define _ddr_mx25uart_tbuf4  0
#else
VB  _ddr_mx25uart_tbuf4[TXBUF_SZ4];
#endif
VB  _ddr_mx25uart_rbuf4[RXBUF_SZ4];
UB  _ddr_mx25uart_sbuf4[RXBUF_SZ4];
T_MX25UART_MNG _ddr_mx25uart_data4;

void _ddr_mx25uart_intr(T_MX25UART_MNG *);
ER _ddr_mx25uartdrv(ID, VP, T_MX25UART_MNG *);

T_CDEV const _ddr_mx25uart_cdev4 = {&_ddr_mx25uart_data4, (FP)_ddr_mx25uartdrv};
T_CFLG const _ddr_mx25uart_cflg4 = {TA_TFIFO|TA_WMUL, 0x00000000};
T_CISR const _ddr_mx25uart_cisr4 = {TA_HLNG, (VP_INT)&_ddr_mx25uart_data4, INT_UART4, (FP)_ddr_mx25uart_intr, IPL_UART4};
#endif

#ifdef UART_5
#if (RTSTL_5 > 32)
#error Invalid RTSTL Value
#endif

#if (RXTL_5 > 32)
#error Invalid RXTL Value
#endif

#if ((TXTL_5 < 2) || (TXTL_5 > 32))
#error Invalid TXTL Value
#endif

#if (TXBUF_SZ5==0)
#define _ddr_mx25uart_tbuf5  0
#else
VB  _ddr_mx25uart_tbuf5[TXBUF_SZ5];
#endif
VB  _ddr_mx25uart_rbuf5[RXBUF_SZ5];
UB  _ddr_mx25uart_sbuf5[RXBUF_SZ5];
T_MX25UART_MNG _ddr_mx25uart_data5;

void _ddr_mx25uart_intr(T_MX25UART_MNG *);
ER _ddr_mx25uartdrv(ID, VP, T_MX25UART_MNG *);

T_CDEV const _ddr_mx25uart_cdev5 = {&_ddr_mx25uart_data5, (FP)_ddr_mx25uartdrv};
T_CFLG const _ddr_mx25uart_cflg5 = {TA_TFIFO|TA_WMUL, 0x00000000};
T_CISR const _ddr_mx25uart_cisr5 = {TA_HLNG, (VP_INT)&_ddr_mx25uart_data5, INT_UART5, (FP)_ddr_mx25uart_intr, IPL_UART5};
#endif

extern UW _ddr_fs_mx25epit_perclk(UW perclk_id, UW max_frq);
extern UW _ddr_fs_mx25epit_ipgclk(void);

/***************************************
        UARTデバイスドライバ初期化
 ***************************************/

ER _ddr_mx25uart_init(ID devid, volatile struct t_uart *uart_port)
{
    BOOL state;
    ER ercd;

  #ifdef UART_1
    if (uart_port == &REG_UART1) {
        memset(&_ddr_mx25uart_data1, 0x00, sizeof(_ddr_mx25uart_data1));
        _ddr_mx25uart_data1.port = &REG_UART1;
        _ddr_mx25uart_data1.tbuf = _ddr_mx25uart_tbuf1;
        _ddr_mx25uart_data1.rbuf = _ddr_mx25uart_rbuf1;
        _ddr_mx25uart_data1.sbuf = _ddr_mx25uart_sbuf1;
        _ddr_mx25uart_data1.tsize = TXBUF_SZ1;
        _ddr_mx25uart_data1.rsize = RXBUF_SZ1;
        _ddr_mx25uart_data1.xoff_size = XOFF_SZ1;
        _ddr_mx25uart_data1.xon_size = XON_SZ1;
        _ddr_mx25uart_data1.aux[0] = (TXTL_1 << 10) | (DCEDTE_1 << 6) | RXTL_1;
        _ddr_mx25uart_data1.aux[1] = (RTSTL_1 << 10);
        _ddr_mx25uart_data1.devhdr = (FP)_ddr_mx25uartdrv;
        if ((ercd = acre_flg((T_CFLG *)&_ddr_mx25uart_cflg1)) > E_OK) {
            _ddr_mx25uart_data1.flgid = (UH)ercd;
            if ((ercd = acre_isr((T_CISR *)&_ddr_mx25uart_cisr1)) < E_OK) {
                del_flg((ID)_ddr_mx25uart_data1.flgid);
            } else {
                _ddr_fs_mx25epit_perclk(15, 66500000);
                state = sns_loc();
                if (state == FALSE) {
                    loc_cpu();
                }
                REG_CCM.CGCR2 |= 0x00004000;
                if (state == FALSE) {
                    unl_cpu();
                }
                dis_int(INT_UART1);
                _ddr_mx25uart_data1.intno = INT_UART1;
                REG_UART1.UCR2 = 0;
                _ddr_mx25uart_data1.isrid = (UH)ercd;
                ercd = vdef_dev(devid, (VP)&_ddr_mx25uart_cdev1);
                ena_int(INT_UART1);
            }
        }
    } else
  #endif

  #ifdef UART_2
    if (uart_port == &REG_UART2) {
        memset(&_ddr_mx25uart_data2, 0x00, sizeof(_ddr_mx25uart_data2));
        _ddr_mx25uart_data2.port = &REG_UART2;
        _ddr_mx25uart_data2.tbuf = _ddr_mx25uart_tbuf2;
        _ddr_mx25uart_data2.rbuf = _ddr_mx25uart_rbuf2;
        _ddr_mx25uart_data2.sbuf = _ddr_mx25uart_sbuf2;
        _ddr_mx25uart_data2.tsize = TXBUF_SZ2;
        _ddr_mx25uart_data2.rsize = RXBUF_SZ2;
        _ddr_mx25uart_data2.xoff_size = XOFF_SZ2;
        _ddr_mx25uart_data2.xon_size = XON_SZ2;
        _ddr_mx25uart_data2.aux[0] = (TXTL_2 << 10) | (DCEDTE_2 << 6) | RXTL_2;
        _ddr_mx25uart_data2.aux[1] = (RTSTL_2 << 10);
        _ddr_mx25uart_data2.devhdr = (FP)_ddr_mx25uartdrv;
        if ((ercd = acre_flg((T_CFLG *)&_ddr_mx25uart_cflg2)) > E_OK) {
            _ddr_mx25uart_data2.flgid = (UH)ercd;
            if ((ercd = acre_isr((T_CISR *)&_ddr_mx25uart_cisr2)) < E_OK) {
                del_flg((ID)_ddr_mx25uart_data2.flgid);
            } else {
                _ddr_fs_mx25epit_perclk(15, 66500000);
                state = sns_loc();
                if (state == FALSE) {
                    loc_cpu();
                }
                REG_CCM.CGCR2 |= 0x00008000;
                if (state == FALSE) {
                    unl_cpu();
                }
                dis_int(INT_UART2);
                _ddr_mx25uart_data2.intno = INT_UART2;
                REG_UART2.UCR2 = 0;
                _ddr_mx25uart_data2.isrid = (UH)ercd;
                ercd = vdef_dev(devid, (VP)&_ddr_mx25uart_cdev2);
                ena_int(INT_UART2);
            }
        }
    } else
  #endif

  #ifdef UART_3
    if (uart_port == &REG_UART3) {
        memset(&_ddr_mx25uart_data3, 0x00, sizeof(_ddr_mx25uart_data3));
        _ddr_mx25uart_data3.port = &REG_UART3;
        _ddr_mx25uart_data3.tbuf = _ddr_mx25uart_tbuf3;
        _ddr_mx25uart_data3.rbuf = _ddr_mx25uart_rbuf3;
        _ddr_mx25uart_data3.sbuf = _ddr_mx25uart_sbuf3;
        _ddr_mx25uart_data3.tsize = TXBUF_SZ3;
        _ddr_mx25uart_data3.rsize = RXBUF_SZ3;
        _ddr_mx25uart_data3.xoff_size = XOFF_SZ3;
        _ddr_mx25uart_data3.xon_size = XON_SZ3;
        _ddr_mx25uart_data3.aux[0] = (TXTL_3 << 10) | (DCEDTE_3 << 6) | RXTL_3;
        _ddr_mx25uart_data3.aux[1] = (RTSTL_3 << 10);
        _ddr_mx25uart_data3.devhdr = (FP)_ddr_mx25uartdrv;
        if ((ercd = acre_flg((T_CFLG *)&_ddr_mx25uart_cflg3)) > E_OK) {
            _ddr_mx25uart_data3.flgid = (UH)ercd;
            if ((ercd = acre_isr((T_CISR *)&_ddr_mx25uart_cisr3)) < E_OK) {
                del_flg((ID)_ddr_mx25uart_data3.flgid);
            } else {
                _ddr_fs_mx25epit_perclk(15, 66500000);
                state = sns_loc();
                if (state == FALSE) {
                    loc_cpu();
                }
                REG_CCM.CGCR2 |= 0x00010000;
                if (state == FALSE) {
                    unl_cpu();
                }
                dis_int(INT_UART3);
                _ddr_mx25uart_data3.intno = INT_UART3;
                REG_UART3.UCR2 = 0;
                _ddr_mx25uart_data3.isrid = (UH)ercd;
                ercd = vdef_dev(devid, (VP)&_ddr_mx25uart_cdev3);
                ena_int(INT_UART3);
            }
        }
    } else
  #endif

  #ifdef UART_4
    if (uart_port == &REG_UART4) {
        memset(&_ddr_mx25uart_data4, 0x00, sizeof(_ddr_mx25uart_data4));
        _ddr_mx25uart_data4.port = &REG_UART4;
        _ddr_mx25uart_data4.tbuf = _ddr_mx25uart_tbuf4;
        _ddr_mx25uart_data4.rbuf = _ddr_mx25uart_rbuf4;
        _ddr_mx25uart_data4.sbuf = _ddr_mx25uart_sbuf4;
        _ddr_mx25uart_data4.tsize = TXBUF_SZ4;
        _ddr_mx25uart_data4.rsize = RXBUF_SZ4;
        _ddr_mx25uart_data4.xoff_size = XOFF_SZ4;
        _ddr_mx25uart_data4.xon_size = XON_SZ4;
        _ddr_mx25uart_data4.aux[0] = (TXTL_4 << 10) | (DCEDTE_4 << 6) | RXTL_4;
        _ddr_mx25uart_data4.aux[1] = (RTSTL_4 << 10);
        _ddr_mx25uart_data4.devhdr = (FP)_ddr_mx25uartdrv;
        if ((ercd = acre_flg((T_CFLG *)&_ddr_mx25uart_cflg4)) > E_OK) {
            _ddr_mx25uart_data4.flgid = (UH)ercd;
            if ((ercd = acre_isr((T_CISR *)&_ddr_mx25uart_cisr4)) < E_OK) {
                del_flg((ID)_ddr_mx25uart_data4.flgid);
            } else {
                _ddr_fs_mx25epit_perclk(15, 66500000);
                state = sns_loc();
                if (state == FALSE) {
                    loc_cpu();
                }
                REG_CCM.CGCR2 |= 0x00020000;
                if (state == FALSE) {
                    unl_cpu();
                }
                dis_int(INT_UART4);
                _ddr_mx25uart_data4.intno = INT_UART4;
                REG_UART4.UCR2 = 0;
                _ddr_mx25uart_data4.isrid = (UH)ercd;
                ercd = vdef_dev(devid, (VP)&_ddr_mx25uart_cdev4);
                ena_int(INT_UART4);
            }
        }
    } else
  #endif

  #ifdef UART_5
    if (uart_port == &REG_UART5) {
        memset(&_ddr_mx25uart_data5, 0x00, sizeof(_ddr_mx25uart_data5));
        _ddr_mx25uart_data5.port = &REG_UART5;
        _ddr_mx25uart_data5.tbuf = _ddr_mx25uart_tbuf5;
        _ddr_mx25uart_data5.rbuf = _ddr_mx25uart_rbuf5;
        _ddr_mx25uart_data5.sbuf = _ddr_mx25uart_sbuf5;
        _ddr_mx25uart_data5.tsize = TXBUF_SZ5;
        _ddr_mx25uart_data5.rsize = RXBUF_SZ5;
        _ddr_mx25uart_data5.xoff_size = XOFF_SZ5;
        _ddr_mx25uart_data5.xon_size = XON_SZ5;
        _ddr_mx25uart_data5.aux[0] = (TXTL_5 << 10) | (DCEDTE_5 << 6) | RXTL_5;
        _ddr_mx25uart_data5.aux[1] = (RTSTL_5 << 10);
        _ddr_mx25uart_data5.devhdr = (FP)_ddr_mx25uartdrv;
        if ((ercd = acre_flg((T_CFLG *)&_ddr_mx25uart_cflg5)) > E_OK) {
            _ddr_mx25uart_data5.flgid = (UH)ercd;
            if ((ercd = acre_isr((T_CISR *)&_ddr_mx25uart_cisr5)) < E_OK) {
                del_flg((ID)_ddr_mx25uart_data5.flgid);
            } else {
                _ddr_fs_mx25epit_perclk(15, 66500000);
                state = sns_loc();
                if (state == FALSE) {
                    loc_cpu();
                }
                REG_CCM.CGCR2 |= 0x00040000;
                if (state == FALSE) {
                    unl_cpu();
                }
                dis_int(INT_UART5);
                _ddr_mx25uart_data5.intno = INT_UART5;
                REG_UART5.UCR2 = 0;
                _ddr_mx25uart_data5.isrid = (UH)ercd;
                ercd = vdef_dev(devid, (VP)&_ddr_mx25uart_cdev5);
                ena_int(INT_UART5);
            }
        }
    } else
  #endif
        ercd = E_NOEXS;
    return ercd;
}

#if (defined(UART_1) || defined(UART_2) || defined(UART_3) || defined (UART_4) || defined (UART_5))

/***************************************
        UART受信終了確認処理
 ***************************************/

BOOL _ddr_mx25uart_check_chr(T_COM_RCV *ReceiveData, VB chr, UB sts)
{
    BOOL flag = FALSE;

    if ((sts & (T_COM_EROR|T_COM_ERP|T_COM_ERF|T_COM_BRK)) != 0)
        flag = TRUE;
    else if (ReceiveData->rcnt == 0)
        flag = TRUE;
    else if (ReceiveData->eos != 0)
    {
        if ((ReceiveData->eos->flg[0] != 0) && (ReceiveData->eos->chr[0] == chr))
            flag = TRUE;
        else if ((ReceiveData->eos->flg[1] != 0) && (ReceiveData->eos->chr[1] == chr))
            flag = TRUE;
        else if ((ReceiveData->eos->flg[2] != 0) && (ReceiveData->eos->chr[2] == chr))
            flag = TRUE;
        else if ((ReceiveData->eos->flg[3] != 0) && (ReceiveData->eos->chr[3] == chr))
            flag = TRUE;
    }
    return flag;
}

/*******************************************
        UART受信エラーステータス解析
 *******************************************/

UB _ddr_mx25uart_getssr(UB ssr)
{
    UB sts = 0;

    if ((ssr & URXD_PRERR) != 0)
        sts |= T_COM_ERP;
    if ((ssr & URXD_BRK) != 0)
        sts |= T_COM_BRK;
    if ((ssr & URXD_FRMERR) != 0)
        sts |= T_COM_ERF;
    if ((ssr & URXD_OVERRUN) != 0)
        sts |= T_COM_EROR;
    return sts;
}

/*******************************
        バッファコピー処理
 *******************************/

BOOL _ddr_mx25uart_copy(T_MX25UART_MNG *pk_UARTmng, T_COM_SND *TransmiteData)
{
    for(; TransmiteData->tcnt != 0; ) {
        if (pk_UARTmng->tcnt < pk_UARTmng->tsize) {
            pk_UARTmng->tbuf[pk_UARTmng->sndp++] = *TransmiteData->tbuf++;
            TransmiteData->tcnt--;
            if (pk_UARTmng->sndp >= pk_UARTmng->tsize) {
                pk_UARTmng->sndp = 0;
            }
            pk_UARTmng->tcnt++;
        } else {
            break;
        }
    }
    return (TransmiteData->tcnt == 0) ? TRUE : FALSE;
}

/***********************************************
        ロカール送信バッファからの送信処理
 ***********************************************/

void _ddr_mx25uart_send_local_buf(T_MX25UART_MNG *pk_UARTmng)
{
    for(; (pk_UARTmng->port->UTS & UTS_TXFULL) == 0; ) {
        pk_UARTmng->port->UTXD = *pk_UARTmng->SndData->tbuf++;
        if (--pk_UARTmng->SndData->tcnt == 0) {
            pk_UARTmng->SndData = 0;
            pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
            iset_flg((ID)pk_UARTmng->flgid, TXI_FLG);
            break;
        }
    }
}

/***********************************************
        内部送信バッファからの送信処理
 ***********************************************/

void _ddr_mx25uart_send_drv_buf(T_MX25UART_MNG *pk_UARTmng)
{
    UH sndp;

    sndp = pk_UARTmng->sndp - pk_UARTmng->tcnt;
    if (pk_UARTmng->tcnt > pk_UARTmng->sndp)
        sndp += pk_UARTmng->tsize;
    for(; (pk_UARTmng->port->UTS & UTS_TXFULL) == 0; ) {
        pk_UARTmng->port->UTXD = pk_UARTmng->tbuf[sndp];
        if (++sndp >= pk_UARTmng->tsize)
            sndp = 0;
        if (--pk_UARTmng->tcnt == 0)
            break;
    }
    if (pk_UARTmng->SndData != 0) {
        if (_ddr_mx25uart_copy(pk_UARTmng, pk_UARTmng->SndData) == TRUE) {
            pk_UARTmng->SndData = 0;
            iset_flg((ID)pk_UARTmng->flgid, TXI_FLG);
        }
    }
    if ((pk_UARTmng->tcnt == 0) && (pk_UARTmng->SndData == 0)) {
        pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
    }
}

/***********************************************
        UART送信データエンプティ割込み処理
 ***********************************************/

void _ddr_mx25uart_txi(T_MX25UART_MNG *pk_UARTmng)
{
    if ((pk_UARTmng->port->UTS & UTS_TXFULL) == 0) {
        if (pk_UARTmng->status.bit.req_xon_xoff == 1) {
            pk_UARTmng->port->UTXD = (pk_UARTmng->status.bit.rx_xoff == 0) ? XON : XOFF;
            pk_UARTmng->status.bit.req_xon_xoff = 0;
        }
        if (pk_UARTmng->status.bit.tx_xoff == 0) {
            if (pk_UARTmng->tsize == 0) {
                if (pk_UARTmng->SndData != 0) {
                    _ddr_mx25uart_send_local_buf(pk_UARTmng);
                } else {
                    pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
                    pk_UARTmng->port->UCR4 &= ~(UCR4_TCEN);
                }
            } else {
                if (pk_UARTmng->tcnt != 0) {
                    _ddr_mx25uart_send_drv_buf(pk_UARTmng);
                } else {
                    pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
                }
           }
        } else {
            pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
            pk_UARTmng->port->UCR4 &= ~(UCR4_TCEN);
        }
    }
}

/***********************************
        受信XOFFのチェック処理
 ***********************************/

void _ddr_mx25uart_chk_rxoff(T_MX25UART_MNG *pk_UARTmng)
{
    if ((pk_UARTmng->status.bit.rx_xoff == 0) &&
        (pk_UARTmng->rcnt >= pk_UARTmng->xoff_size)) {
        pk_UARTmng->status.bit.rx_xoff = 1;
        pk_UARTmng->status.bit.req_xon_xoff = 1;
        pk_UARTmng->port->UCR1 |= UCR1_TRDYEN|UCR1_TXMPTYEN;
        pk_UARTmng->port->UCR4 |= UCR4_TCEN;
        _ddr_mx25uart_txi(pk_UARTmng);
    }
}

/***********************************
        受信XONのチェック処理
 ***********************************/

void _ddr_mx25uart_chk_rxon(T_MX25UART_MNG *pk_UARTmng)
{
    if ((pk_UARTmng->status.bit.rx_xoff == 1) &&
        (pk_UARTmng->rcnt <= pk_UARTmng->xon_size)) {
        pk_UARTmng->status.bit.rx_xoff = 0;
        pk_UARTmng->status.bit.req_xon_xoff = 1;
        pk_UARTmng->port->UCR1 |= UCR1_TRDYEN|UCR1_TXMPTYEN;
        pk_UARTmng->port->UCR4 |= UCR4_TCEN;
        _ddr_mx25uart_txi(pk_UARTmng);
    }
}

/*******************************************
        UART受信データフル割込み処理
 *******************************************/

void _ddr_mx25uart_rxi(T_MX25UART_MNG *pk_UARTmng)
{
    UH rcvp;
    UH urxd;
    VB chr;
    UB sts;

    if ((pk_UARTmng->rcnt < pk_UARTmng->rsize) ||
        (pk_UARTmng->RcvData != 0)) {
        pk_UARTmng->port->USR1 = (USR1_PARITYERR|USR1_FRAMERR|USR1_AGTIM);
        pk_UARTmng->port->USR2 = (USR2_BRCD|USR2_ORE);
        for(; (pk_UARTmng->port->UTS & UTS_RXEMPTY) == 0; ) {
            urxd = pk_UARTmng->port->URXD;
            sts = _ddr_mx25uart_getssr(urxd >> 8);
            chr = urxd & 0xFF;
            if ((pk_UARTmng->status.bit.sft_flw == 1) && (chr == XON)) {
                pk_UARTmng->status.bit.tx_xoff = 0;
                pk_UARTmng->port->UCR1 |= UCR1_TRDYEN|UCR1_TXMPTYEN;
                pk_UARTmng->port->UCR4 |= UCR4_TCEN;
                _ddr_mx25uart_txi(pk_UARTmng);
            } else if ((pk_UARTmng->status.bit.sft_flw == 1) && (chr == XOFF)) {
                pk_UARTmng->status.bit.tx_xoff = 1;
                pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
            } else {
                if (pk_UARTmng->RcvData != 0) {
                    pk_UARTmng->RcvData->rcnt--;
                    *pk_UARTmng->RcvData->rbuf++ = chr;
                    if (pk_UARTmng->RcvData->sbuf != 0)
                        *pk_UARTmng->RcvData->sbuf++ = sts;
                    if (_ddr_mx25uart_check_chr(pk_UARTmng->RcvData, chr, sts) == TRUE) {
                        pk_UARTmng->RcvData = 0;
                        iset_flg((ID)pk_UARTmng->flgid, RXI_FLG);
                    }
                } else if (pk_UARTmng->rcnt < pk_UARTmng->rsize) {
                    rcvp = pk_UARTmng->rcvp + pk_UARTmng->rcnt;
                    if (rcvp >= pk_UARTmng->rsize)
                        rcvp -= pk_UARTmng->rsize;
                    pk_UARTmng->rbuf[rcvp] = chr;
                    if (pk_UARTmng->sbuf != 0)
                        pk_UARTmng->sbuf[rcvp] = sts;
                    if (pk_UARTmng->status.bit.sft_flw == 1)
                        _ddr_mx25uart_chk_rxoff(pk_UARTmng);
                    if (++pk_UARTmng->rcnt == pk_UARTmng->rsize) {
                        pk_UARTmng->port->UCR1 &= ~(UCR1_RRDYEN);
                        pk_UARTmng->port->UCR2 &= ~(UCR2_ATEN);
                        pk_UARTmng->port->UCR3 &= ~(UCR3_PARERREN|UCR3_FRAERREN);
                        pk_UARTmng->port->UCR4 &= ~(UCR4_BKEN|UCR4_OREN);
                        break;
                    }
                }
            }
        }
    } else {
        pk_UARTmng->port->UCR1 &= ~(UCR1_RRDYEN);
        pk_UARTmng->port->UCR2 &= ~(UCR2_ATEN);
        pk_UARTmng->port->UCR3 &= ~(UCR3_PARERREN|UCR3_FRAERREN);
        pk_UARTmng->port->UCR4 &= ~(UCR4_BKEN|UCR4_OREN);
    }
}

/*******************************
        送信FIFO充填処理
 *******************************/

void _ddr_mx25uart_send_char(T_MX25UART_MNG *pk_UARTmng, T_COM_SND *TransmiteData)
{
    if (pk_UARTmng->status.bit.req_xon_xoff == 1) {
        pk_UARTmng->port->UTXD = (pk_UARTmng->status.bit.rx_xoff == 0) ? XON : XOFF;
        pk_UARTmng->status.bit.req_xon_xoff = 0;
    }
    if (pk_UARTmng->status.bit.tx_xoff == 0) {
        for(; (pk_UARTmng->port->UTS & UTS_TXFULL) == 0; ) {
            pk_UARTmng->port->UTXD = *TransmiteData->tbuf++;
            if (--TransmiteData->tcnt == 0)
                break;
        }
    }
}

/***********************************************
        UART送信バッファエンプティ割込み処理
 ***********************************************/

void _ddr_mx25uart_tei(T_MX25UART_MNG *pk_UARTmng)
{
    if ((pk_UARTmng->tcnt == 0) &&
        ((pk_UARTmng->port->USR2 & USR2_TXDC) != 0)) {
        if (pk_UARTmng->wclnid != 0) {
            pk_UARTmng->wclnid = 0;
            iset_flg((ID)pk_UARTmng->flgid, TEI_FLG);
        }
        pk_UARTmng->port->UCR4 &= ~(UCR4_TCEN);
    }
}

/***********************************************
        UART割込み処理
 ***********************************************/

void _ddr_mx25uart_intr(T_MX25UART_MNG *pk_UARTmng)
{
    if  ((pk_UARTmng->port->UCR1 & UCR1_RRDYEN) != 0) {
        _ddr_mx25uart_rxi(pk_UARTmng);
    }
    if  ((pk_UARTmng->port->UCR1 & (UCR1_TRDYEN|UCR1_TXMPTYEN)) != 0) {
        _ddr_mx25uart_txi(pk_UARTmng);
    }
    if  ((pk_UARTmng->port->UCR4 & UCR4_TCEN) != 0) {
        _ddr_mx25uart_tei(pk_UARTmng);
    }
}

/*******************************
        文字列の取り出し処理
 *******************************/

BOOL _ddr_mx25uart_recv_strings(T_MX25UART_MNG *pk_UARTmng, T_COM_RCV *ReceiveData)
{
    BOOL flag;
    VB chr;
    UB sts;

    for (flag = FALSE; flag == FALSE; ) {
        if (ReceiveData->rcnt == 0) {
            flag = TRUE;
        } else if (pk_UARTmng->rcnt == 0) {
            break;
        } else {
            *ReceiveData->rbuf++ = chr = pk_UARTmng->rbuf[pk_UARTmng->rcvp];
            sts = pk_UARTmng->sbuf[pk_UARTmng->rcvp];
            if (ReceiveData->sbuf != 0) {
                *ReceiveData->sbuf++ = sts;
            }
            if (++pk_UARTmng->rcvp >= pk_UARTmng->rsize) {
                pk_UARTmng->rcvp = 0;
            }
            pk_UARTmng->rcnt--;
            ReceiveData->rcnt--;
            if (pk_UARTmng->status.bit.sft_flw == 1) {
                _ddr_mx25uart_chk_rxon(pk_UARTmng);
            }
            flag = _ddr_mx25uart_check_chr(ReceiveData, chr, sts);
        }
    }
    return flag;
}

/*******************************
        UART送信処理
 *******************************/

ER _ddr_mx25uart_snd(T_COM_SND *TransmiteData, T_MX25UART_MNG *pk_UARTmng)
{
    FLGPTN flgptn;
    ID tskid;
    ER ercd = E_OK;

    if ((pk_UARTmng->status.bit.init_flg == 0) || (sns_dpn() == TRUE)) {
        ercd = E_OBJ;
    } else {
        get_tid(&tskid);
        dis_dsp();
        if (((pk_UARTmng->tlockid == 0) || (pk_UARTmng->tlockid == (UH)tskid)) &&
            (pk_UARTmng->status.bit.ena_tx == 1) &&
            (pk_UARTmng->SndData == 0)) {
            dis_int(pk_UARTmng->intno);
            pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
            pk_UARTmng->port->UCR4 &= ~(UCR4_TCEN);
            if ((pk_UARTmng->tcnt == 0) && ((pk_UARTmng->port->UTS & 0x0010) == 0)) {
                _ddr_mx25uart_send_char(pk_UARTmng, TransmiteData);
            }
            ena_int(pk_UARTmng->intno);
            if (_ddr_mx25uart_copy(pk_UARTmng, TransmiteData) == FALSE) {
                pk_UARTmng->SndData = TransmiteData;
                ena_dsp();
                dis_int(pk_UARTmng->intno);
                pk_UARTmng->port->UCR1 |= UCR1_TRDYEN|UCR1_TXMPTYEN;
                pk_UARTmng->port->UCR4 |= UCR4_TCEN;
                ena_int(pk_UARTmng->intno);
                if ((ercd = twai_flg((ID)pk_UARTmng->flgid, TXI_FLG, TWF_ORW, &flgptn, TransmiteData->time)) != E_OK) {
                    dis_int(pk_UARTmng->intno);
                    pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
                    pk_UARTmng->port->UCR4 &= ~(UCR4_TCEN);
                    ena_int(pk_UARTmng->intno);
                    pk_UARTmng->SndData = 0;
                    ercd = pol_flg((ID)pk_UARTmng->flgid, TXI_FLG, TWF_ORW, &flgptn);
                }
                clr_flg((ID)pk_UARTmng->flgid, ~TXI_FLG);
            } else {
                ena_dsp();
                if (pk_UARTmng->tcnt != 0) {
                    dis_int(pk_UARTmng->intno);
                    pk_UARTmng->port->UCR1 |= UCR1_TRDYEN|UCR1_TXMPTYEN;
                    pk_UARTmng->port->UCR4 |= UCR4_TCEN;
                    ena_int(pk_UARTmng->intno);
                }
            }
        } else {
            ena_dsp();
            ercd = E_OBJ;
        }
    }
    return ercd;
}

/*******************************
        UART受信処理
 *******************************/

ER _ddr_mx25uart_rcv(T_COM_RCV *ReceiveData, T_MX25UART_MNG *pk_UARTmng)
{
    FLGPTN flgptn;
    ID tskid;
    ER ercd = E_OK;

    if ((pk_UARTmng->status.bit.init_flg == 0) || (sns_dpn() == TRUE) ||
        (pk_UARTmng->status.bit.ena_rx   == 0)) {
        ercd = E_OBJ;
    } else {
        get_tid(&tskid);
        dis_dsp();
        if (((pk_UARTmng->rlockid == 0) || (pk_UARTmng->rlockid == (UH)tskid)) &&
            (pk_UARTmng->RcvData        == 0)) {
            dis_int(pk_UARTmng->intno);
            pk_UARTmng->port->UCR1 &= ~(UCR1_RRDYEN);
            pk_UARTmng->port->UCR2 &= ~(UCR2_ATEN);
            pk_UARTmng->port->UCR3 &= ~(UCR3_PARERREN|UCR3_FRAERREN);
            pk_UARTmng->port->UCR4 &= ~(UCR4_BKEN|UCR4_OREN);
            ena_int(pk_UARTmng->intno);
            if (_ddr_mx25uart_recv_strings(pk_UARTmng, ReceiveData) == FALSE) {
                pk_UARTmng->RcvData = ReceiveData;
                ena_dsp();
                dis_int(pk_UARTmng->intno);
                pk_UARTmng->port->UCR1 |= (UCR1_RRDYEN);
                pk_UARTmng->port->UCR2 |= (UCR2_ATEN);
                pk_UARTmng->port->UCR3 |= (UCR3_PARERREN|UCR3_FRAERREN);
                pk_UARTmng->port->UCR4 |= (UCR4_BKEN|UCR4_OREN);
                ena_int(pk_UARTmng->intno);
                if ((ercd = twai_flg((ID)pk_UARTmng->flgid, RXI_FLG, TWF_ORW, &flgptn, ReceiveData->time)) != E_OK) {
                    pk_UARTmng->RcvData = 0;
                    ercd = pol_flg((ID)pk_UARTmng->flgid, RXI_FLG, TWF_ORW, &flgptn);
                }
                clr_flg((ID)pk_UARTmng->flgid, ~RXI_FLG);
            } else {
                ena_dsp();
                dis_int(pk_UARTmng->intno);
                pk_UARTmng->port->UCR1 |= (UCR1_RRDYEN);
                pk_UARTmng->port->UCR2 |= (UCR2_ATEN);
                pk_UARTmng->port->UCR3 |= (UCR3_PARERREN|UCR3_FRAERREN);
                pk_UARTmng->port->UCR4 |= (UCR4_BKEN|UCR4_OREN);
                ena_int(pk_UARTmng->intno);
            }
        } else {
            ena_dsp();
            ercd = E_OBJ;
        }
    }
    return ercd;
}

/***********************************
        送信バッファの送出処理
 ***********************************/

ER _ddr_mx25uart_cln_tx_buf(T_MX25UART_MNG *pk_UARTmng, TMO time)
{
    FLGPTN flgptn;
    ID tskid;
    ER ercd;

    get_tid(&tskid);
    if (((pk_UARTmng->tlockid == 0) ||
         (pk_UARTmng->tlockid == (UH)tskid)) &&
        ( pk_UARTmng->SndData == 0)) {
        dis_int(pk_UARTmng->intno);
        if ((pk_UARTmng->tcnt != 0) ||
            ((pk_UARTmng->port->USR2 & USR2_TXDC) == 0)) {
            pk_UARTmng->port->UCR1 |= UCR1_TRDYEN|UCR1_TXMPTYEN;
            pk_UARTmng->port->UCR4 |= UCR4_TCEN;
            pk_UARTmng->wclnid = tskid;
            ena_int(pk_UARTmng->intno);
            if ((ercd = twai_flg((ID)pk_UARTmng->flgid, TEI_FLG, TWF_ORW, &flgptn, time)) != E_OK) {
                pk_UARTmng->wclnid = 0;
                ercd = pol_flg((ID)pk_UARTmng->flgid, TEI_FLG, TWF_ORW, &flgptn);
            }
            clr_flg((ID)pk_UARTmng->flgid, ~TEI_FLG);
        } else {
            ena_int(pk_UARTmng->intno);
            ercd = E_OK;
        }
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***************************************
        送信バッファのリセット処理
 ***************************************/

ER _ddr_mx25uart_rst_tx_buf(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (((pk_UARTmng->tlockid == 0) ||
         (pk_UARTmng->tlockid == (UH)tskid)) &&
        ( pk_UARTmng->SndData == 0)) {
        pk_UARTmng->tcnt = 0;
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***************************************
        受信バッファのリセット処理
 ***************************************/

ER _ddr_mx25uart_rst_rx_buf(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (((pk_UARTmng->rlockid == 0) ||
         (pk_UARTmng->rlockid == (UH)tskid)) &&
        ( pk_UARTmng->RcvData == 0)) {
        pk_UARTmng->rcnt = 0;
        ercd = E_OK;
    } else
        ercd = E_OBJ;
    return ercd;
}

/*******************************
        送信の禁止処理
 *******************************/

ER _ddr_mx25uart_dis_send(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (((pk_UARTmng->tlockid == 0) ||
         (pk_UARTmng->tlockid == (UH)tskid)) &&
        ( pk_UARTmng->SndData == 0) &&
        ( pk_UARTmng->tcnt    == 0) &&
        ((pk_UARTmng->port->UTS & UTS_TXEMPTY) == 0)) {
        dis_int(pk_UARTmng->intno);
        pk_UARTmng->port->UCR1 &= ~(UCR1_TRDYEN|UCR1_TXMPTYEN);
        pk_UARTmng->port->UCR2 &= ~(UCR2_TXEN|UCR2_CTS);
        pk_UARTmng->port->UCR4 &= ~(UCR4_TCEN);
        pk_UARTmng->status.bit.ena_tx = 0;
        ena_int(pk_UARTmng->intno);
        ercd = E_OK;
    } else
        ercd = E_OBJ;
    return ercd;
}

/*******************************
        受信の禁止処理
 *******************************/

ER _ddr_mx25uart_dis_rcv(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (((pk_UARTmng->rlockid == 0) ||
         (pk_UARTmng->rlockid == (UH)tskid)) &&
        ( pk_UARTmng->RcvData == 0) &&
        ( pk_UARTmng->rcnt    == 0) &&
        ((pk_UARTmng->port->UTS & UTS_RXEMPTY) == 0)) {
        dis_int(pk_UARTmng->intno);
        pk_UARTmng->port->UCR1 &= ~(UCR1_RRDYEN);
        pk_UARTmng->port->UCR2 &= ~(UCR2_ATEN|UCR2_RXEN);
        pk_UARTmng->port->UCR3 &= ~(UCR3_PARERREN|UCR3_FRAERREN);
        pk_UARTmng->port->UCR4 &= ~(UCR4_BKEN|UCR4_OREN);
        pk_UARTmng->status.bit.ena_rx = 0;
        ena_int(pk_UARTmng->intno);
        ercd = E_OK;
    } else
        ercd = E_OBJ;
    return ercd;
}

/*******************************
        送信の許可処理
 *******************************/

ER _ddr_mx25uart_ena_send(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if ((pk_UARTmng->rlockid == 0) ||
        (pk_UARTmng->rlockid == (UH)tskid)) {
        dis_int(pk_UARTmng->intno);
        pk_UARTmng->status.bit.ena_tx = 1;
        pk_UARTmng->port->UCR2 |= (UCR2_TXEN|UCR2_CTS);
        ena_int(pk_UARTmng->intno);
        ercd = E_OK;
    } else
        ercd = E_OBJ;
    return ercd;
}

/*******************************
        受信の許可処理
 *******************************/

ER _ddr_mx25uart_ena_rcv(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if ((pk_UARTmng->rlockid == 0) ||
        (pk_UARTmng->rlockid == (UH)tskid)) {
        dis_int(pk_UARTmng->intno);
        pk_UARTmng->status.bit.ena_rx = 1;
        pk_UARTmng->port->UCR1 |= (UCR1_RRDYEN);
        pk_UARTmng->port->UCR2 |= (UCR2_ATEN|UCR2_RXEN);
        pk_UARTmng->port->UCR3 |= (UCR3_PARERREN|UCR3_FRAERREN);
        pk_UARTmng->port->UCR4 |= (UCR4_BKEN|UCR4_OREN);
        ena_int(pk_UARTmng->intno);
        ercd = E_OK;
    } else
        ercd = E_OBJ;
    return ercd;
}

/*******************************
        ブレークの送出処理
 *******************************/

ER _ddr_mx25uart_snd_brk(T_MX25UART_MNG *pk_UARTmng, TMO time)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (((pk_UARTmng->tlockid == 0) ||
         (pk_UARTmng->tlockid == (UH)tskid)) &&
        ( pk_UARTmng->SndData == 0) &&
        ( pk_UARTmng->tcnt    == 0)) {
        if ((pk_UARTmng->port->UTS & UTS_TXEMPTY) != 0) {
            dis_int(pk_UARTmng->intno);
            pk_UARTmng->port->UCR1 |= (UCR1_SNDBRK);
            ena_int(pk_UARTmng->intno);
            dly_tsk(time);
            dis_int(pk_UARTmng->intno);
            pk_UARTmng->port->UCR1 &= ~(UCR1_SNDBRK);
            ena_int(pk_UARTmng->intno);
            ercd = E_OK;
        } else {
            ercd = E_OBJ;
        }
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***********************************
        送信チャネルのロック処理
 ***********************************/

ER _ddr_mx25uart_lock_trans(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    dis_int(pk_UARTmng->intno);
    if ((pk_UARTmng->tlockid == 0) ||
        (pk_UARTmng->SndData == 0)) {
        pk_UARTmng->tlockid = (UH)tskid;
        ercd = E_OK;
    } else if (pk_UARTmng->tlockid == (UH)tskid) {
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    ena_int(pk_UARTmng->intno);
    return ercd;
}

/***********************************
        受信チャネルのロック処理
 ***********************************/

ER _ddr_mx25uart_lock_recv(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    dis_int(pk_UARTmng->intno);
    if ((pk_UARTmng->rlockid == 0) ||
        (pk_UARTmng->RcvData == 0)) {
        pk_UARTmng->rlockid = (UH)tskid;
        ercd = E_OK;
    } else if (pk_UARTmng->rlockid == (UH)tskid) {
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    ena_int(pk_UARTmng->intno);
    return ercd;
}

/***************************************
        送信チャネルのロック解除処理
 ***************************************/

ER _ddr_mx25uart_unlock_trans(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (pk_UARTmng->tlockid == (UH)tskid) {
        pk_UARTmng->tlockid = 0;
        ercd = E_OK;
    } else if (pk_UARTmng->tlockid == 0) {
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***************************************
        受信チャネルのロック解除処理
 ***************************************/

ER _ddr_mx25uart_unlock_recv(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;
    ID tskid;

    get_tid(&tskid);
    if (pk_UARTmng->rlockid == (UH)tskid) {
        pk_UARTmng->rlockid = 0;
        ercd = E_OK;
    } else if (pk_UARTmng->rlockid == 0) {
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***********************************
        アサートRTS処理
 ***********************************/

ER _ddr_mx25uart_asert_rts(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;

    if (pk_UARTmng->status.bit.hrd_flw == 0) {
        dis_int(pk_UARTmng->intno);
        pk_UARTmng->port->UCR2 |= (UCR2_CTS);
        ena_int(pk_UARTmng->intno);
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***********************************
        ネゲートRTS処理
 ***********************************/

ER _ddr_mx25uart_negate_rts(T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;

    if (pk_UARTmng->status.bit.hrd_flw == 0) {
        dis_int(pk_UARTmng->intno);
        pk_UARTmng->port->UCR2 &= ~(UCR2_CTS);
        ena_int(pk_UARTmng->intno);
        ercd = E_OK;
    } else {
        ercd = E_OBJ;
    }
    return ercd;
}

/***********************************
        アサートDTR処理
 ***********************************/

ER _ddr_mx25uart_asert_dtr(T_MX25UART_MNG *pk_UARTmng)
{
    dis_int(pk_UARTmng->intno);
    pk_UARTmng->port->UCR3 |= (UCR3_DSR);
    ena_int(pk_UARTmng->intno);

    return E_OK;
}

/***********************************
        ネゲートDTR処理
 ***********************************/

ER _ddr_mx25uart_negate_dtr(T_MX25UART_MNG *pk_UARTmng)
{
    dis_int(pk_UARTmng->intno);
    pk_UARTmng->port->UCR3 &= ~(UCR3_DSR);
    ena_int(pk_UARTmng->intno);

    return E_OK;
}

/*******************************
        UART制御信号処理
 *******************************/

ER _ddr_mx25uart_ctr(T_COM_CTR const *pk_SerialData, T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd = E_OK;

    if (pk_UARTmng->status.bit.init_flg == 0)
        ercd = E_OBJ;

    if (ercd == E_OK)
        if ((pk_SerialData->command & CLN_TXBUF) == CLN_TXBUF)
            ercd = _ddr_mx25uart_cln_tx_buf(pk_UARTmng, pk_SerialData->time);

    if (ercd == E_OK)
        if ((pk_SerialData->command & RST_TXBUF) == RST_TXBUF)
            ercd = _ddr_mx25uart_rst_tx_buf(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & RST_RXBUF) == RST_RXBUF)
            ercd = _ddr_mx25uart_rst_rx_buf(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & STP_TX) == STP_TX)
            ercd = _ddr_mx25uart_dis_send(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & STP_RX) == STP_RX)
            ercd = _ddr_mx25uart_dis_rcv(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & STA_TX) == STA_TX)
            ercd = _ddr_mx25uart_ena_send(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & STA_RX) == STA_RX)
            ercd = _ddr_mx25uart_ena_rcv(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & SND_BRK) == SND_BRK)
            ercd = _ddr_mx25uart_snd_brk(pk_UARTmng, pk_SerialData->time);

    if (ercd == E_OK)
        if ((pk_SerialData->command & LOC_TX) == LOC_TX)
            ercd = _ddr_mx25uart_lock_trans(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & LOC_RX) == LOC_RX)
            ercd = _ddr_mx25uart_lock_recv(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & UNL_TX) == UNL_TX)
            ercd = _ddr_mx25uart_unlock_trans(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & UNL_RX) == UNL_RX)
            ercd = _ddr_mx25uart_unlock_recv(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & ASR_RTS) == ASR_RTS)
            ercd = _ddr_mx25uart_asert_rts(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & NGT_RTS) == NGT_RTS)
            ercd = _ddr_mx25uart_negate_rts(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & ASR_DTR) != 0)
            ercd = _ddr_mx25uart_asert_dtr(pk_UARTmng);

    if (ercd == E_OK)
        if ((pk_SerialData->command & NGT_DTR) != 0)
            ercd = _ddr_mx25uart_negate_dtr(pk_UARTmng);

    return ercd;
}

/*******************************
        UART状態参照処理
 *******************************/

ER _ddr_mx25uart_ref(T_COM_REF *pk_SerialRef, T_MX25UART_MNG *pk_UARTmng)
{
    UH status = 0;

    if (pk_UARTmng->status.bit.init_flg == 1) {
        dis_int(pk_UARTmng->intno);
        pk_SerialRef->rxcnt = pk_UARTmng->rcnt;
        pk_SerialRef->txcnt = pk_UARTmng->tcnt;
        ena_int(pk_UARTmng->intno);

        status |= T_COM_INIT;
        if ((pk_UARTmng->port->USR2 & USR2_DCDIN) == 0)
            status |= T_COM_CD;
        if ((pk_UARTmng->port->USR2 & USR2_RIIN) == 0)
            status |= T_COM_RI;
        if ((pk_UARTmng->port->USR1 & USR1_RTSS) != 0)
            status |= T_COM_CTS;
        if ((pk_UARTmng->port->UCR3 & UCR3_DSR) == 0)
            status |= T_COM_DTR;
        if ((pk_UARTmng->port->UCR2 & UCR2_CTSC) == 0) {
            if ((pk_UARTmng->port->UCR2 & UCR2_CTS) != 0)
                status |= T_COM_RTS;
        }
        if (pk_UARTmng->status.bit.ena_tx == 1)
            status |= T_COM_ENATX;
        if (pk_UARTmng->status.bit.ena_rx == 1)
            status |= T_COM_ENARX;
        if (pk_UARTmng->status.bit.rx_xoff == 1)
            status |= T_COM_RXOFF;
        if (pk_UARTmng->status.bit.tx_xoff == 1)
            status |= T_COM_TXOFF;
    }
    pk_SerialRef->status = status;
    return E_OK;
}

/*******************************
        UART初期化処理
 *******************************/

ER _ddr_mx25uart_ini(T_COM_SMOD const *pk_SerialMode, T_MX25UART_MNG *pk_UARTmng)
{
    INT i;
    UW ubir;
    UW clksrc;
    ER ercd = E_OK;
    T_MX25UART_MSTS status;

    pk_UARTmng->port->UCR2 = 0;
    for (;;) {
        if ((pk_UARTmng->port->UTS & UTS_SOFTRST) == 0) {
            break;
        } else if (sns_dpn() == TRUE) {
            for(i=0; i<10000;i++);
        } else {
            dly_tsk(1);
        }
    }

    clksrc = _ddr_fs_mx25epit_perclk(15, 66500000);
    if ((clksrc % 6) == 0) {
        clksrc /= 6;
        pk_UARTmng->port->UFCR = pk_UARTmng->aux[0];
    } else if ((clksrc % 7) == 0) {
        clksrc /= 7;
        pk_UARTmng->port->UFCR = pk_UARTmng->aux[0] | 0x00000300;
    } else {
        clksrc /= 5;
        pk_UARTmng->port->UFCR = pk_UARTmng->aux[0] | 0x00000080;
    }
    pk_UARTmng->port->UCR4 = pk_UARTmng->aux[1];

    status.word = 0;

    switch(pk_SerialMode->blen) {
        case BLEN7:
            break;
        case BLEN8:
            pk_UARTmng->port->UCR2 = UCR2_WS;
            break;
        default:
            ercd = E_PAR;
            break;
    }

    switch(pk_SerialMode->par) {
        case PAR_ODD:
            pk_UARTmng->port->UCR2 |= (UCR2_PREN|UCR2_PROE);
            break;
        case PAR_EVEN:
            pk_UARTmng->port->UCR2 |= (UCR2_PREN);
            break;
        default:
            break;
    }

    switch(pk_SerialMode->sbit) {
        case SBIT2:
            pk_UARTmng->port->UCR2 |= (UCR2_STPB);
            break;
        case SBIT1:
            break;
        default:
            ercd = E_PAR;
            break;
    }

    switch(pk_SerialMode->flow) {
        case FLW_HARD:
            pk_UARTmng->port->UCR2 |= (UCR2_CTSC);
            status.bit.hrd_flw = 1;
            break;
        case FLW_XON:
            pk_UARTmng->port->UCR2 |= (UCR2_IRTS);
            status.bit.sft_flw = 1;
            break;
        case FLW_NONE:
            pk_UARTmng->port->UCR2 |= (UCR2_IRTS);
            break;
        default:
            ercd = E_PAR;
            break;
    }

    if ((pk_SerialMode->baud % 200) == 0) {
        ubir = (pk_SerialMode->baud/200)*16;
        if (ubir == 0) {
            ercd = E_PAR;
        }
    } else {
        ubir = 0;
        ercd = E_PAR;
    }

    if ((ubir < 0x10) || (ubir > 0x80000) || ((clksrc/200) > 0x80000)) {
        ercd = E_PAR;
    } else if ((ubir < 0x80) || (ubir > 0x40000) || ((clksrc/200) > 0x40000)) {
        ubir >>= 3;
        clksrc >>= 3;
    } else if ((ubir < 0x4) || (ubir > 0x20000) || ((clksrc/200) > 0x20000)) {
        ubir >>= 2;
        clksrc >>= 2;
    } else if ((ubir < 0x2) || (ubir > 0x10000) || ((clksrc/200) > 0x10000)) {
        ubir >>= 1;
        clksrc >>= 1;
    }
    if (ercd == E_OK) {
        status.bit.init_flg = 1;
        pk_UARTmng->status.word = status.word;
        pk_UARTmng->port->UBIR = ubir-1;
        pk_UARTmng->port->UBMR = (clksrc/200)-1;
        pk_UARTmng->port->UCR3 = 0x00000704;
        if (sns_dpn() == TRUE) {
            for(i=0; i<10000;i++);
        } else {
            dly_tsk(1);
        }
        pk_UARTmng->port->UCR1 |= (UCR1_UARTEN);
    }
    return ercd;
}

/*******************************
        UARTドライバメイン
 *******************************/

ER _ddr_mx25uartdrv(ID FuncID, VP pk_ControlData, T_MX25UART_MNG *pk_UARTmng)
{
    ER ercd;

    switch(FuncID) {
        case TA_COM_INI:
            ercd = _ddr_mx25uart_ini((T_COM_SMOD const *)pk_ControlData, pk_UARTmng);
            break;
        case TA_COM_REF:
            ercd = _ddr_mx25uart_ref((T_COM_REF *)pk_ControlData, pk_UARTmng);
            break;
        case TA_COM_CTR:
            ercd = _ddr_mx25uart_ctr((T_COM_CTR const *)pk_ControlData, pk_UARTmng);
            break;
        case TA_COM_PUTS:
            ercd = _ddr_mx25uart_snd((T_COM_SND *)pk_ControlData, pk_UARTmng);
            break;
        case TA_COM_GETS:
            ercd = _ddr_mx25uart_rcv((T_COM_RCV *)pk_ControlData, pk_UARTmng);
            break;
        default:
            ercd = E_NOSPT;
            break;
    }
    return ercd;
}
#endif
