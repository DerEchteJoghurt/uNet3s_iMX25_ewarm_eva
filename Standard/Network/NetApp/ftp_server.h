/***************************************************************************
    MICRO C CUBE / COMPACT/STANDARD, NETWORK Application
    FTP Server
    Copyright (c) 2014, eForce Co., Ltd. All rights reserved.

    Version Information  2014.03.18: Created
 ***************************************************************************/

#ifndef FTP_SERVER_H
#define FTP_SERVER_H

/* Configuration */
#include "ftp_server_cfg.h"

#if !defined(CFG_FTPS_DAT_BUF_MAX)
#define CFG_FTPS_DAT_BUF_MAX     1024     /* Data buffer size */
#endif
#if !defined(CFG_FTPS_CTL_BUF_MAX)
#define CFG_FTPS_CTL_BUF_MAX     256      /* Control buffer size */
#endif
#if !defined(CFG_FTPS_NET_SOC_MAX)
#define CFG_FTPS_NET_SOC_MAX     10       /* Maximum Sockets (NET_SOC_MAX) */
#endif

#define FTP_SERVER_RETRY_WAIT    100      /* wait retrying(ms) */
#define FTP_SERVER_BOOT          1        /* ftp server task state boot flag */
#define FTP_SERVER_STOP          0        /* ftp server task state stop flag */

/* Login user table */
typedef struct t_ftp_usr_tbl {
    UH dev_num;     /* Network device number (DEV_ANY(0): All device is allowed) */
    VB* usr;        /* User name */
    VB* pwd;        /* Password */
} T_FTP_USR_TBL;

/* Control block */
typedef struct t_ftp_server {
    VB *arg;                /* Command arguments */
    UW file_offset;         /* File start position */
    UW cli_adr;             /* Client IP address */
    ID wai_tsk_id;          /* Wait Task ID */
    ER wai_err;             /* Wait Error */
    UH ctl_sid;             /* Command Socket ID */
    UH dat_sid;             /* Data Socket ID */
    UH sts_flg;             /* Status flag */
    UH cli_port;            /* Client port */
    UH cmd_id;              /* Parsed command index */
    UH rcv_len;             /* Received data size */
    UH rcv_id;              /* Received buffer index */
    UH dev_num;             /* Device number of server listen channel */
    UH cli_dev_num;         /* Device number of client channel */
    UB mod;                 /* Mode (Passive or active) */
    UB typ;                 /* Type (Binary or ascii) */
    VB cmd[CFG_FTPS_CTL_BUF_MAX];           /* Client command */
    VB pwd[CFG_FTPS_PATH_MAX];              /* Print working directory */
    UB dat[CFG_FTPS_DAT_BUF_MAX];           /* Data transfer buffer */
    UB rcv_buf[CFG_FTPS_DAT_BUF_MAX];       /* Receive buffer */
    UB usr[CFG_FTPS_CTL_BUF_MAX];           /* User name buffer */
    UB wai_flg;                             /* Wait flag */
    UB sts_tsk_flg;                         /* Task status flag */
    struct t_ftp_server *next;              /* ftp server next node */
} T_FTP_SERVER;

/* FTP Server API */
ER ftp_server(T_FTP_SERVER *ftp);
ER ftp_server_stop( UW retry );

#endif

