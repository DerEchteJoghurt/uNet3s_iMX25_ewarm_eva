/***************************************************************************
    MICRO C CUBE / COMPACT, NETWORK
    Protocol headers, internal structure & macro definitions
    Copyright (c)  2008-2014, eForce Co., Ltd. All rights reserved.

    Version Information  2008.11.19: Created
                         2010.01.18: 'hhdrsz' field in T_NET_DEV, PPP_HDR_SZ
                         2010.03.24: SOC_FLG_PRT check
                         2010.08.10: Updated for broadcast IP address check
                         2010.08.10: Added net_rand() & net_rand_seed()
                         2010.08.17: Support SOC_RCV_PKT_INF socket option
                         2010.10.02: Updated for IPv6 support
                         2010.11.10: Updated for any network interface
                         2011.01.31: Added laddr6[4] as member of t_net_soc
                         2011.03.07: Updated for received packet queue
                         2011.04.04: Added definition of TCP/MSS for IPv6
                         2011.05.20: Set up networkbuffer offset
                         2011.11.14: Added ACD parameter
                         2011.11.14: Implemented Address Conflict Detection
                         2012.05.21: Implemented Keep-Alive
                         2012.06.06: Implemented port unreachable with ICMPv4
                         2012.10.02  Modify to avoid use of string libraries.
                         2013.04.10  H/W OS supported version
                         2013.07.23  Implemented ready I/O event notification.
                         2013.08.06: Implememted multicast per socket
                         2013.09.25: Implememted local loopback
                         2013.12.06  Change to external function to allocate buffer
                         2014.03.06: SNMP option was added
                         2014.03.31  Moved internal definitions to net_def.h
                         2014.04.15: Add member of T_NET_DEV for device option
                         2014.08.20: Add net_sts_ext function.
                         2014.10.03: Add MAC/PHY common status definitions
                         2014.11.04: Add get_net_sec() function
                         2014.11.26: Add ip fowarding function
                         2014.12.09: Moved definition of internal data to net_def.h
 **************************************************************************/

#ifndef NETHDR_H
#define NETHDR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "net_sup.h"

#ifdef IPV6_SUP
#include "net_hdr6.h"
#endif
/***************************************************************************
 *  Protocol Header Definition
 */

/***************************************************************************
    PPP
***************************************************************************/
#define PPP_HDR_SZ      2   /* for network buffer header alignment */

/***************************************************************************
    Ethernet
***************************************************************************/

#define ETH_TYPE_IP4   0x0800  /* Ethernet Type of IP Protocol  */
#define ETH_TYPE_ARP   0x0806  /* Ethernet Type of ARP Protocol */
#define ETH_TYPE_IP6   0x86DD  /* Ethernet Type of IP6 Protocol */

typedef struct t_eth_hdr {
    UB da[6];
    UB sa[6];
    UH type;
}T_ETH_HDR;
#define ETH_HDR_SZ      14

/**************************************************************************
    ARP
**************************************************************************/

#define ARP_TYPE_ETH    0x0001  /* Hardware type: Ethernet  */
#define ARP_PROTO_IP    0x0800  /* Protocol type: IP        */
#define ARP_HA_LEN      0x06    /* Hardware Address length  */
#define ARP_PA_LEN      0x04    /* Protocol Address length  */
#define ARP_OPC_REQ     0x0001  /* ARP Request  : 1         */
#define ARP_OPC_REP     0x0002  /* ARP Reply    : 2         */
#define ARP_OPC_RREQ    0x0003  /* RARP Request : 3         */
#define ARP_OPC_RREP    0x0004  /* RARP Reply   : 4         */

typedef struct t_arp_hdr {
    UH hw;              /* Hardware Address Space  */
    UH proto;           /* Protocol Address Space  */
    UB ha_len;          /* Hardware Address Length */
    UB pa_len;          /* Protocol Address Length */
    UH op;              /* Opcode: Request | Reply */
    UB sha[6];          /* Sender Hardware Address */
    UB spa[4];          /* Sender Protocol Address */
    UB tha[6];          /* Target Hardware Address */
    UB tpa[4];          /* Target Protocol Address */
}T_ARP_HDR;
#define ARP_HDR_SZ      28

/**************************************************************************
    IP4
**************************************************************************/

#define IP_HDR_VER4     0x04
#define IP_VER          0x0F
#define IP_OFFSET       0x1FFF
#define IP_FLG_MF       0x01
#define IP_FLG_DF       0x02

#define IP_PROTO_ICMP        1       /* ICMP Protocol        */
#define IP_PROTO_IGMP        2       /* IGMP Protocol        */
#define IP_PROTO_TCP         6       /* TCP  Protocol        */
#define IP_PROTO_UDP        17       /* UDP  Protocol        */
#define IP_PROTO_UDPL      136       /* UDP-Lite Protocol    */

typedef struct t_ip4_hdr {
    UB   ver;                   /* Version, Internal Header Length */
    UB   tos;                   /* Type of Service */
    UH   tl;                    /* Total Length */
    UH   id;                    /* Identification */
    UH   fo;                    /* Flags, Fragment Offset */
    UB   ttl;                   /* Time to Live */
    UB   prot;                  /* Protocol Number */
    UH   hc;                    /* Header Checksum */
    UW   sa;                    /* Source IP Address */
    UW   da;                    /* Destination IP Address */
}T_IP4_HDR;
#define IP4_HDR_SZ      20

typedef struct t_ip4_pseudo {
    UW sa;
    UW da;
    UH proto;
    UH len;
}T_IP4_PSEUDO;

/**************************************************************************
    UDP
**************************************************************************/

typedef struct t_udp_hdr {
    UH sp;                  /* Source Port */
    UH dp;                  /* Destination Port */
    UH len;                 /* Data Length */
    UH cs;                  /* Checksum */
} T_UDP_HDR;
#define UDP_HDR_SZ      8

/**************************************************************************
    TCP
**************************************************************************/

#define TCP_UNUSED          0x00
#define TCP_CLOSED          0x01
#define TCP_LISTEN          0x02
#define TCP_SYN_SENT        0x03
#define TCP_SYN_RECEIVED    0x04
#define TCP_ESTABLISHED     0x05
#define TCP_FIN_WAIT1       0x06
#define TCP_FIN_WAIT2       0x07
#define TCP_CLOSE_WAIT      0x08
#define TCP_CLOSING         0x09
#define TCP_LAST_ACK        0x0A
#define TCP_TIME_WAIT       0x0B

#define TCP_FLG_FIN         0x0001
#define TCP_FLG_SYN         0x0002
#define TCP_FLG_RST         0x0004
#define TCP_FLG_PSH         0x0008
#define TCP_FLG_ACK         0x0010
#define TCP_FLG_URG         0x0020

typedef struct t_tcp_hdr {
    UH  sp;     /* Source port */
    UH  dp;     /* Destination port */
    UW  seq;    /* Sequence value */
    UW  ack;    /* Acknowledgment value */
    UH  flag;   /* Data offset 3 and TCP Flags */
    UH  win;    /* TCP window value */
    UH  cs;     /* TCP Checksum */
    UH  up;     /* Urgent pointer */
}T_TCP_HDR;
#define TCP_HDR_SZ      20

/**************************************************************************
    ICMP
**************************************************************************/

/* ICMP Type :- RFC 792 */
#define ICMP_ECHO_REPLY     0   /* Echo Reply               */
#define ICMP_DST_UNREACH    3   /* Destination Unreachable  */
#define ICMP_SRC_QUENC      4   /* Source Quench            */
#define ICMP_REDIRECT       5   /* Redirect                 */
#define ICMP_ECHO_REQUEST   8   /* Echo Request             */
#define ICMP_TIME_EXCEED    11  /* Time Exceeded            */
#define ICMP_PRM_PROB       12  /* Parameter Problem        */
#define ICMP_TIMES_REQUEST  13  /* Timestamp Request        */
#define ICMP_TIMES_REPLY    14  /* Timestamp Reply          */
#define ICMP_ADDR_REQUEST   17  /* AddressMask Request      */
#define ICMP_ADDR_REPLY     18  /* AddressMask Reply        */

typedef struct t_icmp_hdr {
    UB type;                /* Type */
    UB code;                /* Code */
    UH cs;                  /* Checksum */
    UH id;                  /* Identifier */
    UH seq;                 /* Sequence Number */
}T_ICMP_HDR;
#define ICMP_HDR_SZ     8

/**************************************************************************
    IGMP
**************************************************************************/

#define IGMP_QUERY       0x11   /* Query            */
#define IGMP_REPORT_V1   0x12   /* Version1 Report  */
#define IGMP_REPORT      0x16   /* Version2 Report  */
#define IGMP_LEAVE       0x17   /* Leave            */

typedef struct t_igmp_hdr {
    UB type;    /* Type          */
    UB mrt;     /* Max Resp Time */
    UH cs;      /* Checksum      */
    UW ga;      /* Group Address */
} T_IGMP_HDR;
#define IGMP_HDR_SZ     8


/***************************************************************************
    Network Buffer
***************************************************************************/

#define IP_RCV_BCAST    0x0001
#define IP_RCV_MCAST    0x0002
#define TCP_DAT_BUF     0x0004
#define LOCAL_LOOPBK    0x0008

#define HW_CS_RX_IPH4   0x0010
#define HW_CS_RX_DATA   0x0020
#define HW_CS_TX_IPH4   0x0040
#define HW_CS_TX_DATA   0x0080

#define HW_CS_IPH4_ERR  0x0100
#define HW_CS_DATA_ERR  0x0200

#define PKT_FLG_BCAST   IP_RCV_BCAST
#define PKT_FLG_MCAST   IP_RCV_MCAST
#define PKT_FLG_TCP     TCP_DAT_BUF

typedef struct t_net_buf {
    UW  *next;
    ID  mpfid;
    struct t_net  *net;
    struct t_net_dev  *dev;
    struct t_net_soc  *soc;
    ER  ercd;       /* Socket Error                 */
    UH  flg;        /* Broadcast/Multicast          */
    UH  seq;        /* IP Fragment Sequence         */
    UH  hdr_len;    /* *hdr length                  */
    UH  dat_len;    /* *dat length                  */
    UB  *hdr;       /* 2byte Aligned                */
    UB  *dat;       /* 4byte Aligned                */
    UB  buf[2];     /* Packet Data                  */
}T_NET_BUF;


/***************************************************************************
    Network Device
***************************************************************************/

/* Device Type */
#define NET_DEV_TYPE_LOOP   0   /* LoopBack Device  */
#define NET_DEV_TYPE_ETH    1   /* Ethernet Device  */
#define NET_DEV_TYPE_PPP    2   /* PPP              */
#define NET_DEV_TYPE_PPPOE  3   /* PPPoE            */

/* Device Status */
#define NET_DEV_STS_NON     0    /* Device not exists       */
#define NET_DEV_STS_INI     1    /* Device Initializized    */
#define NET_DEV_STS_DIS     2    /* Device Disabled         */

/* Device Flag */
#define NET_DEV_FLG_PROMISC 1    /* Device Promiscous        */
#define NET_DEV_FLG_BCAST   2    /* Device support Broadcast */
#define NET_DEV_FLG_MCAST   4    /* Device support Multicast */

/* Device Configuration */
enum net_dev_ctl {
NET_DEV_CFG_MAC,                 /* MAC Address configuration */
NET_DEV_CFG_MTU,                 /* MTU                       */
NET_DEV_CFG_PROMISC,             /* Enable/Disable Promiscous */
NET_DEV_CFG_BCAST,               /* Enable/Disable MultiCast  */
NET_DEV_CFG_MCAST                /* Enable/Disable BroadCast  */
};

/* Reference options */
#define REF_ETH_LINK_STS        0x0001U     /* Link status */
#define REF_ETH_UPD_STS         0x0002U     /* Update status */

/* Callback events */
#define EV_CBK_DEV_LINK         0x0001U     /* Device link change event */
#define EV_CBK_DEV_CHG_IP       0x0002U     /* Device IP change event   */
#define EV_CBK_ARP_CRE          0x0010U     /* ARP create               */
#define EV_CBK_ARP_DEL          0x0020U     /* ARP delete               */
#define EV_CBK_ARP_CHG_IP       0x0040U     /* ARP IP dev_num changed   */
#define EV_CBK_ARP_CHG_MAC      0x0080U     /* ARP MAC changed          */
#define EV_CBK_SOC_CRE          0x0100U     /* Socket create            */
#define EV_CBK_SOC_DEL          0x0200U     /* Socket delete            */
#define EV_CBK_SOC_CHG          0x0400U     /* Socket status changed    */
#define EV_CBK_SOC_CHG_TCP      0x0800U     /* Socket TCP stat changed  */

#define EV_CBK_DEV_MSK          0x000FU     /* Device mask              */
#define EV_CBK_ARP_MSK          0x00F0U     /* ARP mask                 */
#define EV_CBK_SOC_MSK          0x0F00U     /* Socket mask              */

#define PHY_STS_LINK_DOWN       0x0000U     /* PHY media link down      */
#define PHY_STS_10HD            0x0100U     /* PHY 10M/Half-Duplex      */
#define PHY_STS_10FD            0x0200U     /* PHY 10M/Full-Duplex      */
#define PHY_STS_100HD           0x0400U     /* PHY 100M/Half-Duplex     */
#define PHY_STS_100FD           0x0800U     /* PHY 100M/Full-Duplex     */
#define PHY_STS_1000FD          0x1000U     /* PHY 1000M/Full-Duplex    */
#define PHY_STS_MSK             0xff00U     /* PHY mask */
#define ETH_STS_INV             0x0000U     /* Invalid */
#define ETH_STS_INI             0x0001U     /* Initialized */
#define ETH_STS_RST             0x0010U     /* Reset */
#define ETH_STS_ERR             0x0080U     /* Error */
#define ETH_STS_MSK             0x00ffU     /* Mask */

#define ARP_RESOLVE_IP         0
#define ARP_PROBE_IP           1
#define ARP_ANNOUNCE_IP        2
#define ARP_GRATUITOUS         3

#ifdef ACD_SUP
typedef struct t_net_acd {
    UW ip;
    UB mac[6];
}T_NET_ACD;

typedef ER (*ACD_HND)(T_NET_ACD*);
#endif /* ACD_SUP */

typedef struct t_net_adr {
    UB ver;         /* IP4/IPv6         */
    UB mode;        /* STATIC or DHCP   */
    UW ipaddr;      /* Default IP Addr  */
    UW gateway;     /* Default Gateway  */
    UW mask;        /* Subnet Mask      */
}T_NET_ADR;

/***************************************************************************
 *  Socket
 */

typedef struct t_node {
    UH  port;   /* Port number 1 - 65535, 0 -> PORT any */
    UB  ver;    /* IP Address type */
    UB  num;    /* Device number   */
    UW  ipa;    /* IPv4 Address    */
#ifdef IPV6_SUP
    UW  ip6a[4];/* IPv6 Address    */
#endif
}T_NODE;

typedef struct t_rcv_pkt_inf {
   UW   src_ipa;    /* Source IP Address */
   UW   dst_ipa;    /* Destination IP Address */
#ifdef IPV6_SUP
    UW  ip6sa[4];   /* IPv6 Source Address     */
    UW  ip6da[4];   /* IPv6 Destination Address    */
#endif
   UH   src_port;   /* Source Port */
   UH   dst_port;   /* Destination Port */
   UB   ttl;        /* IP TTL */
   UB   tos;        /* IP TOS */
   UB   ver;        /* IP Version */
   UB   num;        /* Received Device Number */
}T_RCV_PKT_INF;

/* Socket callback  prototype */

typedef void(*SOC_HND)(UH,UH,ER);

#define EV_SOC_CON      0x0001
#define EV_SOC_CLS      0x0002
#define EV_SOC_SND      0x0004
#define EV_SOC_RCV      0x0008
#define EV_SOC_SRY      0x0010
#define EV_SOC_RRY      0x0020
#define EV_RDY_SND      0x0100
#define EV_RDY_RCV      0x0200
#define EV_SOC_ALL      0xFFFF


#define INADDR_ANY          ((UW)0U)     /* Auto IP ADDRESS */
#define PORT_ANY            ((UH)0U)     /* Auto PORT       */
#define DEV_ANY             ((UH)0U)
/* Supported IP VERSION */

#define IP_VER4             0       /* IPv4 */
#define IP_VER6             1       /* IPv6 */

/* SOC_CON */

#define SOC_SER         0           /* Wait for connection      */
#define SOC_CLI         1           /* Establish connection     */

/* SOC_CLS */

#define SOC_TCP_CLS         0       /* CLOSE Connection */
#define SOC_TCP_SHT         1       /* CLOSE Transmission */

/* SOC_ABT */

#define SOC_ABT_ALL         0       /* ABORT All Activities             */
#define SOC_ABT_SND         1       /* ABORT Send Process               */
#define SOC_ABT_RCV         2       /* ABORT Recv Process               */
#define SOC_ABT_CON         3       /* ABORT Connection Process         */
#define SOC_ABT_CLS         4       /* ABORT Connection closing process */

/* SOC_CFG */
/* SOC_REF */
                                    /* Socket configuration             */
#define SOC_IP_TTL          0
#define SOC_IP_TOS          1
#define SOC_IP_MTU          2
#define SOC_TCP_MTU         3
#define SOC_MCAST_TTL       4
#define SOC_MCAST_LOOP      5
#define SOC_MCAST_JOIN      6
#define SOC_MCAST_DROP      7
#define SOC_BCAST_RECV      8
#define SOC_TMO_SND         9
#define SOC_TMO_RCV         10
#define SOC_TMO_CON         11
#define SOC_TMO_CLS         12
#define SOC_IP_LOCAL        13
#define SOC_IP_REMOTE       14
#define SOC_CBK_HND         15
#define SOC_CBK_FLG         16
#define SOC_TCP_STATE       17
#define SOC_RCV_PKT_INF     18
#define SOC_PRT_LOCAL       19

#define NET_IP4_CFG         0
#define NET_IP4_TTL         1
#define NET_BCAST_RCV       2
#define NET_MCAST_JOIN      3
#define NET_MCAST_DROP      4
#define NET_MCAST_TTL       5
#ifdef ACD_SUP
#define NET_ACD_CBK         6
#endif

/* Gateway */
#define FLT_PROT_ALL     0x00
#define FLT_PROT_ICMP    IP_PROTO_ICMP
#define FLT_PROT_TCP     IP_PROTO_TCP
#define FLT_PROT_UDP     IP_PROTO_UDP
#define FLT_PORT_ALL     0x0000
#define FLT_ICMPTYPE_ALL 0xFFFF

typedef void(*IP_FWD_EV_CBK)(UW ev, VP inf);

/* evnet success and failure */
#define FWD_EV_OK                0x10000000
#define FWD_EV_ERR               0x20000000

/* evnet trigger */
#define FWD_EV_PKT               0x01000000
#define FWD_EV_API               0x02000000
#define FWD_EV_TIM               0x04000000

/* event paket forwarding procedure */
#define FWD_EV_PRC_SUCCESS       0x00000001
#define FWD_EV_NATTBL_IN         0x00000002
#define FWD_EV_NATTBL_IN_GPK     0x00000004
#define FWD_EV_NATTBL_OUT_TCP    0x00000008
#define FWD_EV_NATTBL_OUT_TMO    0x00000010
#define FWD_EV_NATTBL_OUT_FUL    0x00000020
#define FWD_EV_FILTER_ALLOW      0x00000040
#define FWD_EV_FLTTBL_IN         0x00000080
#define FWD_EV_FLTTBL_OUT        0x00000100
#define FWD_EV_PRC_ERR_LOW       0x00000200
#define FWD_EV_PRC_ERR_SAMEIF    0x00000400
#define FWD_EV_PRC_ERR_NORTE     0x00000800
#define FWD_EV_PRC_ERR_TTL       0x00001000
#define FWD_EV_PRC_ERR_MEM       0x00002000

/* evnet mask */
#define FWD_EV_MSK_ALL           0xffffffff


#define EV_LINK     -97
#define EV_ADDR     -98


/***************************************************************************
 *  API
 */

/* TCP/IP Stack */

ER net_ini(void);
ER net_cfg(UH dev_num, UH opt, VP val);
ER net_ref(UH dev_num, UH opt, VP val);
ER net_ext(void);

/* Network Buffer */

ER net_buf_ini(void);
ER net_buf_get(T_NET_BUF **buf, UH len, TMO tmo);
void net_buf_ret(T_NET_BUF *buf);

/* Network Device */

ER net_dev_ini(UH dev_num);
ER net_dev_cls(UH dev_num);
ER net_dev_sts(UH dev_num, UH opt, VP val);
ER net_dev_ctl(UH dev_num, UH opt, VP val);
void net_pkt_rcv(T_NET_BUF *pkt);

/* Socket */
#ifndef NET_C
ER cre_soc(UB proto, T_NODE *host);
ER del_soc(UH sid);
#endif
ER con_soc(UH sid, T_NODE *host, UB con_flg);
ER snd_soc(UH sid, VP data, UH len);
ER rcv_soc(UH sid, VP data, UH len);
ER cls_soc(UH sid, UB cls_flg);
ER cfg_soc(ID sid, UB code, VP val);
ER ref_soc(ID sid, UB code, VP val);
ER abt_soc(UH sid, UB code);

/* Gateway */
#ifdef IP4_FWD_SUP
ER add_flt_ip(UW dstip, UB prot, UH dstport, UW fwdip, UH fwdport);
ER add_flt_tcp(UH dstport, UW fwdip, UH fwdport);
ER add_flt_udp(UH dstport, UW fwdip, UH fwdport);
ER add_flt_icmp(UW fwdip);
ER rmv_flt(ID id);
ER set_glb_if(UINT dev_num);
void set_usr_cbk(IP_FWD_EV_CBK cbk, UW cbk_flt);
#else
#define add_flt_ip(a, b, c, d, e)        (E_NOSPT)
#define add_flt_tcp(a, b, c)             (E_NOSPT)
#define add_flt_udp(a, b, c)             (E_NOSPT)
#define add_flt_icmp(a)                  (E_NOSPT)
#define rmv_flt(a)                       (E_NOSPT)
#define set_glb_if(a)                    (E_NOSPT)
#define set_usr_cbk(a, b)                ((void)0)
#endif

void net_tim_tsk(VP_INT exinf);

ER snd_rdy(ID sid);
ER rcv_rdy(ID sid);

#ifdef LO_IF_SUP
typedef ER(*LO_PKT_HDL)(UH,  T_NET_BUF*);
#endif

#ifndef NET_C
#define soc_cre cre_soc
#define soc_del del_soc
#endif
#define soc_con con_soc
#define soc_snd snd_soc
#define soc_rcv rcv_soc
#define soc_cls cls_soc
#define soc_cfg cfg_soc
#define soc_ref ref_soc
#define soc_abt abt_soc

/* Misc */

UW ip_aton(const char *str);
void ip_ntoa(const char *s, UW ipaddr);
UW ip_byte2n(char *s);
void ip_n2byte(char *s, UW ip);

void net_rand_seed(UW seed);
UW net_rand(void);


#ifdef ARP_API_SUP
ER arp_static(T_NET *net, UW ip, UB *mac);
ER arp_ref(T_NET *net, UW ip, UB *mac);
#endif

#ifdef ACD_SUP
ER net_acd(UH dev_num, T_NET_ACD *acd);
#endif

UW get_net_sec(void);
void* net_memset(void *d, int c, SIZE n);
void* net_memcpy(void *d, const void *s, SIZE n);
int net_memcmp(const void *d, const void *s, SIZE n);


#ifdef NET_C
typedef struct t_soc_table {
    UH  sid;        /* Socket ID,   0 - Unused, 1 to NET_SOC_MAX + 1  */
    UB  proto;      /* IP Protocol, 0 - Unused, 17 for TCP, 6 for UDP */
    UH  port;       /* Local Port,  0 - Default, 1 to 65535 */
    TMO snd_tmo;
    TMO rcv_tmo;
    TMO con_tmo;
    TMO cls_tmo;
    UW  sbufsz;
    UW  rbufsz;
    UH  dev_num;    /* Device Number */
    UB  ver;        /* IP version */
}T_SOC_TABLE;
#endif


#ifdef _UC3_ENDIAN_LITTLE
UH ntohs(UH val);
UW ntohl(UW val);
#else
#define ntohs(x) (x)
#define ntohl(x) (x)
#endif /* _UC3_ENDIAN_LITTLE */

#define htons(x) ntohs(x)
#define htonl(x) ntohl(x)

extern UW NET_DEV_MAX;
extern UW NET_SOC_MAX;
extern UW NET_TCP_MAX;
extern UW NET_ARP_MAX;
extern UW NET_MGR_MAX;
extern UW NET_IPR_MAX;
extern UW NET_BUF_CNT;
extern UW NET_BUF_SZ;
extern UW TCP_SND_WND_MAX;

#ifdef __cplusplus
}
#endif
#endif /* NETHDR_H */
