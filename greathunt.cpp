//includes
//included all for avoiding errors later

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
using namespace std;
int initiateRandom(void);
int getRandom(int,int);
/*
NoLoc: locations
NoVisit: locations visited by each team
NoTeams: teams
NoClue: type of clues for each location. hence C>
*/



int main(int narg, char* args[])
{
    initiateRandom();
    if(narg==4)
    {
        int NoLoc=atoi(args[1]);
        int NoVisit=atoi(args[2]);
        int NoTeams=atoi(args[3]);
        int NoClue=atoi(args[4]);
    }
    else
        cout<<"error in input arguments";
    return 0;
}


/////RANDOM NUMBER FUNCTIONS/////
//defined separately so that any random genetaror may be used
int initiateRandom()
{
    srand(time(NULL));
    return 0;
}

int getRandom(int low,int high)
{
    return low+(rand()%(high-low));
}
/////END OF RANDOM FUNCTIONS BLOCK/////
