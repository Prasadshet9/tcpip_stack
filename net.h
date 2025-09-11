/*
--------------Network Properties---------------

            RO_re
                Flag;
    L3 Prop:    Loopback Address Flag
                lb Address         
-----------------------------------------------
            0/0 - interface
    L2 Prop:    Mac address

    L3 Prop:    IP Address Flag
                IP Address
                Mask
-----------------------------------------------
*/
#ifndef __NET__
#define __NET__

#include <string.h>
#include "util.h"


typedef unsigned char boolean;
typedef boolean bool_t;
#define SET_BIT(n, pos)               (n = n | (1 << pos))
#define IS_BIT_SET(n, bit)       (n & (1 << (bit)))

#define L3_ROUTER                (1 << 0)  /*this will have loopback configured*/
#define L2_SWITCH                (1 << 1)
#define HUB                      (1 << 2)


typedef struct interface_ interface_t;
typedef struct node_ node_t;


typedef struct ip_add_{
    char ip_addr[16];    /*255:255:255:255 --> 15 Char + '\0' -> 16*/
}ip_add_t;


typedef struct mac_addr_{
    char mac[48];    /*255:255:255:255 --> 17 Char + '\0' -> 18*/
}mac_add_t;

typedef struct node_nw_prop_{
    unsigned int flag;
    /*L3 Properties*/
    bool_t is_lb_addr_config;
    ip_add_t lb_addr;
}node_nw_prop_t;

typedef struct intf_nw_prop_{
    /*L2 Properties*/
    mac_add_t mac_addr;
    /*L3 Properties*/
    bool_t is_ip_addr_config;
    ip_add_t ip_add;
    char mask;
}intf_nw_prop_t;

static inline void init_node_nw_prop(node_nw_prop_t *node_nw_props)
{
    node_nw_props->flag = 0;
    node_nw_props->is_lb_addr_config = FALSE;
    memset(node_nw_props->lb_addr.ip_addr, 0, 16);
}

static inline void init_intf_nw_prop(intf_nw_prop_t *intf_nw_props)
{
    memset(intf_nw_props->mac_addr.mac, 0, 48);
    intf_nw_props->is_ip_addr_config = FALSE;
    intf_nw_props->mask = 0;
    memset(intf_nw_props->ip_add.ip_addr, 0, 16);
    
}

#define IF_MAC(intf_ptr)                 ((intf_ptr)->intf_nw_props.mac_addr.mac)
#define IF_IP(interface)                 ((interface)->intf_nw_props.ip_add.ip_addr)

extern void node_set_device_type(node_t *node, unsigned int type);
extern void node_set_loopback_address(node_t *node, char *ip_addr);
extern void node_set_intf_ip_address(node_t *node, char *intf_name, char *intf_ip_addr, char subnet);


#endif