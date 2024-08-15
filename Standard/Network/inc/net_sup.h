/***************************************************************************
    MICRO C CUBE / NETWORK
    Static configuration header
    Copyright (c)  2014, eForce Co., Ltd. All rights reserved.

    Version Information  2014.03.31  Created.
                         2014.07.31  Defined NET3_VER
 **************************************************************************/

#ifndef NETSUP_H
#define NETSUP_H
#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************/
/* CPU Architecture dependent Macros                                      */
/**************************************************************************/

#ifdef TKERNEL_PRID     /* Kernel ���ʔԍ� */
#if ((TKERNEL_PRID & 0x0F00) == 0x0100)
#define NET_C_OS        /* Using Compact Kernel */
#elif ((TKERNEL_PRID & 0x0F00) == 0x0200) 
#define NET_S_OS        /* Using Standard Kernel */
#endif
#else
#define NET_HW_OS       /* Using H/W RTOS */
#endif

/* Define endian, if not already defined else where */
#if !defined(_UC3_ENDIAN_BIG) && !defined(_UC3_ENDIAN_LITTLE)
#if defined (__CC_ARM)     /* for ARM Compiler */
#if !defined (__LITTLE_ENDIAN)
#define _UC3_ENDIAN_LITTLE
#endif
#endif
#if defined (__ICCARM__)  /* for IAR Compiler */
#if (__LITTLE_ENDIAN__ == 1)
#define _UC3_ENDIAN_LITTLE
#endif
#endif
#if defined (__GNUC__)    /* for GCC Compiler */
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define _UC3_ENDIAN_LITTLE
#endif
#endif
#if defined (__TMS470__)  /* for CCS Compiler */
#if defined (__little_endian__)
#define _UC3_ENDIAN_LITTLE
#endif
#endif
#ifdef _SH                /* for SuperH */
#ifdef _LIT
#define _UC3_ENDIAN_LITTLE
#endif
#endif
#if defined(__GCC_NDS32)  /* for ANDES GCC */
#define _UC3_ENDIAN_LITTLE
#endif
#endif

/**************************************************************************/
/* Network Architecture dependent Macros                                  */
/**************************************************************************/

#define NET3_VER        3

#ifdef NET_C_OS
#define NET_C           /* Using Network Configurator */
#endif

#ifdef NET_C
#define MAC_RESOLVE     /* MAC Resolver */
#ifdef MAC_RESOLVE
#define UDP_MAC_PORT    5000
#endif
#endif

#ifndef UNDEF_TCP
#define TCP_SUP         /* TCP Enabled */
#endif
#ifndef UNDEF_UDP
#define UDP_SUP         /* UDP Enabled */
#endif
#ifndef UNDEF_IPR
#define IPR_SUP         /* IP Reassembly Enabled */
#endif
#ifndef UNDEF_PING
#define PING_SUP        /* ICMP API Enabled */
#endif

#ifdef UDP_SUP
#ifndef UNDEF_MCAST
#define MCAST_SUP       /* IGMP Enabled */
#endif
#endif

#ifdef TCP_SUP
#ifndef UNDEF_KEEPALIVE
#define KEEPALIVE_SUP
#endif
#endif

#ifndef UNDEF_ACD
#define ACD_SUP
#endif

#ifndef UNDEF_STS       /* Network status Enabled */
#define STS_SUP
#endif


#ifdef POSIX_API_SUP
#define IO_READY_SUP
#define LO_IF_SUP
#ifdef  MCAST_SUP
    #define MCAST_SOC_SUP   /* spec for multicast per socket */
#endif
#define EXT_ALOC_SUP
#endif

#ifdef NET_HW_OS
#ifndef EXT_ALOC_SUP
#define EXT_ALOC_SUP
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif /* NETSUP_H */
