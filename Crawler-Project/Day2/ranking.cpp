#include <iostream>
#include <fstream>
#include "string(module).h"
using namespace std;

int main()
{

    char searchword[100];
    cout << "\n Enter word: ";
    cin >> searchword;
    char checkword[100];
    my_strcpy(checkword,'\0');
    my_strcat(checkword,searchword);
   
    ifstream filep("seo_data.txt");
    if(!filep.is_open()){
        cerr<<"\nFile Not open";
        return 1;
    }
    char line[256];
    bool flag=0;
    while(filep.getline(line,256)){
        if(my_strcasestr(line,checkword)!=NULL){
            cout<<line;
            flag=1;
        }
    }
    if(!flag){
        cout<<"No Word Found";
    }
    filep.close();
}