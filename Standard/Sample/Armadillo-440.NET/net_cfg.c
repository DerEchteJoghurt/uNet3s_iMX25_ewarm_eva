/************************************************************************
    TCP/IP Configuration File
    
    Copyright (c) 2014 eForce Co., Ltd. All rights reserved.
    
    2014-03-06: Created
 ************************************************************************/

#include "kernel.h"
#include "net_hdr.h"
#include "net_def.h"
#include "net_sts.h"
#include <string.h>

/*******************************************
    Define Local IP Address
********************************************/
T_NET_ADR gNET_ADR[] = {
    {
        0x0,            /* Reserved */
        0x0,            /* Reserved */
        0xC0A80158,     /* IP address  (192.168.  1. 88) */
        0xC0A80101,     /* Gateway     (192.168.  1.  1) */
        0xFFFFFF00,     /* Subnet mask (255.255.255.  0) */
    }
};

/*******************************************
    Define TCP/IP Kernel resource
********************************************/
const T_CMPF c_net_mpf = {TA_TFIFO, 64, 1576, NULL, NULL};


/*******************************
     Memory function
 *******************************/
void* net_memset(void *d, int c, SIZE n)
{
#ifdef _KERNEL_MEMSET_
    return _kernel_memset(d, c, n);
#else
    return memset(d, c, n);
#endif
}

void* net_memcpy(void *d, const void *s, SIZE n)
{
#ifdef _KERNEL_MEMCPY_
    return _kernel_memcpy(d, s, n);
#else
    return memcpy(d, s, n);
#endif
}

int net_memcmp(const void *d, const void *s, SIZE n)
{
#ifdef _KERNEL_MEMCMP_
    return _kernel_memcmp(d, s, n);
#else
    return memcmp(d, s, n);
#endif
}

