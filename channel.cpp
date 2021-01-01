//
// Created by arabica on 28.12.2020.
//

#include "channel.h"
int channel::find_chan_by_name(std::vector<channel> channels, std::string name) {

    for (int i =0; i< channels.size(); i++){
        if (channels[i].name==name)
            return i;
    }
    return -1;
}
int channel::find_user(int usr) {
    for (int i =0 ; i< this->users.size();i++){
        if(this->users[i] == usr){
            return i;
        }
    }
    return -1;
}

void channel::delete_user_from_channels(std::vector<channel> &channels, int user) {
    for(int i = 0; i< channels.size(); i++){
        for(int j = 0; j < channels[i].users.size(); j++){
            if (channels[i].users[j] == user){

                channels[i].users.erase(channels[i].users.begin() + j);
            }
        }
    }
}