/***************************************************************************
    Micro C Cube Standard, KERNEL
    ARMv5T dependent internal edefinitions

    Copyright (c)  2008, eForce Co.,Ltd.  All rights reserved.

    Version Information  2008.06.05: Created
 ***************************************************************************/

#ifndef _UC3CPU_H_
#define _UC3CPU_H_


typedef struct t_intpara {
    UW      *savedt;
    UW      intinfo;
    FP      intfunc;
    T_ISR   *next;
} T_INTPARA;

typedef struct t_vinftbl {
    UW      intinfo;
    FP      intfunc;
    T_ISR   *next;
    T_ISR   *prev;
} T_VINFTBL;

typedef struct t_armv5t_defint {
    UW          cmd[11];
    FP          entry;
    T_VINFTBL   vinftbl;
} T_ARMV5T_DEFINT;

extern IMASK _kernel_get_imask(void);
extern IMASK _kernel_set_imask(IMASK imask);
extern void _kernel_clean_data_cache(void *ptr, SIZE sz);
extern void _kernel_invalid_data_cache(void *ptr, SIZE sz);
extern void _kernel_invalid_inst_cache(void *ptr, SIZE sz);
extern void _kernel_synch_cache(void);

#endif
