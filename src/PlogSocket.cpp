#include "PlogSocket.h"


PlogSocket::PlogSocket() {
    
}

void PlogSocket::connectSocket() {
    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Opening stream socket");
        exit(1);
    }
    
    /* Connect socket using server name indicated in the command line */
    server.sin_family = AF_INET;
    hp = gethostbyname("127.0.0.1");
    if (hp == NULL)
    {
        perror("Trying to get host by name");
        exit(2);
    }
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons(60070);
    
    if (connect(sock, (struct sockaddr *)&server, sizeof server) < 0)
    {
        perror("Connecting stream socket");
        exit(1);
    }
}

void PlogSocket::sendMessage(char *buf) {
    /* Get data from stdio and send through socket */
    if (write (sock, buf, strlen(buf)+1) < 0)
        perror("Writing on stream socket");
}

char* PlogSocket::receiveMessage() {
    //int bytesRecv = SOCKET_ERROR;
    int pos = 0;
    char * answer;
    while (true) {
        recv(sock, &answer[pos], 1, 0);
        if (answer[pos] == '\n')
            break;
        pos++;
    }
    answer[pos] = 0;
    return answer;
}

void PlogSocket::disconnectSocket() {
    close(sock);
}