/***********************************************************************
  　sample program for Armadillo-440 Platform (CPU: i.MX257)

  　 Copyright (c)  2010, eForce Co., Ltd.  All rights reserved.

 ***********************************************************************/

#include <string.h>
#include "kernel.h"
#include "imx25.h"
#include "DDR_COM.h"

/* チック時間の定義（ミリ秒単位） */

#ifndef TICK
#define TICK    1
#endif

typedef struct t_msgblk {
    T_MSG   header;
    UINT    cnt;
    VB      buf[120];
} T_MSGBLK;

ID MainTaskID;
ID SubTaskID;
ID SndTaskID;
ID RcvTaskID;
ID ComTaskID;
ID MpfID;
ID MbxID;
#define ID_UART2 1

T_COM_SMOD const uart_ini = {115200, BLEN8, PAR_NONE, SBIT1, FLW_XON};
T_CMPF const cmpf = {TA_TFIFO, 20, sizeof(T_MSGBLK), 0, "Mpf"};
T_CMBX const cmbx = {TA_TFIFO|TA_MFIFO, 0, 0, "Mbx"};

VB const * const demo_str[] = {"\n\r\teForce Operating System Sample Program V1.0\n\r\t\tSerial Port (UART2)\r\n"};


/******************************************************************
        システム用メモリを確保
 ******************************************************************/

#ifdef __ICCARM__
#pragma section = "SYSMEM"
int SYSMEM[0x0C000/sizeof(int)] @ "SYSMEM";
#endif

#ifdef __CC_ARM
int SYSMEM[0x0C000/sizeof(int)] __attribute__ ((section ("SYSMEM"), zero_init));
#endif


/******************************************************************
        スタック用メモリとプール用のメモリを確保
 ******************************************************************/

#ifdef __ICCARM__
#pragma section = "STKMEM"
int STKMEM[0x80000/sizeof(int)] @ "STKMEM";
#pragma section = "MPLMEM"
int MPLMEM[0x70000/sizeof(int)] @ "MPLMEM";
#endif

#ifdef __CC_ARM
int STKMEM[0x80000/sizeof(int)] __attribute__ ((section ("STKMEM"), zero_init));
int MPLMEM[0x70000/sizeof(int)] __attribute__ ((section ("MPLMEM"), zero_init));
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


/*******************************
  　    Com Task
 *******************************/

void ComTask(VP_INT exinf)
{
    UINT txcnt;
    VB c;

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

    ini_com(ID_UART2, &uart_ini);
    ctr_com(ID_UART2, STA_COM, 0);

    ctr_com(ID_UART2, SND_BRK, 100);

    txcnt = strlen(demo_str[0]);
    puts_com(ID_UART2, (VB *)demo_str[0], &txcnt, TMO_FEVR);

    for(;;) {
        getc_com(ID_UART2, &c, 0, TMO_FEVR);
        putc_com(ID_UART2, c, TMO_FEVR);
    }
}

T_CTSK const ctsk_com = {TA_HLNG|TA_ACT, (VP_INT)0, (FP)ComTask, 1, 0x400, 0, "ComTask"};


/*******************************
  　    Sub Task
 *******************************/

void SubTask(VP_INT exinf)
{
    loc_cpu();
    REG_GPIO3.DR ^= 0x30000000;
    unl_cpu();

    dly_tsk(100);

    loc_cpu();
    REG_GPIO3.DR ^= 0x30000000;
    unl_cpu();
}

T_CTSK const ctsk_sub = {TA_HLNG, (VP_INT)0, (FP)SubTask, 2, 0x400, 0, "SubTask"};


/*******************************
  　    Main Task
 *******************************/

void MainTask(VP_INT exinf)
{
    REG_IOMUXC.SW_MUX_CTL_PAD_NFALE = 5;    /* GPIO3_28 */
    REG_IOMUXC.SW_MUX_CTL_PAD_NFCLE = 5;    /* GPIO3_29 */
    loc_cpu();
    REG_GPIO3.DR &= ~0x30000000;
    REG_GPIO3.DR |= 0x20000000;
    REG_GPIO3.GDIR |= 0x30000000;
    unl_cpu();

    for(;;) {
        act_tsk(SubTaskID);
        dly_tsk(200);
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
    SubTaskID = acre_tsk((T_CTSK *)&ctsk_sub);
    ComTaskID = acre_tsk((T_CTSK *)&ctsk_com);
    MpfID = acre_mpf((T_CMPF *)&cmpf);
    MbxID = acre_mbx((T_CMBX *)&cmbx);
}


/*******************************
  　    初期化ルーチン
 *******************************/

extern void _ddr_fs_mx25asic_init(void);

int main(void)
{
    T_CSYS csys;

    /* ダミーアクセス */

    SYSMEM[0] = 0;
    STKMEM[0] = 0;
    MPLMEM[0] = 0;

    /* ハードウェアの初期化の残り */

    _ddr_fs_mx25asic_init();

    /* システムの生成と起動 */

    csys.tskpri_max = 8;
    csys.tskid_max = 7;
    csys.semid_max = 8;
    csys.flgid_max = 8;
    csys.dtqid_max = 8;
    csys.mbxid_max = 8;
    csys.mtxid_max = 8;
    csys.mbfid_max = 8;
    csys.porid_max = 8;
    csys.mpfid_max = 8;
    csys.mplid_max = 8;
    csys.almid_max = 8;
    csys.cycid_max = 8;
    csys.isrid_max = 10;
    csys.devid_max = 8;
    csys.tick = TICK;
    csys.ssb_num = 10;
    csys.sysmem_top = (VP)&SYSMEM[0];
    csys.sysmem_end = (VP)(&SYSMEM[0]+sizeof(SYSMEM)/sizeof(int));
    csys.stkmem_top = (VP)&STKMEM[0];
    csys.stkmem_end = (VP)(&STKMEM[0]+sizeof(STKMEM)/sizeof(int));
    csys.mplmem_top = (VP)&MPLMEM[0];
    csys.mplmem_end = (VP)(&MPLMEM[0]+sizeof(MPLMEM)/sizeof(int));
    csys.sysidl = SYSTEM_IDLE;
    csys.inistk = STACK_ID_INIT;
    csys.trace = TRACE_DISABLE;
    csys.agent = AGENT_DISABLE;
    start_uC3(&csys, initpr);
}
