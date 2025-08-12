#ifndef CRAWLER_H
#define CRAWLER_H

#include "hashcpp.h"
#include "ll.h"
#include "file.h"
#include "strings.h"
#include "crawler.h"
#include "seo.h"

class crawler {
private:
    hashTable<char*, char*>* obj;

public:
    crawler();
    ~crawler();

    bool checkdirectory(char* path);
    void createdirectory(char* path);
    bool checkurl(char* url);
    char* downloadfile(char* url, char* directorypath);
    LL<char*>* readfile(char* filepath, char* directorypath, char* urlpath);
    void recursiveCrawler(char* url, char* directorypath, int maxDepth);
    int stringtoint(char* depth);
    bool isCrawlablePage(const char* url);
    char* deleteSlash(const char* url);
    void toAbsoluteUrl(const char* base_url, const char* relative_url, char* absolute_url);
    bool endsWith(const char* url, const char* ext);
    bool startwiht(const char* url, const char* ext);
};

#endif