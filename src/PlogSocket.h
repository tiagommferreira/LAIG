

#ifndef __CGFExample__PlogSocket__
#define __CGFExample__PlogSocket__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy()...
#include <stdlib.h>	// for atoi()...
#include <unistd.h>	// for gethostname()...
#include <ctype.h>	// for tolower()...
#include <iostream>

#define BUFS	1024
#define NAMS	64


class PlogSocket {
public:
    PlogSocket();
    void connectSocket();
    void sendMessage(char*);
    char* receiveMessage();
    void disconnectSocket();
private:
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[BUFS];
};

#endif /* defined(__CGFExample__PlogSocket__) */
