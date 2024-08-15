/***************************************************************************
    MICRO C CUBE / NETWORK
    Internal structure & macro definitions
    Copyright (c)  2014, eForce Co., Ltd. All rights reserved.

    Version Information  2014.03.31  Created.
                         2014.06.18  SNMP compact was supported.
                         2014.11.26: Add ip fowarding function
                         2014.12.09: Moved definition of internal data from net_def.h
 **************************************************************************/

#ifndef NETDEF_H
#define NETDEF_H
#ifdef __cplusplus
extern "C" {
#endif

#include "net_sup.h"

/**************************************************************************
    Misc Controll Flag
**************************************************************************/

#define  PKT_CTL_REP_UNREACH          0x00000001
#define  PKT_CTL_SKIP_IPCS            0x00000002
#define  PKT_CTL_SKIP_TCPCS           0x00000004
#define  PKT_CTL_SKIP_UDPCS           0x00000008


#define NET_BUF_MNG_SZ 42

#define NET_LOG(x)
#define NET_ERR(x)

#define NET_ADR_MOD_NONE       0
#define NET_ADR_MOD_STATIC     1
#define NET_ADR_MOD_DHCP       2
#define NET_ADR_MOD_AUTO       3

#define NET_ADR_TYPE_GLOBAL    0x01
#define NET_ADR_TYPE_LOCAL     0x00

/***************************************************************************
    Network
***************************************************************************/
extern UB IPR_TIMER_ON;
extern UB IGMP_TIMER_ON;
extern UB IGMPV1_TIMER_ON;
#ifdef IPV6_SUP
extern UB IPV6_TIMER_ON;
#endif


/***************************************************************************
    Network
***************************************************************************/
#define ARP_UNUSED      0x00   /* Entry is Empty                */
#define ARP_RESOLVING   0x01   /* Resolving Remote IP Address   */
#define ARP_VALID       0x02   /* Valid IP & MAC values         */
#define ARP_STATIC      0x04   /* Static ARP entry              */


/***************************************************************************
    Network
***************************************************************************/

/* IGMP Group State */
#define IGMP_NON_MEMBER     0
#define IGMP_DLY_MEMBER     1
#define IGMP_IDLE_MEMBER    2

/* IGMP Version 1 Router Present Time out */
#define IGMPV1_PRE_TMO  400000  /* 400 Seconds */
#define IGMP_REPORT_TMO 10000   /* 10 Seconds  */

#define IGMP_MSG_LEN        0x1C    /* 28 IP4HDR + IGMP + RouterAlertOption*/
#define IGMP_ALL_SYSTEMS    0xE0000001   /* 224.0.0.1 */
#define IGMP_ALL_ROUTERS    0xE0000002   /* 224.0.0.2 */


/***************************************************************************
    Network
***************************************************************************/

#define SEQ_LT(a,b)     ((int)((UW)(a)-(UW)(b)) < 0)
#define SEQ_LEQ(a,b)    ((int)((UW)(a)-(UW)(b)) <= 0)
#define SEQ_GT(a,b)     ((int)((UW)(a)-(UW)(b)) > 0)
#define SEQ_GEQ(a,b)    ((int)((UW)(a)-(UW)(b)) >= 0)

#define TCP_SET_RET     0x0001  /* Retry Timer      */
#define TCP_SET_ACK     0x0002  /* Delay ACK Timer  */
#define TCP_SET_PRB     0x0004  /* Delay ACK Timer  */
#ifdef KEEPALIVE_SUP
#define TCP_SET_KPA     0x0008
#endif
#define TCP_SET_CON     0x0010
#define TCP_SET_CLS     0x0020
#define TCP_SET_DAT     0x0040

#define TCP_TIM_RET     0x0001
#define TCP_TIM_USR     0x0011
#define TCP_TIM_SND     0x0021
#define TCP_TIM_CLS     0x0041
#define TCP_TIM_IDE     0x0081
#define TCP_TIM_PRB     0x0101
#define TCP_TIM_ACK     0x1000   /* Delay ACK */

/* Con, ret, dack, persist, keepalive, finwait2, timewait */


#define TIM_LEQ     SEQ_LEQ

#define IS_LBACK_IP(i)      ((((UW)(i)) & 0xFF000000) == 0x7F000000)
#define IS_MCAST_IP(i)      ((((UW)(i)) & 0xF0000000) == 0xE0000000)
#define IS_RES_BCAST_IP(i)  ((UW)(i) == 0xFFFFFFFF)
#define IS_BCAST_IP(i,a,m)  (((UW)(i) == 0xFFFFFFFF) || \
                             ((UW)(i)== ((UW)(a) | ~(UW)(m))))
#define IS_ROUTE_IP(l,i,m)  ((((UW)(l))&((UW)(m))) == (((UW)(i))&((UW)(m))))

#define SOC_FLG_SER     0x8000  /* Passive Connection */
#define SOC_FLG_PRT     0x4000  /* Port Any           */

#define SOC_UNUSED          TCP_UNUSED
#define SOC_CREATED         TCP_CLOSED
#define SOC_CONNECTED       TCP_ESTABLISHED

#define SOC_TCP_ACP     SOC_SER     /* TCP ACTIVE connection    */
#define SOC_TCP_CON     SOC_CLI     /* TCP PASSIVE connection   */
#define SOC_UDP_SND     SOC_SER     /* Use Receive IP           */
#define SOC_UDP_RCV     SOC_CLI     /* Set Remote IP            */


/* Well know ports          0 -1023     */
/* Registered ports         1024-49151  */
/* Dynamic/Private ports    49152-65535 */
#define EPHEMERAL_PORT      49152

/* Inc ISS for each second */
#define TCP_ISS_INCR        (125*1024L)

/***************************************************************************
 *  Internal
 */

#define DEV_STR_LEN     8       /* Device Name Length */
#define ETH_ADR_LEN     6

typedef struct t_net_dev {
    UB name[DEV_STR_LEN];       /* Device Name                  */
    UH num;                     /* Device Number                */
    UH type;                    /* Device Type                  */
    UH sts;                     /* Device Status                */
    UH flg;                     /* Dummy                        */
    ER (*ini)(UH);              /* Initialize the device        */
    ER (*cls)(UH);              /* Uninitialize the device      */
    ER (*ctl)(UH,UH,VP);        /* Configure the device         */
    ER (*ref)(UH,UH,VP);        /* Read status of the device    */
    ER (*out)(UH,T_NET_BUF*);   /* Write frame to the device    */
    void (*cbk)(UH,UH,VP);      /* Device event notifier        */
    UW *tag;                    /* Device specific              */
    union  {                    /* Address                      */
    struct {
    UB mac[ETH_ADR_LEN];
    }eth;
    }cfg;
    UH  hhdrsz;                 /* Device header length         */
    UH  hhdrofs;                /* Device header offset         */
    VP  opt;                    /* Misc                         */
}T_NET_DEV;

typedef struct t_net_cfg {
    UW  use;
    /* Interface    */
    UW  PATH_MTU;

    /* ARP          */
    UW  ARP_RET_CNT;
    UW  ARP_RET_TMO;
    UW  ARP_CLR_TMO;
#ifdef ACD_SUP
    UW  ARP_PRB_WAI;
    UW  ARP_PRB_NUM;
    UW  ARP_PRB_MIN;
    UW  ARP_PRB_MAX;
    UW  ARP_ANC_WAI;
    UW  ARP_ANC_NUM;
    UW  ARP_ANC_INT;
#endif

    /* IP           */
    UW  IP4_TTL;
    UW  IP4_TOS;
    UW  IP4_IPR_TMO;    /*ip4_ipr_tmo, ip4_ipr_max*/

    /* IGMP         */
    UW  IP4_MCAST_TTL;
    UW  IGMP_V1_TMO;
    UW  IGMP_REP_TMO;

    /* TCP          */
    UW  TCP_MSS;
#ifdef IPV6_SUP
    UW  TCP_MSS_IPV6;
#endif

    UW  TCP_RTO_INI;
    UW  TCP_RTO_MIN;
    UW  TCP_RTO_MAX;

    UW  TCP_SND_WND;
    UW  TCP_RCV_WND;

    UW  TCP_DUP_CNT;

    UW  TCP_CON_TMO;
    UW  TCP_SND_TMO;
    UW  TCP_CLS_TMO;
    UW  TCP_CLW_TMO;
    UW  TCP_ACK_TMO;

#ifdef KEEPALIVE_SUP
    UW  TCP_KPA_CNT;
    UW  TCP_KPA_INT;
    UW  TCP_KPA_TMO;
#endif

    /* Datagram(UDP&ICMP) */
    UW  PKT_RCV_QUE;

    /* Misc Controll Flag */
    UW  PKT_CTL_FLG;

}T_NET_CFG;

typedef struct t_net {
    struct t_net *next; /* Next interface in the list */
    ER (*out)(T_NET_BUF*);
    T_NET_DEV    *dev;  /* Net Device           */
    T_NET_ADR    *adr;  /* Host Address         */
#ifdef IPV6_SUP
    T_NET6_ADR   *ip6adr;/* Host Address         */
#endif
    T_NET_CFG    *cfg;  /* Net Configuration    */
    UH flag;            /* BCast/MCast          */
    UH ident;           /* IP Identification    */
    UW igmpv1_tmo;
    UB igmpv1_router;   /* IGMPV1 Router Present */
    UB igmp_exists;
#ifdef ACD_SUP
    ID prbtskid;        /* IP addr probing task    */
    T_NET_ACD *acd;     /* IP addr probing result  */
    ACD_HND   acdcbk;   /* Callback for detecting address conflict*/
#endif
}T_NET;

typedef struct t_net_arp {
    UW ipaddr;      /* Resolved or Resolving IP address         */
    UB mac[6];      /* Valid MAC when ARP status is ARP_VALID   */
    UB sts;         /* Unused->Resolving->Valid->Unused         */
    UB cnt;         /* Retry Count (Resolving)                  */
    UW tmo;         /* Retry (Resolving)/Cache (Valid)          */
    T_NET *net;     /* Network Interface                        */
    UW *ipq;        /* Queue IP packet during Resolving IP      */
    UH chg_flg;     /* Dirty flag                               */
}T_NET_ARP;

typedef struct t_net_mgr {
    UW ga;          /* Multicast Group Address  */
    UW tmo;         /* Report Time out          */
    UB cnt;         /* Report Retry count       */
    UB flg;         /* More than one host exist */
    UB state;       /* Group State              */
    UB ref;         /* Socket Count             */
    T_NET *net;     /* Network Interface        */
}T_NET_MGR;

typedef struct t_net_ipr {
    UW *ipq;        /* Fragment packet  Queue   */
    UW *top;        /* First Fragment packet    */
    UW sa;          /* Hash value               */
    UW da;          /* Hash value               */
#ifdef IPV6_SUP
    UW ip6sa[4];
    UW ip6da[4];
#endif
    UH id;          /* Hash value               */
    UB prot;        /* Hash value               */
    UB flg;         /* First&Last Frg received  */
    UH tlen;        /* Required Length          */
    UH rlen;        /* Received Length          */
    UH cnt;         /* No. of Fragments Received*/
    UH iphdrlen;    /* First Fragment IPhdr len */
    UW tmo;         /* Reassembly Timeout       */
}T_NET_IPR;

typedef struct t_net_tcp {
    struct t_net_soc *soc;
    /* TCP Connection control */
    UB bsd;
    UB dup_cnt;
    UH rtt;
    UH sflg;
    UH tim_flg;
    UH chg_flg;     /* Dirty flag */
    UW tcp_tmo;
#ifdef KEEPALIVE_SUP
    UW kpa_cnt;
    UW kpa_tmo;
#endif

    /* TCP Receive Control  */
    UW *rdatque;
    UW rbufsz;      /* Rcv Buffer size */
    UW rdatsz;      /* Len of data available in Rcv buffer */
    UW irs;
    UW rcv_wnd;
    UW rcv_nxt;
    UW rcv_up;
    UW ack_tmo;     /* Delay ACK Timer */
    UW mss;

    /* TCP Transmit Control */
    UB *snd_buf;
    UW sputp;
    UW sbufsz;
    UW snd_len;
    UW iss;
    UW rcv_mss;
    UW snd_wnd;
    UW snd_una;
    UW snd_nxt;
    UW snd_max;
    UW snd_wl1;
    UW snd_wl2;
    UW snd_up;
    UW ret_tmo;     /* Retry Timer */

    /* TCP Flow Control */
    UW cwnd;
    UW ssth;
    UW recover;

    /* RTO */
    UW rto;
    UW srtt;
    UW rttvar;
    UW rtt_seq;
}T_NET_TCP;
/*35*/

typedef struct t_net_soc {
    T_NET_TCP *tcp; /* TCP control Block */
    T_NET *net;     /* I/F to Send/Recv  */
    T_NET *usr_net;
    UH sid;         /* 0 to max */
    UH state;       /* CREATED/CONNECTED */
    UH lport;
    UH rport;
    UW raddr;
#ifdef IPV6_SUP
    UW  laddr6[4];
    UW  raddr6[4];
#endif
    UB rqsz;
    UB ver;         /* IP Version */
    UB proto;       /* TCP/UDP  */
    UB fncd;
    UB tos;
    UB ttl;
    UH flg;
    UH chg_flg;     /* Dirty flag */
    ER slen;
    ER rlen;
    ER ercd;         /* socket error */
    UW  *sdatque;
    UW  *rdatque;
    void (*cbk)(UH,UH,ER);
    UH cptn;
    UH wptn;
    ID ctskid;      /* Con/Cls Task */
    ID rtskid;      /* Snd Task     */
    ID stskid;      /* Rcv Task     */
    TMO snd_tmo;     /* User timeout for send process            */
    TMO rcv_tmo;     /* User timeout for receive process         */
    TMO con_tmo;     /* User timeout for connect process         */
    TMO cls_tmo;     /* User timeout for close process           */
    T_RCV_PKT_INF  rpi;    /* Received packet information       */
    UW mgr_idx;
}T_NET_SOC;

typedef struct {
    UW dst;   /* Host byte order */
    UW mask;
    UW gwy;
    UB devnum;
} T_NET_RTE;

typedef struct {
    UW lip;    /* Network byte order */
    UW gip;
    UW tmo;
    UH lport;  /* port or ID */
    UH masq;   /* port or ID */
    UH gport;
    UH sts;
    UB prot;
    UB devnum;

} T_NET_NAT;

typedef struct {
    ID id;          /* for application I/F */
    UW fwdip;       /* PK */
    UW srcip;       /* allow remote ip (not use) */
    UW dstip;       /* normally global I/F address */
    UH dstport;     /* port or icmp type/code (optional) */
    UH fwdport;     /* same dstport if it is not specified */
    UB prot;        /* protocol (optional) */
    UB devnum;      /* device ID  */

} T_NET_FLT;

extern UW NET_TICK;
extern UW NET_SEC;

/* Status */
#define NET_STS_CLR        0x00    /* Clear */
#define NET_STS_CRE        0x01    /* Create */
#define NET_STS_DEL        0x02    /* Delete */
#define NET_STS_CHG        0x04    /* Changed */
#define NET_STS_CHG_TCP    0x05    /* Changed TCP */

ER eth_pkt_out(T_NET_BUF *pkt);
ER ppp_pkt_out(T_NET_BUF *pkt);

void arp_timer(UW ctick);
ER arp_resolve(T_NET_BUF *pkt);
void arp_recv(T_NET_BUF *pkt);
ER arp_send(T_NET *net, UW tpa, UB type);

void ip4_rcv(T_NET_BUF *pkt);
void icmp_pkt_rcv(T_NET_BUF *pkt);
#ifdef PING_SUP
ER icmp_rcv(T_NET_SOC *soc, VP data, UH len);
ER icmp_snd(T_NET_SOC *soc, VP data, UH len);
ER icmp_error(T_NET_BUF *pkt);
#endif

#ifdef IPV6_SUP
void ip6_rcv(T_NET_BUF *nbuf);
ER ip6_snd(T_NET_BUF *pkt);
ER icmp6_pkt_snd(T_NET_BUF *pkt, UH dlen);
void icmp6_err_snd(T_NET_BUF *pkt, UB type, UB code, UW offset);
#endif

#ifdef IPR_SUP
void ipr_init(void);
void ipr_timer(UW ctimval);
ER ip4_reassembly(T_NET_BUF **pkt, T_IP4_HDR *ip4hdr);
ER ipf_snd(T_NET_BUF *pkt);
#endif

#ifdef MCAST_SUP
void igmp_init(void);
void igmp_timer(UW ctimval);
void igmpv1_timer(UW ctimval);
UB is_mgroup_in(T_NET *net, UW mcast);
B mgroup_index(T_NET *net, UW mcast);
ER igmp_join(T_NET *net, UW ga);
ER igmp_leave(T_NET *net, UW ga);

void igmp_rcv(T_NET_BUF *pkt);
void igmp_snd(T_NET *net, UW ga, UB type);
#endif

UW net_csum(UH *dat, UH len, UW c);
UH ip4_csum(T_NET_BUF *pkt);
UH icmp_csum(T_NET_BUF *pkt);
UH tcp_csum(T_NET_BUF *pkt);
#define udp_csum(x) tcp_csum(x)
#define igmp_csum(x) icmp_csum(x)

#ifdef UDP_SUP
void udp_pkt_rcv(T_NET_BUF *pkt);
ER udp_rcv(T_NET_SOC *soc, VP data, UH len);
ER udp_snd(T_NET_SOC *soc, VP data, UH len);
#endif

#ifdef TCP_SUP
void tcp_usr_timer(void);
void tcp_ack_timer(void);
void tcp_dat_timer(void);

void tcp_out(T_NET_TCP *tcp, UH flag, UH rts_flg);
ER tcp_ack(T_NET_TCP *tcp, UB flag);
ER tcp_out_rst(T_NET_BUF *rpkt, UH len);

void tcp_pkt_rcv(T_NET_BUF *pkt);
UH tcp_wnd_adv(T_NET_TCP *tcp);
void tcp_wnd_upd(T_NET_TCP *tcp, UH len);

ER tcp_cre(T_NET_SOC *soc);
ER tcp_del(T_NET_SOC *soc);
ER tcp_con(T_NET_SOC *soc, T_NODE *host, UB con_flg);
ER tcp_cls(T_NET_SOC *soc, UB cls_flg);
ER tcp_abt(T_NET_TCP *tcp, UB code);
ER tcp_snd(T_NET_SOC *soc, VP data, UH len);
ER tcp_rcv(T_NET_SOC *soc, VP data, UH len);
#endif

#ifdef STS_SUP
ER net_sts_snmp_ena(void);
ER net_sts_snmp_dis(void);
#endif

#ifdef STS_SUP
ER net_sts_ini(void);
ER net_sts_ext(void);
void net_sts_inc(UH grp_id, UH id);
void net_sts_dec(UH grp_id, UH id);
void net_sts_add(UH grp_id, UH id, UW dat);
ER net_sts_get(UH grp_id, UH id, UW* dat);
ER net_sts_upd(void);
void net_sts_eth_cbk(UH dev_num, UH evt, VP sts);
void net_sts_cbk(UH dev_num, UH evt, VP sts);
#else
#define net_sts_ini()               ((void)0)
#define net_sts_ext()               ((void)0)
#define net_sts_inc(g, i)           ((void)0)
#define net_sts_dec(g, i)           ((void)0)
#define net_sts_add(g, i, d)        ((void)0)
#define net_sts_get(g, i, d)        ((void)0)
#define net_sts_upd()               ((void)0)
#define net_sts_eth_cbk(d, e, s)    ((void)0)
#define net_sts_cbk(d, e, s)        ((void)0)
#endif

#ifdef IP4_FWD_SUP
ER net_ip4_fwd_ini(VP);
ER nat_from_global(T_IP4_HDR *);
ER nat_to_global(T_IP4_HDR *);
ER ip4_fwd_pkt(T_NET_BUF *, T_IP4_HDR *, T_NET *);
T_NET *get_fwd_net(T_IP4_HDR *);
void nat_timer(UW);
#else
#define net_ip4_fwd_ini(a)          ((void)0)
#define ip4_fwd_pkt(a, b, c)        ((void)0)
#define nat_from_global(a)          (E_OK)
#define nat_to_global(a)            (E_OK)
#define get_fwd_net(a)              (0)
#define nat_timer(a)                ((void)0)
#endif

void soc_ini(void);
void soc_wakeup(T_NET_BUF *pkt);
UH get_eport(UB proto);
ER soc_event(T_NET_SOC *soc, UH ptn, ER ercd);


/***************************************************************************
 *  Configuration
 */


/**************************************************************************/
/* TCP/IP Default Configuration Values                                    */
/**************************************************************************/

#define DEF_NET_DEV_MAX     1       /* Maximum Interface            */
#define DEF_NET_SOC_MAX     10      /* Maximum Sockets (TCP&UDP)    */
#define DEF_NET_TCP_MAX     5       /* Maximum TCP Control blocks   */
#define DEF_NET_ARP_MAX     8       /* ARP Cache                    */
#define DEF_NET_MGR_MAX     8       /* Multicast Group              */
#define DEF_NET_IPR_MAX     2       /* IP Reassembly                */
#define DEF_NET_BUF_CNT     8
#define DEF_NET_BUF_SZ      1576
#define DEF_NET_BUF_OFFSET  2
#define DEF_PATH_MTU        1500    /* IP Path MTU                  */
#define DEF_ARP_RET_CNT     3           /* 3 Times  */
#define DEF_ARP_RET_TMO     1000        /* 1 sec    */
#define DEF_ARP_CLR_TMO     20*60*1000  /* 20 min   */
#define DEF_ARP_PRB_WAI     1*1000
#define DEF_ARP_PRB_NUM     3
#define DEF_ARP_PRB_MIN     1*1000
#define DEF_ARP_PRB_MAX     2*1000
#define DEF_ARP_ANC_WAI     2*1000
#define DEF_ARP_ANC_NUM     2
#define DEF_ARP_ANC_INT     2*1000
#define DEF_IP4_TTL         64
#define DEF_IP4_TOS         0
#define DEF_IP4_IPR_TMO     10*1000     /* 10 sec   */
#define DEF_IP4_MCAST_TTL   1
#define DEF_IGMP_V1_TMO     400*1000
#define DEF_IGMP_REP_TMO    10*1000
#define DEF_TCP_MSS         (DEF_PATH_MTU-40)   /* TCP MSS */
#define DEF_TCP_RTO_INI     3*1000      /* 3 sec    */
#define DEF_TCP_RTO_MIN     500         /* 500 msec */
#define DEF_TCP_RTO_MAX     60*1000     /* 60 sec   */
#define DEF_TCP_SND_WND     1024
#define DEF_TCP_RCV_WND     1024
#define DEF_TCP_DUP_CNT     4
#define DEF_TCP_CON_TMO     75*1000     /* 75 secs */
#define DEF_TCP_SND_TMO     64*1000     /* 64 secs */
#define DEF_TCP_CLS_TMO     75*1000     /* 75 secs */
#define DEF_TCP_CLW_TMO     20*1000     /* 20 secs */
#define DEF_TCP_ACK_TMO     200
#define DEF_TCP_KPA_CNT     0           /* 0 times(Disable) */
#define DEF_TCP_KPA_INT     1*1000      /* 1 secs */
#define DEF_TCP_KPA_TMO     7200*1000   /* 7200 secs(2 hours) */
#define DEF_PKT_RCV_QUE     1

#define DEF_NET_TSK_PRI     4
#define DEF_NET_TSK_SIZ     1024

#define DEF_STS_UPD_RES     2000

#ifdef IPV6_SUP     
#define IP6_MIN_MTU     1280

#define DEF_NET6_BUF_SZ     DEF_NET_BUF_SZ

/* Neighbor Discovery */
#define DEF_NEIGH_CACHE     05
#define DEF_DST_CACHE       05
#define DEF_RTR_LST         02
#define DEF_PRFX_LST        05
#define DEF_PMTU_CACHE      05

#define DEF_DAD_CNT         01
#define DEF_IPV6_TIM_RES    10

#define DEF_UCAST_CNT       3   /* Linklocal, site local and Global */
#define DEF_MCAST_CNT       3   /* All node and Solicit node */

#define DEF_TCP_MSS_IPV6    (DEF_PATH_MTU-60)   /* TCP MSS */

#endif


#ifdef DEF_CFG

#define NET_DEV_MAX     DEF_NET_DEV_MAX
#define NET_SOC_MAX     DEF_NET_SOC_MAX
#define NET_TCP_MAX     DEF_NET_TCP_MAX
#define NET_ARP_MAX     DEF_NET_ARP_MAX
#define NET_MGR_MAX     DEF_NET_MGR_MAX
#define NET_IPR_MAX     DEF_NET_IPR_MAX
#define NET_BUF_CNT     DEF_NET_BUF_CNT
#define NET_BUF_SZ      DEF_NET_BUF_SZ
#define PATH_MTU        DEF_PATH_MTU
#define ARP_RET_CNT     DEF_ARP_RET_CNT
#define ARP_RET_TMO     DEF_ARP_RET_TMO
#define ARP_CLR_TMO     DEF_ARP_CLR_TMO
#ifdef ACD_SUP
#define ARP_PRB_WAI     DEF_ARP_PRB_WAI
#define ARP_PRB_NUM     DEF_ARP_PRB_NUM
#define ARP_PRB_MIN     DEF_ARP_PRB_MIN
#define ARP_PRB_MAX     DEF_ARP_PRB_MAX
#define ARP_ANC_WAI     DEF_ARP_ANC_WAI
#define ARP_ANC_NUM     DEF_ARP_ANC_NUM
#define ARP_ANC_INT     DEF_ARP_ANC_INT
#endif
#define IP4_TTL         DEF_IP4_TTL
#define IP4_TOS         DEF_IP4_TOS
#define IP4_IPR_TMO     DEF_IP4_IPR_TMO
#define IP4_MCAST_TTL   DEF_IP4_MCAST_TTL
#define IGMP_V1_TMO     DEF_IGMP_V1_TMO
#define IGMP_REP_TMO    DEF_IGMP_REP_TMO
#define TCP_MSS         DEF_TCP_MSS
#ifdef IPV6_SUP
#define TCP_MSS_IPV6    DEF_TCP_MSS_IPV6
#endif
#define TCP_RTO_INI     DEF_TCP_RTO_INI
#define TCP_RTO_MIN     DEF_TCP_RTO_MIN
#define TCP_RTO_MAX     DEF_TCP_RTO_MAX
#define TCP_SND_WND     DEF_TCP_SND_WND
#define TCP_RCV_WND     DEF_TCP_RCV_WND
#define TCP_SND_WND_MAX DEF_TCP_SND_WND
#define TCP_DUP_CNT     DEF_TCP_DUP_CNT
#define TCP_CON_TMO     DEF_TCP_CON_TMO
#define TCP_SND_TMO     DEF_TCP_SND_TMO
#define TCP_CLS_TMO     DEF_TCP_CLS_TMO
#define TCP_CLW_TMO     DEF_TCP_CLW_TMO
#define TCP_ACK_TMO     DEF_TCP_ACK_TMO
#ifdef KEEPALIVE_SUP
#define TCP_KPA_CNT     DEF_TCP_KPA_CNT
#define TCP_KPA_INT     DEF_TCP_KPA_INT
#define TCP_KPA_TMO     DEF_TCP_KPA_TMO
#endif
#define PKT_RCV_QUE     DEF_PKT_RCV_QUE

#else

#define PATH_MTU        net->cfg->PATH_MTU
#define ARP_RET_CNT     net->cfg->ARP_RET_CNT
#define ARP_RET_TMO     net->cfg->ARP_RET_TMO
#define ARP_CLR_TMO     net->cfg->ARP_CLR_TMO
#ifdef ACD_SUP
#define ARP_PRB_WAI     net->cfg->ARP_PRB_WAI
#define ARP_PRB_NUM     net->cfg->ARP_PRB_NUM
#define ARP_PRB_MIN     net->cfg->ARP_PRB_MIN
#define ARP_PRB_MAX     net->cfg->ARP_PRB_MAX
#define ARP_ANC_WAI     net->cfg->ARP_ANC_WAI
#define ARP_ANC_NUM     net->cfg->ARP_ANC_NUM
#define ARP_ANC_INT     net->cfg->ARP_ANC_INT
#endif
#define IP4_TTL         net->cfg->IP4_TTL
#define IP4_TOS         net->cfg->IP4_TOS
#define IP4_IPR_TMO     net->cfg->IP4_IPR_TMO
#define IP4_MCAST_TTL   net->cfg->IP4_MCAST_TTL
#define IGMP_V1_TMO     net->cfg->IGMP_V1_TMO
#define IGMP_REP_TMO    net->cfg->IGMP_REP_TMO
#define TCP_MSS         net->cfg->TCP_MSS
#ifdef IPV6_SUP
#define TCP_MSS_IPV6    net->cfg->TCP_MSS_IPV6
#endif
#define TCP_RTO_INI     net->cfg->TCP_RTO_INI
#define TCP_RTO_MIN     net->cfg->TCP_RTO_MIN
#define TCP_RTO_MAX     net->cfg->TCP_RTO_MAX
#define TCP_SND_WND     net->cfg->TCP_SND_WND
#define TCP_RCV_WND     net->cfg->TCP_RCV_WND
#define TCP_DUP_CNT     net->cfg->TCP_DUP_CNT
#define TCP_CON_TMO     net->cfg->TCP_CON_TMO
#define TCP_SND_TMO     net->cfg->TCP_SND_TMO
#define TCP_CLS_TMO     net->cfg->TCP_CLS_TMO
#define TCP_CLW_TMO     net->cfg->TCP_CLW_TMO
#define TCP_ACK_TMO     net->cfg->TCP_ACK_TMO
#ifdef KEEPALIVE_SUP
#define TCP_KPA_CNT     net->cfg->TCP_KPA_CNT
#define TCP_KPA_INT     net->cfg->TCP_KPA_INT
#define TCP_KPA_TMO     net->cfg->TCP_KPA_TMO
#endif
#define PKT_RCV_QUE     net->cfg->PKT_RCV_QUE

#define REP_UNREACH    (net->cfg->PKT_CTL_FLG & PKT_CTL_REP_UNREACH)
#define SKIP_IPCS      (net->cfg->PKT_CTL_FLG & PKT_CTL_SKIP_IPCS)
#define SKIP_TCPCS     (net->cfg->PKT_CTL_FLG & PKT_CTL_SKIP_TCPCS)
#define SKIP_UDPCS     (net->cfg->PKT_CTL_FLG & PKT_CTL_SKIP_UDPCS)

#endif  /* DEF_CFG */

extern const T_CMPF c_net_mpf;
extern const T_CTSK c_net_tsk;
extern const T_CSEM c_net_sem;


/* other */
void loc_tcp(void);
void ulc_tcp(void);

void arp_ini(void);
void arp_rmv_que(T_NET_BUF *pkt, ER err);

T_NET *get_net_bynum(UH num);
T_NET *get_net_default(void);

void add2que_end(UW **que, T_NET_BUF *pkt);
void rmv4que_top(UW **que);


#ifdef NET_C
extern T_SOC_TABLE *pSOC_TABLE;
#endif
extern T_NET_SOC   *pNET_SOC;
extern T_NET_TCP   *pNET_TCP;
extern T_NET_MGR   *pNET_MGR;
extern T_NET_IPR   *pNET_IPR;
extern const VP net_inftbl[8];

extern ID ID_NET_TSK;
extern ID ID_NET_SEM;
extern ID ID_NET_MPF;

extern T_NET       gNET[];
extern T_NET_ADR   gNET_ADR[];
extern T_NET_DEV   gNET_DEV[];
extern T_NET_ARP   gNET_ARP[];
extern T_NET_CFG   gNET_CFG[];
extern ER net_memini(void);
extern ER net_memext(void);
extern ER net_memget(VP *adr, UINT n, TMO tmo, ID *id);
extern ER net_memret(VP adr, ID id);


#ifdef __cplusplus
}
#endif
#endif /* NETDEF_H */

