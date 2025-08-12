#include<iostream>
// #include "./library.h"
#include "./crawler.h"
using namespace std;



int main(int argc,char* argv[]){
    crawler* obj=new crawler();
    if(argc<3){
        cerr<<"Error: Invalid data";
        return 1;
    }
    char *url=argv[1];
    // if(!obj->checkurl(url)){
    //     cerr<<"Invalid Url";
    //     return 1;
    // }
     int depth=obj->stringtoint(argv[3]);
    if(depth<0&&depth>3){
        cerr<<"Invalid Depth";
        return 1;
    }
    char *dirctorypath=argv[2];

    if(!obj->checkdirectory(dirctorypath)){
        obj->createdirectory(dirctorypath);
    }
    // char* filepath=obj->downloadfile(url,dirctorypath);
    // cout<<filepath;


    // char *allhtmldata=obj->readfile(filepath);
    // cout<<allhtmldata;
char url1[100]={"https://www.linkedin.com/feed/update/urn:li:activity:7326883592423329792"};
    char directorypath[100] = "./pages";
    obj->recursiveCrawler(url1,directorypath,1);
    // startCrawler(filepath,)
    
}