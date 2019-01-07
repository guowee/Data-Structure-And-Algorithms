#include <cstdio>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define DEFAULT_PORT  10086
#define BUFFER_SIZE 1024
const char* IP = "127.0.0.1";

int main()
{
	socklen_t len;
	char buf[BUFFER_SIZE];

	///����sockfd
	int sock_cli = socket(AF_INET, SOCK_STREAM, 0);

	///����sockaddr_in
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(DEFAULT_PORT);  ///�������˿�

	if (inet_aton(IP,(struct in_addr*)&servaddr.sin_addr.s_addr) == 0) {
		perror("IP error");
		exit(1);
	}

	//���ӷ��������ɹ�����0�����󷵻�-1
	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) <0)
	{
		perror("connect");
		exit(1);
	}

	printf("******Client Start******\n");
	char sendbuf[BUFFER_SIZE];
	char recvbuf[BUFFER_SIZE];
	//�ͻ��˽�����̨�������Ϣ���͸��������ˣ�������ԭ��������Ϣ
	while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
	{
		send(sock_cli, sendbuf, strlen(sendbuf), 0); ///����
		if (strcmp(sendbuf, "exit\n") == 0)
		{
			printf("client exited.\n");
			break;
		}
		printf("client receive:\n");
		recv(sock_cli, recvbuf, sizeof(recvbuf), 0); ///����
		fputs(recvbuf, stdout);

		memset(sendbuf, 0, sizeof(sendbuf));
		memset(recvbuf, 0, sizeof(recvbuf));
	}
	
	close(sock_cli);
	return 0;
}