#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;
const int teams=120;
const int locations=7;
const int clueTypes=7;
const int steps=5;

int main()
{
    int location[teams][steps];
    int clue[teams][steps];
    int locationLoad[locations][steps];
    int totalLocationLoad[locations];
    int clueDist[locations][clueTypes];

    //initialization loops
    for(int i=0;i<locations;i++)
    {
        for(int j=0;j<steps;j++)
            locationLoad[i][j]=0;
        totalLocationLoad[i]=0;
    }
    for(int i=0;i<locations;i++)
    {
        for(int j=0;j<clueTypes;j++)
            clueDist[i][j]=0;
    }

    //loading files & values
    ifstream locationFile;
    locationFile.open("SouthLocTable.txt");
    for(int i=0;i<teams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            locationFile>>location[i][j];
        }
    }
    for(int i=0;i<teams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            cout<<location[i][j]<<"\t";
        }
        cout<<endl;
    }
    locationFile.close();

    locationFile.open("SouthClueList.txt");
    for(int i=0;i<teams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            locationFile>>clue[i][j];
        }
    }
    cout<<endl;
    for(int i=0;i<teams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            cout<<clue[i][j]<<"\t";
        }
        cout<<endl;
    }
    locationFile.close();

    for(int i=0;i<teams;i++)
    {
        for(int j=0;j<steps;j++)
        {
            totalLocationLoad[ location[i][j]-1 ]++;
            locationLoad[ location[i][j]-1 ][j]++;
        }
    }

    cout<<"\nLocation Loads\n";
    for(int i=0;i<locations;i++)
        cout<<i<<"\t"<<totalLocationLoad[i]<<endl;

    cout<<"\nLocation loads per step\n";
    for(int i=0;i<locations;i++)
    {
        for(int j=0;j<steps;j++)
            cout<<locationLoad[i][j]<<"\t";
        cout<<endl;
    }
    ofstream clueFile;
    clueFile.open("SouthClueFile.txt");
    for(int l=0;l<locations;l++)
    {
        for(int c=0;c<clueTypes;c++)
        {
            clueFile<<"clue "<<c+1<<" leading to location "<<l+1<<endl;
            cout<<"clue "<<c+1<<" leading to location "<<l+1<<endl;
            for(int i=0;i<teams;i++)
            {
                for(int j=0;j<steps;j++)
                {
                    if((location[i][j]==l+1)&&(clue[i][j]==c+1))
                        if(j)   {cout<<i+1<<"\t"<<j+1<<"\t"<<location[i][j-1]<<endl;
                                clueFile<<i+1<<"\t"<<j+1<<"\t"<<location[i][j-1]<<endl;}
                        else    {cout<<i+1<<"\t"<<j+1<<"\t"<<0<<endl;
                                clueFile<<i+1<<"\t"<<j+1<<"\t"<<0<<endl;}
                }
            }
        }
    }

    cout<<"Finish Clues\n";
    clueFile<<"Finish Clues\n";
    for(int i=0;i<teams;i++)
    {
        cout<<i+1<<"\t"<<steps+1<<"\t"<<location[i][steps-1]<<endl;
        clueFile<<i+1<<"\t"<<steps+1<<"\t"<<location[i][steps-1]<<endl;
    }
    clueFile.close();


    //list of teams visiting a location & what clue to give them.
    clueFile.open("SouthLocationClues.txt");
    cout<<"start location\n";
    clueFile<<"start location\n";
    for(int i=0;i<teams;i++)
    {
        cout<<i+1<<"\t"<<0<<"\t"<<location[i][0]<<"\t"<<clue[i][0]<<endl;
        clueFile<<i+1<<"\t"<<0<<"\t"<<location[i][0]<<"\t"<<clue[i][0]<<endl;
    }
    for(int l=0;l<locations;l++)
    {
        cout<<"location "<<l+1<<endl;
        clueFile<<"location "<<l+1<<endl;
        for(int i=0;i<teams;i++)
        {
            for(int j=0;j<steps;j++)
            {
                if(location[i][j]==l+1)
                {
                    if(j==steps-1)
                    {
                        cout<<i+1<<"\t"<<steps<<"\tf"<<"\t"<<1<<endl;
                        clueFile<<i+1<<"\t"<<steps<<"\tf"<<"\t"<<1<<endl;

                    }
                    else
                    {
                        cout<<i+1<<"\t"<<j+1<<"\t"<<location[i][j+1]<<"\t"<<clue[i][j+1]<<endl;
                        clueFile<<i+1<<"\t"<<j+1<<"\t"<<location[i][j+1]<<"\t"<<clue[i][j+1]<<endl;
                    }
                }
            }
        }
    }
    return 0;

}
