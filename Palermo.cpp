#include "Players.h"
#include "Rounds.h"

//GLOBAL VARIABLES, MAY BE USED LATER OUTSIDE AND INSIDE OF THE main() FUNTION

int plel;//Player To Be Eliminated
int plsav;//Player To Be Saved
int err;//Global Error Variable (Use Of Exceptions)
int vote_temp;//Temporary Variable For Voting
int max_vt;//Max Amount Of Votes In Each Voting Phase

using namespace std;//Else cin/cout Are Ambiguous(?)

int main(){
    
    Round info;//Object That Saves All Infom (Last Player Killed And/Or Voted Out As Well As The Turn Number)
    int gang;//Cell Which Is The Gangster
    int doc;//Cell Which Is The Doctor
    string temp;//Temporary Value (Sets Name/Role)
    player input;//Object Type Player (To Be Pushed Back In The Vector)
    vector<player> people;//Vector Type "player" class That Saves The Different Objects
    int player_count=0;//Player Counter

    //INITIALIZATION OF (ALLOCATING NAMES,ROLES INITIAL VOTES(0))//

ifstream infile;

    infile.open("players.txt");
    if(infile.fail()){
        cerr << "Input File not found.\n";
        exit(1);
    }
    while(!infile.eof()){
        infile >> temp;
        input.SetName(temp);//Sets Name
        infile >> temp;
        input.SetRole(temp);//Sets Role
        people.push_back(input);//Pushes Back The Player Object In A Player Type Vector (Saves Objects As Elements Of The Array)
        player_count++;
    }
    infile.close();

    for(int i=0;i<player_count;i++){
        people[i].SetHealth(true);//Sets All People To Alive
    }

    //Scouting For Each Cell That Has The Special Roles

    for(int i=0;i<player_count;i++){
        if(people[i].GetRole()=="gangster"){
            gang=i;//Vector Starts From 0
        }
        if(people[i].GetRole()=="doctor"){
            doc=i;//Vector Starts From 0
        }
    }
    for(int i=0;i<player_count;i++){
        people[i].SetVotes();//Set All Votes To 0
    }

    info.SetTurn();//Sets The Turn To 0

    //WHILE START//

    while(player_count>3 && people[gang].GetHealth()!=false){

        info.SetLPK(-1);//Sets The Value Which Indicates No one Has Been Eliminated
        info.SetLPV(-1);//Sets The Value Which Indicates No one Has Been Eliminated
        info.TurnChange();//Adds One To Turn Counter

        //NIGHT PHASE//

        cout<<"Night Engulfs The City Of Palermo\n";
        cout<<"The Gangster Is Called To Pick A Player To Eliminate\n";
        cout<<"Which Player Is To Be Eliminated?\n";
        cin>>plel;

        err=1;

        while(err==1){

            err=0;
            try{
                if(plel<0 || plel>player_count || people[plel].GetHealth()==false){
                    throw 1;
                    }
                }
                catch(int v){
                    cerr<<"Please Choose A Valid Input(Players Which Exist In The Game)\n";
                    err=v;
                }   
                if (err==1){
                    cin>>plel;
                }
        } 
        if(people[doc].GetHealth()==true){
            cout<<"The Doctor Is Called To Pick A Player To Save\n";
            cout<<"Which Player Is To Be Saved?\n";
            cin>>plsav;

            err=1;

            while(err==1){

                err=0;
                try{
                    if(plsav<0 || plsav>player_count || people[plsav].GetHealth()==false){
                        throw 1;
                        }
                    }
                    catch(int v){
                        cerr<<"Please Choose A Valid Input(Players Which Exist In The Game)\n";
                        err=v;
                    }   
                    if (err==1){
                        cin>>plel;
                    }
            }
        }else{
            cout<<"The Doctor Is Dead, And So No One Can Be Saved\n";
        }

        if(plsav==plel){
            cout<<"None Was Eliminated\n";//When The Doctor Chooses The Same Player Which Was To Be Eliminated, Then Nothing Happens
        }else if(plsav!=plel){
            people[plel].SetHealth(false);//Boolean False --> No Longer Alive
            cout<<"Player "<< plel <<" Was Eliminated\n";
            info.SetLPK(plel);
        }

        //DAY/VOTING PHASE//

        cout<<"Day Arises In The City Of Palermo\n";
        cout<<"All Players Are Called To Vote Which Is The Gangster\n";
        for(int i=0;i<player_count;i++){
            if(people[i].GetHealth()==true){
                cout<<"Player "<< i <<" Votes For\n";
                cin>>vote_temp;
                    err=1;

                while(err==1){

                    err=0;
                    try{
                        if(vote_temp<0 || vote_temp>player_count || people[vote_temp].GetHealth()==false){
                            throw 1;
                            }
                        }
                        catch(int v){
                            cerr<<"Please Choose A Valid Input(Players Which Exist In The Game)\n";
                            err=v;
                        }   
                        if (err==1){
                            cin>>vote_temp;
                        }
                }
                people[vote_temp].Voting();

                }
            }

            for(int i=0;i<player_count;i++){
                if(people[i].GetVotes() != 0){
                cout<<"Player "<< i <<" Has "<< people[i].GetVotes() <<" Votes\n";

            //SCOUTING FOR THE MAX AMMOUNT OF VOTES//

                max_vt=people[0].GetVotes();//Set The Initial Max Amount

                for(int i=0; i<player_count; i++){
                    if(people[i].GetVotes()>max_vt){
                        max_vt=people[i].GetVotes();
                    }
                }
                for(int i=0; i<player_count; i++){
                    if(people[i].GetVotes()==max_vt){
                        cout<<"Player "<< i << " Has The Most Votes And So He Is Voted Out";
                        people[i].SetHealth(false);//Eliminates The Voted Person
                        info.SetLPV(i);
                    }
                }
            }
        }//TERMINATION OF THE ELECTION//

        for(int i=0;i<player_count;i++){
            people[i].SetVotes();//Resets All Votes To 0 For The Next Turn
        }

    //WRITE OUTPUT FILE//

    ofstream outfile;
        outfile.open("output.txt");
            if(outfile.fail()){
            cerr << "Output File not found.\n";
            exit(1);
        }

        outfile <<"Turn "<< info.GetTurn() << "\n";

        if(info.GetLPK()==-1){
            outfile << "No One Has Been Eliminated\n";
        }else{
            outfile <<"Player "<< info.GetLPK() << "\n";
        }
        if(info.GetLPV()==-1){
            outfile << "No One Has Been Voted Out\n";
        }else{
            outfile <<"Player "<< info.GetLPV() << "\n";
        }

    if(player_count<3 || people[gang].GetHealth()==false){
        cout<<"The Game Has Ended\n";
    }

        if(people[gang].GetHealth()==false){
            cout<<"The Gangster Has Been Eliminated\nThe Game Ends\n";
            exit(1);
        }

    }//WHILE END//

    infile.close();
}