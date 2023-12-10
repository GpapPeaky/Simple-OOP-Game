#include "std_lib_facilities.h"



    class player{

        private:

            string name;
            string role;
            bool isalive;
            int votes;
            bool alive;
        
        public:
            
            void SetHealth(bool v1);//Setters
            void SetName(string v2);
            void SetRole(string v3);
            void SetVotes();
            void Voting();//Editor/Change Of Value
            int GetVotes();//Getters
            bool GetHealth();
            string GetName();
            string GetRole();

            //Get Methods Return A Value
            //Set Methods Fix A Value

            //constructors

            player();

            player(string name, bool isalive, string role );

    };