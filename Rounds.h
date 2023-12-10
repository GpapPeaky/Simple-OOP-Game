#include "std_lib_facilities.h"

class Round{

        private:
        
        int last_player_voted;
        int last_player_killed;
        int turn;

        public:

        void SetLPK(int p);
        int GetLPK();
        void SetLPV(int x);
        int GetLPV();
        void SetTurn();
        void TurnChange();
        int GetTurn();

    };