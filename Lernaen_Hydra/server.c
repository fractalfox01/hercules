#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define MAX 80
#define PORT 7331
#define SA struct sockaddr

static void active_connection(int sockfd)
{
	char buff[MAX];

	while (1)
	{
		bzero(buff, MAX);

		read(sockfd, buff, sizeof(buff));
		if (strncmp("ping", buff, 4) == 0)
		{
			write(sockfd, "pong pong\n", 11);
			memset(buff, '\0', MAX);
		}
		if (strncmp("pong", buff, 4) == 0)
		{
			write(sockfd, "pong", 4);
			memset(buff, '\0', MAX);
		}
		if (strncmp("exit", buff, 4) == 0)
		{
			printf("Server Exit...\n");
			break ;
		}
		else
		{
			memset(buff, '\0', sizeof(buff));
		}
	}
}

static void	daemonizer(void)
{
	pid_t	pid;

	pid = fork();

	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	if (setsid() < 0)
		exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int sockfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cli;

	if (ac == 2)
	{
		if (strncmp("-D", av[1], 2) == 0)
			daemonizer();
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		printf("socket creation failed\n");
		exit(0);
	}
	else
	{
		printf("socket successfully created..\n");
	}
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("socket bind failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully binded..\n");
	}

	if (listen(sockfd, 5) != 0)
	{
		printf("Listen failed.\n");
		exit(0);
	}
	else
	{
		printf("Server Listening...\n");
	}

	connfd = accept(sockfd, (SA *)&cli, &len);
	if (connfd < 0)
	{
		printf("server accept failed..\n");
		exit(0);
	}
	else
	{
		printf("server accepted the client...\n");
	}

	active_connection(connfd);

	close(sockfd);
}
