#ifndef __GRAPH__
#define __GRAPH__

#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void dumpinterface(interface_t* intf);
void dumpgraph(graph_t* graph);

void dumpnode(node_t* node);

graph_t* create_new_graph(char *topology_name)
{
    graph_t *graph = calloc(1, sizeof(graph_t));
    strncpy(graph->topology_name, topology_name, 32);
    graph->topology_name[32] = '\0';
    glthread_init(&graph->node_list);
    return graph;
}



node_t* create_new_node(graph_t *graph, char *node_name)
{
    node_t *new_node = calloc(1, sizeof(node_t));
    strncpy(new_node->node_name, node_name, NODE_NAME_SIZE);
    new_node->node_name[16] = '\0';
    glthread_init(&new_node->graph_glue);

    glthread_add_next(&graph->node_list, &new_node->graph_glue);
    return new_node;
}


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

void insert_link_between_two_nodes(node_t* node1, node_t* node2, char* from_if_name, char* to_if_name, unsigned int cost)
{
    link_t *link = calloc(1, sizeof(link_t));
    strncpy(link->intf1.if_name, from_if_name, 16);
    strncpy(link->intf2.if_name, to_if_name, 16);

    link->intf1.att_node = node1;
    link->intf2.att_node = node2;

    link->intf1.link = link;
    link->intf2.link = link;

    link->cost = cost;

    int getemptyslot = get_node_intf_available_slot(node1);
    node1->intf[getemptyslot] = &link->intf1;
    getemptyslot = get_node_intf_available_slot(node2);
    node2->intf[getemptyslot] = &link->intf2;
}


void dumpgraph(graph_t* graph)
{
    printf("Topology Name: %s\n", graph->topology_name);
    node_t* node = NULL;
    glthread_t* curr;

    ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr)
    node = graph_glue_to_node(curr);
    dumpnode(node);
    ITERATE_GLTHREAD_END(&graph->node_list, curr)
}



void dumpnode(node_t* node)
{
    printf("Node Name: %s\n", node->node_name);
    unsigned int i=0;
    for(;i<MAX_INTF_PER_NODE; i++)
    {
        if(!node->intf[i])
        break;

        dumpinterface(node->intf[i]);
    }
}

void dumpinterface(interface_t* intf)
{
    link_t* link = intf->link;
    node_t* node = get_nbr_node(intf); 
    printf("LocalNode: %s, Interface Name %s, NbrNode %s, Cost %u \n", intf->att_node->node_name, intf->if_name, node->node_name, link->cost);
}















#endif