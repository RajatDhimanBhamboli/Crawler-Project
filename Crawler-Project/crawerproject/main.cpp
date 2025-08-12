#include <iostream>
#include "././library/crawler.h"

using namespace std;

int main(int argc, char* argv[]) {
    crawler* obj = new crawler();
    if (argc < 3) {
        cerr << "Error: Invalid data";
        return 1;
    }
    char* url = argv[1];
    int depth = obj->stringtoint(argv[3]);
    if (depth < 0 || depth > 3) {
        cerr << "Invalid Depth";
        return 1;
    }
    char* directorypath = argv[2];

    if (!obj->checkdirectory(directorypath)) {
        obj->createdirectory(directorypath);
    }

    obj->recursiveCrawler(url, directorypath, depth);
    delete obj;
    return 0;
}