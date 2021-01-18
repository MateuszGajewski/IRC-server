//
// Created by arabica on 28.12.2020.
//
#include "user.h"
#ifndef SK_CHANNEL_H
#define SK_CHANNEL_H

//Klasa implementująca pojedyńczy kanał serwera IRC

class channel {
public:
    std::string name;
    std::vector<std::string> users;
    static int find_chan_by_name(std::vector<channel> channels, std::string name);
    int find_user(std::string usr);
    static void delete_user_from_channels(std::vector<channel> &channels, std::string user);
    void change_nick(std::string nick);


};


#endif //SK_CHANNEL_H
