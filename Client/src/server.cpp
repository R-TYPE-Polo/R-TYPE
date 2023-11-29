/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT    8080
#define MAXLINE 1024

int sendToServer(std::string messageToSend)
{
    int                sockfd;
    char               buffer[MAXLINE];
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family      = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port        = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    socklen_t len;
    int       n;

    len = sizeof(cliaddr); //len is value/result

    n         = recvfrom(sockfd, (char*)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, messageToSend, messageToSend.size(), MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);
    std::cout << "Hello message sent." << std::endl;

    return 0;
}
