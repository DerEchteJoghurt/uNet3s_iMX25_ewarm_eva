/***************************************************************************
    Micro C Cube Standard, KERNEL
    ARMv5T dependent internal predefinitions

    Copyright (c)  2008-2010, eForce Co., Ltd. All rights reserved.

    Version Information
            2008.06.05: Created.
            2008.12.28: Moved the TA_USR declaration.
            2010.10.07: Modified for VFP9-S architecture.
                        Removed exception number.
 ***************************************************************************/

#ifndef _UC3PRE_H_
#define _UC3PRE_H_


typedef long    T_REG;

typedef struct t_cpudep {
    FP      udfhdr;
    FP      svchdr;
    FP      prahdr;
    FP      dtahdr;
  #if defined(_TARGET_FPU_VFP) || defined(__ARMVFP__)
    T_REG   fpscr;
    T_REG   fpexc;
    T_REG   fpinst;
    T_REG   fpinst2;
  #endif
} T_CPUDEP;

#define CPU_DEPENDEND T_CPUDEP  cpudep;

#endif
