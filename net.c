#include "graph.h"

void interface_assign_mac_address(interface_t* interface)
{
    memset(interface->intf_nw_props.mac_addr.mac, 0 , 48);
    strncpy(interface->intf_nw_props.mac_addr.mac, interface->att_node->node_name, NODE_NAME_SIZE);
    strncat(interface->intf_nw_props.mac_addr.mac, interface->if_name, IF_NAME_SIZE);
}


void node_set_device_type(node_t *node, unsigned int type)
{
    SET_BIT(node->node_nw_props.flag, type);
}

void node_set_loopback_address(node_t *node, char *ip_addr)
{
    assert(ip_addr);
    if(IS_BIT_SET(node->node_nw_props.flag, HUB))
        assert(0);
    if(!IS_BIT_SET(node->node_nw_props.flag, L3_ROUTER))
        assert(0);
    
    /*The node is configured as a ROUTER and the IP Address can be configured*/
    node->node_nw_props.is_lb_addr_config = TRUE;
    strncpy(node->node_nw_props.lb_addr.ip_addr, ip_addr, 16);
    //return TRUE;
}


void node_set_intf_ip_address(node_t *node, char *intf_name, char *intf_ip_addr, char subnet)
{

    interface_t *interface = get_node_if_by_name(node, intf_name);
    if(!interface)
        assert(0);

    interface->intf_nw_props.is_ip_addr_config = TRUE;
    strncpy(IF_IP(interface), intf_ip_addr, 16);
    interface->intf_nw_props.mask = subnet;
    //return TRUE;
}