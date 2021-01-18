//
// Created by arabica on 16.12.2020.
//
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
#ifndef SK_USER_H
#define SK_USER_H

//Klasa implementująca użytkownika kanału IRC

class user {
public:
    int fd;                                 //deskryptor
    bool to_write = false;                  //zmienna informująca o niewysłanych komunikatach do użytkownika
    int status = 0;                         //czy użytjownik jest aktywny
    std::string ip;
    std::string nick="-1";
    std::vector<std::string> communicats;



};


#endif //SK_USER_H
