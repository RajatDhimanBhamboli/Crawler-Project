#include<iostream>
#include "./library.h"

using namespace std;



int main(int argc,char* argv[]){
    
    if(argc<3){
        cerr<<"Error: Invalid data";
        return 1;
    }
    char *url=argv[1];
    if(!checkurl(url)){
        cerr<<"Invalid Url";
        return 1;
    }
    char *dirctorypath=argv[2];
    if(!checkdirectory(dirctorypath)){
        createdirectory(dirctorypath);
    }
    char* filepath=downloadfile(url,dirctorypath);
    cout<<filepath;
}