/***************************************************************************
    Network Sample Application Configuration
    Copyright (c)  2014, eForce Co., Ltd. All rights reserved.

    2014-08-14: Created.
 ***************************************************************************/
#ifndef _SAMPLE_NETAPP_CFG_H
#define _SAMPLE_NETAPP_CFG_H

#include "net_hdr.h"
#include "net_strlib.h"
#include "shell.h"

#ifndef NULL
#define NULL    ((void*)0)
#endif

extern ER dns_get_ipa_opt(UW dnsd_ipa, VB *str, UW *ipa);

/*****************************************************************************
    Socket ID & Kernel ID
*****************************************************************************/
#ifdef NET_C
#include "kernel_id.h"
#include "net_id.h"
#define ID_ICMP_PING    ID_ICMP
#else
/* socket ID */
extern ID ID_ICMP_PING;
#ifdef IPV6_SUP
extern ID ID_ICMP_PING6;
#endif
extern ID ID_UDP_DNS;
extern ID ID_TCP_FTP_CTL;
extern ID ID_TCP_FTP_DAT;
extern ID ID_TCP_HTTP;
extern ID ID_TCP_SMTP;
extern ID ID_UDP_SNTPS;
extern ID ID_UDP_SNTPC;
extern ID ID_UDP_TFTP;

/* kernel object ID */
extern ID ID_HTTP_MSG_MPF;      /* fixed memory pool */
#endif

/*****************************************************************************
    Sample Application Settings
*****************************************************************************/

#define SPL_LF              "\r\n"          /* Line feed code */

/* Default DNS server */
extern T_NET_ADR gNET_ADR[];
#define SPL_DNS_SERVER      gNET_ADR[0].gateway

/*---- FTP  ----------------------------------------------------------------*/
/* FTP settings (ftp command) */
#define SPL_FTP_CTL_PORT    21
#define SPL_FTP_DAT_PORT    20
#define SPL_FTP_LS_BUF_SZ   1024            /* LIST/NLST result buffer size */

/*---- HTTP ----------------------------------------------------------------*/
/* HTTP settings (http_xxx command) */
#define SPL_HTTP_USR_BUF    64
#define SPL_HTTP_PW_BUF     64
#define SPL_HTTP_B_USR      "demo_basic"    /* Basic Auth Username */
#define SPL_HTTP_B_PW       "password"      /* Basic Auth Password */
#define SPL_HTTP_D_USR      "demo_digest"   /* Digest Auth Username */
#define SPL_HTTP_D_PW       "password"      /* Digest Auth Password */

/*---- SMTP ----------------------------------------------------------------*/
/* SMTP settings (mail command) */
#define SPL_SMTP_SERVER     "smtp.demo.co.jp"
#define SPL_SMTP_PORT       25
#define SPL_SMTP_USER       "from@demo.co.jp"       /* SMTP Authentication username */
#define SPL_SMTP_PASS       "password"              /* SMTP Authentication password */
#define SPL_SMTP_AUTH       SMTP_AUTH_CMD5          /* [SMTP_NO_AUTH | SMTP_AUTH_PLAIN | SMTP_AUTH_CMD5] */

/* send mail settings */
#define SPL_ML_FROM         "from_user <from@demo.co.jp>"
#define SPL_ML_TO           "to_user <to@demo.co.jp>"
#define SPL_ML_CC           "cc_user <cc@demo.co.jp>"
#define SPL_ML_BCC          0
#define SPL_ML_SUBJECT      "SMTPクライアント 送信テスト"
#define SPL_ML_BODY         "メール本文1行目\r\nメール本文2行目"
#define SPL_ML_CHARSET      "shift-jis"
#define SPL_ML_CHARSET8BIT  1       /* 1: Charset is 8bit. / 0: Charset is 7bit. */

#define SPL_ML_ATTACH_FILE
#ifdef SPL_ML_ATTACH_FILE
  #define SPL_MLAF_USE_MEM  1                       /* Use memory, or file(filesystem) */
  #define SPL_MLAF_NAME     "test.dat"              /* Attach Filename */
  #define SPL_MLAF_BUFPATH  (VP)shell_usr_cmd_mail  /* memory: Base Addr / file: Path */
  #define SPL_MLAF_BUFLEN   0xF0                    /* memory: length / file: not use */
#endif

/*---- SNTP ----------------------------------------------------------------*/
#define SNTP_DEV_ID         1

/*---- Telnet --------------------------------------------------------------*/

/*---- TFTPc----------------------------------------------------------------*/
/* TFTPc settings (tftp command) */
#define SPL_TFTP_PORT       69



#endif /* _SAMPLE_NETAPP_CFG_H */
