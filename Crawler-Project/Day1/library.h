#include<iostream>
#include<filesystem>
#include"./string(module).h"
#include <sys/types.h>
#include<cstdlib>
#include<ctime>


bool checkdirectory(char* path){
    if(!filesystem::exists(path)){
         return false;
    }
    return true;
}
void createdirectory(char *path){
    if (filesystem::create_directories(path)) {
            cout << "Directory created: " << path << std::endl;
        } else {
            cerr << "Failed to create directory." << std::endl;
        }
}
char * longnumbertostring(long long time){
        cout<<"\ntime hai in numbr: "<<time;

    int sum=0,n=0;
    char * name = (char*)malloc(30);
    long long reversenumber=0;
    while(time>0){
        n=time%10;
        reversenumber=reversenumber*10+n;
        time/=10;
    }
    cout<<"\n reverse nukmbver : "<<reversenumber;
    int i=0;
    while (reversenumber>0)
    {
        char p=(reversenumber%10)+'0';
        name[i]=p;
        reversenumber/=10;
        i++;
    }
    name[i]='\0';
    char html[]={'.','h','t','m','l','\0'};
    my_strcat(name,html);
   
        cout<<"\ntime hai in string: "<<name;   

    return name;
}

char * generateUniqueName(){
    
    time_t now=time(0);
    cout<<"\ntime hai in numbr: "<<now;
    char *tostring=longnumbertostring(now);     
    return tostring;
}


bool checkurl(char *url){
    const char htt[]={"https://"};
    char * result=my_strstr(url,htt);
    if(!result){
        return false;
    }
    else return true;
}

char * downloadfile(char * url,char *dirctorypath){
    
     char  fileurl[100];
     my_strcpy(fileurl,dirctorypath);
     char cd[]="/";
          my_strcat(fileurl,cd);

     my_strcat(fileurl,generateUniqueName());
    
     char* command=new char[200];
     char wget[]="wget -O ";
     char c[]=" ";
     my_strcpy(command,wget);
     my_strcat(command,fileurl);
     my_strcat(command,c);
     my_strcat(command,url);
        cout<<command<<endl;
     int result=system(command);
     if(result!=0){
        cerr<<"Error failed to Download";
        return nullptr;
     }
     cout<<"Successfull";
     return command;
}