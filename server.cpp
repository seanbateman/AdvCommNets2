#include <stdio.h>
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>


#define BUFFSIZE = 512;
#define PORT = 8888;

void die(char *s){
    perror(s);
    exit(1);
}

int main(void){
    struct sockaddr_in me;
    struct sockaddr_in other;
    char buffer[BUFFSIZE];
    
    int sock;
    int i;
    int send_length = sizeof(other);
    int recv_length;
    
    
    if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    } 
    
    memset((char *) &me, 0, sizeof(me));
    
    me.sin_family = AF_INET;
    me.sin_port = htons(PORT);
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sock , (struct sockaddr*)&me, sizeof(me)) == -1){
        die("bind");
    }
    
    while(1){
        printf("Waiting for data");
        fflush(stout);
        
        if(recv_length = recvfrom(sock, buffer, BUFFSIZE, 0, (struct sockaddr *) &other, &me) == -1){
            die("recvfrom()");
        }
        
        printf("Received packet from %s:%d\n", inet_ntoa(other.sin_addr), ntohs(other.sin_port));
        printf("Data: %s\n" , buffer);
        
        if (sendto(sock, buffer, recv_length, 0, (struct sockaddr*) &other, send_lengthlen) == -1)
        {
            die("sendto()");
        }
    }
    
    close(sock);
    return 0;
}