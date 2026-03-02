#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Server/protocol.h"

int main(){
	int sock;
	struct sockaddr_in server_addr;
	RobotCommand cmd = {0,0,0,1};

	sock = socket(AF_INET, SOCK_DGRAM,0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr = inet_addr("100.78.54.126");

	printf("Controle Remoto Ativo via Tailscale. Pressione W para mover...\n");
	
	while(1) {
		char tecla = getchar();
		if(tecla=='w'){cmd.y=100; cmd.x=0;}
		if(tecla=='s'){cmd.y=0; cmd.x=0;}
		if(tecla=='q')break;

		sendto(sock, &cmd, sizeof(RobotCommand), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
		
		printf("Enviando: Y=%d | Bateria: (Aguardando Telemetria...)\n", cmd.y);
	}
	close(sock);
	return 0;
}
