#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define	PORT 7331 
#define SA struct sockaddr

static void active_connection(int sockfd)
{
	char buff[MAX];
	int n;

	while (1)
	{
		bzero(buff, sizeof(buff));
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		if (strlen(buff) == 5)
		{	
			if (strncmp("ping", buff, 4) == 0 || strncmp("pong", buff, 4) == 0)
			{
				write(sockfd, buff, sizeof(buff));
				bzero(buff, sizeof(buff));
				read(sockfd, buff, sizeof(buff));
				printf("%s\n", buff);
			}
			if (strncmp("exit", buff, 4) == 0)
			{
				write(sockfd, buff, sizeof(buff));
				bzero(buff, sizeof(buff));
				return ;
			}
			bzero(buff, sizeof(buff));
		}
		else
			memset(buff, '\0', sizeof(buff));
	}			
}

int	main(void)
{
	int sockfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET	, SOCK_STREAM, 0);

	if (sockfd == -1)
	{
		printf("Socket creation failed...\n");
		return (0);
	}
	else
		printf("socket Created Successfully..\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("Connection with the server failed..\n");
		return (0);
	}
	else
	{
		printf("Connecting to host %s on port %d\n", "127.0.0.1", PORT);
	}

	active_connection(sockfd);

	close(sockfd);
	return (0);
}
