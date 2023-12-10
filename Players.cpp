#include "Players.h"


void player::SetName(string n){
    name = n; //Setter
}

string player::GetName(){
    return name;//Getter
}

void player::SetRole(string r){
    role = r;//Setter
}

string player::GetRole(){
    return role;//Getter
}

void player::SetHealth(bool sh){
    isalive = sh;//Setter
}

bool player::GetHealth(){
    return isalive;//Getter
}

void player::SetVotes(){
    votes=0;
}

void player::Voting(){
    votes++;
}

int player::GetVotes(){
    return votes;
}

player::player(string name, bool isalive, string role){ //Primary Constructor
    name = GetName();
    role = GetRole();
    isalive = GetHealth();
    votes = 0;
}

player::player(){
    name="NULL";
    role="Civilian";
    alive=true;
}

