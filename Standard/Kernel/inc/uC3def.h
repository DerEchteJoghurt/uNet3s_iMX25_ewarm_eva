/***************************************************************************
    Micro C Cube Standard, KERNEL
    Kernel internal definitions

    Copyright (c)  2008-2010, eForce Co.,Ltd.  All rights reserved.

    Version Information
            2008.07.29: Created
            2009.03.13: Moved version information.
            2009.03.31: Corrected TimeEvent Handler.
            2009.07.20: Modified the initializing of object queue.
            2009.09.28: Modified for the erro-code handler.
            2010.12.20: Modified for the system contorol block.
 ***************************************************************************/

#ifndef _UC3DEF_H_
#define _UC3DEF_H_

typedef struct t_wtcb {
    struct t_wtcb   *next;
    struct t_wtcb   *prev;
} T_WTCB;

typedef union t_tpri {
    T_WTCB      *mwait;
    T_WTCB      wait;
} T_TPRI;

typedef struct t_inf {
    UH          limit;
    UH          usedc;
} T_INF;

typedef struct t_rinf {
    UH          limit;
    UH          nextt;
} T_RINF;

typedef struct t_mem {
    struct t_mem *next;
    SIZE        size;
} T_MEM;

typedef struct t_csts {
    UB          catr;
    UB          oatr;
    UB          msts;
    UB          wsts;
} T_CSTS;

typedef struct t_ssb {
    VP_INT      p1;
    VP_INT      p2;
    struct t_ssb *snext;
    struct t_ssb *sprev;
    T_CSTS      stat;
    FP          sysfunc;
    VP_INT      p3;
    VP_INT      p4;
    VP_INT      p5;
    VP_INT      p6;
} T_SSB;

typedef struct t_cyc {
    FP          cychdr;
    VP_INT      exinf;
    T_SSB       *snext;
    T_SSB       *sprev;
    T_CSTS      stat;
    FP          sysfunc;
    SYSTIM      stime;
    RELTIM      cyctim;
    ID          cycid;
    VB const    *name;
} T_CYC;

typedef union t_qcyc {
    T_CYC       **cyc;
    T_INF       *inf;
} T_QCYC;

typedef struct t_alm {
    FP          almhdr;
    VP_INT      exinf;
    T_SSB       *snext;
    T_SSB       *sprev;
    T_CSTS      stat;
    FP          sysfunc;
    SYSTIM      stime;
    ID          almid;
    VB const    *name;
} T_ALM;

typedef union t_qalm {
    T_ALM       **alm;
    T_INF       *inf;
} T_QALM;

typedef struct t_ovr {
    FP          ovrhdr;
    UH          ovratr;
} T_OVR;

typedef struct t_flg {
    T_TPRI      que;
    FLGPTN      flgptn;
    UH          flgatr;
    UH          flgid;
    VB const    *name;
} T_FLG;

typedef union t_qflg {
    T_FLG       **flg;
    T_INF       *inf;
} T_QFLG;

typedef struct t_sem {
    T_TPRI      que;
    UH          sematr;
    UH          semid;
    UH          semcnt;
    UH          maxsem;
    VB const    *name;
} T_SEM;

typedef union t_qsem {
    T_SEM       **sem;
    T_INF       *inf;
} T_QSEM;

typedef struct t_dtq {
    T_TPRI      sque;
    T_WTCB      que;
    UH          dtqatr;
    UH          dtqid;
    VP_INT      *dtq;
    UH          dtqcnt;
    UH          cnt;
    UH          put;
    VB const    *name;
} T_DTQ;

typedef union t_qdtq {
    T_DTQ       **dtq;
    T_INF       *inf;
} T_QDTQ;

typedef struct t_mhd {
    T_MSG       *top;
    T_MSG       *btm;
} T_MHD;

typedef struct t_mmhd {
    T_MHD       *mque;
    PRI         maxmpri;
} T_MMHD;

typedef union t_mpri {
    T_MHD       sngl;
    T_MMHD      mult;
} T_MPRI;

typedef struct t_mbx {
    T_TPRI      que;
    UH          mbxatr;
    UH          mbxid;
    T_MPRI      mprihd;
    VB const    *name;
} T_MBX;

typedef union t_qmbx {
    T_MBX       **mbx;
    T_INF       *inf;
} T_QMBX;

typedef struct t_mtx {
    T_TPRI      que;
    struct t_mtx *locked;
    UH          mtxatr;
    UH          mtxid;
    UH          tskid;
    UH          pri;
    VB const    *name;
} T_MTX;

typedef union t_qmtx {
    T_MTX       **mtx;
    T_INF       *inf;
} T_QMTX;

typedef struct t_mbf {
    T_TPRI      sque;
    T_WTCB      wque;
    UH          mbfatr;
    UH          mbfid;
    UH          maxmsz;
    UH          cnt;
    SIZE        mbfsz;
    UB          *mbf;
    UW          putp;
    UW          getp;
    SIZE        frsz;
    VB const    *name;
} T_MBF;

typedef union t_qmbf {
    T_MBF       **mbf;
    T_INF       *inf;
} T_QMBF;

typedef struct t_por {
    T_TPRI      cque;
    T_WTCB      aque;
    UH          poratr;
    UH          porid;
    UH          maxcmsz;
    UH          maxrmsz;
    VB const    *name;
} T_POR;

typedef union t_qpor {
    T_POR       **por;
    T_INF       *inf;
} T_QPOR;

typedef struct t_mpl {
    T_TPRI      que;
    T_MEM       *top;
    UH          mplatr;
    UH          mplid;
    SIZE        mplsz;
    SIZE        allsz;
    VP          mpl;
    VP          allad;
    VB const    *name;
} T_MPL;

typedef union t_qmpl {
    T_MPL       **mpl;
    T_INF       *inf;
} T_QMPL;

typedef struct t_mpf {
    T_TPRI      que;
    UH          mpfatr;
    UH          mpfid;
    UW          blkcnt;
    UW          blksz;
    T_MEM       *top;
    VP          allad;
    SIZE        allsz;
    VB const    *name;
} T_MPF;

typedef union t_qmpf {
    T_MPF       **mpf;
    T_INF       *inf;
} T_QMPF;

typedef struct t_isr {
    struct t_isr *next;
    struct t_isr *prev;
    UH          isratr;
    UH          intno;
    FP          isr;
    VP_INT      exinf;
} T_ISR;

typedef union t_qisr {
    T_ISR       **isr;
    T_INF       *inf;
} T_QISR;

typedef struct t_dev {
    VP          ctrblk;
    FP          devhdr;
    VB const    *name;
} T_DEV;

typedef union t_qdev {
    T_DEV       **dev;
    T_INF       *inf;
} T_QDEV;

typedef union t_qrdq {
    T_WTCB      *rdq;
    T_RINF      *inf;
} T_QRDQ;

typedef struct t_tcb {
    T_WTCB      wtcb;
    T_SSB       *snext;
    T_SSB       *sprev;
    T_CSTS      stat;
    FP          sysfunc;
    SYSTIM      stime;
    UB          ovrsts;
    UB          texsts;
    UH          tskid;
    UH          ovrtim;
    UH          wup;
    UH          sus;
    UH          act;
    UH          cpri;
    UH          bpri;
    UH          ipri;
    UH          wobjid;
    T_REG       *sp;
    FP          task;
    T_REG       *stk;
    SIZE        stksz;
    FP          texrtn;
    TEXPTN      texptn;
    VP_INT      p1;
    VP_INT      p2;
    T_REG       pc;
    T_WTCB      *wque;
    VP_INT      exinf;
    T_MTX       *lockmtx;
    VP_INT      p3;
    VP_INT      p4;
    VP_INT      p5;
    VP_INT      p6;
    VB const    *name;
} T_TCB;

typedef union t_qtcb {
    T_TCB       **tcb;
    T_INF       *inf;
} T_QTCB;

typedef struct t_systbl {
    union {
        struct {
            UB  dsp;
            UB  ims;
            UB  dlock;
            UB  cims;
        } s;
        UW      dspint;
    } stat;
    UB          iims;
    UB          icnt;
    UB          rdsp;
    UB          dummy;
    T_SSB       *snext;
    UH          tid;
    UH          pri;
    UH          ssb_cnt;
    UH          ssb_min;
    UH          tick;
    UH          rdmcnt;
    T_SSB       *ssb_top;
    T_SSB       *ssb_btm;
    SYSTIM      systim;
    SYSTIM      diftim;
    T_SSB       *cssb;
    T_TCB       *ctcb;
    T_QRDQ      qrdq;
    T_SSB       *ssb_free;
    T_MEM       *free_sys;
    T_MEM       *free_stk;
    T_MEM       *free_mpl;
    T_OVR       *ovr;
    T_QTCB      qtcb;
    T_QSEM      qsem;
    T_QFLG      qflg;
    T_QDTQ      qdtq;
    T_QMBX      qmbx;
    T_QMTX      qmtx;
    T_QMBF      qmbf;
    T_QPOR      qpor;
    T_QMPF      qmpf;
    T_QMPL      qmpl;
    T_QALM      qalm;
    T_QCYC      qcyc;
    T_QISR      qisr;
    T_QDEV      qdev;
    FP          ctrtim;
    FP          sysidl;
    FP          inistk;
    FP          ctxtrace0;
    FP          ctxtrace1;
    FP          ctxtrace2;
    FP          ctxtrace3;
    FP          systrace;
    FP          rettrace;
    T_CYC       *agentmng;
    UW          ctxid_c;
    UW          ctxid_s;
    UW          agenttim;
    FP          mplfunc;
    FP          mbffunc;
    FP          mtxfunc;
    FP          umtxfunc;
    UW          atrhandler;
    FP          errhandler;
    FP          ctxtrace4;
    CPU_DEPENDEND
} T_SYSTBL;

/* common function definitions */

#ifdef _UC3KRNCM1_C_
ER _kernel_relmem(T_MEM **base, T_MEM *blk, SIZE sz);
ER _kernel_ini_objque(void **que, UINT idmax, UINT limit);
PRI _kernel_cgetpri(T_TCB *tcb);
void _kernel_inique(T_WTCB *que, ID max);
void _kernel_deqtcb(T_WTCB *wtcb);
void _kernel_enqtcb(T_WTCB *bwtcb, T_WTCB *wtcb);
void _kernel_enqrdq(T_TCB *tcb);
void _kernel_getsize(T_MEM **base, SIZE *size, SIZE *maxsz);
T_MEM *_kernel_getmem(T_MEM **base, SIZE sz);
T_TCB *_kernel_gettcb(T_WTCB *wtcb, PRI primax);
#else
extern ER _kernel_relmem(T_MEM **base, T_MEM *blk, SIZE sz);
extern ER _kernel_ini_objque(void **que, UINT idmax);
extern PRI _kernel_cgetpri(T_TCB *tcb);
extern void _kernel_inique(T_WTCB *que, ID max);
extern void _kernel_deqtcb(T_WTCB *wtcb);
extern void _kernel_enqtcb(T_WTCB *bwtcb, T_WTCB *wtcb);
extern void _kernel_enqrdq(T_TCB *tcb);
extern void _kernel_getsize(T_MEM **base, SIZE *size, SIZE *maxsz);
extern T_MEM *_kernel_getmem(T_MEM **base, SIZE sz);
extern T_TCB *_kernel_gettcb(T_WTCB *wtcb, PRI primax);
#endif

#ifdef _UC3CHGPRI_C_
void _kernel_chgpri(T_TCB *tcb, PRI tskpri);
#else
extern void _kernel_chgpri(T_TCB *tcb, PRI tskpri);
#endif

#ifdef _UC3CRETSK_C_
ER _kernel_acttsk(T_TCB *tcb);
BOOL _kernel_acttsk_1(T_SSB *par, BOOL retcd);
void _kernel_statsk_2(T_TCB *tcb, VP_INT stacd);
#else
extern ER _kernel_acttsk(T_TCB *tcb);
extern BOOL _kernel_acttsk_1(T_SSB *par, BOOL retcd);
extern void _kernel_statsk_2(T_TCB *tcb, VP_INT stacd);
#endif

#ifdef _UC3CALPOR_C_
BOOL _kernel_calpor(T_POR *por, RDVPTN calptn, UB *from_msg, UINT cmsgsz, ID tskid);
#else
extern BOOL _kernel_calpor(T_POR *por, RDVPTN calptn, UB *from_msg, UINT cmsgsz, ID tskid);
#endif

#ifdef _UC3SIGTIM_C_
void _kernel_enqtim(T_TCB *tcb, SYSTIM *systim, TMO timout);
#else
extern void _kernel_enqtim(T_TCB *tcb, SYSTIM *systim, TMO timout);
#endif

#ifdef _UC3KRNCM2_C_
void _kernel_blktrace(UW ctxid, FN fncode, ID objid, VP blk, SIZE blksz);
void _kernel_timfunc(T_CSTS stat, UH objid, FP timfunc, VP_INT exinf);
void _kernel_ovrfunc(ATR atr, FP ovrfunc, T_TCB *tcb);
void _kernel_setctx(T_TCB *tcb, VP_INT stacd);
void _kernel_iniint(void);
void _kernel_entisr(T_ISR *isr);
void _kernel_agentfunc(FP agentfunc);
BOOL _kernel_inihdr(T_SSB *ssb);
BOOL _kernel_snsloc(void);
IMASK _kernel_setims(IMASK imask);
IMASK _kernel_getims(void);
UW _kernel_micro_systim(void);
#else
extern void _kernel_blktrace(UW ctxid, FN fncode, ID objid, VP blk, SIZE blksz);
extern void _kernel_timfunc(T_CSTS stat, UH objid, FP timfunc, VP_INT exinf);
extern void _kernel_ovrfunc(ATR atr, FP ovrfunc, T_TCB *tcb);
extern void _kernel_setctx(T_TCB *tcb, VP_INT stacd);
extern void _kernel_iniint(void);
extern void _kernel_entisr(T_ISR *isr);
extern void _kernel_agentfunc(FP agentfunc);
extern BOOL _kernel_inihdr(T_SSB *ssb);
extern BOOL _kernel_snsloc(void);
extern IMASK _kernel_setims(IMASK imask);
extern IMASK _kernel_getims(void);
extern UW _kernel_micro_systim(void);
#endif

#ifdef _UC3KRNCM3_C_
#else
extern T_SYSTBL _kernel_systbl;
extern T_RVER const _kernel_ver;
#endif

extern void int_abort(void);

extern T_SSB *_kernel_getssb(void);
extern void _kernel_entint(void);
extern void _kernel_entsys(BOOL);
extern void _kernel_relrun(void);
extern void _kernel_inthdr(void);
extern void _kernel_enqssb(T_SSB *);
extern void _kernel_dispatch(void);
extern void _kernel_lock(void);
extern void _kernel_unlock(void);

/* atribute definitions */

#define TA_TSK      0x00u
#define TA_IDL      0x10u
#define TA_SSB      0x20u
#define TA_INI      0x30u
#define TA_CYC      0x40u
#define TA_OVR      0x50u
#define TA_EXC      0x60u
#define TA_AGT      0x70u
#define TA_ALM      0x80u

#define TA_SYS      0x00u
#define TA_INT      0x01u
#define TA_STA      0x02u

#define TA_USTK     0x08u

#define TTS_FIFO    0x20u
#define TTS_TMR     0x80u

#define TA_UBUF     0x80u

#define TALM_RST    0x02u
#define TALM_PND    0x10u
#define TCYC_PND    0x10u

#define TS_SLP      1
#define TS_DLY      2
#define TS_RDV      3
#define TS_SEM      4
#define TS_FLG      5
#define TS_SDTQ     6
#define TS_RDTQ     7
#define TS_MBX      8
#define TS_MTX      9
#define TS_SMBF     10
#define TS_RMBF     11
#define TS_CAL      12
#define TS_ACP      13
#define TS_MPF      14
#define TS_MPL      15

#endif
