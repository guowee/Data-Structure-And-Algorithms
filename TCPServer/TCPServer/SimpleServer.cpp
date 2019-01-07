#include "SimpleServer.h"

SimpleServer::SimpleServer() : mFd(0) {}

SimpleServer::~SimpleServer() {
	if (mFd > 0)
	{
		::close(mFd);
	}
}

int SimpleServer::start(const unsigned int port)
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);

	if (sfd < 0)
	{
		return sfd;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;//Э��
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP��ַ
	addr.sin_port = htons(port);//�˿ں�
	bzero(&(addr.sin_zero), 8);
	
	if (::bind(sfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		perror("bind error.");
		goto close_fd;
	}

	if (::listen(sfd, 10) < 0) {
		perror("listen error.");
		goto close_fd;
	}

	mFd = sfd;
	return mFd;

close_fd:
	::close(sfd);
	return -1;
}

int SimpleServer::accept()
{
	struct sockaddr_in remote_addr;
	socklen_t addr_len = sizeof(remote_addr);
	return ::accept(mFd, (struct sockaddr *) &remote_addr, &addr_len);
}





