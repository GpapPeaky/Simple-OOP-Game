#include "Rounds.h"

void Round::SetLPK(int v1){
    last_player_killed = v1;
}

int Round::GetLPK(void){
    return last_player_killed;
}

void Round::SetLPV(int v2){
    last_player_voted = v2;
}

int Round::GetLPV(void){
    return last_player_voted;
}

void Round::SetTurn(void){
    turn=0;
}

void Round::TurnChange(void){
    turn++;
}

int Round::GetTurn(void){
    return turn;
}
