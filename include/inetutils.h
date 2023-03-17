#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

void resolve_host(const char *host, struct sockaddr_in *addr);

void resolve_port(const char *port, struct sockaddr_in *addr);
