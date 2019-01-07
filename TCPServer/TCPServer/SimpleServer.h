#ifndef MINICAP_SIMPLE_SERVER_H
#define MINICAP_SIMPLE_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define MAXSIZE 2048

class SimpleServer
{
public:
	SimpleServer();
	~SimpleServer();

	int start(const unsigned int port);
	int accept();

private:
	int mFd;
};
#endif
