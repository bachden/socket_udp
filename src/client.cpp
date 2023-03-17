// Client side implementation of UDP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <inetutils.h>

#define DEFAULT_PORT 8080
#define MAXLINE 1024

// Driver code
int main(int argc, char **argv) {
	int sockfd;
	char buffer[MAXLINE];
	const char *hello = "Hello from client";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(DEFAULT_PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if (argc > 1) {
		resolve_host(argv[1], &servaddr);
	}

	if (argc > 2) {
		resolve_port(argv[2], &servaddr);
	}

	std::cout << "Connecting to: " << inet_ntoa(servaddr.sin_addr) << ":"
			<< ntohs(servaddr.sin_port) << std::endl;

	int n;
	socklen_t len;

	sendto(sockfd, (const char*) hello, strlen(hello), 0,
			(const struct sockaddr*) &servaddr, sizeof(servaddr));

	std::cout << "Hello message sent." << std::endl;

	n = recvfrom(sockfd, (char*) buffer, MAXLINE,
	MSG_WAITALL, (struct sockaddr*) &servaddr, &len);
	buffer[n] = '\0';
	std::cout << "Server :" << buffer << std::endl;

	close(sockfd);
	return 0;
}
