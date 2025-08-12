#include <iostream>
#include <fstream>
#include "library/crawler.h"
#include "library/strings.h"
using namespace std;

bool isUrlCrawled(const char *url, const char *filename)
{
    ifstream filep(filename);
    if (!filep.is_open())
    {
        return false;
    }
    char line[256];
    char urlPattern[200] = {'\0'};
    my_strcpy(urlPattern, "Url is : ");
    my_strcat(urlPattern, url);
    while (filep.getline(line, 256))
    {
        if (my_strcasestr(line, urlPattern) != nullptr)
        {
            filep.close();
            return true;
        }
    }
    filep.close();
    return false;
}

void searchKeyword(const char *url, const char *keyword, const char *filename)
{
    ifstream filep(filename);
    if (!filep.is_open())
    {
        cerr << "\nError: Could not open " << filename << endl;
        return;
    }
    char checkword[100] = {'\0'};
    char unique[3] = {'-', '>'};
    my_strcat(checkword, unique);
    my_strcat(checkword, keyword);

    char urlPattern[200] = {'\0'};
    my_strcpy(urlPattern, "Url is : ");
    my_strcat(urlPattern, url);

    cout << "\nSearching for keyword '" << keyword << "' in data for URL: " << url << endl;
    char line[256];
    bool flag = false;
    while (filep.getline(line, 256))
    {
        if (my_strcasestr(line, urlPattern) != nullptr && my_strcasestr(line, checkword) != nullptr)
        {
            cout << line << endl;
            flag = true;
        }
    }
    if (!flag)
    {
        cout << "\nNo matching keyword found for this URL." << endl;
    }
    filep.close();
}

int main()
{
    char url[200];
    char keyword[100];
    char directorypath[100] = "./output";
    char seoFile[100] = "./seo_data.txt";
    int depth;
    cout<<"\n\t\t\t\t CRAWLER \t\t\t\t\n";
    cout << "\nEnter the website URL to crawl/search: ";
    cin >> url;
    cout << "\nEnter the keyword to search: ";
    cin >> keyword;
    cout << "\nEnter the crawl depth : ";
    cin >> depth;

    if (depth < 0 || depth > 10)
    {
        cerr << "Invalid Depth";
        return 1;
    }

    crawler *obj = new crawler();

    if (!obj->checkdirectory(directorypath))
    {
        obj->createdirectory(directorypath);
    }

    bool checkcrawl = isUrlCrawled(url, seoFile);

    if (checkcrawl)
    {
        int choice;
        cout << "\nThis URL has been crawled before. Do you want to:\n1. Use previous data\n2. Crawl again for latest data\nEnter choice (1/2): ";
        cin >> choice;
        if (choice == 1)
        {
            cout << "\nUsing previous crawl data." << endl;

            searchKeyword(url, keyword, seoFile);
        }
        else if (choice == 2)
        {
            cout << "\nReCrawling the URL: " << url << endl;
            obj->recursiveCrawler(url, directorypath, depth);
            searchKeyword(url, keyword, seoFile);
        }
        else if (choice != 2)
        {
            cerr << "Invalid choice. Exiting.";
            delete obj;
            return 1;
        }
    }
    else
    {
        cout << "\nCrawling the URL: " << url << endl;

        obj->recursiveCrawler(url, directorypath, depth);
        searchKeyword(url, keyword, seoFile);
    }

    delete obj;
    return 0;
}