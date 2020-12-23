//
// Created by arabica on 16.12.2020.
//

#include "server.h"
#include "user.h"

int	server::handle_clients( fd_set *fds, fd_set *fds_w, std::vector<user> &users)
{
    int rd = 0;
    std::cout<<users.size()<<std::endl;
    for (int i = 0 ; i< users.size(); i++)
    {

        char buff[1024];
        if (FD_ISSET(users[i].fd, fds))
        {
            rd = server::recive_msg(buff, users[i].fd);
            if (rd == 0){
                shutdown(users[i].fd, SHUT_RDWR);
                users[i].status = -1;
                continue;}
            std::cout<<buff<<std::endl;

            if (buff[0] == 'P'){continue;}
            char ans[] = "%reply :127.0.0.1 001 a Welcome to my IRC server a!a@127.0.0.1.\n \r";
            server::send_msg(ans, users[i].fd);
            for (int i =0; i< 1024; i++){
                buff[i] = 0;
            }
            //close(users[i]);
        }
        //FD_CLR(&fds);
        if (FD_ISSET(users[i].fd, fds_w))
        {
            char ans[] = "%reply :127.0.0.1 001 a Welcome to my IRC server a!a@127.0.0.1.\r";
            server::send_msg(ans, users[i].fd);
            users[i].to_write = false;
            //close(users[i]);
        }
    }
    return (0);
}

void server::send_msg(char * buff, int cfd){
    int rc = 0;
    while (buff[rc-1] != '\n'){
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
int	server::accept_new_user(std::vector<user> *users, int g_socket_fd)
{
    struct sockaddr_in	r_addr;
    socklen_t		addrlen;
    int			nsock;

    nsock = server::accept_con(g_socket_fd, &r_addr);
    user u = user();
    u.fd = nsock;
    (*users).push_back(u);
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
void server::update_fdset(fd_set *fds, fd_set *fds_w,  int *fd_max, std::vector<user> &users, int g_socket_fd)
{

    for (int i =0; i<users.size(); i++){
        if (users[i].status == -1)
            del_user(users, i);
    }
    *fd_max = g_socket_fd;
    FD_ZERO(fds);
    FD_SET(g_socket_fd, fds);
    FD_ZERO(fds_w);
    FD_SET(g_socket_fd, fds_w);

    for (int i = 0 ; i< users.size(); i++)
    {
        FD_SET(users[i].fd, fds);
        if (users[i].to_write == true)
            FD_SET(users[i].fd, fds_w);
        *fd_max = (users[i].fd > *fd_max ? users[i].fd: *fd_max);

    }
    FD_ZERO(fds_w);
}

[[noreturn]] int server::begin_server(int port){

    int			fd_max, g_socket_fd;
    std::vector<user> users;
    struct sockaddr_in	l_addr;

    if ((g_socket_fd = server::create_s_socket(&l_addr, port)) == -1)
        return (-1);
    listen(g_socket_fd, 10);
    //init_handler(&h, &users, &chans);
    while (1)
    {


        server::update_fdset(&fds, &fds_w, &fd_max, users, g_socket_fd);
        if (select(fd_max + 1, &fds, NULL, NULL, NULL) < 0){
            std::cout<<"elo"<<std::endl;
            continue;
        }
        if (FD_ISSET(g_socket_fd, &fds))
            server::accept_new_user(&users, g_socket_fd);
        server::handle_clients(&fds, &fds_w, users);
    }
    return 0;

}
void server::del_user(std::vector<user> &users, int ind) {
    users.erase(users.begin()+ind);
}
