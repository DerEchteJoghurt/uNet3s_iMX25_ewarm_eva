/***********************************************************************
    Micro C Cube Standard, Multi-Core Extension
    Synchronization and Asynchronization System Call

    Copyright (c)  2013, eForce Co., Ltd. All rights reserved.

    Version Information
            2009.09.28: Created.
            2013.02.19: Added the spin-lock API.
************************************************************************/

#ifndef _UC3MCEXT_H_
#define _UC3MCEXT_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifndef ASYNCBUF_NUM
#define ASYNCBUF_NUM    1
#endif
#ifndef CORE_NUM
#define CORE_NUM        1
#endif

typedef struct t_cmdbuf {
    FN          func_n;
    ID          ctexid;
    UW          seq_no;
    FP          func;
    FP          ret_pc;
    VP_INT      para[7];
} T_CMDBUF;

typedef struct t_asynctbl {
    UW          lock;
    UW          cnt;
    UW          ptr;
    UW          dummy;
    T_CMDBUF    cmdbuf[ASYNCBUF_NUM];
} T_ASYNCTBL;

typedef struct t_synctbl {
    UW          lock;
    UW          fin;
    ER          error;
    VP_INT      ret_v;
    T_CMDBUF    cmdbuf;
} T_SYNCTBL;

typedef struct t_seq_no {
    UW          lock;
    UW          no;
} T_SEQ_NO;

typedef struct t_mcore_ext {
    UB          ready[4];
    UINT        core_max;
    UINT        async_max;
    T_SEQ_NO    seq_no;
    T_ASYNCTBL  *asynctbl[4];
    T_SYNCTBL   *synctbl[4];
} T_MCORE_EXT;

extern T_ASYNCTBL _kernel_asynctbl[CORE_NUM];
extern T_SYNCTBL _kernel_synctbl[CORE_NUM];
extern T_MCORE_EXT _kernel_mcore_ext;
extern void _kernel_async_sync_event_set(ID coreid);
extern void _kernel_async_sync_event_clear(void);
extern UW _kernel_get_seqno(void);
extern ER _kernel_async_sys(FN func_n, ID coreid, UW seq_no, FP ret_pc, FP func, VP_INT *para);
extern BOOL _kernel_async_sys_1(T_SSB *par, BOOL retcd);
extern ER _kernel_sync_sys(FN func_n, ID coreid, UW seq_no, FP ret_pc, FP func, VP_INT *para);
extern BOOL _kernel_sync_sys_1(T_SSB *par, BOOL retcd);
extern void _kernel_systrace(T_CMDBUF *buffer, UW para_n);
extern void _kernel_rettrace(T_CMDBUF *buffer, ER ercd);
extern void _kernel_error_handler(FN func_code, ER error_code, VP_INT *para);
extern void _kernel_spin_lock(UW *flag);
extern ID _kernel_spin_unlock(UW *flag);
extern ID _kernel_spin_lock_test(UW *flag);
extern ID _kernel_spin_locked_test(UW *flag);

#ifdef __cplusplus
}
#endif
#endif /* _UC3MCEXT_H_ */
