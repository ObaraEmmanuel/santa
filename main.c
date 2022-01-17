#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9990
#define BUFF_SIZE 4096
#define SA struct sockaddr

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed!\n");
        exit(EXIT_FAILURE);
    } else
        printf("Socket successfully created...\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("20.110.238.2");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed!\n");
        exit(EXIT_FAILURE);
    }

    char buff[BUFF_SIZE];
    size_t input_len = recv(sockfd, buff, BUFF_SIZE, 0);

    long floor_num = 0;
    for(size_t i = 0; i < input_len - 1; i++){
        if(buff[i] == '(')floor_num++;
        else if(buff[i] == ')') floor_num--;
    }
    char floor[20];
    sprintf(floor, "%ld\n", floor_num);
    printf("input: %s", buff);
    printf("floor: %s", floor);
    send(sockfd, floor, 20, 0);
    bzero(buff, BUFF_SIZE);
    recv(sockfd, buff, BUFF_SIZE, 0);
    printf("%s", buff);
    // the server seems to do the opposite so
    // my answers are always correct in magnitude but wrong in sign
    // this seems to be a problem on the server end.
    return 0;
}
