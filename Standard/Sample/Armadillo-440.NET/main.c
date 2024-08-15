/**
 * @brief   Sample program for Armadillo-440 Platform (CPU: i.MX257)
 * @date    2015.08.18
 * @author  Copyright (c) 2010-2015, eForce Co.,Ltd.  All rights reserved.
 *
 * @par     History
 *          - rev 1.1 (2015.08.18) i-cho
 *            Initial version.
 */

#include <string.h>
#include "kernel.h"
#include "imx25.h"
#include "DDR_COM.h"
//#include "DDR_FS_MX25ETH.h"
#include "net_hdr.h"
#include "net_strlib.h"

/* チック時間の定義（ミリ秒単位） */

#ifndef TICK
#define TICK    1
#endif

ID MainTaskID;
#define ID_UART2 1

T_COM_SMOD const uart_ini = {115200, BLEN8, PAR_NONE, SBIT1, FLW_NONE};
VB const * const demo_str = "\n\r\teForce Operating System Sample Program V1.0\n\r\t\tSerial Port (UART2)\r\n";

/******************************************************************
        システム用メモリを確保
 ******************************************************************/

#ifdef __ICCARM__
#pragma section = "SYSMEM"
int SYSMEM[0x10000/sizeof(int)] @ "SYSMEM";
#endif

#ifdef __CC_ARM
int SYSMEM[0x10000/sizeof(int)] __attribute__ ((section ("SYSMEM"), zero_init));
#endif


/******************************************************************
        スタック用メモリとプール用のメモリを確保
 ******************************************************************/

#ifdef __ICCARM__
#pragma section = "STKMEM"
int STKMEM[0x100000/sizeof(int)] @ "STKMEM";
#pragma section = "MPLMEM"
int MPLMEM[0x100000/sizeof(int)] @ "MPLMEM";
#endif

#ifdef __CC_ARM
int STKMEM[0x100000/sizeof(int)] __attribute__ ((section ("STKMEM"), zero_init));
int MPLMEM[0x100000/sizeof(int)] __attribute__ ((section ("MPLMEM"), zero_init));
#endif


/******************************************************************
        ヒープ不使用を宣言
 ******************************************************************/

#ifdef __CC_ARM
#pragma import(__use_no_heap)
#endif


/******************************************************************
        異常割り込み処理
            割込みハンドラの定義も割込みサービスルーチンの生成も
            されていないのに割込みを受け付けた場合に到達
 ******************************************************************/

void int_abort(void)
{
    for(;;);
}

void puts_com_opt(VB *msg)
{
    UINT txcnt;

    txcnt = net_strlen(msg);
    puts_com(ID_UART2, msg, &txcnt, TMO_FEVR);
}

/*******************************
  callback routine for ethernet
 *******************************/
#define put_str(x)  puts_com_opt(x)
const VB apl_msg_cbk_eth[] = "\r\n-- Callback of ethernet --\r\n\r\n";

void apl_eth_cbk(UH dev_num, UH evt, VP sts)
{
    UW sts_lnk;
    
    /* Callback function of ethernet driver */
    /* イーサネットドライバのコールバック関数 */
    /* gNET_DEV.usr_cbk(net_cfg.c)で本関数を登録 */

    /* 下記はデバッグ用のメッセージ表示 */
    /* リリース時はコールバック関数の中で時間のかかる処理を実装しない */
    if (evt == EV_CBK_DEV_LINK) {
        sts_lnk = (UW)sts;
        if (sts_lnk == PHY_STS_LINK_DOWN) {
            loc_cpu();
            REG_GPIO3.DR |= 0x00010000;  /* LINK-LED inactive */
            unl_cpu();
        } else {
            loc_cpu();
            REG_GPIO3.DR &= ~0x00010000; /* LINK-LED active */
            unl_cpu();
        }
    }
    
    return;
}


/***********************************
  　    Initializing hardware
 ***********************************/

void hw_init(void)
{
    /* FEC Alternete mode & PAD setting */
  #if 0  /* this mode is default */
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_MDC    = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_MDIO   = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_TDATA0 = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_TDATA1 = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_TX_EN  = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_RDATA0 = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_RDATA1 = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_RX_DV  = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_FEC_TX_CLK = 0;
  #endif
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_MDC    = 0x0060;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_MDIO   = 0x0170;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_TDATA0 = 0x0061;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_TDATA1 = 0x0061;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_TX_EN  = 0x0061;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_RDATA0 = 0x0040;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_RDATA1 = 0x0040;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_RX_DV  = 0x0040;
    REG_IOMUXC.SW_PAD_CTL_PAD_FEC_TX_CLK = 0x01e0;

    /* RXD2/TXD2/CTS2/RTS2/DTR2/DSR2/DCD2/RI2 Alternete mode */
    REG_IOMUXC.SW_MUX_CTL_PAD_UART2_RXD = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_UART2_TXD = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_UART2_RTS = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_UART2_CTS = 0;
    REG_IOMUXC.SW_MUX_CTL_PAD_UART1_RXD = 3;    /* UART2 DTR */
    REG_IOMUXC.SW_MUX_CTL_PAD_UART1_TXD = 3;    /* UART2 DSR */
    REG_IOMUXC.SW_MUX_CTL_PAD_UART1_RTS = 3;    /* UART2 DCD */
    REG_IOMUXC.SW_MUX_CTL_PAD_UART1_CTS = 3;    /* UART2 RI */
    REG_IOMUXC.SW_PAD_CTL_PAD_UART2_RTS = 0x000000E0;
    REG_IOMUXC.SW_PAD_CTL_PAD_UART2_CTS = 0x00000060;
    REG_IOMUXC.SW_PAD_CTL_PAD_UART1_RXD = 0x00000020;
    REG_IOMUXC.SW_PAD_CTL_PAD_UART1_TXD = 0x000000A0;
    REG_IOMUXC.SW_PAD_CTL_PAD_UART1_CTS = 0x000000E0;
    REG_IOMUXC.SW_MUX_CTL_PAD_BOOT_MODE1 = 5;
    REG_GPIO4.DR |= 0x80000000;
    REG_GPIO4.GDIR |= 0x80000000;

    REG_IOMUXC.SW_MUX_CTL_PAD_UPLL_BYPCLK = 5;  /* GPIO3_16(LINKLED) */
    REG_IOMUXC.SW_MUX_CTL_PAD_VSTBY_ACK   = 5;  /* GPIO3_18(PHY_RST) */
    REG_IOMUXC.SW_MUX_CTL_PAD_NFALE = 5;    /* GPIO3_28 */
    REG_IOMUXC.SW_MUX_CTL_PAD_NFCLE = 5;    /* GPIO3_29 */

    REG_GPIO3.DR &= ~0x30050000;
    REG_GPIO3.DR |= 0x20050000;
    REG_GPIO3.GDIR |= 0x30050000;
}


/*******************************
  　    Main Task
 *******************************/
extern INT cgi_val;
extern ER net_setup(void);
extern ER net_sta_console(void);
void MainTask(VP_INT exinf)
{
    ER ercd = E_OK;

    /* Initialize Console */
    ini_com(ID_UART2, &uart_ini);
    ctr_com(ID_UART2, STA_COM, 0);

    ctr_com(ID_UART2, SND_BRK, 100);
    puts_com_opt((VB *)demo_str);
    
    /* Initialize Network */
    ercd = net_setup();
    if (ercd != E_OK) {
        return;
    }
    cgi_val = 1;

    /* Initialize Console */
    net_sta_console();
    
    for(;;) {
        loc_cpu();
        REG_GPIO3.DR ^= 0x30000000;
        unl_cpu();

        dly_tsk(cgi_val * 100);

        loc_cpu();
        REG_GPIO3.DR ^= 0x30000000;
        unl_cpu();

        dly_tsk(cgi_val * 100);
    }
}

T_CTSK const ctsk_main = {TA_HLNG|TA_ACT, (VP_INT)0, (FP)MainTask, 3, 0x400, 0, "MainTask"};


/*******************************
  　    OSの初期化ルーチン
 *******************************/

extern void _ddr_fs_mx25epit_init(UINT);
extern ER _ddr_mx25uart_init(ID, volatile struct t_uart *);

void initpr(void)
{
    _ddr_fs_mx25epit_init(TICK);
    _ddr_mx25uart_init(ID_UART2, &REG_UART2);
    MainTaskID = acre_tsk((T_CTSK *)&ctsk_main);
}


/*******************************
  　    初期化ルーチン
 *******************************/
ER ercd;
extern void _ddr_fs_mx25asic_init(void);

int main(void)
{
    T_CSYS csys;

    /* ダミーアクセス */

    SYSMEM[0] = 0;
    STKMEM[0] = 0;
    MPLMEM[0] = 0;

    /* ハードウェアの初期化の残り */
    hw_init();
    _ddr_fs_mx25asic_init();

    /* システムの生成と起動 */

    csys.tskpri_max = 8;
    csys.tskid_max  = 10;
    csys.semid_max  = 10;
    csys.flgid_max  = 10;
    csys.dtqid_max  = 8;
    csys.mbxid_max  = 10;
    csys.mtxid_max  = 8;
    csys.mbfid_max  = 8;
    csys.porid_max  = 8;
    csys.mpfid_max  = 8;
    csys.mplid_max  = 8;
    csys.almid_max  = 8;
    csys.cycid_max  = 8;
    csys.isrid_max  = 10;
    csys.devid_max  = 8;
    csys.tick       = TICK;
    csys.ssb_num    = 10;
    csys.sysmem_top = (VP)&SYSMEM[0];
    csys.sysmem_end = (VP)((ADDR)&SYSMEM[0]+sizeof(SYSMEM));
    csys.stkmem_top = (VP)&STKMEM[0];
    csys.stkmem_end = (VP)((ADDR)&STKMEM[0]+sizeof(STKMEM));
    csys.mplmem_top = (VP)&MPLMEM[0];
    csys.mplmem_end = (VP)((ADDR)&MPLMEM[0]+sizeof(MPLMEM));
    csys.sysidl = SYSTEM_IDLE;
    csys.inistk = STACK_ID_INIT;
    csys.trace = TRACE_DISABLE;
    csys.agent = AGENT_DISABLE;
    
    ercd = start_uC3(&csys, initpr);
    
    return ercd ;
}
