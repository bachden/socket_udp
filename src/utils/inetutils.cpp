#include <inetutils.h>

void resolve_host(const char *host, struct sockaddr_in *addr) {
	if (inet_pton(AF_INET, host, &addr->sin_addr.s_addr)) {
		addr->sin_family = AF_INET;
		return;
	}

	if (inet_pton(AF_INET6, host, &addr->sin_addr.s_addr)) {
		addr->sin_family = AF_INET6;
		return;
	}

	struct hostent *ghbn = gethostbyname(host);
	if (ghbn) {
		memcpy(&addr->sin_addr.s_addr, ghbn->h_addr, ghbn->h_length);
		addr->sin_family = ghbn->h_addrtype;
		return;
	}

	std::cerr << "Failed to resolve " << host << std::endl;
}

void resolve_port(const char *port, struct sockaddr_in *addr) {
	addr->sin_port = htons(atoi(port));
}
