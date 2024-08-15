/***********************************************************************
    Micro C Cube Standard, DEVICE DRIVER
    Interrupt controller for Freescale i.MX25

    Copyright (c)  2010, eForce Co., Ltd. All rights reserved.

    Version Information
            2010.10.26: Created
 ***********************************************************************/

#include "uC3sys.h"

#include "imx25.h"


#define VIC_SIZE    64

#ifdef __ICCARM__
#pragma section = "VINFTBL"
T_VINFTBL vinftbl[VIC_SIZE] @ "VINFTBL";
#pragma section = "VECTTBL"
int _kernel_dummy_2 @ "VECTTBL";
#endif

#ifdef __CC_ARM
T_VINFTBL vinftbl[VIC_SIZE] __attribute__ ((section ("VINFTBL"), zero_init));
int _kernel_dummy_2  __attribute__ ((section ("VECTTBL"), zero_init));
#endif


/*******************************
  Å@    èâä˙âªÉãÅ[É`Éì
 *******************************/

void _ddr_fs_mx25asic_init(void)
{
    _kernel_dummy_2 = 0;

    REG_ASIC.INTENABLEH = 0;
    REG_ASIC.INTENABLEL = 0;
    REG_ASIC.NIPRIORITY[7] = 0;
    REG_ASIC.NIPRIORITY[6] = 0;
    REG_ASIC.NIPRIORITY[5] = 0;
    REG_ASIC.NIPRIORITY[4] = 0;
    REG_ASIC.NIPRIORITY[3] = 0;
    REG_ASIC.NIPRIORITY[2] = 0;
    REG_ASIC.NIPRIORITY[1] = 0;
    REG_ASIC.NIPRIORITY[0] = 0;
    REG_ASIC.NIMASK = 16;
    REG_ASIC.INTCNTL = 0x00000000;
}


/***********************************
    Enable Interrupt
 ***********************************/

ER ena_int(INTNO intno)
{
    UW priority;
    ER ercd;

    if (intno < VIC_SIZE) {
        _kernel_lock();
        priority = REG_ASIC.NIPRIORITY[7-(intno/8)] & ~(0xF << ((intno%8)*4));
        priority |= (vinftbl[intno].intinfo & 0x0F) << ((intno%8)*4);
        REG_ASIC.NIPRIORITY[7-(intno/8)] = priority;
        REG_ASIC.INTENNUM = intno;
        _kernel_unlock();
        ercd = E_OK;
    } else {
        ercd = E_PAR;
    }
    return ercd;
}


/***********************************
    Disable Interrupt
 ***********************************/

ER dis_int(INTNO intno)
{
    ER ercd;

    if (intno < VIC_SIZE) {
        REG_ASIC.INTDISNUM = intno;
        ercd = E_OK;
    } else {
        ercd = E_PAR;
    }
    return ercd;
}


/***********************************
    Kernel internal functions
 ***********************************/

void nopending(void)
{
    ;
}

BOOL _kernel_pre_inthdr(T_INTPARA *intpara)
{
    INTNO intno;
    BOOL nestflag;
    PRI pri;
    UW temp;

    temp = REG_ASIC.NIVECSR;
    pri = temp & 0xFF;
    intno = temp>>16;
    temp = (intno << 16) | REG_ASIC.NIMASK;
    if (intno <= 63) {
        intpara->intinfo = (vinftbl[intno].intinfo & 0xFFFFFF00) | pri;
        intpara->intfunc = vinftbl[intno].intfunc;
        intpara->next = vinftbl[intno].next;
        REG_ASIC.NIMASK = pri;
        nestflag = TRUE;
    } else {
        intpara->intfunc = &nopending;
        nestflag = FALSE;
    }

    *intpara->savedt = temp;
    return nestflag;
}

void _kernel_post_inthdr(UW savedt)
{
    INTNO intno;

    intno = (savedt >> 16);
    if (intno <= 63) {
        REG_ASIC.NIMASK = (savedt & 0xFF);
    }
}
