#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;

const int teams=120;
const int locations=7;
const int clueTypes=7;
const int steps=5;

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

int main()
{
    randomInitiate();
    int recalculate;
    int delta=0,delta2=0;
    int location[teams][steps];
    int clue[teams][steps];
    int locationLoad[locations][steps];
    int totalLoad[locations];
    int locationSlot[locations][steps];
    int clueToAssign;
    int clueThreshold[locations];
    int clueLoad[locations][clueTypes];
    int clueSlot[locations][clueTypes];
    int threshold;
    int check;
    int count;
    int locToAssign;
    ofstream f;
    if(teams%locations) threshold=delta+1+teams/locations;
    else                threshold=delta+teams/locations;

    //clue calculation loop
    for(recalculate=1;recalculate!=0;)
    {
        recalculate=0;
        for(int i=0;i<locations;i++)
        {
            for(int j=0;j<steps;j++)
            {
                locationSlot[i][j]=threshold;
                locationLoad[i][j]=0;
            }
            totalLoad[i]=0;
        }
        for(int i=0;i<teams;i++)
        {
            for(int j=0;j<steps;j++)
            {
                for(count=0;count<200;count++)
                {
                    locToAssign=randomNumber(0,locations-1);
                    if(locationSlot[locToAssign][j]>0)
                    {
                        check=0;
                        for(int k=0;k<j;k++)
                        {
                            if(location[i][k]==locToAssign)
                            {
                                check=1;
                                break;
                            }
                        }
                        if(check==0)
                        {
                            location[i][j]=locToAssign;
                            locationLoad[locToAssign][j]++;
                            locationSlot[locToAssign][j]--;
                            totalLoad[locToAssign]++;
                            break;
                        }
                    }
                }
                if(count == 200)
                {
                    cout<<"err\t"<<i<<"\t"<<j<<endl;
                    recalculate=1;
                    break;
                }
            }
        if(recalculate)
            break;
        }

    }


    //clue allotment

    for(int i=0;i<locations;i++)
    {
        if(totalLoad[i]%clueTypes)  clueThreshold[i]=1+delta2+totalLoad[i]/clueTypes;
        else                        clueThreshold[i]=delta2+totalLoad[i]/clueTypes;
    }

    for(recalculate=1;recalculate!=0;)
    {
        recalculate=0;
        for(int i=0;i<locations;i++)
        {
            for(int j=0;j<clueTypes;j++)
            {
                clueLoad[i][j]=0;
                clueSlot[i][j]=clueThreshold[i];
            }
        }
        for(int i=0;i<teams;i++)
        {
            for(int j=0;j<steps;j++)
            {
                for(count=0;count<200;count++)
                {
                    clueToAssign=randomNumber(0,clueTypes-1);
                    if(clueSlot[location[i][j]][clueToAssign]>0)
                    {
                        check=0;
                        for(int k=0;k<j;k++)
                        {
                            if(clue[i][k]==clueToAssign)
                            {
                                check=1;
                                break;
                            }
                        }
                        if(check==0)
                        {
                            clue[i][j]=clueToAssign;
                            clueSlot[location[i][j]][clueToAssign]--;
                            clueLoad[location[i][j]][clueToAssign]++;
                            break;
                        }
                    }
                }
                if(count==200)
                {
                    recalculate=1;
                    break;
                }
            }
            if(recalculate==1)
                break;
        }
    }

    f.open("SouthLocTable.txt");
     //location output
    cout<<"\nLocation Table\n";
    for(int i=0;i<teams;i++)
    {
        cout<<i<<"\t";
        for(int j=0;j<steps;j++)
        {
            f<<location[i][j]+1<<"\t";
            cout<<location[i][j]<<"\t";
        }
        cout<<endl;
        f<<endl;
    }
    f.close();

    f.open("SouthLocationLoad.txt");
    //location load output
    cout<<"\n\nLocationLoads\n";
    for(int i=0;i<locations;i++)
    {
        for(int j=0;j<steps;j++)
        {
            f<<locationLoad[i][j]<<"\t";
            cout<<locationLoad[i][j]<<"\t";
        }
        f<<endl;
        cout<<endl;
    }
    f.close();

    //clues output
    f.open("SouthClueList.txt");
    cout<<"\n\nClues table\n";
    for(int i=0;i<teams;i++)
    {
        cout<<i<<"\t";
        for(int j=0;j<steps;j++)
        {
            cout<<clue[i][j]<<"\t";
            f<<clue[i][j]+1<<"\t";
        }
        f<<endl;
        cout<<endl;
    }
    f.close();

    //clue load output
    f.open("SouthCluePrints.txt");
    cout<<"\n\nClueLoads\n";
    for(int i=0;i<locations;i++)
    {
        for(int j=0;j<clueTypes;j++)
        {
            f<<clueLoad[i][j]<<"\t";
            cout<<clueLoad[i][j]<<"\t";
        }
        f<<endl;
        cout<<endl;
    }
    f.close();

    return 0;
}
