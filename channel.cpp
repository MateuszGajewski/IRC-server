//
// Created by arabica on 28.12.2020.
//

#include "channel.h"
//Fnkcja służąca do znajdowania kanału o podnej nazwie w wektorze kanałów
int channel::find_chan_by_name(std::vector<channel> channels, std::string name) {

    for (int i =0; i< channels.size(); i++){
        if (channels[i].name==name)
            return i;
    }
    return -1;
}
//Funkcja służąca do znajdowania użytkownika o podanym nicku w kanale
int channel::find_user(std::string usr) {
    for (int i =0 ; i< this->users.size();i++){
        if(this->users[i] == usr){
            return i;
        }
    }
    return -1;
}
//Usuwanie użytkownika z kanału
void channel::delete_user_from_channels(std::vector<channel> &channels, std::string user) {
    for(int i = 0; i< channels.size(); i++){
        for(int j = 0; j < channels[i].users.size(); j++){
            if (channels[i].users[j] == user){

                channels[i].users.erase(channels[i].users.begin() + j);
            }
        }
    }
}
//Rozgłaszanie zmiany nicka użytkownika
void channel::change_nick(std::string nick) {
    for(int i =0; i < this->users.size(); i++){

    }
}