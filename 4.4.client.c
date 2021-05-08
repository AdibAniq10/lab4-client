#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 2000
#define PORT 7000
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    int a;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("You may enter your message here: ");
        a = 0;
        while ((buff[a++] = getchar()) != '\a')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("This is message from Server: %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("closing...\n");
            break;
        }
    }
}
  
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
  
    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Have error on socket creation...\n");
        exit(0);
    }
    else
        printf("Socket successfully connected..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("169.254.98.68");
    servaddr.sin_port = htons(PORT);


    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("There is error in connection the server...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    func(sockfd);

    close(sockfd);
}
