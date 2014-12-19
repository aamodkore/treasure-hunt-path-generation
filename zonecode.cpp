#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;
/////parameters/////
const int totalTeams=120;
const int zones=2;
const int steps=5;
const int totalLocations=7;
const int zoneLocations[zones]={3,4};
const int maxLocationsInZone=4;             //max of all entries of zoneLocations[]
int locationsInZone[zones][maxLocationsInZone];
//code is designed only for 2 zones. they cannot be increased.
////////////////////
/////functions randomization/////
int randomInitiate()
{
    srand(time(NULL));
    return 0;
}

int randomNumber(int min,int max)
{
    max++;
    if(max>min)
        return (min+rand()%(max-min));
    else
        return (max+rand()%(min-max));
}
/////////////////////////////////
/////threshold function/////
int setZoneThreshold()
{
    if(totalTeams%zones==0)
    return (totalTeams/zones);
    else
    return (totalTeams/zones+1);
}

int setLocationThreshold()
{
    if((totalTeams)%totalLocations==0)
        return (totalTeams/totalLocations);
    else
        return int(10+(totalTeams/(float)totalLocations));
}
////////////////////////////

/////MAIN FUNCTION/////
int main()
{
    //zone code
    int zoneThreshold=setZoneThreshold();
    randomInitiate();

    int zone[totalTeams];           //holds zone data for each team
    int toSetAsZone;                //temp variable
    int zoneCountLeft[zones];       //slots left in the zone

    for(int i=0;i<zones;i++)
        zoneCountLeft[i]=zoneThreshold;

    //alloting start zones for each team
    for(int i=0;i<totalTeams;i++)
    {
        //keep generating random numbers until a non-full zone is encountered
        for(;1;)
        {
            toSetAsZone=randomNumber(0,1);
            if(zoneCountLeft[toSetAsZone]>0)    //test if the zone is not already full
            {
                zone[i]=toSetAsZone;
                zoneCountLeft[toSetAsZone]--;
                break;
            }
        }
    }

    ofstream zoneFile;
    zoneFile.open("ZoneAllotment.txt");
    zoneFile<<zones<<"\t"<<zoneThreshold-zoneCountLeft[0]<<"\t"<<zoneThreshold-zoneCountLeft[1]<<endl<<endl;

    cout<<"Zone 0 alloted to "<<zoneThreshold-zoneCountLeft[0];
    cout<<"Zone 1 alloted to "<<zoneThreshold-zoneCountLeft[1];

    for(int i=0;i<totalTeams;i++)
    {
        cout<<i<<"\t"<<zone[i]<<endl;
        zoneFile<<i+1<<"\t"<<zone[i]+1<<endl;
    }
    zoneFile.close();

    //zone code complete
    //zone[i] contains the zone to start for the 'i'th team.


    //code to assign locations
    //ofstream locationFile;
    //locationFile.open("LocationAllotment.txt");
    int presentStep=0;
    int locationCountLeft[totalLocations][steps];
    int location[totalTeams][steps];
    int locationToAssign;
    for (int i=0;i<totalLocations;i++)
    {
        for(int j=0;j<steps;j++)
            locationCountLeft[i][j]=setLocationThreshold();
    }
    cout<<"\nThreshold"<<setLocationThreshold()<<endl;
    //defining which locations in what zone;
    /*
    locationsInZone[0][0]=0;
    locationsInZone[0][1]=1;
    locationsInZone[0][2]=2;
    locationsInZone[0][3]=99;    //error code
    locationsInZone[1][0]=3;
    locationsInZone[1][1]=4;
    locationsInZone[1][2]=5;
    locationsInZone[1][3]=6;
    */
    int teamInZone;
    int visited;
    int visitCount[totalLocations];
    for(int i=0;i<totalLocations;i++)
        visitCount[i]=0;
    int loopCounter;


    for(int i=0;i<totalTeams;i++)
    {
        //assign location after checking which zone
        //assumption that team does not visit 1 location in every zone
        cout<<i<<"\t";
        for(presentStep=0;presentStep<steps;presentStep++)
        {
            if(presentStep<zoneLocations[zone[i]]-1)
                //present zone
                teamInZone=zone[i];
            else
                //team has crossed from one zone to another
                teamInZone=1-zone[i];
            //zone detection is properly implemented
            //cout<<teamInZone<<"\t";
            //figure out the loop
            for(loopCounter=0;loopCounter<5000;loopCounter++)        //keep on getting random numbers till condition satisfied
            {
                if (teamInZone)
                    locationToAssign=randomNumber(3,6);
                else
                    locationToAssign=randomNumber(0,2);
                //check if the randomly alloted location is available ie check from availability counter.
                if(locationCountLeft[locationToAssign][presentStep]>0)
                {
                    //now check if team has already not visited that location
                    visited=0;
                    for(int k=0;k<presentStep;k++)
                    {
                        if (location[i][k]==locationToAssign)
                        {
                            visited=1;
                            break;
                        }
                    }
                    if(visited==0)
                    {
                        location[i][presentStep]=locationToAssign;
                        locationCountLeft[locationToAssign][presentStep]--;
                        visitCount[locationToAssign]++;
                        cout<<locationToAssign<<"\t";
                        break;
                    }
                }
            }
            if(loopCounter==4999)
            {

                for(int k=0;k<totalLocations;k++)
                    if(locationCountLeft[k]>0)
                    {
                        location[i][presentStep]=k;
                        locationCountLeft[k][presentStep]--;
                        cout<<k<<"\t";
                    }
            }
        }
        cout<<endl;
    }

    //print locations
    cout<<endl<<endl<<"Location List";
    for(int i=0;i<totalLocations;i++)
        cout<<visitCount[i]<<"\t";
    cout<<endl;
    for(int i=0;i<totalTeams;i++)
    {
        for(int j=0;j<steps;j++)
            cout<<location[i][j]<<"\t";
        cout<<endl;
    }

    return 0;
}
