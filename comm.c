#include "comm.h"
#include "graph.h"
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h> /*for struct hostent*/


void init_udp_socket(node_t *node)
{
    if(node->udp_port_number)
        return;
    
    node->udp_port_number = get_next_udp_port_number();

    int udp_socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(udp_socket_fd == -1)
    {
        printf("Socket creation failed at node: %s", node->node_name);
        return;
    }

    struct sockaddr_in node_addr;
    node_addr.sinfamily = AF_INET;
    node_addr.sin_port        = htons(ode->udp_port_number);
    node_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(udp_socket_fd, (struct sockaddr_in *)&node_addr, sizeof(sockaddr_in)) == -1){
        printf("Error : socket bind failed for Node %s\n", node->node_name);
        close(udp_sock_fd);
        return;
    }

}