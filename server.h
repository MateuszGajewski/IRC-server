//
// Created by arabica on 16.12.2020.
//

#ifndef SK_SERVER_H
#define SK_SERVER_H

#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <vector>
#include "user.h"
#include "channel.h"

//Klasa implementująca serwer IRC

class server {
public:
    fd_set		fds;
    fd_set  fds_w;


    int begin_server(int port);

    static int accept_new_user(std::vector<user> *users, int g_socket_fd);

    static void update_fdset(fd_set *fds, fd_set *fds_w, int *fd_max, std::vector<user> &users, int g_socket_fd);

    static int create_s_socket(struct sockaddr_in *sock, int port);

    static int accept_con(int socket_fd, struct sockaddr_in *r_addr);

    static int handle_clients(fd_set *fds, fd_set *fds_w, std::vector<user> &users);
    static void send_msg(char * buff, int cfd);
    static int recive_msg(char * buff, int cfd);
    static void del_user(std::vector<user> &users, int ind);
    static void handle_cmd(int num, char *buff, std::vector<user> &users);
    static void register_user(int num , std::vector<std::string> args, std::vector<user> &users);
    static void handle_chan(int num , std::vector<std::string> args, std::vector<user> &users);
    static void privmsg(int num, std::vector<std::string> args, std::vector<user> &users);
    static int find_usr_by_nick(std::string nick, std::vector<user> &users);
    static void broadcast_nick_to_chan(std::string nick);


};


#endif //SK_SERVER_H
