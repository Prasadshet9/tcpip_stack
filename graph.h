#ifndef __GRAPH_H__
#define __GRAPH_H__

/*
                          +----------+
                      0/4 |          |0/0
         +----------------+   R0_re  +---------------------------+
         |                |          |                           |
         |                +----------+                           |
         |                                                       |
         |                                                       |
         |                                                       |
         |                                                       |
         |0/5                                                    |0/1
     +---+---+                                              +----+-----+
     |       |0/3                                        0/2|          |
     | R2_re +----------------------------------------------+    R1_re |
     |       |                                              |          |
     +-------+                                              +----------+
*/

#include <glthread/glthread.h>
#include <assert.h>
#include "net.h"

#define NODE_NAME_SIZE   16
#define IF_NAME_SIZE     16
#define MAX_INTF_PER_NODE   10

/*Forward Declarations*/
typedef struct node_ node_t;
typedef struct link_ link_t;
typedef struct intf_nw_prop_ intf_nw_prop_t;

typedef struct interface_ {

    char if_name[IF_NAME_SIZE];
    struct node_ *att_node;
    struct link_ *link;
    intf_nw_prop_t intf_nw_props;
} interface_t;

struct link_ {

    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
}; 

struct node_ {

    char node_name[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE];
    int udp_port_number;
    int udp_sock_fd;
    node_nw_prop_t node_nw_props;
    glthread_t graph_glue;
};


typedef struct graph_{

    char topology_name[32];
    glthread_t node_list; 
} graph_t;

static inline node_t* get_nbr_node(interface_t *interface)
{
    assert(interface->att_node);
    assert(interface->link);

    link_t *link = interface->link;
    if(&link->intf1 == interface)
        return link->intf2.att_node;
    else
        return link->intf1.att_node;
}

static inline int 
get_node_intf_available_slot(node_t *node)
{
    for(int i = 0; i<MAX_INTF_PER_NODE; i++)
    {
        if(node->intf[i])
            continue;
        return i;
    }
    return -1;
}

GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, graph_glue)


static inline interface_t* get_node_if_by_name(node_t *node, char *if_name)
{
    int i ;
    interface_t *intf;

    for( i = 0 ; i < MAX_INTF_PER_NODE; i++){
        intf = node->intf[i];
        if(!intf) return NULL;
        if(strncmp(intf->if_name, if_name, IF_NAME_SIZE) == 0){
            return intf;
        }
    }
    return NULL;
}

extern void dumpgraph(graph_t* graph);

#endif
