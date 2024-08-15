/***************************************************************************
    MICRO C CUBE / NETWORK
    Network parameter for evaluation
    Copyright (c)  2014, eForce Co., Ltd. All rights reserved.

    Version Information  2014.12.09  Created.
 **************************************************************************/

#ifndef NETEVA_H
#define NETEVA_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    VP data[12];
#ifdef IPV6_SUP
    VP data2[1];
#endif
}__T_NET;

typedef struct {
    VP data[15];
}__T_NET_DEV;

typedef struct {
    VP data[7];
}__T_NET_ARP;

typedef struct {
    VP data[24];
    VP data2[4];
#ifdef IPV6_SUP
    VP data3[16];
#endif
}__T_NET_SOC;

typedef struct {
    VP data[35];
}__T_NET_TCP;


#define T_NET       __T_NET
#define T_NET_DEV   __T_NET_DEV
#define T_NET_ARP   __T_NET_ARP
#define T_NET_SOC   __T_NET_SOC
#define T_NET_TCP   __T_NET_TCP

#ifdef __cplusplus
}
#endif
#endif /* NETEVA_H */
