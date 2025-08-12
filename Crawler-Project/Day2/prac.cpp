#include <iostream>
#include "./crawler.h"

using namespace std;

int main()
{
    crawler *obj = new crawler();
    char url[100]={"https://www.linkedin.com/feed/update/urn:li:activity:7326883592423329792"};
    char directorypath[100] = "./output";
    obj->recursiveCrawler((char*)url, (char *)directorypath, 2);
    delete obj;
    return 0;
}