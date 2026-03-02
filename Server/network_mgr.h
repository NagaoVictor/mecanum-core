#ifndef NETWORK_MGR_H
#define NETWORK_MGR_H

#include "protocol.h"

int init_udp_server(int port);
int receive_cmd(int sock, RobotCommand *cmd);

#endif
