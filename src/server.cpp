// Server side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inetutils.h>

#define DEFAULT_PORT 8080
#define MAXLINE 1024

// Driver code
int main(int argc, char *argv[]) {
	int sockfd;
	char buffer[MAXLINE];
	const char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(DEFAULT_PORT);

	if (argc > 1)
		resolve_host(argv[1], &servaddr);
	if (argc > 2)
		resolve_port(argv[2], &servaddr);

	// Bind the socket with the server address
	if (bind(sockfd, (const struct sockaddr*) &servaddr, sizeof(servaddr))
			< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	} else {
		printf("Server bound to %s:%d\n", inet_ntoa(servaddr.sin_addr),
				servaddr.sin_port);
	}

	socklen_t len;
	int n;

	len = sizeof(cliaddr); // len is value/result

	n = recvfrom(sockfd, (char*) buffer, MAXLINE, MSG_WAITALL,
			(struct sockaddr*) &cliaddr, &len);
	buffer[n] = '\0';
	char *ip = inet_ntoa(cliaddr.sin_addr);
	std::cout << "Client " << ip << ":" << cliaddr.sin_port << " >> " << buffer
			<< std::endl;
	sendto(sockfd, (const char*) hello, strlen(hello), 0,
			(const struct sockaddr*) &cliaddr, len);
	std::cout << "Hello message sent." << std::endl;

	return 0;
}
