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
#include "graph.h"


graph_t *build_first_topo()
{
    graph_t* topo = create_new_graph("Topology");
    node_t* R0_re = create_new_node(topo, "R0_re");
    node_t* R1_re = create_new_node(topo, "R1_re");
    node_t* R2_re = create_new_node(topo, "R2_re");

    insert_link_between_two_nodes(R0_re,R1_re, "0/0", "0/1", 0);
    insert_link_between_two_nodes(R1_re,R2_re, "0/2", "0/3", 0);
    insert_link_between_two_nodes(R2_re,R0_re, "0/5", "0/4", 0);
    return topo;
}