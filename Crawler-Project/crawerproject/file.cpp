#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include "././library/file.h"

using namespace std;

bool checkdirectory(char* path) {
    return filesystem::exists(path);
}

void createdirectory(char* path) {
    if (filesystem::create_directories(path)) {
        cout << "Directory created: " << path << endl;
    } else {
        cerr << "Failed to create directory." << endl;
    }
}

char* longnumbertostring(long long time) {
    char* name = (char*)malloc(30);
    long long reversenumber = 0;
    int i = 0;
    while (time > 0) {
        int n = time % 10;
        reversenumber = reversenumber * 10 + n;
        time /= 10;
    }
    while (reversenumber > 0) {
        char p = (reversenumber % 10) + '0';
        name[i++] = p;
        reversenumber /= 10;
    }
    name[i] = '\0';
    char html[] = {'.', 'h', 't', 'm', 'l', '\0'};
    my_strcat(name, html);
    return name;
}

char* generateUniqueName() {
    time_t now = time(0);
    return longnumbertostring(now);
}

char* downloadfile(char* url, char* directorypath) {
    char* fileurl = new char[100];
    my_strcpy(fileurl, directorypath);
    char cd[] = "/";
    my_strcat(fileurl, cd);
    my_strcat(fileurl, generateUniqueName());
    char command[200];
    char wget[] = "wget -q -O ";
    char c[] = " ";
    my_strcpy(command, wget);
    my_strcat(command, fileurl);
    my_strcat(command, c);
    my_strcat(command, url);
    cout << command << endl;
    int result = system(command);
    if (result != 0) {
        cerr << "Error failed to Download";
        delete[] fileurl;
        return nullptr;
    }
    else 
    cout<<"\nDownload Success\n";
    return fileurl;
}

char* readfile(char* filepath) {
    char* alldata = new char[10000];
    ifstream in(filepath, ios::in);
    if (!in.is_open()) {
        cout << "can't read";
        delete[] alldata;
        return nullptr;
    }
    char ch;
    int i = 0;
    while (in.get(ch)) {
        alldata[i++] = ch;
    }
    in.close();
    alldata[i] = '\0';
    cout << "aall: " << alldata;
    return alldata;
}