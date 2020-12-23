//
// Created by arabica on 16.12.2020.
//

#include "server.h"

int	server::handle_clients( fd_set *fds, std::vector<int> users)
{
    int rd = 0;
    std::cout<<users.size()<<std::endl;
    for (int i = 0 ; i< users.size(); i++)
    {

        char buff[1024];
        if (FD_ISSET(users[i], fds))
        {
            rd = server::recive_msg(buff, users[i]);
            if (rd == 0){
            close(users[i]);
                continue;}
            std::cout<<buff<<std::endl;
            char ans[] = "%reply elo \n \r";
            if (buff[0] == 'P'){continue;}
            server::send_msg(ans, users[i]);
            for (int i =0; i< 1024; i++){
                buff[i] = 0;
            }
            //close(users[i]);
        }
        //FD_CLR(&fds);
    }
    return (0);
}

void server::send_msg(char * buff, int cfd){
    int rc = 0;
    while (buff[rc-1] != '\r'){
        rc += write(cfd, buff+rc, 1);
    }


}
int	server::accept_con(int socket_fd, struct sockaddr_in *r_addr)
{
    socklen_t		addrlen;
    int			out_fd;

    addrlen = sizeof(struct sockaddr_in);
    if ((out_fd = accept(socket_fd,
                         (struct sockaddr *)r_addr,
                         (socklen_t*)&addrlen)) == -1)
        return (-1);
    return (out_fd);
}

int	server::create_s_socket(struct sockaddr_in *sock, int port)
{
    int	socket_fd;
    int	en;

    memset(sock, 0, sizeof(*sock));
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (-1);
    en = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(int)) < 0)
        return (-1);
    sock->sin_family = AF_INET;
    sock->sin_addr.s_addr = INADDR_ANY;
    sock->sin_port = htons(port);
    if (bind(socket_fd, (struct sockaddr *)sock, sizeof(*sock)) < 0)
        return (-1);
    return (socket_fd);
}
int	server::accept_new_user(std::vector<int> * users, int g_socket_fd)
{
    struct sockaddr_in	r_addr;
    socklen_t		addrlen;
    int			nsock;

    nsock = server::accept_con(g_socket_fd, &r_addr);
    (*users).push_back(nsock);
    std::cout<< "Incoming connection from %s"<<inet_ntoa(r_addr.sin_addr)<<std::endl;
}

int server::recive_msg(char * buff, int cfd){
    int rc =0;
    int r = 1;
    while(r!=0){
        r = read(cfd, buff+rc, 1);
        rc+=r;
        if(*(buff+rc-1) == '\n'){
            std::cout<<rc<<std::endl;
            return 1;
            break;
        }
    }
    if (rc == 0){std::cout<<"quit"<<std::endl; return 0;}
}
void server::update_fdset(fd_set *fds, int *fd_max, std::vector<int> users, int g_socket_fd)
{


    *fd_max = g_socket_fd;
    FD_ZERO(fds);
    FD_SET(g_socket_fd, fds);

    for (int i = 0 ; i< users.size(); i++)
    {
        FD_SET(users[i], fds);
        *fd_max = (users[i] > *fd_max ? users[i]: *fd_max);

    }
}

[[noreturn]] int server::begin_server(int port){

    int			fd_max, g_socket_fd;
    std::vector<int> users;
    struct sockaddr_in	l_addr;

    if ((g_socket_fd = server::create_s_socket(&l_addr, port)) == -1)
        return (-1);
    listen(g_socket_fd, 10);
    //init_handler(&h, &users, &chans);
    while (1)
    {


        server::update_fdset(&fds, &fd_max, users, g_socket_fd);
        if (select(fd_max + 1, &fds, NULL, NULL, NULL) < 0)
            std::cout<<"elo"<<std::endl;
        if (FD_ISSET(g_socket_fd, &fds))
            server::accept_new_user(&users, g_socket_fd);
        server::handle_clients(&fds, users);
    }
    return 0;

}
