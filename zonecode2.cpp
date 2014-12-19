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
const int clueTypes=7;
int setLocationThreshold(void);
const int thresholdPerLocation=setLocationThreshold();
const int zone1Loc[3]={0,1,2};
const int zone2Loc[4]={3,4,5,6};
////////////////////

/////functions randomization/////
int randomInitiate()
{
    srand(1111993);
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
/////fucntions Threshold/////
int setLocationThreshold(void)
{
    if(totalTeams%totalLocations)
        return (3+(totalTeams/totalLocations));
    else
        return (2+totalTeams/totalLocations);
}
/////////////////////////////

/////main Function//////
int main()
{
    randomInitiate();
    //necessary arrays
    int zone[totalTeams];                //contains starting zone of each team
    int location[totalTeams][steps];    //holds the location distribution
    int clues[totalTeams][steps];       //holds the clue distribution
    int locToAssign;
    ofstream locFile;
    ofstream locLoadFile;
    int totalLoad[totalLocations];
    int clueSlots[totalLocations][clueTypes];
    int clueThreshold[totalLocations];
    int clueToAssign;
    int clueLoad[totalLocations][clueTypes];
    //tracker arrays keeps track of which which clue goes to what team at what time

    //element 0 should hold team no, l the step at which it gets the clue, 2 the location at which it gets the clue
    int locationClue[totalLocations][clueTypes][thresholdPerLocation][3];

    //keeps track of location loads
    int locationLoad[totalLocations][steps];

    //how many more can the location handle. *used for calculation* not output
    int locationSlots[totalLocations][steps];
    int recalculate;
    int stepNow,zoneNow;
    int counter;
    int check;


    for(recalculate=1;recalculate!=0;)
    {
    recalculate=0;
    for(int i=0;i<totalLocations;i++)
    {
        for(int j=0;j<steps;j++)
        {
            locationSlots[i][j]=thresholdPerLocation;
            //cout<<locationSlots[i][j]<<"\t";
        }
        //cout<<endl;
    }
    //initializing all the arrays
    //for(int i=0;i<totalTeams;i++)
    //    zone[i]=9;
    for(int i=0;i<totalLocations;i++)
    {
        for(int j=0;j<steps;j++)
        locationLoad[i][j]=0;
    }

    //step one set location 1 for eash
    for(int i=0;i<totalTeams;i++)
    {
        for(;1;)
        {
            locToAssign=randomNumber(0,totalLocations-1);
            if(locationSlots[locToAssign][0]>0)
            {
                location[i][0]=locToAssign;
                locationSlots[locToAssign][0]--;
                locationLoad[locToAssign][0]++;
                if(locToAssign<3)
                    zone[i]=0;
                else zone[i]=1;
                break;
            }
        }
    }

    //set locations for all

    for(int i=0;i<totalTeams;i++)
    {
       for(stepNow=1;stepNow<steps;stepNow++)
       {
           if(zone[i])
           {
               if(stepNow<3)   zoneNow=1;
               else            zoneNow=0;
           }
           else
           {
               if(stepNow<2)    zoneNow=0;
               else             zoneNow=1;
           }
           for(counter=0;counter<200;counter++)
           {
               if(zoneNow)  locToAssign=randomNumber(3,6);
               else         locToAssign=randomNumber(0,2);
               if(locationSlots[locToAssign][stepNow]>0)
               {
                   check=0;
                   for(int k=0;k<stepNow;k++)
                        if (location[i][k]==locToAssign)
                        {
                            check=1;
                            break;
                        }
                    if(check==0)
                    {
                        location[i][stepNow]=locToAssign;
                        locationSlots[locToAssign][stepNow]--;
                        locationLoad[locToAssign][stepNow]++;
                        break;
                    }
               }
           }
           if(counter==200)
           {
               if(zone[i])
           {
               if(stepNow<2)   zoneNow=1;
               else            zoneNow=0;
           }
           else
           {
               if(stepNow<3)    zoneNow=0;
               else             zoneNow=1;
           }
           for(counter=0;counter<200;counter++)
           {
               if(zoneNow)  locToAssign=randomNumber(3,6);
               else         locToAssign=randomNumber(0,2);
               if(locationSlots[locToAssign][stepNow]>0)
               {
                   check=0;
                   for(int k=0;k<stepNow;k++)
                        if (location[i][k]==locToAssign)
                        {
                            check=1;
                            break;
                        }
                    if(check==0)
                    {
                        location[i][stepNow]=locToAssign;
                        locationSlots[locToAssign][stepNow]--;
                        locationLoad[locToAssign][stepNow]++;
                        break;
                    }
               }
           }
           }
           if(counter==200)
           {
               location[i][stepNow]=99;
               recalculate++;
               //cout<<"recalculation trigger"<<endl;
           }
       }
    }
    cout<<recalculate<<"\t";
    if(recalculate<1)  break;
    }

    cout<<"\nLoad Calculations\n";
    for(int i=0;i<totalLocations;i++)
    {
        totalLoad[i]=0;
        for(int j=0;j<steps;j++)
        {
            totalLoad[i]+=locationLoad[i][j];
            cout<<totalLoad[i]<<"\t"<<locationLoad[i][j]<<endl;
        }
    }

    //display & print all locations
    locFile.open("LocationList.txt");
    cout<<"\n\nLocation List\n";
    for(int i=0;i<totalTeams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            locFile<<location[i][j]+1<<"\t";
            cout<<location[i][j]<<"\t";
        }
        locFile<<endl;
        cout<<endl;
    }
    locFile.close();

    locLoadFile.open("LocationLoads.txt");
    cout<<endl<<"Location Load"<<endl;
    for(int i=0;i<totalLocations;i++)
    {
        for(int j=0;j<steps;j++)
        {
            locLoadFile<<locationLoad[i][j]<<"\t";
            cout<<locationLoad[i][j]<<"\t";
        }
        locLoadFile<<endl;
        cout<<endl;
    }
    locLoadFile<<endl<<endl;
    cout<<"\n\nTotal Load on Locations\n";
    for(int i=0;i<totalLocations;i++)
    {
        cout<<i<<"\t"<<totalLoad[i]<<endl;
        locLoadFile<<i<<"\t"<<totalLoad[i]<<endl;
    }
    locLoadFile.close();
    cout<<"\nLocation Allotment complete\n\n";
    //location allotment done


    //start clue allotment;
    for(int i=0;i<totalLocations;i++)
        for(int j=0;j<clueTypes;j++)
            clueLoad[i][j]=0;
    cout<<"\n\nClue allotment testing\n\n";
    for(int i=0;i<totalLocations;i++)
    {
        if(totalLoad[i]%clueTypes)
            clueThreshold[i]=2+totalLoad[i]/clueTypes;
        else clueThreshold[i]=1+totalLoad[i]/clueTypes;
        cout<<clueThreshold[i]<<endl;
    }
    for(int i=0;i<totalLocations;i++)
        for(int j=0;j<clueTypes;j++)
            clueSlots[i][j]=clueThreshold[i];

    for(int i=0;i<totalLocations;i++)
    {
        for(int j=0;j<clueTypes;j++)
        {
            cout<<clueSlots[i][j]<<"\t";
        }
        cout<<endl;
    }
    //the loop for clues!
    int count;
    cout<<endl<<"Major testing for clue allotment\n";
    for(int i=0;i<totalTeams;i++)
    {
        for(stepNow=0;stepNow<steps;stepNow++)
        {
            for(count=0;count<300;count++)
            {
                clueToAssign=randomNumber(0,6);
                check=0;
                if(clueSlots[ location[i][stepNow] ][clueToAssign] >0)
                {
                    for(int k=0;k<stepNow;k++)
                    {
                        if(clues[i][k]==clueToAssign)
                        {
                            check=1;
                            break;
                        }
                    }
                    if(check==0)
                    {
                        clues[i][stepNow]=clueToAssign;
                        //if(location[i][stepNow]==0)
                        //    cout<<"reached loc1\t";//<<clueToAssign<<endl;
                        clueLoad[ location[i][stepNow] ][clueToAssign]++;
                        clueSlots[ location[i][stepNow ]][clueToAssign]--;
                        break;
                    }
                }
            }
            if(count==300)
            {
                for(int k=0;k<clueTypes;k++)
                {
                    cout<<clueSlots[location[i][stepNow]][k]<<"\t";
                }
                /*for(int k=0;k<clueTypes;k++)
                {
                    if(clueSlots[location[i][stepNow]][k]>0)
                    {
                        for(int l=0;l<stepNow;l++)
                        {
                            if(clues[i][l]==l)
                                check=1;
                                break;
                        }
                        if(check==0)
                        {
                            clues[i][stepNow]=k;
                            cout<<clueToAssign<<"\t";
                            clueSlots[location[i][stepNow]][k]--;
                            break;
                        }
                    }
                }*/
            }
        }
    }

    //clue printing
    ofstream cluePrints;
    cluePrints.open("ListOfCluePrints.txt");
    for(int i=0;i<totalLocations;i++)
    {
        for(int k=0;k<clueTypes;k++)
        {
            cluePrints<<clueLoad[i][k]<<"\t";
            cout<<clueLoad[i][k]<<"\t";
        }
        cluePrints<<endl;
        cout<<endl;
    }
    cluePrints.close();

    ofstream cluePrintList;
    cluePrintList.open("ClueList.txt");
    cout<<endl;
    for(int i=0;i<totalTeams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            cluePrintList<<clues[i][j]+1<<"\t";
            cout<<clues[i][j]<<"\t";
        }
        cout<<endl;
        cluePrintList<<endl;
    }
    cluePrintList.close();
    //clue allotment complete... phew!!!

    //data extraction
    int actualLocation[totalTeams][steps+2];
    for(int i=0;i<totalTeams;i++)
    {
        for(int j=0;j<steps+2;j++)
        {
            if(j==0)
                actualLocation[i][j]=0;
            else
                if(j==steps+1) actualLocation[i][j]=99;
                else    actualLocation[i][j]=location[i][j-1]+1;
        }
    }
    cout<<"\nActual LocationList\n";
    for(int i=0;i<totalTeams;i++)
    {
        for(int j=0;j<steps+2;j++)
        {
            cout<<actualLocation[i][j]<<"\t";
        }
        cout<<endl;
    }

    //data extraction starts

    //get clues allocated to locations

    //get distribution of clue types to teams, steps, positions.
    int max=0;
    for(int i=0;i<totalLocations;i++)
    {
        for(int j=0;j<clueTypes;j++)
        {
            if(clueLoad[i][j]>max)
                max=clueLoad[i][j];
        }
    }
    const int maxLoad=max;
    int clueUsed[totalLocations][clueTypes][maxLoad][3];
    //initialize the array
    for(int i=0;i<totalLocations;i++)
        for(int j=0;j<clueTypes;j++)
            for(int k=0;k<clueLoad[i][j];k++)
                for(int l=0;l<3;l++)
                    clueUsed[i][j][k][l]=0;


    return 0;
}
