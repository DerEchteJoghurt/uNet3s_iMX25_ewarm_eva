/****************************************************************************
    Micro C Cube Standard, KERNEL
    Kernel common definitions

    Copyright (c)  2008-2015, eForce Co.,Ltd.  All rights reserved.

    Version Information
            2008.06.19: Created.
            2008.10.24: Corrected the error in writing.
            2008.11.27: Corrected the function definitions.
            2009.07.20: Modified the configuration of object max ID.
            2009.09.28: Modified for the multi-core extension.
            2009.11.11: Corrected the function code.
            2010.12.29: Added the function code.
            2013.09.20: Modified TSZ_MPF macro.
            2013.09.30: Supported the YDC SystemMacroTrace.
            2014.08.19: Supported the CubeGEAR Trace.
            2015.02.19: Added "C" linkage macro.
 ****************************************************************************/

#ifndef _KERNEL_H_
#define _KERNEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "itron.h"

#ifdef _UC3SYS_H_
#define EXTERN
#else
#define EXTERN  extern
#endif

/***********************************
        �p�P�b�g�`��
 ***********************************/

/* �^�X�N�Ǘ��@�\ */

typedef struct t_ctsk {
    ATR         tskatr;         /* �^�X�N����                               */
    VP_INT      exinf;          /* �^�X�N�̊g�����                         */
    FP          task;           /* �^�X�N�̋N���Ԓn                         */
    PRI         itskpri;        /* �^�X�N�̋N�����D��x                     */
    SIZE        stksz;          /* �^�X�N�̃X�^�b�N�T�C�Y                   */
    VP          stk;            /* �^�X�N�̃X�^�b�N�̈�̐擪�Ԓn           */
    VB const    *name;          /* �^�X�N�̖���                             */
} T_CTSK;

typedef struct t_rtsk {
    STAT        tskstat;        /* �^�X�N���                               */
    PRI         tskpri;         /* �^�X�N�̌��ݗD��x                       */
    PRI         tskbpri;        /* �^�X�N�̃x�[�X�D��x                     */
    STAT        tskwait;        /* �҂��v��                                 */
    ID          wobjid;         /* �҂��Ώۂ̃I�u�W�F�N�g��ID�ԍ�           */
    TMO         lefttmo;        /* �^�C���A�E�g����܂ł̎���               */
    UINT        actcnt;         /* �N���v���L���[�C���O��                   */
    UINT        wupcnt;         /* �N���v���L���[�C���O��                   */
    UINT        suscnt;         /* �����҂��v���l�X�g��                     */
} T_RTSK;

typedef struct t_rtst {
    STAT        tskstat;        /* �^�X�N���                               */
    STAT        tskwait;        /* �҂��v��                                 */
} T_RTST;

/* �^�X�N��O�����@�\ */

typedef struct t_dtex {
    ATR         texatr;         /* �^�X�N��O�������[�`������               */
    FP          texrtn;         /* �^�X�N��O�������[�`���̋N���Ԓn         */
} T_DTEX;

typedef struct t_rtex {
    STAT        texstat;        /* �^�X�N��O�����̏��                     */
    TEXPTN      pndptn;         /* �ۗ���O�v��                             */
} T_RTEX;

/* �����E�ʐM�@�\�i�Z�}�t�H�j */

typedef struct t_csem {
    ATR         sematr;         /* �Z�}�t�H����                             */
    UINT        isemcnt;        /* �Z�}�t�H�̎������̏����l                 */
    UINT        maxsem;         /* �Z�}�t�H�̍ő厑����                     */
    VB const    *name;          /* �Z�}�t�H�̖���                           */
}T_CSEM;

typedef struct t_rsem {
    ID          wtskid;         /* �Z�}�t�H�̑҂��s��̐擪�̃^�X�N��ID�ԍ� */
    UINT        semcnt;         /* �Z�}�t�H�̌��݂̎�����                   */
} T_RSEM;

/* �����E�ʐM�@�\�i�C�x���g�t���O�j */

typedef struct t_cflg {
    ATR         flgatr;         /* �C�x���g�t���O����                       */
    FLGPTN      iflgptn;        /* �C�x���g�t���O�̃r�b�g�p�^�[���̏����l   */
    VB const    *name;          /* �C�x���g�t���O�̖���                     */
} T_CFLG;

typedef struct t_rflg {
    ID          wtskid;         /* �C�x���g�t���O�̑҂��s��̐擪�̃^�X�N��ID�ԍ�   */
    FLGPTN      flgptn;         /* �C�x���g�t���O�̌��݂̃r�b�g�p�^�[��             */
} T_RFLG;

/* �����E�ʐM�@�\�i�f�[�^�L���[�j */

typedef struct t_cdtq {
    ATR         dtqatr;         /* �f�[�^�L���[����                         */
    UINT        dtqcnt;         /* �f�[�^�L���[�̗e�ʁi�f�[�^�̌��j       */
    VP          dtq;            /* �f�[�^�L���[�̈�̐擪�Ԓn               */
    VB const    *name;          /* �f�[�^�L���[�̖���                       */
} T_CDTQ;

typedef struct t_rdtq {
    ID          stskid;         /* �f�[�^�L���[�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ� */
    ID          rtskid;         /* �f�[�^�L���[�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ� */
    UINT        sdtqcnt;        /* �f�[�^�L���[�ɓ����Ă���f�[�^�̐�               */
} T_RDTQ;

/* �����E�ʐM�@�\�i���[���{�b�N�X�j */

typedef struct t_cmbx {
    ATR         mbxatr;         /* ���[���{�b�N�X����                               */
    PRI         maxmpri;        /* ���M����郁�b�Z�[�W�̗D��x�̍ő�l             */
    VP          mprihd;         /* �D��x�ʂ̃��b�Z�[�W�L���[�w�b�_�̗̈�̐擪�Ԓn */
    VB const    *name;          /* ���[���{�b�N�X�̖���                             */
} T_CMBX;

typedef struct t_rmbx {
    ID          wtskid;         /* ���[���{�b�N�X�̑҂��s��̐擪�̃^�X�N��ID�ԍ�       */
    struct t_msg    *pk_msg;    /* ���b�Z�[�W�L���[�̐擪�̃��b�Z�[�W�p�P�b�g�̐擪�Ԓn */
} T_RMBX;

typedef struct t_msg {
    struct t_msg    *msgque;    /* ���b�Z�[�W�w�b�_                         */
} T_MSG;

typedef struct t_msg_pri {
    struct t_msg_pri    *msgque;/* ���b�Z�[�W�w�b�_                         */
    PRI                 msgpri; /* ���b�Z�[�W�D��x                         */
} T_MSG_PRI;

/* �g�������E�ʐM�@�\�i�~���[�e�b�N�X�j */

typedef struct t_cmtx {
    ATR         mtxatr;         /* �~���[�e�b�N�X����                       */
    PRI         ceilpri;        /* �~���[�e�b�N�X�̏���D��x               */
    VB const    *name;          /* �~���[�e�b�N�X�̖���                     */
} T_CMTX;

typedef struct t_rmtx {
    ID          htskid;         /* �~���[�e�b�N�X�����b�N���Ă���^�X�N��ID�ԍ�     */
    ID          wtskid;         /* �~���[�e�b�N�X�̑҂��s��̐擪�̃^�X�N��ID�ԍ�   */
} T_RMTX;

/* �g�������E�ʐM�@�\�i���b�Z�[�W�o�b�t�@�j */

typedef struct t_cmbf {
    ATR         mbfatr;         /* ���b�Z�[�W�o�b�t�@����                       */
    UINT        maxmsz;         /* ���b�Z�[�W�̍ő�T�C�Y�i�o�C�g���j           */
    SIZE        mbfsz;          /* ���b�Z�[�W�o�b�t�@�̈�̃T�C�Y�i�o�C�g���j   */
    VP          mbf;            /* ���b�Z�[�W�o�b�t�@�̈�̐擪�Ԓn             */
    VB const    *name;          /* ���b�Z�[�W�o�b�t�@�̖���                     */
} T_CMBF;

typedef struct t_rmbf {
    ID          stskid;         /* ���b�Z�[�W�o�b�t�@�̑��M�҂��s��̐擪�̃^�X�N��ID�ԍ�   */
    ID          rtskid;         /* ���b�Z�[�W�o�b�t�@�̎�M�҂��s��̐擪�̃^�X�N��ID�ԍ�   */
    UINT        smsgcnt;        /* ���b�Z�[�W�o�b�t�@�ɓ����Ă��郁�b�Z�[�W�̐�             */
    SIZE        fmbfsz;         /* ���b�Z�[�W�o�b�t�@�̈�̋󂫗̈�̃T�C�Y�i�o�C�g���j     */
} T_RMBF;

/* �g�������E�ʐM�@�\�i�����f�u�|�[�g�j */

typedef struct t_cpor {
    ATR         poratr;         /* �����f�u�|�[�g����                       */
    UINT        maxcmsz;        /* �ďo�����b�Z�[�W�̍ő�T�C�Y�i�o�C�g���j */
    UINT        maxrmsz;        /* �ԓ����b�Z�[�W�̍ő�T�C�Y�i�o�C�g���j   */
    VB const    *name;          /* �����f�u�|�[�g�̖���                     */
} T_CPOR;

typedef struct t_rpor {
    ID          ctskid;         /* �����f�u�|�[�g�̌ďo���҂��s��̐擪�̃^�X�N��ID�ԍ� */
    ID          atskid;         /* �����f�u�|�[�g�̎�t�҂��s��̐擪�̃^�X�N��ID�ԍ�   */
} T_RPOR;

typedef struct t_rrdv {
    ID          wtskid;         /* �����f�u�I���҂���Ԃ̃^�X�N��ID�ԍ�     */
} T_RRDV;

/* �������v�[���Ǘ��@�\�i�Œ蒷�������v�[���j */

typedef struct t_cmpf {
    ATR         mpfatr;         /* �Œ蒷�������v�[������                   */
    UINT        blkcnt;         /* �l���ł��郁�����u���b�N���i���j       */
    UINT        blksz;          /* �������u���b�N�̃T�C�Y�i�o�C�g���j       */
    VP          mpf;            /* �Œ蒷�������v�[���̈�̐擪�Ԓn         */
    VB const    *name;          /* �Œ蒷�������v�[���̖���                 */
} T_CMPF;

typedef struct t_rmpf {
    ID          wtskid;         /* �Œ蒷�������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ�   */
    UINT        fblkcnt;        /* �Œ蒷�������v�[���̋󂫃������u���b�N���i���j     */
} T_RMPF;

/* �������v�[���Ǘ��@�\�i�ϒ��������v�[���j */

typedef struct t_cmpl {
    ATR         mplatr;         /* �ϒ��������v�[������                       */
    SIZE        mplsz;          /* �ϒ��������v�[���̈�̃T�C�Y�i�o�C�g���j   */
    VP          mpl;            /* �ϒ��������v�[���̈�̐擪�Ԓn             */
    VB const    *name;          /* �ϒ��������v�[���̖���                     */
} T_CMPL;

typedef struct t_rmpl {
    ID          wtskid;         /* �ϒ��������v�[���̑҂��s��̐擪�̃^�X�N��ID�ԍ�   */
    SIZE        fmplsz;         /* �ϒ��������v�[���̋󂫗̈�̍��v�T�C�Y�i�o�C�g���j */
    UINT        fblksz;         /* �߂��Ɋl���\�ȍő僁�����u���b�N�T�C�Y�i�o�C�g���j */
} T_RMPL;

/* ���ԊǗ��@�\�i�����n���h���j */

typedef struct t_ccyc {
    ATR         cycatr;         /* �����n���h������                         */
    VP_INT      exinf;          /* �����n���h���̊g�����                   */
    FP          cychdr;         /* �����n���h���̋N���Ԓn                   */
    RELTIM      cyctim;         /* �����n���h���̋N������                   */
    RELTIM      cycphs;         /* �����n���h���̋N���ʑ�                   */
    VB const    *name;          /* �����n���h���̖���                       */
} T_CCYC;

typedef struct t_rcyc {
    STAT        cycstat;        /* �����n���h���̓�����                   */
    RELTIM      lefttim;        /* �����n���h�������ɋN�����鎞���܂ł̎��� */
} T_RCYC;

/* ���ԊǗ��@�\�i�A���[���n���h���j */

typedef struct t_calm {
    ATR         almatr;         /* �A���[���n���h������                     */
    VP_INT      exinf;          /* �A���[���n���h���̊g�����               */
    FP          almhdr;         /* �A���[���n���h���̋N���Ԓn               */
    VB const    *name;          /* �A���[���n���h���̖���                   */
} T_CALM;

typedef struct t_ralm {
    STAT        almstat;        /* �A���[���n���h���̓�����               */
    RELTIM      lefttim;        /* �A���[���n���h���̋N�������܂ł̎���     */
} T_RALM;

/* ���ԊǗ��@�\�i�I�[�o�����n���h���j */

typedef struct t_dovr {
    ATR         ovratr;         /* �I�[�o�����n���h������                   */
    FP          ovrhdr;         /* �I�[�o�����n���h���̋N���Ԓn             */
} T_DOVR;

typedef struct t_rovr {
    STAT        ovrstat;        /* �I�[�o�����n���h���̓�����             */
    OVRTIM      leftotm;        /* �c��̃v���Z�b�T����                     */
} T_ROVR;

/* �Ǝ��@�\�i�f�o�C�X�h���C�o�j */

typedef struct t_cdev {
    VP          ctrblk;         /* ������̐擪�Ԓn                       */
    FP          devhdr;         /* �f�o�C�X�h���C�o�̋N���Ԓn               */
    VB const    *name;          /* �f�o�C�X�h���C�o�̖���                   */
} T_CDEV;

/* �V�X�e���Ǘ��@�\ */

typedef struct t_csys {
    UH          tskpri_max;     /* �^�X�N�D��x�̍ő�l                     */
    UH          tskid_max;      /* �^�X�NID�̍ő�l                         */
    UH          semid_max;      /* �Z�}�t�HID�̍ő�l                       */
    UH          flgid_max;      /* �C�x���g�t���OID�̍ő�l                 */
    UH          dtqid_max;      /* �f�[�^�L���[ID�̍ő�l                   */
    UH          mbxid_max;      /* ���[���{�b�N�XID�̍ő�l                 */
    UH          mtxid_max;      /* �~���[�e�b�N�XID�̍ő�l                 */
    UH          mbfid_max;      /* ���b�Z�[�W�o�b�t�@ID�̍ő�l             */
    UH          porid_max;      /* �����f�u�|�[�gID�̍ő�l                 */
    UH          mpfid_max;      /* �Œ蒷�������v�[��ID�̍ő�l             */
    UH          mplid_max;      /* �ϒ��������v�[��ID�̍ő�l             */
    UH          almid_max;      /* �A���[���n���h��ID�̍ő�l               */
    UH          cycid_max;      /* �����n���h��ID�̍ő�l                   */
    UH          isrid_max;      /* �����݃T�[�r�X���[�`��ID�̍ő�l         */
    UH          devid_max;      /* �f�o�C�X�h���C�oID�̍ő�l               */
    UH          tick;           /* �`�b�N���ԁi�_�b�j                       */
    UH          ssb_num;        /* �V�X�e���T�[�r�X�u���b�N�̐�����       */
    VP          sysmem_top;     /* �V�X�e���������̐擪�Ԓn                 */
    VP          sysmem_end;     /* �V�X�e���������̃T�C�Y                   */
    VP          stkmem_top;     /* �X�^�b�N�p�������̐擪�Ԓn               */
    VP          stkmem_end;     /* �X�^�b�N�p�������̃T�C�Y                 */
    VP          mplmem_top;     /* �������v�[���p�������̐擪�Ԓn           */
    VP          mplmem_end;     /* �������v�[���p�������̃T�C�Y             */
    FP          ctrtim;         /* �^�C�}����֐��̔Ԓn                     */
    FP          sysidl;         /* �A�C�h���֐��̔Ԓn                       */
    FP          inistk;         /* �X�^�b�N�������֐��̔Ԓn                 */
    FP          trace;          /* �g���[�X�@�\�������֐��̔Ԓn             */
    FP          agent;          /* �G�[�W�F���g�@�\�������֐��̔Ԓn         */
} T_CSYS;

typedef struct t_rsys {
    SIZE        fsyssz;         /* �V�X�e���������̋󂫗̈�̍��v�T�C�Y     */
    SIZE        fstksz;         /* �X�^�b�N�������̋󂫗̈�̍��v�T�C�Y     */
    SIZE        fmplsz;         /* �v�[���������̋󂫗̈�̍��v�T�C�Y       */
    UH          utskid;         /* �����ς݃^�X�NID�̌�                   */
    UH          usemid;         /* �����ς݃Z�}�t�HID�̌�                 */
    UH          uflgid;         /* �����ς݃C�x���g�t���OID�̌�           */
    UH          udtqid;         /* �����ς݃f�[�^�L���[ID�̌�             */
    UH          umbxid;         /* �����ς݃��[���{�b�N�XID�̌�           */
    UH          umtxid;         /* �����ς݃~���[�e�b�N�XID�̌�           */
    UH          umbfid;         /* �����ς݃��b�Z�[�W�o�b�t�@ID�̌�       */
    UH          uporid;         /* �����ς݃����f�u�|�[�gID�̌�           */
    UH          umpfid;         /* �����ς݌Œ蒷�������v�[��ID�̌�       */
    UH          umplid;         /* �����ς݉ϒ��������v�[��ID�̌�       */
    UH          ualmid;         /* �����ς݃A���[���n���h��ID�̌�         */
    UH          ucycid;         /* �����ςݎ����n���h��ID�̌�             */
    UH          uisrid;         /* �����ς݊����݃T�[�r�X���[�`��ID�̌�   */
    UH          ssbcnt;         /* SSB�̍ŏ���                            */
} T_RSYS;

/* �����݊Ǘ��@�\ */

typedef struct t_dinh {
    ATR         inhatr;         /* �����݃n���h������                       */
    FP          inthdr;         /* �����݃n���h���̋N���Ԓn                 */
    IMASK       imask;          /* �����݃n���h���̊����݃}�X�N���x��       */
} T_DINH;

typedef struct t_cisr {
    ATR         isratr;         /* �����݃T�[�r�X���[�`������                   */
    VP_INT      exinf;          /* �����݃T�[�r�X���[�`���̊g�����             */
    INTNO       intno;          /* �����݃T�[�r�X���[�`����t�����銄���ݔԍ�   */
    FP          isr;            /* �����݃T�[�r�X���[�`���̋N���Ԓn             */
    IMASK       imask;          /* �����݃T�[�r�X���[�`���̊����݃}�X�N���x��   */
} T_CISR;

typedef struct t_risr {
    INTNO       intno;          /* �����݃T�[�r�X���[�`����t�����������ݔԍ�   */
    FP          isr;            /* �����݃T�[�r�X���[�`���̋N���Ԓn             */
} T_RISR;

/* �V�X�e���\���Ǘ��@�\ */

typedef struct t_dexc {
    ATR         excatr;         /* CPU��O�n���h���̑���                    */
    FP          exchdr;         /* CPU��O�n���h���̋N���Ԓn                */
} T_DEXC;

typedef struct t_rcfg {
    UH          tskpri_max;     /* �^�X�N�D��x�̍ő�l                     */
    UH          tskid_max;      /* �^�X�NID�̍ő�l                         */
    UH          semid_max;      /* �Z�}�t�HID�̍ő�l                       */
    UH          flgid_max;      /* �C�x���g�t���OID�̍ő�l                 */
    UH          dtqid_max;      /* �f�[�^�L���[ID�̍ő�l                   */
    UH          mbxid_max;      /* ���[���{�b�N�XID�̍ő�l                 */
    UH          mtxid_max;      /* �~���[�e�b�N�XID�̍ő�l                 */
    UH          mbfid_max;      /* ���b�Z�[�W�o�b�t�@ID�̍ő�l             */
    UH          porid_max;      /* �����f�u�|�[�gID�̍ő�l                 */
    UH          mpfid_max;      /* �Œ蒷�������v�[��ID�̍ő�l             */
    UH          mplid_max;      /* �ϒ��������v�[��ID�̍ő�l             */
    UH          almid_max;      /* �A���[���n���h��ID�̍ő�l               */
    UH          cycid_max;      /* �����n���h��ID�̍ő�l                   */
    UH          isrid_max;      /* �����݃T�[�r�X���[�`��ID�̍ő�l         */
    UH          devid_max;      /* �f�o�C�X�h���C�oID�̍ő�l               */
    UH          tick;           /* �`�b�N���ԁi�_�b�j                       */
    UH          ssb_cnt;        /* �V�X�e���T�[�r�X�u���b�N�̐�����       */
} T_RCFG;

typedef struct t_rver {
    UH          maker;          /* �J�[�l���̃��[�J�R�[�h                   */
    UH          prid;           /* �J�[�l���̎��ʔԍ�                       */
    UH          spver;          /* ITRON�d�l�̃o�[�W�����ԍ�                */
    UH          prver;          /* �J�[�l���̃o�[�W�����ԍ�                 */
    UH          prno[4];        /* �J�[�l���̐��i���                       */
} T_RVER;

/***********************************
        �萔
 ***********************************/

/* �I�u�W�F�N�g���� */

#define TA_NULL     0           /* �I�u�W�F�N�g�������w�肵�Ȃ�             */
#define TA_HLNG     0x00u       /* ��������̃C���^�t�F�[�X                 */
#define TA_ASM      0x01u       /* �A�Z���u������̃C���^�t�F�[�X           */
#define TA_ACT      0x02u       /* �^�X�N���N�����ꂽ��ԂŐ���             */
#define TA_RSTR     0x04u       /* ����^�X�N                               */

#define TA_AUX      0x10u       /* �\������                                 */
#define TA_DSP      0x20u       /* DSP������                              */
#define TA_FPU      0x40u       /* FPU������                              */
#define TA_VPU      0x80u       /* VPU������                              */

#define TA_TFIFO    0x00u       /* FIFO���̑҂��s��                         */
#define TA_TPRI     0x01u       /* �^�X�N�D�揇�̑҂��s��                   */

#define TA_MFIFO    0x00u       /* FIFO���̃��b�Z�[�W�L���[                 */
#define TA_MPRI     0x02u       /* �D��x���̃��b�Z�[�W�L���[               */

#define TA_WSGL     0x00u       /* �C�x���g�t���O�̕����^�X�N�҂����֎~     */
#define TA_WMUL     0x02u       /* �C�x���g�t���O�̕����^�X�N�҂�������     */
#define TA_CLR      0x04u       /* �҂��������̃C�x���g�t���O�̃N���A       */

#define TA_INHERIT  0x02u       /* �D��x�p���v���g�R��                     */
#define TA_CEILING  0x03u       /* �D��x����v���g�R��                     */

#define TA_STA      0x02u       /* �����n���h���𓮍삵�Ă����ԂŐ���     */
#define TA_PHS      0x04u       /* �����n���h���̈ʑ���ۑ�                 */

/* �^�C���A�E�g�w�� */

#define TMO_POL     0           /* �|�[�����O                               */
#define TMO_FEVR    -1          /* �i�v�҂�                                 */

/* �V�X�e���R�[���̓��샂�[�h */

#define TWF_ANDW    0x00u       /* �C�x���g�t���O��AND�҂�                  */
#define TWF_ORW     0x01u       /* �C�x���g�t���O��OR�҂�                   */

/* �I�u�W�F�N�g�̏�� */

#define TTS_RUN     0x01u       /* ���s���                                 */
#define TTS_RDY     0x02u       /* ���s�\���                             */
#define TTS_WAI     0x04u       /* �҂����                                 */
#define TTS_SUS     0x08u       /* �����҂����                             */
#define TTS_WAS     0x0Cu       /* ��d�҂����                             */
#define TTS_DMT     0x10u       /* �x�~���                                 */

#define TTW_SLP     0x0001u     /* �N���҂����                             */
#define TTW_DLY     0x0002u     /* ���Ԍo�ߑ҂����                         */
#define TTW_SEM     0x0004u     /* �Z�}�t�H�����̊l���҂����               */
#define TTW_FLG     0x0008u     /* �C�x���g�t���O�̑҂����                 */
#define TTW_SDTQ    0x0010u     /* �f�[�^�L���[�ւ̑��M�҂����             */
#define TTW_RDTQ    0x0020u     /* �f�[�^�L���[����̎�M�҂����           */
#define TTW_MBX     0x0040u     /* ���[���{�b�N�X����̎�M�҂����         */
#define TTW_MTX     0x0080u     /* �~���[�e�b�N�X�̃��b�N�҂����           */
#define TTW_SMBF    0x0100u     /* ���b�Z�[�W�o�b�t�@�ւ̑��M�҂����       */
#define TTW_RMBF    0x0200u     /* ���b�Z�[�W�o�b�t�@����̎�M�҂����     */
#define TTW_CAL     0x0400u     /* �����f�u�̌Ăяo���҂����               */
#define TTW_ACP     0x0800u     /* �����f�u�̎�t�҂����                   */
#define TTW_RDV     0x1000u     /* �����f�u�̏I���҂����                   */
#define TTW_MPF     0x2000u     /* �Œ蒷�������u���b�N�̊l���҂����       */
#define TTW_MPL     0x4000u     /* �ϒ��������u���b�N�̊l���҂����       */

#define TTEX_ENA    0x00u       /* �^�X�N��O�n���h���̋����             */
#define TTEX_DIS    0x01u       /* �^�X�N��O�n���h���̋֎~���             */

#define TCYC_STP    0x00u       /* �����n���h�������삵�Ă��Ȃ�             */
#define TCYC_STA    0x01u       /* �����n���h�������삵�Ă���               */

#define TALM_STP    0x00u       /* �A���[���n���h�������삵�Ă��Ȃ�         */
#define TALM_STA    0x01u       /* �A���[���n���h�������삵�Ă���           */

#define TOVR_STP    0x00u       /* ����v���Z�b�T���Ԃ��ݒ肳��Ă��Ȃ�     */
#define TOVR_STA    0x01u       /* ����v���Z�b�T���Ԃ��ݒ肳��Ă���       */

/* ���̑��̒萔 */

#define TSK_SELF    0           /* ���^�X�N�w��                             */
#define TSK_NONE    0           /* �Y������^�X�N���Ȃ�                     */

#define TPRI_SELF   0           /* ���^�X�N�̃x�[�X�D��x�̎w��             */
#define TPRI_INI    0           /* �^�X�N�̋N�����D��x�̎w��               */

#define TKERNEL_MAKER   0x0000  /* �J�[�l���̃��[�J�R�[�h                   */
#define TKERNEL_SPVER   0x5403  /* ITRON�d�l�̃o�[�W�����ԍ�                */

/***********************************
        �\���萔�ƃ}�N��
 ***********************************/

/* �I�u�W�F�N�g�E�D��x�͈̔� */

#define TMIN_TPRI   1           /* �^�X�N�D��x�̍ŏ��l                     */
#define TMAX_TPRI   31          /* �^�X�N�D��x�̍ő�l                     */

#define TMIN_MPRI   1           /* ���b�Z�[�W�D��x�̍ŏ��l                 */
#define TMAX_MPRI   31          /* ���b�Z�[�W�D��x�̍ő�l                 */

#define TMIN_OBJ    1           /* �^�X�N�ȊO�̃I�u�W�F�N�gID�̍ŏ��l       */
#ifndef TMAX_OBJ
#define TMAX_OBJ    999         /* �^�X�N�ȊO�̃I�u�W�F�N�gID�̍ő�l       */
#endif

#define TMIN_TSK    1           /* �^�X�NID�̍ŏ��l                         */
#ifndef TMAX_TSK
#define TMAX_TSK    255         /* �^�X�NID�̍ő�l                         */
#endif

/* �L���[�C���O/�l�X�g�񐔂̍ő�l */

#define TMAX_ACTCNT 999         /* �^�X�N�̋N���v���L���[�C���O���̍ő�l   */
#define TMAX_WUPCNT 999         /* �^�X�N�̋N���v���L���[�C���O���̍ő�l   */
#define TMAX_SUSCNT 999         /* �^�X�N�̋����҂��v���l�X�g���̍ő�l     */
#define TMAX_MAXSEM 999         /* �Z�}�t�H�̍ő厑�����̍ő�l             */

/* �r�b�g�p�^�[���̃r�b�g�� */

#define TBIT_TEXPTN _kernel_INT_BIT
#define TBIT_FLGPTN _kernel_INT_BIT
#define TBIT_RDVPTN _kernel_INT_BIT

/* �K�v�ȃ������̈�̃T�C�Y */

#define TSZ_DTQ(i)      ((i)*sizeof(VP_INT))
#define TSZ_MPRIHD(i)   ((i)*sizeof(VP)*2)
#define TSZ_MBF(i,j)    ((i)*((j+_kernel_ALIGN_SIZE-1)&(0-_kernel_ALIGN_SIZE)))

#define TSZ_MPF(i,j)    ((i)*(((j)+(_kernel_ALIGN_SIZE-1))&(~(_kernel_ALIGN_SIZE-1))))
#define TSZ_MPL(i,j)    ((i)*((j+_kernel_ALIGN_SIZE+_kernel_ALIGN_SIZE-1)&(0-_kernel_ALIGN_SIZE)))


/***********************************
        �G���[�R�[�h
 ***********************************/

#define E_SYS       -5          /* 0xFFFB: �V�X�e���G���[                   */
#define E_NOSPT     -9          /* 0xFFF7: ���T�|�[�g�G���[                 */
#define E_RSFN      -10         /* 0xFFF6: �\��@�\�R�[�h                   */
#define E_RSATR     -11         /* 0xFFF5: �\�񑮐�                         */
#define E_PAR       -17         /* 0xFFEF: �p�����[�^�G���[                 */
#define E_ID        -18         /* 0xFFEE: �s��ID�ԍ�                       */
#define E_CTX       -25         /* 0xFFE7: �R���e�L�X�g�G���[               */
#define E_MACV      -26         /* 0xFFE6: �������A�N�Z�X�ᔽ               */
#define E_OACV      -27         /* 0xFFE5: �I�u�W�F�N�g�A�N�Z�X�ᔽ         */
#define E_ILUSE     -28         /* 0xFFE4: �T�[�r�X�R�[���s���g�p           */
#define E_NOMEM     -33         /* 0xFFDF: �������s��                       */
#define E_NOID      -34         /* 0xFFDE: ID�ԍ��s��                       */
#define E_OBJ       -41         /* 0xFFD7: �I�u�W�F�N�g��ԃG���[           */
#define E_NOEXS     -42         /* 0xFFD6: �I�u�W�F�N�g������               */
#define E_QOVR      -43         /* 0xFFD5: �L���[�C���O�I�[�o�t���[         */
#define E_RLWAI     -49         /* 0xFFCF: �҂���Ԃ̋�������               */
#define E_TMOUT     -50         /* 0xFFCE: �|�[�����O���s�܂��̓^�C���A�E�g */
#define E_DLT       -51         /* 0xFFCD: �҂��I�u�W�F�N�g�̍폜           */
#define E_CLS       -52         /* 0xFFCC: �҂��I�u�W�F�N�g�̏�ԕω�       */
#define E_WBLK      -57         /* 0xFFC7: �m���u���b�L���O��t             */
#define E_BOVR      -58         /* 0xFFC6: �o�b�t�@�I�[�o�t���[             */


/***********************************
        �@�\�R�[�h
 ***********************************/

#define TFN_ACT_TSK     -0x07   /* act_tsk                                  */
#define TFN_IACT_TSK    -0x71   /* iact_tsk                                 */
#define TFN_STA_TSK     -0x09   /* sta_tsk                                  */
#define TFN_ROT_RDQ     -0x55   /* rot_rdq                                  */
#define TFN_IROT_RDQ    -0x79   /* irot_rdq                                 */
#define TFN_SET_FLG     -0x2B   /* set_flg                                  */
#define TFN_ISET_FLG    -0x76   /* iset_flg                                 */
#define TFN_IVSIG_OVR   -0xF7   /* ivsig_ovr                                */
#define TFN_SIG_SEM     -0x23   /* sig_sem                                  */
#define TFN_ISIG_SEM    -0x75   /* isig_sem                                 */
#define TFN_ISIG_TIM    -0x7D   /* isig_tim                                 */
#define TFN_PSND_DTQ    -0x36   /* psnd_dtq                                 */
#define TFN_FSND_DTQ    -0x38   /* fsnd_dtq                                 */
#define TFN_IPSND_DTQ   -0x77   /* ipsnd_dtq                                */
#define TFN_IFSND_DTQ   -0x78   /* ifsnd_dtq                                */
#define TFN_WUP_TSK     -0x13   /* wup_tsk                                  */
#define TFN_IWUP_TSK    -0x72   /* iwup_tsk                                 */
#define TFN_REL_WAI     -0x15   /* rel_wai                                  */
#define TFN_IREL_WAI    -0x73   /* irel_wai                                 */
#define TFN_REL_MPF     -0x47   /* rel_mpf                                  */
#define TFN_GET_MPF     -0x49   /* get_mpf                                  */
#define TFN_PGET_MPF    -0x4A   /* pget_mpf                                 */
#define TFN_TGET_MPF    -0x4B   /* tget_mpf                                 */
#define TFN_REL_MPL     -0xA3   /* rel_mpl                                  */
#define TFN_GET_MPL     -0xA5   /* get_mpl                                  */
#define TFN_PGET_MPL    -0xA6   /* pget_mpl                                 */
#define TFN_TGET_MPL    -0xA7   /* tget_mpl                                 */


#define TFN_VACT_TSK    -0xE1   /* vact_tsk   : Multi-Core Extension        */
#define TFN_VSTA_TSK    -0xE2   /* vsta_tsk   : Multi-Core Extension        */
#define TFN_VWUP_TSK    -0xE3   /* vwup_tsk   : Multi-Core Extension        */
#define TFN_VREL_WAI    -0xE4   /* vrel_wai   : Multi-Core Extension        */
#define TFN_VSIG_SEM    -0xE5   /* vsig_sem   : Multi-Core Extension        */
#define TFN_VPOL_SEM    -0xE6   /* vpol_sem   : Multi-Core Extension        */
#define TFN_VSET_FLG    -0xE7   /* vset_flg   : Multi-Core Extension        */
#define TFN_VCLR_FLG    -0xE8   /* vclr_flg   : Multi-Core Extension        */
#define TFN_VPOL_FLG    -0xE9   /* vpol_flg   : Multi-Core Extension        */
#define TFN_VPSND_DTQ   -0xEA   /* vpsnd_dtq  : Multi-Core Extension        */
#define TFN_VFSND_DTQ   -0xEB   /* vfsnd_dtq  : Multi-Core Extension        */
#define TFN_VPRCV_DTQ   -0xEC   /* vprcv_dtq  : Multi-Core Extension        */
#define TFN_VROT_RDQ    -0xED   /* vrot_rdq   : Multi-Core Extension        */


/*******************************************
        �g���[�X�@�\�p�����[�^
 *******************************************/

EXTERN  void _kernel_cside_tarce_1(void);
EXTERN  void _kernel_cside_tarce_2(void);
EXTERN  void _kernel_cside_tarce_3(void);
EXTERN  void _kernel_cside_tarce_4(void);
EXTERN  void _kernel_cside_tarce_5(void);
EXTERN  void _kernel_cside_tarce_6(void);
EXTERN  void _kernel_advice_tarce_1(void);
EXTERN  void _kernel_advice_tarce_2(void);
EXTERN  void _kernel_advice_tarce_3(void);
EXTERN  void _kernel_cubegear_task_trace(void);

#define TRACE_DISABLE               (FP)0

#define CSIDE_TASK_TRACE            (FP)_kernel_cside_tarce_1
#define CSIDE_SYSCALL_TRACE         (FP)_kernel_cside_tarce_2
#define CSIDE_TASK_SYSCALL_TRACE    (FP)_kernel_cside_tarce_3
#define CSIDE_TASK_INT_TRACE        (FP)_kernel_cside_tarce_4
#define CSIDE_FULL_TRACE            (FP)_kernel_cside_tarce_5
#define CSIDE_MEMBLK_TRACE          (FP)_kernel_cside_tarce_6
#define ADVICE_TASK_TRACE           (FP)_kernel_advice_tarce_1
#define ADVICE_TASK_SYSCALL_TRACE   (FP)_kernel_advice_tarce_2
#define CubeGEAR_TASK_TRACE         (FP)_kernel_cubegear_task_trace

/*******************************************
        �G�[�W�F���g�@�\�p�����[�^
 *******************************************/

EXTERN  void _kernel_cside_agent(void);

#define AGENT_DISABLE               (FP)0

#define CSIDE_AGENT                 (FP)_kernel_cside_agent


/*******************************************
        �R���t�B�O���[�V�����p�����[�^
 *******************************************/

EXTERN  void _kernel_zero_init_stack(INT *, SIZE, ID);
EXTERN  void _kernel_id_init_stack(INT *, SIZE, ID);

#define SYSTEM_IDLE             (FP)0
#define USER_IDLE(p1)           (FP)p1

#define STACK_NO_INIT           (FP)0
#define STACK_ZERO_INIT         (FP)&_kernel_zero_init_stack
#define STACK_ID_INIT           (FP)&_kernel_id_init_stack
#define STACK_USER_INIT(p1)     (FP)&(p1)

/***************************************
        �V�X�e���������X�^�[�g�֐�
 ***************************************/

EXTERN  ER      start_uC3(T_CSYS *sys, FP inihdr);

/***********************************
        �Ē�`�V�X�e���R�[��
 ***********************************/

EXTERN  ER      iact_tsk(ID tskid);
EXTERN  ER      slp_tsk(void);
EXTERN  ER      iwup_tsk(ID tskid);
EXTERN  ER      irel_wai(ID tskid);
EXTERN  ER      isig_sem(ID semid);
EXTERN  ER      wai_sem(ID semid);
EXTERN  ER      pol_sem(ID semid);
EXTERN  ER      iset_flg(ID flgid, FLGPTN setptn);
EXTERN  ER      wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
EXTERN  ER      pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
EXTERN  ER      ipsnd_dtq(ID dtqid, VP_INT data);
EXTERN  ER      psnd_dtq(ID dtqid, VP_INT data);
EXTERN  ER      snd_dtq(ID dtqid, VP_INT data);
EXTERN  ER      ifsnd_dtq(ID dtqid, VP_INT data);
EXTERN  ER      prcv_dtq(ID dtqid, VP_INT *p_data);
EXTERN  ER      rcv_dtq(ID dtqid, VP_INT *p_data);
EXTERN  ER      rcv_mbx(ID mbxid, T_MSG **ppk_msg);
EXTERN  ER      prcv_mbx(ID mbxid, T_MSG **ppk_msg);
EXTERN  ER      loc_mtx(ID mtxid);
EXTERN  ER      ploc_mtx(ID mtxid);
EXTERN  ER      snd_mbf(ID mbfid, VP msg, UINT msgsz);
EXTERN  ER      psnd_mbf(ID mbfid, VP msg, UINT msgsz);
EXTERN  ER_UINT rcv_mbf(ID mbfid, VP msg);
EXTERN  ER_UINT prcv_mbf(ID mbfid, VP msg);
EXTERN  ER_UINT cal_por(ID porid, RDVPTN calptn, VP msg, UINT cmsgsz);
EXTERN  ER_UINT acp_por(ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg);
EXTERN  ER_UINT pacp_por(ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg);
EXTERN  ER      get_mpf(ID mpfid, VP *p_blk);
EXTERN  ER      pget_mpf(ID mpfid, VP *p_blk);
EXTERN  ER      get_mpl(ID mplid, UINT blksz, VP *p_blk);
EXTERN  ER      pget_mpl(ID mplid, UINT blksz, VP *p_blk);
EXTERN  ER      irot_rdq(PRI tskpri);
EXTERN  ER      iget_tid(ID *p_tskid);
EXTERN  ER      iloc_cpu(void);
EXTERN  ER      iunl_cpu(void);

EXTERN  ER      ivact_tsk(ID coreid, ID tskid);
EXTERN  ER      ivwup_tsk(ID coreid, ID tskid);
EXTERN  ER      ivrel_wai(ID coreid, ID tskid);
EXTERN  ER      ivsig_sem(ID coreid, ID semid);
EXTERN  ER      ivset_flg(ID coreid, ID flgid, FLGPTN setptn);
EXTERN  ER      ivpsnd_dtq(ID coreid, ID dtqid, VP_INT data);
EXTERN  ER      ivfsnd_dtq(ID coreid, ID dtqid, VP_INT data);
EXTERN  ER      ivrot_rdq(ID coreid, PRI tskpri);
EXTERN  ER      ivsig_tim(ID coreid);

#define iact_tsk(p1)            (act_tsk(p1))
#define slp_tsk()               (tslp_tsk(TMO_FEVR))
#define iwup_tsk(p1)            (wup_tsk(p1))
#define irel_wai(p1)            (rel_wai(p1))
#define isig_sem(p1)            (sig_sem(p1))
#define pol_sem(p1)             (twai_sem(p1,TMO_POL))
#define wai_sem(p1)             (twai_sem(p1,TMO_FEVR))
#define iset_flg(p1,p2)         (set_flg(p1,p2))
#define pol_flg(p1,p2,p3,p4)    (twai_flg(p1,p2,p3,p4,TMO_POL))
#define wai_flg(p1,p2,p3,p4)    (twai_flg(p1,p2,p3,p4,TMO_FEVR))
#define ipsnd_dtq(p1,p2)        (tsnd_dtq(p1,p2,TMO_POL))
#define psnd_dtq(p1,p2)         (tsnd_dtq(p1,p2,TMO_POL))
#define snd_dtq(p1,p2)          (tsnd_dtq(p1,p2,TMO_FEVR))
#define ifsnd_dtq(p1,p2)        (fsnd_dtq(p1,p2))
#define prcv_dtq(p1,p2)         (trcv_dtq(p1,p2,TMO_POL))
#define rcv_dtq(p1,p2)          (trcv_dtq(p1,p2,TMO_FEVR))
#define prcv_mbx(p1,p2)         (trcv_mbx(p1,p2,TMO_POL))
#define rcv_mbx(p1,p2)          (trcv_mbx(p1,p2,TMO_FEVR))
#define ploc_mtx(p1)            (tloc_mtx(p1,TMO_POL))
#define loc_mtx(p1)             (tloc_mtx(p1,TMO_FEVR))
#define psnd_mbf(p1,p2,p3)      (tsnd_mbf(p1,p2,p3,TMO_POL))
#define snd_mbf(p1,p2,p3)       (tsnd_mbf(p1,p2,p3,TMO_FEVR))
#define prcv_mbf(p1,p2)         (trcv_mbf(p1,p2,TMO_POL))
#define rcv_mbf(p1,p2)          (trcv_mbf(p1,p2,TMO_FEVR))
#define cal_por(p1,p2,p3,p4)    (tcal_por(p1,p2,p3,p4,TMO_FEVR))
#define pacp_por(p1,p2,p3,p4)   (tacp_por(p1,p2,p3,p4,TMO_POL))
#define acp_por(p1,p2,p3,p4)    (tacp_por(p1,p2,p3,p4,TMO_FEVR))
#define pget_mpf(p1,p2)         (tget_mpf(p1,p2,TMO_POL))
#define get_mpf(p1,p2)          (tget_mpf(p1,p2,TMO_FEVR))
#define pget_mpl(p1,p2,p3)      (tget_mpl(p1,p2,p3,TMO_POL))
#define get_mpl(p1,p2,p3)       (tget_mpl(p1,p2,p3,TMO_FEVR))
#define irot_rdq(p1)            (rot_rdq(p1))
#define iget_tid(p1)            (get_tid(p1))
#define iloc_cpu()              (loc_cpu())
#define iunl_cpu()              (unl_cpu())

#define ivact_tsk(p1,p2)        (vact_tsk(p1,p2))
#define ivwup_tsk(p1,p2)        (vwup_tsk(p1,p2))
#define ivrel_wai(p1,p2)        (vrel_wai(p1,p2))
#define ivsig_sem(p1,p2)        (vsig_sem(p1,p2))
#define ivset_flg(p1,p2,p3)     (vset_flg(p1,p2,p3))
#define ivpsnd_dtq(p1,p2,p3)    (vpsnd_dtq(p1,p2,p3))
#define ivfsnd_dtq(p1,p2,p3)    (vfsnd_dtq(p1,p2,p3))
#define ivrot_rdq(p1,p2)        (vrot_rdq(p1,p2))


/***************************************
        �V�X�e���R�[���t�b�N�֐�
 ***************************************/

#ifndef DISABLE_HOOK
#ifndef _UC3SYS_H_
#define acre_tsk                    _kernel_acre_tsk
#define cre_tsk                     _kernel_cre_tsk
#define del_tsk                     _kernel_del_tsk
#define act_tsk                     _kernel_act_tsk
#define can_act                     _kernel_can_act
#define sta_tsk                     _kernel_sta_tsk
#define ext_tsk                     _kernel_ext_tsk
#define exd_tsk                     _kernel_exd_tsk
#define ter_tsk                     _kernel_ter_tsk
#define chg_pri                     _kernel_chg_pri
#define get_pri                     _kernel_get_pri
#define ref_tsk                     _kernel_ref_tsk
#define ref_tst                     _kernel_ref_tst
#define tslp_tsk                    _kernel_tslp_tsk
#define wup_tsk                     _kernel_wup_tsk
#define can_wup                     _kernel_can_wup
#define rel_wai                     _kernel_rel_wai
#define sus_tsk                     _kernel_sus_tsk
#define rsm_tsk                     _kernel_rsm_tsk
#define frsm_tsk                    _kernel_frsm_tsk
#define dly_tsk                     _kernel_dly_tsk
#define acre_sem                    _kernel_acre_sem
#define cre_sem                     _kernel_cre_sem
#define del_sem                     _kernel_del_sem
#define sig_sem                     _kernel_sig_sem
#define twai_sem                    _kernel_twai_sem
#define ref_sem                     _kernel_ref_sem
#define acre_flg                    _kernel_acre_flg
#define cre_flg                     _kernel_cre_flg
#define del_flg                     _kernel_del_flg
#define set_flg                     _kernel_set_flg
#define clr_flg                     _kernel_clr_flg
#define twai_flg                    _kernel_twai_flg
#define ref_flg                     _kernel_ref_flg
#define acre_dtq                    _kernel_acre_dtq
#define cre_dtq                     _kernel_cre_dtq
#define del_dtq                     _kernel_del_dtq
#define tsnd_dtq                    _kernel_tsnd_dtq
#define fsnd_dtq                    _kernel_fsnd_dtq
#define trcv_dtq                    _kernel_trcv_dtq
#define ref_dtq                     _kernel_ref_dtq
#define acre_mbx                    _kernel_acre_mbx
#define cre_mbx                     _kernel_cre_mbx
#define del_mbx                     _kernel_del_mbx
#define snd_mbx                     _kernel_snd_mbx
#define trcv_mbx                    _kernel_trcv_mbx
#define ref_mbx                     _kernel_ref_mbx
#define acre_mtx                    _kernel_acre_mtx
#define cre_mtx                     _kernel_cre_mtx
#define del_mtx                     _kernel_del_mtx
#define unl_mtx                     _kernel_unl_mtx
#define tloc_mtx                    _kernel_tloc_mtx
#define ref_mtx                     _kernel_ref_mtx
#define acre_mbf                    _kernel_acre_mbf
#define cre_mbf                     _kernel_cre_mbf
#define del_mbf                     _kernel_del_mbf
#define tsnd_mbf                    _kernel_tsnd_mbf
#define trcv_mbf                    _kernel_trcv_mbf
#define ref_mbf                     _kernel_ref_mbf
#define acre_por                    _kernel_acre_por
#define cre_por                     _kernel_cre_por
#define del_por                     _kernel_del_por
#define tcal_por                    _kernel_tcal_por
#define tacp_por                    _kernel_tacp_por
#define fwd_por                     _kernel_fwd_por
#define rpl_rdv                     _kernel_rpl_rdv
#define ref_por                     _kernel_ref_por
#define ref_rdv                     _kernel_ref_rdv
#define acre_mpf                    _kernel_acre_mpf
#define cre_mpf                     _kernel_cre_mpf
#define del_mpf                     _kernel_del_mpf
#define tget_mpf                    _kernel_tget_mpf
#define rel_mpf                     _kernel_rel_mpf
#define ref_mpf                     _kernel_ref_mpf
#define acre_mpl                    _kernel_acre_mpl
#define cre_mpl                     _kernel_cre_mpl
#define del_mpl                     _kernel_del_mpl
#define tget_mpl                    _kernel_tget_mpl
#define rel_mpl                     _kernel_rel_mpl
#define ref_mpl                     _kernel_ref_mpl
#define set_tim                     _kernel_set_tim
#define get_tim                     _kernel_get_tim
#define acre_cyc                    _kernel_acre_cyc
#define cre_cyc                     _kernel_cre_cyc
#define del_cyc                     _kernel_del_cyc
#define sta_cyc                     _kernel_sta_cyc
#define stp_cyc                     _kernel_stp_cyc
#define ref_cyc                     _kernel_ref_cyc
#define acre_alm                    _kernel_acre_alm
#define cre_alm                     _kernel_cre_alm
#define del_alm                     _kernel_del_alm
#define sta_alm                     _kernel_sta_alm
#define stp_alm                     _kernel_stp_alm
#define ref_alm                     _kernel_ref_alm
#define def_ovr                     _kernel_def_ovr
#define sta_ovr                     _kernel_sta_ovr
#define stp_ovr                     _kernel_stp_ovr
#define ref_ovr                     _kernel_ref_ovr
#define rot_rdq                     _kernel_rot_rdq
#define get_tid                     _kernel_get_tid
#define loc_cpu                     _kernel_loc_cpu
#define unl_cpu                     _kernel_unl_cpu
#define dis_dsp                     _kernel_dis_dsp
#define ena_dsp                     _kernel_ena_dsp
#define sns_ctx                     _kernel_sns_ctx
#define sns_loc                     _kernel_sns_loc
#define sns_dsp                     _kernel_sns_dsp
#define sns_dpn                     _kernel_sns_dpn
#define ref_sys                     _kernel_ref_sys
#define def_inh                     _kernel_def_inh
#define acre_isr                    _kernel_acre_isr
#define cre_isr                     _kernel_cre_isr
#define del_isr                     _kernel_del_isr
#define ref_isr                     _kernel_ref_isr
#define chg_ims                     _kernel_chg_ims
#define get_ims                     _kernel_get_ims
#define ena_int                     _kernel_ena_int
#define dis_int                     _kernel_dis_int
#define ref_cfg                     _kernel_ref_cfg
#define ref_ver                     _kernel_ref_ver
#define vact_tsk                    _kernel_vact_tsk
#define vsta_tsk                    _kernel_vsta_tsk
#define vwup_tsk                    _kernel_vwup_tsk
#define vrel_wai                    _kernel_vrel_wai
#define vsig_sem                    _kernel_vsig_sem
#define vpol_sem                    _kernel_vpol_sem
#define vset_flg                    _kernel_vset_flg
#define vclr_flg                    _kernel_vclr_flg
#define vpol_flg                    _kernel_vpol_flg
#define vpsnd_dtq                   _kernel_vpsnd_dtq
#define vfsnd_dtq                   _kernel_vfsnd_dtq
#define vprcv_dtq                   _kernel_vprcv_dtq
#define vrot_rdq                    _kernel_vrot_rdq

#endif
#endif

/* �^�X�N�Ǘ��@�\ */

EXTERN  ER_ID   acre_tsk(T_CTSK *pk_ctsk);
EXTERN  ER      cre_tsk(ID tskid, T_CTSK *pk_ctsk);
EXTERN  ER      del_tsk(ID tskid);
EXTERN  ER      act_tsk(ID tskid);
EXTERN  ER_UINT can_act(ID tskid);
EXTERN  ER      sta_tsk(ID tskid, VP_INT stacd);
EXTERN  void    ext_tsk(void);
EXTERN  void    exd_tsk(void);
EXTERN  ER      ter_tsk(ID tskid);
EXTERN  ER      chg_pri(ID tskid, PRI tskpri);
EXTERN  ER      get_pri(ID tskid, PRI *p_tskpri);
EXTERN  ER      ref_tsk(ID tskid, T_RTSK *pk_rtsk);
EXTERN  ER      ref_tst(ID tskid, T_RTST *pk_rtst);

/* �^�X�N�t�������@�\ */

EXTERN  ER      tslp_tsk(TMO timout);
EXTERN  ER      wup_tsk(ID tskid);
EXTERN  ER_UINT can_wup(ID tskid);
EXTERN  ER      rel_wai(ID tskid);
EXTERN  ER      sus_tsk(ID tskid);
EXTERN  ER      rsm_tsk(ID tskid);
EXTERN  ER      frsm_tsk(ID tskid);
EXTERN  ER      dly_tsk(RELTIM dlytim);

/* �^�X�N��O�����@�\ */

EXTERN  ER      def_tex(ID tskid, T_DTEX *pk_dtex);
EXTERN  ER      ras_tex(ID tskid, TEXPTN rasptn);
EXTERN  ER      iras_tex(ID tskid, TEXPTN rasptn);
EXTERN  ER      dis_tex(void);
EXTERN  ER      ena_tex(void);
EXTERN  BOOL    sns_tex(void);
EXTERN  ER      ref_tex(ID tskid, T_RTEX *pk_rtex);

/* �����E�ʐM�@�\�i�Z�}�t�H�j */

EXTERN  ER_ID   acre_sem(T_CSEM *pk_csem);
EXTERN  ER      cre_sem(ID semid, T_CSEM *pk_csem);
EXTERN  ER      del_sem(ID semid);
EXTERN  ER      sig_sem(ID semid);
EXTERN  ER      twai_sem(ID semid, TMO tmout);
EXTERN  ER      ref_sem(ID semid, T_RSEM *pk_rsem);

/* �����E�ʐM�@�\�i�C�x���g�t���O�j */

EXTERN  ER_ID   acre_flg(T_CFLG *pk_cflg);
EXTERN  ER      cre_flg(ID flgid, T_CFLG *pk_cflg);
EXTERN  ER      del_flg(ID flgid);
EXTERN  ER      set_flg(ID flgid, FLGPTN setptn);
EXTERN  ER      clr_flg(ID flgid, FLGPTN clrptn);
EXTERN  ER      twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);
EXTERN  ER      ref_flg(ID flgid, T_RFLG *pk_rflg);

/* �����E�ʐM�@�\�i�f�[�^�L���[�j */

EXTERN  ER_ID   acre_dtq(T_CDTQ *pk_cdtq);
EXTERN  ER      cre_dtq(ID dtqid, T_CDTQ *pk_cdtq);
EXTERN  ER      del_dtq(ID dtqid);
EXTERN  ER      tsnd_dtq(ID dtqid, VP_INT data, TMO tmout);
EXTERN  ER      fsnd_dtq(ID dtqid, VP_INT data);
EXTERN  ER      trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout);
EXTERN  ER      ref_dtq(ID dtqid, T_RDTQ *pk_rdtq);

/* �����E�ʐM�@�\�i���[���{�b�N�X�j */

EXTERN  ER_ID   acre_mbx(T_CMBX *pk_cmbx);
EXTERN  ER      cre_mbx(ID mbxid, T_CMBX *pk_cmbx);
EXTERN  ER      del_mbx(ID mbxid);
EXTERN  ER      snd_mbx(ID mbxid, T_MSG *pk_msg);
EXTERN  ER      trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);
EXTERN  ER      ref_mbx(ID mbxid, T_RMBX *pk_rmbx);

/* �g�������E�ʐM�@�\�i�~���[�e�b�N�X�j */

EXTERN  ER_ID   acre_mtx(T_CMTX *pk_cmtx);
EXTERN  ER      cre_mtx(ID mtxid, T_CMTX *pk_cmtx);
EXTERN  ER      del_mtx(ID mtxid);
EXTERN  ER      unl_mtx(ID mtxid);
EXTERN  ER      tloc_mtx(ID mtxid, TMO tmout);
EXTERN  ER      ref_mtx(ID mtxid, T_RMTX *pk_rmtx);

/* �g�������E�ʐM�@�\�i���b�Z�[�W�o�b�t�@�j */

EXTERN  ER_ID   acre_mbf(T_CMBF *pk_cmbf);
EXTERN  ER      cre_mbf(ID mbfid, T_CMBF *pk_cmbf);
EXTERN  ER      del_mbf(ID mbfid);
EXTERN  ER      tsnd_mbf(ID mbfid, VP msg, UINT msgsz, TMO tmout);
EXTERN  ER_UINT trcv_mbf(ID mbfid, VP msg, TMO tmout);
EXTERN  ER      ref_mbf(ID mbfid, T_RMBF *pk_rmbf);

/* �g�������E�ʐM�@�\�i�����f�u�j */

EXTERN  ER_ID   acre_por(T_CPOR *pk_cpor);
EXTERN  ER      cre_por(ID porid, T_CPOR *pk_cpor);
EXTERN  ER      del_por(ID porid);
EXTERN  ER_UINT tcal_por(ID porid, RDVPTN calptn, VP msg, UINT cmsgsz, TMO tmout);
EXTERN  ER_UINT tacp_por(ID porid, RDVPTN acpptn, RDVNO *p_rdvno, VP msg, TMO tmout);
EXTERN  ER      fwd_por(ID porid, RDVPTN calptn, RDVNO rdvno, VP msg, UINT cmsgsz);
EXTERN  ER      rpl_rdv(RDVNO rdvno, VP msg, UINT msgsz);
EXTERN  ER      ref_por(ID porid, T_RPOR *pk_rpor);
EXTERN  ER      ref_rdv(RDVNO rdvno, T_RRDV *pk_rrdv);

/* �������v�[���Ǘ��@�\�i�Œ蒷�������v�[���j */

EXTERN  ER_ID   acre_mpf(T_CMPF *pk_cmpf);
EXTERN  ER      cre_mpf(ID mpfid, T_CMPF *pk_cmpf);
EXTERN  ER      del_mpf(ID mpfid);
EXTERN  ER      tget_mpf(ID mpfid, VP *p_blk, TMO tmout);
EXTERN  ER      rel_mpf(ID mpfid, VP p_blk);
EXTERN  ER      ref_mpf(ID mpfid, T_RMPF *pk_rmpf);

/* �������v�[���Ǘ��@�\�i�ϒ��������v�[���j */

EXTERN  ER_ID   acre_mpl(T_CMPL *pk_cmpl);
EXTERN  ER      cre_mpl(ID mplid, T_CMPL *pk_cmpl);
EXTERN  ER      del_mpl(ID mplid);
EXTERN  ER      tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
EXTERN  ER      rel_mpl(ID mplid, VP p_blk);
EXTERN  ER      ref_mpl(ID mplid, T_RMPL *pk_rmpl);

/* ���ԊǗ��@�\�i�V�X�e�������Ǘ��j */

EXTERN  ER      set_tim(SYSTIM *p_systim);
EXTERN  ER      get_tim(SYSTIM *p_systim);
EXTERN  ER      isig_tim(void);
EXTERN  UW      vget_tms(void);

/* ���ԊǗ��@�\�i�����n���h���j */

EXTERN  ER_ID   acre_cyc(T_CCYC *pk_ccyc);
EXTERN  ER      cre_cyc(ID cycid, T_CCYC *pk_ccyc);
EXTERN  ER      del_cyc(ID cycid);
EXTERN  ER      sta_cyc(ID cycid);
EXTERN  ER      stp_cyc(ID cycid);
EXTERN  ER      ref_cyc(ID cycid, T_RCYC *pk_rcyc);

/* ���ԊǗ��@�\�i�A���[���n���h���j */

EXTERN  ER_ID   acre_alm(T_CALM *pk_calm);
EXTERN  ER      cre_alm(ID almid, T_CALM *pk_calm);
EXTERN  ER      del_alm(ID almid);
EXTERN  ER      sta_alm(ID almid, RELTIM almtim);
EXTERN  ER      stp_alm(ID almid);
EXTERN  ER      ref_alm(ID almid, T_RALM *pk_ralm);

/* ���ԊǗ��@�\�i�I�[�o�����n���h���j */

EXTERN  ER      def_ovr(T_DOVR *pk_dovr);
EXTERN  ER      ivsig_ovr(void);
EXTERN  ER      sta_ovr(ID tskid, OVRTIM ovrtim);
EXTERN  ER      stp_ovr(ID tskid);
EXTERN  ER      ref_ovr(ID tskid, T_ROVR *pk_rovr);

/* �V�X�e����ԊǗ��@�\ */

EXTERN  ER      rot_rdq(PRI tskpri);
EXTERN  ER      get_tid(ID *p_tskid);
EXTERN  ER      loc_cpu(void);
EXTERN  ER      unl_cpu(void);
EXTERN  ER      dis_dsp(void);
EXTERN  ER      ena_dsp(void);
EXTERN  BOOL    sns_ctx(void);
EXTERN  BOOL    sns_loc(void);
EXTERN  BOOL    sns_dsp(void);
EXTERN  BOOL    sns_dpn(void);
EXTERN  ER      ref_sys(T_RSYS *pk_rsys);

/* �����݊Ǘ��@�\ */

EXTERN  ER      def_inh(INHNO inhno, T_DINH *pk_dinh);
EXTERN  ER_ID   acre_isr(T_CISR *);
EXTERN  ER      cre_isr(ID isrid, T_CISR *pk_cisr);
EXTERN  ER      del_isr(ID isrid);
EXTERN  ER      ref_isr(ID isrid, T_RISR *pk_risr);
EXTERN  ER      chg_ims(IMASK imask);
EXTERN  ER      get_ims(IMASK *p_imask);
EXTERN  ER      ena_int(INTNO intno);
EXTERN  ER      dis_int(INTNO intno);

/* �f�o�C�X�Ǘ��@�\ */

EXTERN  ER      vdef_dev(ID devid, T_CDEV *pk_cdev);
EXTERN  ER      vctr_dev(ID devid, ID funcid, VP ctrdev);

/* �V�X�e���\���Ǘ��@�\ */

EXTERN  ER      def_exc(EXCNO excno, T_DEXC *pk_dexc);
EXTERN  ER      vdef_err(ATR atr, FP func);
EXTERN  ER      ref_cfg(T_RCFG *pk_rcfg);
EXTERN  ER      ref_ver(T_RVER *pk_rver);

/* �}���`�R�A�g���Ǘ��@�\ */

EXTERN  ER      ivsig_tim(ID coreid);
EXTERN  ER      vact_tsk(ID coreid, ID tskid);
EXTERN  ER      vsta_tsk(ID coreid, ID tskid, VP_INT stacd);
EXTERN  ER      vwup_tsk(ID coreid, ID tskid);
EXTERN  ER      vrel_wai(ID coreid, ID tskid);
EXTERN  ER      vsig_sem(ID coreid, ID semid);
EXTERN  ER      vpol_sem(ID coreid, ID semid);
EXTERN  ER      vset_flg(ID coreid, ID flgid, FLGPTN setptn);
EXTERN  ER      vclr_flg(ID coreid, ID flgid, FLGPTN clrptn);
EXTERN  ER      vpol_flg(ID coreid, ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
EXTERN  ER      vpsnd_dtq(ID coreid, ID dtqid, VP_INT data);
EXTERN  ER      vfsnd_dtq(ID coreid, ID dtqid, VP_INT data);
EXTERN  ER      vprcv_dtq(ID coreid, ID dtqid, VP_INT *p_data);
EXTERN  ER      vrot_rdq(ID coreid, PRI tskpri);

#ifdef __cplusplus
}
#endif

#endif  /* _KERNEL_H_ */
