#include <iostream>
#include <fstream>
#include <filesystem>
#include "././library/crawler.h"

using namespace std;

crawler::crawler()
{
    obj = new hashTable<char *, char *>();
}

crawler::~crawler()
{
    delete obj;
}

bool crawler::checkdirectory(char *path)
{
    return filesystem::exists(path);
}

void crawler::createdirectory(char *path)
{
    if (filesystem::create_directories(path))
    {
        cout << "Directory created: " << path << endl;
    }
    else
    {
        cerr << "Failed to create directory." << endl;
    }
}

bool crawler::checkurl(char *url)
{
    const char htt[] = {"http://"};
    const char https[] = {"https://"};
    return (my_strstr(url, htt) || my_strstr(url, https));
}

char *crawler::downloadfile(char *url, char *directorypath)
{
    if (!url || !checkurl(url))
    {
        cerr << "Invalid URL: " << (url ? url : "null") << endl;
        return nullptr;
    }
    char *fileurl = new char[200];
    my_strcpy(fileurl, directorypath);
    char cd[] = "/";
    my_strcat(fileurl, cd);
    my_strcat(fileurl, generateUniqueName());

    char command[400];
    char wget[] = "wget -q -O ";
    char c[] = " ";
    char slash[] = "\"";
    my_strcpy(command, wget);
    my_strcat(command, fileurl);
    my_strcat(command, c);

    my_strcat(command, slash);
    my_strcat(command, url);
    my_strcat(command, slash);

    cout << command << endl;
    int result = system(command);
    if (result != 0)
    {
        cerr << "Error failed to Download";
        delete[] fileurl;
        return nullptr;
    }
    return fileurl;
}

LL<char *> *crawler::readfile(char *filepath, char *directorypath, char *urlpath)
{
    ofstream outq("filepath.txt", ios::app);

    if (outq.is_open())
    {
        outq << "\n"
             << urlpath << "\n"
             << filepath << "\n"
             << "\n";
        outq.close();
    }
    LL<char *> *ll = new LL<char *>();

    char *urls = new char[1000];
    char *Allcharacter = new char[10000000];
    char *absolutepath = new char[1000]();
    if (!urls)
    {
        cout << "Memory allocation failed\n";
        delete[] urls;
        delete[] Allcharacter;
        delete[] absolutepath;
        return nullptr;
    }
    ifstream in(filepath, ios::in);
    if (!in.is_open())
    {
        cout << "Can't read file\n";
        delete[] urls;
        delete[] Allcharacter;
        delete[] absolutepath;
        return nullptr;
    }

    char ch;
    bool insideTag = false;
    bool anchorTag = false;
    bool hrefMatch = false;
    bool readingUrl = false;
    bool quotes = false;
    int urlIndex = 0;
    const char hrefPattern[] = "href=";
    int hrefIndex = 0;
    int wordindex = 0;
    bool insidescript = 0;
    char tagBuffer[50];
    char anchorBuffer[4];
    int anchoeindex = 0;
    int tagIndex = 0;
    bool insideScript = false;
    bool insideStyle = false;

    while (in.get(ch))
    {
        if (ch == '<')
        {
            tagIndex = 0;
            tagBuffer[tagIndex++] = ch;
            tagBuffer[tagIndex] = '\0';
        }
        else if (tagIndex > 0 && tagIndex < 49)
        {
            tagBuffer[tagIndex++] = ch;
            tagBuffer[tagIndex] = '\0';

            if (!insideScript && my_strcasestr(tagBuffer, "<script"))
            {
                insideScript = true;
                tagIndex = 0;
            }
            if (!insideStyle && my_strcasestr(tagBuffer, "<style"))
            {
                insideStyle = true;
                tagIndex = 0;
            }

            if (insideScript && my_strcasestr(tagBuffer, "</script"))
            {
                insideScript = false;
                tagIndex = 0;
            }
            if (insideStyle && my_strcasestr(tagBuffer, "</style"))
            {
                insideStyle = false;
                tagIndex = 0;
            }

            if (ch == '>')
            {
                tagIndex = 0;
            }
        }

        if (insideScript || insideStyle)
        {
            continue;
        }

        if (ch == '<')
        {
            insideTag = true;
            anchorTag = false;
            hrefIndex = 0;
            anchorBuffer[anchoeindex++] = ch;
            anchorBuffer[anchoeindex] = '\0';
        }
        if (insideTag && anchoeindex < sizeof(anchorBuffer) - 1)
        {
            anchorBuffer[anchoeindex++] = ch;
            anchorBuffer[anchoeindex] = '\0';
            if (my_strcasestr(anchorBuffer, "<a"))
            {
                anchorTag = true;
            }
        }
        if (anchorTag && insideTag)
        {
            if (hrefIndex < stringlength(hrefPattern) &&
                (ch == hrefPattern[hrefIndex] || ch == (hrefPattern[hrefIndex] - 32)))
            {
                hrefIndex++;
                if (hrefIndex == stringlength(hrefPattern))
                {
                    hrefMatch = true;
                }
            }
            else if (hrefMatch && ch == '"')
            {
                readingUrl = !readingUrl;

                if (!readingUrl)
                {
                    urls[urlIndex] = '\0';

                    if (isCrawlablePage(urls) && ((startwiht(urls, "http") || startwiht(urls, "https"))))
                    {
                        char *normalizedUrl = deleteSlash(urls);
                        if (!obj->searching(normalizedUrl))
                        {
                            char *urlCopy = new char[stringlength(normalizedUrl) + 1];
                            my_strcpy(urlCopy, normalizedUrl);
                            ll->insertionAtEnd(urlCopy);
                            delete[] normalizedUrl;
                        }
                    }
                    else if (urls[0] == '/')
                    {
                        absolutepath[0] = '\0';
                        toAbsoluteUrl(urlpath, urls, absolutepath);
                        if (isCrawlablePage(absolutepath) && !obj->searching(absolutepath))
                        {
                            char *urlCopy = new char[stringlength(absolutepath) + 1]();
                            my_strcpy(urlCopy, absolutepath);
                            ll->insertionAtEnd(urlCopy);
                        }
                    }

                    urlIndex = 0;
                    hrefMatch = false;
                }
            }
            else if (readingUrl && urlIndex < 999)
            {
                urls[urlIndex++] = ch;
            }
            else
            {
                hrefIndex = 0;
            }
        }

        if (insideTag && ch == '"' && !quotes)
        {
            quotes = true;
        }
        else if (insideTag && ch == '"' && quotes)
        {
            quotes = false;
        }

        if (!insideTag && !quotes)
        {
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
            {
                Allcharacter[wordindex++] = ch;
            }
            else
            {
                Allcharacter[wordindex++] = ' ';
            }
        }

        if (ch == '>')
        {
            if (wordindex > 0 && Allcharacter[wordindex - 1] != ' ')
            {
                Allcharacter[wordindex++] = ' ';
            }
            anchoeindex = 0;
            insideTag = false;
            anchorTag = false;
            hrefMatch = false;
            hrefIndex = 0;

            urlIndex = readingUrl ? urlIndex : 0;
        }
    }
    in.close();
    delete[] urls;

    cout << "Extracted URLs:\n";
    cout << urlpath;
    cout << "\n"
         << absolutepath << "  absolute path hai ";
    ll->display();
    cout << "\nHashTable:\n";
    obj->displayHash();
    Allcharacter[wordindex] = '\0';

    const char *stopwords[] = {
        "a", "about", "am", "an", "and", "any", "are", "article", "as", "at",
        "be", "because", "been", "but", "by", "can", "com", "content", "could",
        "css", "did", "do", "does", "domains", "for", "from", "gif", "had",
        "has", "have", "he", "her", "here", "his", "how", "html", "http",
        "https", "i", "if", "image", "img", "in", "is", "it", "its", "java",
        "jpeg", "jpg", "js", "just", "li", "m4a", "m4v", "may", "me", "might",
        "mov", "mp3", "mp4", "must", "my", "news", "no", "not", "null", "of",
        "on", "or", "otf", "page", "pdf", "png", "psd", "py", "raw", "sass",
        "script", "scss", "she", "shall", "should", "so", "style", "svg",
        "tif", "tiff", "them", "their", "they", "this", "to", "ttf", "wav", "the",
        "was", "we", "webm", "webp", "were", "what", "when", "where", "while",
        "who", "why", "will", "with", "woff", "woff2", "would", "www", "you",
        "your", ".aac", ".aax", ".ai", ".aiff", ".alac", ".ape", ".au", ".avi",
        ".avif", ".bmp", ".bpg", ".dss", ".eot", ".eps", ".f4v", ".flac", ".flv",
        ".gsm", ".heic", ".heif", ".ico", ".json", ".jsx", ".less", ".mkv", ".mpc",
        ".mpeg", ".mpg", ".ogg", ".tsx", ".ts", ".webm", ".webp", ".wma", ".wmv", "nbsp", "more", "hour"};
    int stopcount = sizeof(stopwords) / sizeof(stopwords[0]);
    char *cleanText = normalize_whitespace(Allcharacter);
    char arr[200] = {"\0"};
    my_strcat(arr, urlpath);

    my_strcat(arr, "   ");
    my_strcat(arr, filepath);
    cout << arr << "Arr hai ji";
    
    most_frequent_word(cleanText, stopwords, stopcount, arr);
    cout << "jgkvjkgvjkbvjk";
    free(cleanText);
    return ll;
}

void crawler::recursiveCrawler(char *url, char *directorypath, int maxDepth)
{
    if (!url || !directorypath || maxDepth == 0)
        return;
    if (!checkurl(url))
    {
        cout << "Skipping invalid URL: " << url << endl;
        return;
    }

    char *urlslash = deleteSlash(url);
    Node<char *, char *> *node = obj->searching(urlslash);
    if (node)
    {
        delete[] urlslash;
        cout << "already hash mai hai ";
        return;
    }

    char *urlCopy = new char[stringlength(urlslash) + 1];
    my_strcpy(urlCopy, urlslash);
    char *filepath = downloadfile(urlCopy, directorypath);
    if (!filepath)
    {
        delete[] urlCopy;
        delete[] urlslash;
        return;
    }

    obj->insertion(urlCopy, filepath);
    LL<char *> *links = readfile(filepath, directorypath, urlCopy);
    llNode<char *> *head = links->gethead();
    while (head)
    {

        recursiveCrawler(head->val, directorypath, maxDepth - 1);
        head = head->next;
    }
    delete links;
    delete[] filepath;
}

int crawler::stringtoint(char *depth)
{
    int num = 0;
    int size = stringlength(depth);
    for (int i = 0; i < size; i++)
    {
        num = num * 10 + (depth[i] - '0');
    }
    return num;
}

bool crawler::isCrawlablePage(const char *url)
{
    if (!url || stringlength(url) == 0)
        return false;
    int len = stringlength(url);
    if (my_strcasestr(url, ".css") || my_strcasestr(url, ".js") || my_strcasestr(url, ".svg") ||
        my_strcasestr(url, ".jpg") || my_strcasestr(url, ".jpeg") ||
        my_strcasestr(url, ".png") || my_strcasestr(url, ".woff") || my_strcasestr(url, ".ttf") || my_strcasestr(url, "mailto:") ||
        my_strcasestr(url, "javascript:") ||
        url[0] == '#')
    {
        return false;
    }
    if (endsWith(url, ".html") || endsWith(url, ".htm") || endsWith(url, ".php") ||
        endsWith(url, ".aspx") || endsWith(url, ".jsp") || endsWith(url, ".com") ||
        url[len - 1] == '/')
    {
        return true;
    }
    return true;
}

char *crawler::deleteSlash(const char *url)
{
    int length = stringlength(url);
    char *changeurl = new char[length + 1];
    my_strcpy(changeurl, url);
    char *questionmark = new char[2];

    questionmark[0] = {'?'};
    if (length > 0 && changeurl[length - 1] == '/' && my_strstr(changeurl, questionmark) == nullptr)
    {
        changeurl[length - 1] = '\0';
    }
    return changeurl;
}

void crawler::toAbsoluteUrl(const char *base_url, const char *relative_url, char *absolute_url)
{
    if (!base_url || !relative_url || !absolute_url)
    {
        absolute_url[0] = '\0';
        return;
    }
    absolute_url[0] = '\0';
    my_strcpy(absolute_url, base_url);
    int len = stringlength(absolute_url);
    if (len > 0 && absolute_url[len - 1] == '/')
    {
        absolute_url[len - 1] = '\0';
        len--;
    }
    if (relative_url[0] != '/')
    {
        my_strcat(absolute_url, "/");
    }
    my_strcat(absolute_url, relative_url);
}

bool crawler::endsWith(const char *url, const char *ext)
{
    long urllength = stringlength(url);
    long extlength = stringlength(ext);
    if (urllength < extlength)
        return false;
    for (long i = 0; i < extlength; i++)
    {
        if (url[urllength - extlength + i] != ext[i])
        {
            return false;
        }
    }
    return true;
}

bool crawler::startwiht(const char *url, const char *ext)
{
    long urllength = stringlength(url);
    long extlength = stringlength(ext);
    if (urllength < extlength)
        return false;
    for (long i = 0; i < extlength; i++)
    {
        if (url[i] != ext[i])
        {
            return false;
        }
    }
    return true;
}