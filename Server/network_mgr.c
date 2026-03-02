#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "protocol.h"

int init_udp_server(int port){
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_addr.s_addr = INADDR_ANY,
		.sin_port = htons(port)
	};
	bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	return sock;
}

int receive_cmd(int sock, RobotCommand *cmd) {
	int n = recv(sock, cmd, sizeof(RobotCommand),0);
	if (n<0) perror("Erro no recv");
	return n;
}
