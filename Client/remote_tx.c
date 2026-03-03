#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <termios.h>
#include "../Server/protocol.h"

char getch(){
	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) <0) perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0) perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0,TCSADRAIN, &old) <0) perror("tcsetattr ~ICANON");
	return buf;

}	



int main(){
	int sock;
	struct sockaddr_in server_addr;
	RobotCommand cmd = {0,0,0,0};

	sock = socket(AF_INET, SOCK_DGRAM,0);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr = inet_addr("100.78.54.126");

	printf("Controle Remoto Ativo via Tailscale. Pressione W para mover...\n");
	
	while(1) {
		char tecla = getch();
		
		

		if(tecla=='w'){cmd.y=100;cmd.x=0; cmd.r=0;}
		else if(tecla=='s'){cmd.y=-100;cmd.x=0; cmd.r=0;}
		else if(tecla=='a'){cmd.y=0;cmd.x=-100;cmd.r=0;}
		else if(tecla=='d'){cmd.y;cmd.x=100;cmd.r=0;}
		else if(tecla=='j'){cmd.y=0; cmd.x=0;cmd.r=-50;}
		else if(tecla=='l'){cmd.y=0;cmd.x=0;cmd.r=50;}
		else if(tecla=='q')break;
		else {cmd.y =0; cmd.x=0; cmd.r=0; }		

		sendto(sock,&cmd, sizeof(RobotCommand), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		printf("\rEnviado -> Y:%d X:%d R:%d ", cmd.y, cmd.x, cmd.r);
		fflush(stdout);		

		usleep(20000);
		cmd.y=0;cmd.x=0;cmd.r=0;
		sendto(sock,&cmd, sizeof(RobotCommand), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		}
	close(sock);
	return 0;
}
	
