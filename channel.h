//
// Created by arabica on 28.12.2020.
//
#include "user.h"
#ifndef SK_CHANNEL_H
#define SK_CHANNEL_H


class channel {
public:
    std::string name;
    std::vector<int> users;
    static int find_chan_by_name(std::vector<channel> channels, std::string name);
    int find_user(int usr);
    static void delete_user_from_channels(std::vector<channel> &channels, int user);


};


#endif //SK_CHANNEL_H
