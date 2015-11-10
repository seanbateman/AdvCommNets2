#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <arpa/inet.h>
#include <sys/socket.h>

#define "SERVER 127.0.0.1"
#define BUFSIZE 512
#define PORT 8888

void die(char *s)
{
    perror(s);
    exit(1);
}

void main(void){
    struct sockaddr_in other;
    char buffer[BUFSIZE];
    char data[BUFSIZE];
    int sock;
    int i;
    int send_length = sizeof(other);
    
    if((sock = socket(AF_NET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("Socket");
    }
    
    memset((char *) &other, 0, sizeof(other));
    
    other.sin_family =AF_NET;
    other.sin_port = htons(PORT);
    
    if(inet_aton(SERVER, other.sin_addr) == 0){
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    while(1){
        printf("Enter Data");
        gets(data);
        
        if(sendto(sock, data, strlen(data), 0, (struct sockaddr *) &other, send_length) == -1){
            die("sendto()");
        }
        
        memset(buffer, '\0', BUFSIZE);
        
        if(recvfrom(sock, buffer, BUFSIZE, 0, (struct sockaddr *) &other, &send_length) == -1){
            die("recvfrom()"");
        }
        
        puts(buffer);
    }
    
    close(sock);
    return 0;
}