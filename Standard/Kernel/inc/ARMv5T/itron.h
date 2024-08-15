/***************************************************************************
    Micro C Cube Standard, KERNEL
    ITRON macro definitions for ARMv5T dependent definitions

    Copyright (c)  2008-2015, eForce Co.,Ltd.  All rights reserved.

    Version Information
            2008.06.05: Created.
            2008.11.25: Corrected product version.
            2008.12.28: Moved the TA_USR declaration.
            2010.10.07: Modified for VFP9-S architecture.
                        Added exception number.
            2015.05.08: Changed TKERNEL_PRVER to v1.11.0
 ***************************************************************************/

#ifndef _ITRON_H_
#define _ITRON_H_

#ifndef NULL
#ifdef __cplusplus
#define NULL    (0)
#else
#define NULL    ((void *)0)
#endif
#endif

#define TRUE    1
#define FALSE   0

#define E_OK    0

#define TA_USR      0x10u

#define _kernel_INT_SIZE    4
#define _kernel_SIZE_SIZE   4
#define _kernel_ALIGN_SIZE  8
#define _kernel_INT_BIT     (_kernel_INT_SIZE*8)

#define TKERNEL_PRID    0x0242
#define TKERNEL_PRVER   0x1110


#define EXC_UDF     1
#define EXC_SVC     2
#define EXC_PRA     3
#define EXC_DTA     4


/************************************
    Data Types
 ************************************/

typedef signed char B;
typedef signed short H;
typedef signed long W;
typedef unsigned char UB;
typedef unsigned short UH;
typedef unsigned long UW;
typedef char VB;
typedef short VH;
typedef long VW;
typedef void *VP;
typedef void (*FP)(void);

#ifdef _kernel_longlong
typedef signed long long D;
typedef unsigned long long UD;
typedef long long VD;
#endif

typedef unsigned long SIZE;
typedef unsigned long ADDR;

typedef int INT;
typedef unsigned int UINT;

typedef VP VP_INT;

typedef INT BOOL;
typedef INT FN;
typedef INT ER;
typedef INT ID;
typedef INT PRI;
typedef INT BOOL_ID;
typedef INT RDVNO;
typedef INT ER_ID;
typedef INT ER_UINT;
typedef UINT TEXPTN;
typedef UINT FLGPTN;
typedef UINT RDVPTN;
typedef UINT INHNO;
typedef UINT INTNO;
typedef UINT IMASK;
typedef UINT EXCNO;

typedef UINT ATR;
typedef UINT STAT;
typedef UINT MODE;

#ifdef _kernel_longlong
typedef UD SYSTIM;
#else
typedef struct t_systim {
    UW utime;
    UW ltime;
} SYSTIM;
#endif
typedef W TMO;

typedef UW RELTIM;
typedef UH OVRTIM;

/************************************
    ARMv5T dependent definitions
 ************************************/

#if defined(_TARGET_FPU_VFP) || defined(__ARMVFP__)
UW vget_fpscr(void);
UW vget_fpexc(void);
UW vget_fpinst(void);
UW vget_fpinst2(void);
void vset_fpscr(UW fpscr);
void vset_fpexc(UW fpexc);
void vset_fpinst(UW fpinst);
void vset_fpinst2(UW fpinst2);
void vena_vfp(void);
void vdis_vfp(void);
#endif

extern void _kernel_clean_data_cache(void *ptr, SIZE sz);
extern void _kernel_invalid_data_cache(void *ptr, SIZE sz);
extern void _kernel_invalid_inst_cache(void *ptr, SIZE sz);
extern void _kernel_synch_cache(void);
extern void _kernel_data_memory_barrier(void);

#endif /* _ITRON_H_ */
