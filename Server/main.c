#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "protocol.h"
#include "motor_driver.h"
#include "network_mgr.h"

volatile RobotCommand global_cmd = {0,0,0,0};

void* net_thread(void* arg) {
	RobotCommand *cmd_ptr = (RobotCommand*)arg;
	int sock = init_udp_server(8888);
	if (sock < 0){
		perror("Erro ao abrir socket UDP");
		return NULL;
		}	
	
	while(1) {
		receive_cmd(sock,cmd_ptr);
	}
	return NULL;
}

int main() {
	pthread_t tid;
	fd_i2c = init_pca9685();
	if (fd_i2c < 0){
		printf("Erro: Hardware PCA9685 (0x40) nao encontrado!\n");
		return 1;
	}
	if (pthread_create(&tid, NULL, net_thread,(void*)&global_cmd) !=0) {
		perror("Erro ao criar thread de rede");
		return 1;
	};
	
	printf("--- Core do Robo Ativo (PI 5) ---\n");
	while(1) {
				
		
		apply_mecanum(global_cmd.x, global_cmd.y, global_cmd.r);
		
		printf("\r[Y:%4d | X:%4d]", global_cmd.y, global_cmd.x);
		fflush(stdout);
		
		
		usleep(20000);

	}
	return 0;
}
