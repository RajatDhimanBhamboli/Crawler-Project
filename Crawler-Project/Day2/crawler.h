#include <iostream>
#include <fstream>
#include <filesystem>
#include "./hashcpp.h"
#include <cstring>

#include "./ll.h"
using namespace std;

class crawler
{
private:
    hashTable<char *, char *> *obj = new hashTable<char *, char *>();
    LL<char *> *ll = new LL<char *>();

public:
    ~crawler()
    {
        delete obj;
        delete ll;
    }

    bool checkdirectory(char *path)
    {
        if (!filesystem::exists(path))
        {
            return false;
        }
        return true;
    }

    void createdirectory(char *path)
    {
        if (filesystem::create_directories(path))
        {
            cout << "Directory created: " << path << std::endl;
        }
        else
        {
            cerr << "Failed to create directory." << std::endl;
        }
    }

    char *longnumbertostring(long long time)
    {

        int sum = 0, n = 0;
        char *name = (char *)malloc(30);
        long long reversenumber = 0;
        while (time > 0)
        {
            n = time % 10;
            reversenumber = reversenumber * 10 + n;
            time /= 10;
        }
        int i = 0;
        while (reversenumber > 0)
        {
            char p = (reversenumber % 10) + '0';
            name[i] = p;
            reversenumber /= 10;
            i++;
        }
        name[i] = '\0';
        char html[] = {'.', 'h', 't', 'm', 'l', '\0'};
        my_strcat(name, html);

        return name;
    }

    char *generateUniqueName()
    {

        time_t now = time(0);
        char *tostring = longnumbertostring(now);
        return tostring;
    }

    bool checkurl(char *url)
    {
        const char htt[] = {"http://"};
        char *result = my_strstr(url, htt);
        if (!result)
        {
            return false;
        }
        else
            return true;
    }

    char *downloadfile(char *url, char *dirctorypath)
    {

        char *fileurl = new char[100];
        my_strcpy(fileurl, dirctorypath);
        char cd[] = "/";
        my_strcat(fileurl, cd);

        my_strcat(fileurl, generateUniqueName());

        char command[200];
        char wget[] = "wget -O ";
        char c[] = " ";
        my_strcpy(command, wget);
        my_strcat(command, fileurl);
        my_strcat(command, c);
        my_strcat(command, url);
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

    bool isEqualInsensitive(const char *s1, const char *s2, int l)
    {
        for (int i = 0; i < l; i++)
        {
            char a = s1[i];
            char b = s2[i];
            if (a >= 'A' && a <= 'Z')
                a += 32;
            if (b >= 'A' && b <= 'Z')
                b += 32;
            if (a != b)
                return false;
        }
        return true;
    }

    bool endsWith(const char *url, const char *ext)
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
    bool startwiht(const char *url, const char *ext)
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

    LL<char *> *readfile(char *filepath, char *directorypath, char *urlpath)
    {
        char *urls = new char[1000];
        char *Allcharacter = new char[1000000];
        if (!urls)
        {
            cout << "Memory allocation failed\n";
            return nullptr;
        }
        cout << "\nReading file: " << filepath << "\n";
        ifstream in(filepath, ios::in);
        if (!in.is_open())
        {
            cout << "Can't read file\n";
            delete[] urls;
            return nullptr;
        }

        char ch;
        bool insideTag = false;
        bool anchorTag = false;
        bool hrefMatch = false;
        bool readingUrl = false;
        int urlIndex = 0;
        const char hrefPattern[] = "href=";
        int hrefIndex = 0;
        int wordindex = 0;
        bool insideStyle = false;
        char styleBuffer[10];
        int styleIndex = 0;

        while (in.get(ch))
        {

            if (ch == '<')
            {
                styleIndex = 0;
                styleBuffer[styleIndex++] = ch;
            }
            else if (styleIndex > 0 && styleIndex < 9)
            {
                styleBuffer[styleIndex++] = ch;
                styleBuffer[styleIndex] = '\0';

                if (isEqualInsensitive(styleBuffer, "<style", 6))
                {
                    insideStyle = true;
                    styleIndex = 0;
                }
                if (isEqualInsensitive(styleBuffer, "</style", 7))
                {
                    insideStyle = false;
                    styleIndex = 0;
                }
            }
            if (insideStyle)
            {
                continue;
            }
            if (ch == '<')
            {
                insideTag = true;
                hrefIndex = 0;
            }
            if (insideTag && (ch == 'a' || ch == 'A'))
            {
                anchorTag = true;
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
                        // if (checkurl(urls) || my_strstr(urls, "/")) {
                        if ((startwiht(urls, "http") || startwiht(urls, "https")) &&
                            (endsWith(urls, ".html")))
                        {

                            if (!obj->searching(urls))
                            {
                                char *urlCopy = new char[stringlength(urls) + 1];
                                my_strcpy(urlCopy, urls);
                                ll->insertionAtEnd(urlCopy);
                                // obj->insertion(urlCopy,directorypath );
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

            if (!insideTag)
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
        ll->display();
        cout << "\nHashTable:\n";
        obj->displayHash();
        Allcharacter[wordindex] = '\0';

        const char *stopwords[] = {
            "the", "and", "is", "of", "to", "a", "in", "it", "for", "on", "with", "as", "at",
            "this", "by", "from", "or", "an", "be", "are", "was", "that", "but", "not",
            "have", "has", "had", "you", "i", "we", "they", "he", "she", "his", "her",
            "them", "its", "which", "will", "their", "been", "if", "can", "would",
            "do", "does", "did", "so", "about", "my", "your", "me", "no", "just",
            "https", "http", "com", "www", "html", "content", "style", "script",
            "page", "news", "article", "image", "img"};
        int stopcount = sizeof(stopwords) / sizeof(stopwords[0]);
        char *cleanText = normalize_whitespace(Allcharacter);
        cout << "hare krishna\n\n\n";
        char arr[200] = {"\0"};
        my_strcat(arr, urlpath);

        my_strcat(arr, "/");
        my_strcat(arr, filepath);
        most_frequent_word(cleanText, stopwords, stopcount, arr);
        cout << "jgkvjkgvjkbvjk";
        free(cleanText);
        return ll;
    }

    void recursiveCrawler(char *url, char *dirctorypath, int maxDepth)
    {
        if (!url || !dirctorypath || maxDepth <= 0)
        {
            return;
        }

        Node<char *, char *> *node = obj->searching(url);
        if (node)
        {
            return;
        }

        // Mark URL as visited before processing
        // if (node)
        // {
        //     obj->changevalue(url, 1);
        // }
        char *urlCopy = new char[stringlength(url) + 1];
        my_strcpy(urlCopy, url);

        char *filepath = downloadfile(url, dirctorypath);
        if (!filepath)
        {
            delete[] urlCopy;
            return;
        }

        obj->insertion(urlCopy, filepath);

        LL<char *> *links = readfile(filepath, dirctorypath, url);

        llNode<char *> *head = ll->gethead();
        while (head)
        {
            recursiveCrawler(head->val, dirctorypath, maxDepth - 1);
            head = head->next;
        }

        delete[] filepath;
    }
    int stringlength(const char *str)
    {
        int count = 0;

        for (int i = 0; str[i] != '\0'; i++)
        {
            count++;
        }
        return count;
    }

    bool my_strcmp(const char *a, const char *b)
    {
        int i = 0;
        while (a[i] != '\0')
        {
            if (a[i] != b[i])
            {
                return false;
            }
            i++;
        }
        return true;
    }
    char *my_strcat(char *dest, const char *src)
    {
        int i = 0;
        while (dest[i] != '\0')
        {
            i++;
        }
        int j = 0;
        while (src[j] != '\0')
        {
            dest[i++] = src[j++];
        }
        dest[i] = '\0';
        return dest;
    }
    char *my_strcpy(char *dest, const char *src)
    {
        int i = 0;
        while (src[i] != '\0')
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        return dest;
    }
    // LL<char *> *readfile(char *filepath, char *dirctorypath)
    // {
    //     char *urls = new char[1000];
    //     cout << "\n"
    //          << filepath << "\n";
    //     ifstream in(filepath, ios::in);
    //     if (!in || !in.is_open())
    //     {
    //         cout << "Can't read\n";
    //         delete[] urls;
    //         return nullptr;
    //     }
    //     char ch;
    //     bool insideTag = false;
    //     char buffer[10];
    //     int bufIndex = 0;
    //     bool readingUrl = false;
    //     int urlIndex = 0;
    //     while (in.get(ch))
    //     {
    //         if (ch == '<')
    //         {
    //             insideTag = true;
    //             bufIndex = 0;
    //         }
    //         if (insideTag && bufIndex < 9)
    //         {
    //             buffer[bufIndex++] = ch;
    //             buffer[bufIndex] = '\0';
    //             if (bufIndex == 2 && (buffer[1] == 'a' || buffer[1] == 'A'))
    //             {
    //                 char temp[10];
    //                 int tempIndex = 0;
    //                 while (in.get(ch) && tempIndex < 6)
    //                 {
    //                     temp[tempIndex++] = ch;
    //                     if (tempIndex >= 5 && isEqualInsensitive(temp + tempIndex - 5, "href="))
    //                     {
    //                         in.get(ch);
    //                         if (ch == '"' )
    //                         {
    //                             char quoteChar = ch;
    //                             urlIndex = 0;
    //                             while (in.get(ch) && ch != quoteChar && urlIndex < 999)
    //                             {
    //                                 urls[urlIndex++] = ch;
    //                             }
    //                             urls[urlIndex] = '\0';
    //                             // if ((startwiht(urls, "http") || startwiht(urls, "https")) &&
    //                             //     (endsWith(urls, ".html") || endsWith(urls, "/") || endsWith(urls, ".php") || endsWith(urls, ".aspx") || endsWith(urls, ".htm") || endsWith(urls, ".jsp")))
    //                             // {
    //                             // if(endsWith(urls,"/")){
    //                             cout<<"\n\n\n\n"<<urls<<"\n\n";
    //                              if ((startwiht(urls, "http") || startwiht(urls, "https")) &&
    //                                 ( endsWith(urls, "/") ))
    //                             {
    //                                 cout<<"\n\n\n\n"<<urls<<"\n\n";
    //                                 if (!obj->searching(urls))
    //                                 {
    //                                     // return nullptr ;
    //                                     char *urlCopy = new char[stringlength(urls) + 1];
    //                                     my_strcpy(urlCopy, urls);
    //                                     ll->insertionAtEnd(urlCopy);
    //                                     // obj->insertion(urlCopy, 0); // Mark as unvisited
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //                 insideTag = false;
    //             }
    //         }
    //         if (ch == '>')
    //         {
    //             insideTag = false;
    //             bufIndex = 0;
    //         }
    //     }
    //     in.close();
    //     delete[] urls;
    //     cout << "\n\nNewly Created HashTable: ";
    //     obj->displayHash();
    //     cout << "\n\nNewly linked list return ki hai  HashTable: ";
    //     ll->display();
    //     return ll;
    // }

    char *my_strchr(const char *s, int c)
    {
        int i = 0;
        while (s[i] != '\0')
        {
            if (s[i] == (char)c)
            {
                return (char *)&s[i];
            }
            i++;
        }
        return NULL;
    }

    int stringtoint(char *depth)
    {
        int num = 0;
        int size = stringlength(depth);
        for (int i = 0; i < size; i++)
        {
            num = num * 10 + (depth[i] - '0');
        }
        return num;
    }

    char *my_strstr(const char *haystack, const char *needle)
    {
        int i = 0;
        while (haystack[i] != '\0')
        {
            int j = 0;
            while (needle[j] != '\0' && haystack[i + j] == needle[j])
            {
                j++;
            }
            if (needle[j] == '\0')
            {
                return (char *)&haystack[i];
            }
            i++;
        }
        return NULL;
    }

    void reverse_inplace(char *s)
    {
        int n = stringlength(s);
        for (int i = 0; i < n / 2; i++)
        {
            char temp = s[i];
            s[i] = s[n - i - 1];
            s[n - i - 1] = temp;
        }
        cout << "\nreverse string : " << s;
    }

    int is_palindrome(const char *s)
    {
        if (!s)
            return 0;

        int n = stringlength(s);
        for (int i = 0; i < n / 2; i++)
        {
            if (s[i] != s[n - i - 1])
            {
                return 0;
            }
        }
        return 1;
    }

    int count_words(const char *s)
    {
        int i = 0;
        int flag = 0, count = 0;
        while (s[i] != '\0')
        {
            if (s[i] != ' ' && flag == 0)
            {
                if (flag == 0)
                    count++;
                flag = 1;
            }
            else if (s[i] == ' ' && flag == 1)
            {
                flag = 0;
            }
            i++;
        }
        return count;
    }

    char *lowercase(const char *haystack)
    {
        int n = stringlength(haystack);
        char *lower = (char *)malloc(n + 1);
        for (int i = 0; i < n; i++)
        {
            char ch = haystack[i];
            if (ch >= 'A' && ch <= 'Z')
            {
                lower[i] = ch + 32;
            }
            else
            {
                lower[i] = ch;
            }
        }
        lower[n] = '\0';
        return lower;
    }

    char *normalize_whitespace(const char *str)
    {
        int len = stringlength(str);
        char *result = (char *)malloc(len + 1);
        int j = 0;
        int flag = 1;

        for (int i = 0; i < len; i++)
        {
            char ch = str[i];

            if (ch == ' ' || ch == '\t' || ch == '\n')
            {
                if (!flag)
                {
                    result[j++] = ' ';
                    flag = 1;
                }
            }
            else
            {
                result[j++] = ch;
                flag = 0;
            }
        }
        result[j] = '\0';
        return result;
    }

    char *my_strcasestr(char *haystack, char *needle)
    {
        int i = 0;
        needle = lowercase(needle);
        haystack = lowercase(haystack);
        while (haystack[i] != '\0')
        {
            int j = 0;
            while (needle[j] != '\0' && haystack[i + j] == needle[j])
            {
                j++;
            }
            if (needle[j] == '\0')
            {
                return (char *)&haystack[i];
            }
            i++;
        }
        return NULL;
    }

    void most_frequent_word(char *text, const char **stopwords, int stopcount, char *url)
    {
        char *lower_text = lowercase(text);
        hashTable<char *, int> *obj = new hashTable<char *, int>();
        char sample[2000][100];
        int flag = 0, wordIndex = 0, charIndex = 0;

        for (int i = 0; lower_text[i] != '\0'; i++)
        {
            if (lower_text[i] != ' ' && lower_text[i] != '\t' && lower_text[i] != '\n')
            {
                if (flag == 0)
                {
                    flag = 1;
                    charIndex = 0;
                }
                if (charIndex < 99)
                {
                    sample[wordIndex][charIndex++] = lower_text[i];
                }
            }
            else if (flag == 1)
            {
                sample[wordIndex][charIndex] = '\0';
                wordIndex++;
                flag = 0;
                if (wordIndex >= 2000)
                {
                    cout << "Warning: Too many words, truncating\n";
                    break;
                }
            }
        }

        if (flag == 1 && wordIndex < 2000)
        {
            sample[wordIndex][charIndex] = '\0';
            wordIndex++;
        }

        cout << "\nExtracted words:\n";
        for (int k = 0; k < wordIndex; k++)
        {
            cout << sample[k] << "\n";
        }

        for (int k = 0; k < wordIndex; k++)
        {
            bool isStopword = false;
            for (int j = 0; j < stopcount; j++)
            {
                char *stopword_lower = lowercase(stopwords[j]);
                if (my_strcmp(sample[k], stopword_lower))
                {
                    isStopword = true;
                    free(stopword_lower);
                    break;
                }
                free(stopword_lower);
            }

            if (!isStopword)
            {
                char *wordCopy = new char[stringlength(sample[k]) + 1];
                my_strcpy(wordCopy, sample[k]);

                Node<char *, int> *node = obj->searching(wordCopy);
                if (node != NULL)
                {
                    obj->changevalue(wordCopy, node->value + 1);
                    delete[] wordCopy;
                }
                else
                {
                    obj->insertion(wordCopy, 1);
                }
            }
        }

        char mostWord[50] = "";
        int maxCount = 0;
        for (int b = 0; b < obj->hashSize; b++)
        {
            Node<char *, int> *temp = obj->hashmap[b];
            while (temp)
            {
                if (temp->value > maxCount)
                {
                    maxCount = temp->value;
                    my_strcpy(mostWord, temp->key);
                }
                temp = temp->next;
            }
        }

        cout << "\nHash Table Contents:\n";
        obj->displayHash();
        cout << "\nMost frequent word: " << mostWord << " (Count: " << maxCount << ")\n";
        ofstream out("seo_data.txt", ios::app);

        if (out.is_open())
        {
            out << "Url is : " << url << " , FrequentWord : " << mostWord << ", Count : " << maxCount << "\n";
            out.close();
        }

        free(lower_text);
        delete obj;
    }

    // void most_frequent_word(char *text, const char **stopwords, int stopcount)
    // {
    //     text = lowercase(text);
    //     hashTable<char *, int> *obj = new hashTable<char *, int>();
    //     int i = 0;
    //     cout << "\n kya ha\n";
    //     char sample[2000][100];
    //     int flag = 0, count = 0, wordIndex = 0, charIndex = 0;
    //     while (text[i] != '\0')
    //     {
    //         if (text[i] != ' ')
    //         {
    //             if (flag == 0)
    //             {
    //                 flag = 1;
    //                 charIndex = 0;
    //             }
    //             sample[wordIndex][charIndex++] = text[i];
    //         }
    //         else if (flag == 1)
    //         {
    //             sample[wordIndex][charIndex] = '\0';
    //             wordIndex++;
    //             flag = 0;
    //         }
    //         i++;
    //
    //     if (flag == 1)
    //     {
    //         sample[wordIndex][charIndex] = '\0';
    //         wordIndex++;
    //     }
    //     for (int k = 0; k < wordIndex; k++)
    //     {
    //         bool isStopword = false;
    //         for (int j = 0; j < stopcount; j++)
    //         {
    //             char *stopword_lower = lowercase(stopwords[j]);
    //             if (my_strcmp(sample[k], stopwords[j]))
    //             {
    //                 isStopword = true;
    //                 free(stopword_lower);
    //                 break;
    //             }
    //         }
    //         if (!isStopword)
    //         {
    //             char *wordCopy = new char[stringlength(sample[k]) + 1];
    //             my_strcpy(wordCopy, sample[k]);
    //             if (obj->checkisPresent(sample[k]))
    //             {
    //                 Node<char *, int> *node = obj->searching(wordCopy);
    //                 if (node != NULL)
    //                     obj->changevalue(wordCopy, node->value + 1);
    //                 delete[] wordCopy;
    //             }
    //             else
    //             {
    //                 obj->insertion(wordCopy, 1);
    //             }
    //         }
    //     }
    //     cout << "\n kya ha\n";
    //     char mostWord[50] = "";
    //     int maxCount = 0;
    //     for (int b = 0; b < obj->hashSize; b++)
    //     {
    //         Node<char *, int> *temp = obj->hashmap[b];
    //         while (temp)
    //         {
    //             if (temp->value > maxCount)
    //             {
    //                 maxCount = temp->value;
    //                 my_strcpy(mostWord, temp->key);
    //             }
    //             temp = temp->next;
    //         }
    //     }
    //     cout << "\n\n\n\n\n\n";
    //     obj->displayHash();
    //     cout << "\n\n\n\n\n\n\n\n\n";
    //     cout << "\nfrequent word: " << mostWord << " " << maxCount << "\n";
    //     free(text);
    //     delete obj;
    // }

    char *placeholder(char *templates, const char *data[], int size)
    {
        int i = 0;
        static char result[1000];
        int valueindex = 0;
        while (templates[i] != '\0')
        {
            if (templates[i] == '{' && templates[i + 1] == '{')
            {
                i += 2;
                int keyindex = 0;
                char samplek[50];
                while (!(templates[i] == '}' && templates[i + 1] == '}') && templates[i] != '\0')
                {
                    samplek[keyindex++] = templates[i];
                    i++;
                }
                samplek[keyindex] = '\0';
                i += 2;
                int flag = 0;
                for (int j = 0; j < size; j++)
                {
                    if (my_strcmp(samplek, data[j]))
                    {
                        my_strcpy(&result[keyindex], (char *)data[j + 1]);
                        valueindex += stringlength(data[j]);
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    valueindex += stringlength(samplek) + 4;
                }
            }
            else
            {
                result[valueindex++] = templates[i];
            }
            i++;
        }
        result[valueindex] = '\0';

        return result;
    }
};
