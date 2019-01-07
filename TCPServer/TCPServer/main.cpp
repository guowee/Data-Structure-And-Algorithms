#include <cstdio>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include "SimpleServer.h"

#define DEFAULT_PORT 10086

int main(int argc, char *argv[])
{
    printf("Start Minicap Server!\n");
	unsigned int port = DEFAULT_PORT;
	unsigned char buffer[MAXSIZE];

	SimpleServer server;


	if (!server.start(port)) {
		printf("Unable to start server.\n");
		return EXIT_FAILURE;
	}
	int accept_fd, sed_len,recv_len,i;
	while (1)
	{
		if ((accept_fd = server.accept()) == -1) {
			perror("accept socket error.");
			continue;
		}

		printf("New client connection!\n");

		if (!fork()) {
			while (1) {
				memset(buffer, 0, MAXSIZE);
				if((recv_len = recv(accept_fd,buffer,MAXSIZE,0)) < 0){
					perror("receive fail!\n");
					close(accept_fd);
					exit(0);
				}
				else if (recv_len > 0) {
					buffer[recv_len] = '\0';
					printf("recvbytes= %d\n", recv_len);
					for (i = 0; i < recv_len; i++)
					{
						printf("0x%02x\n", (unsigned char)buffer[i]);
					}
					//printf("received a connection : %s\n",buf);
					if (sed_len = send(accept_fd, buffer, recv_len, 0) == -1) {
						perror("send fail!\n");
						close(accept_fd);
						exit(0);
					}
					else {
						printf("sendbytes=%d\n", sed_len);
						//	printf("send beyts are:%s\n",buf);
					}
				}
			}
		}
		close(accept_fd);
		waitpid(-1, NULL, WNOHANG);
	}
    return EXIT_SUCCESS;
}