#include <iostream>
#include "./hashcpp.h"

using namespace std;

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
char *my_strcpy(char *dest,const  char *src)
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
char *lowercase(const char *haystack) {
    int n = stringlength(haystack);
    char *lower = (char *)malloc(n + 1);
    for (int i = 0; i < n; i++) {
        char ch = haystack[i];
        if (ch >= 'A' && ch <= 'Z') {
            lower[i] = ch + 32;
        } else {
            lower[i] = ch; 
        }
    }
    lower[n] = '\0';
    return lower;
}

char *normalize_whitespace(const char *str) {
    int len = stringlength(str);
    char *result = (char *)malloc(len + 1); 
    int j = 0;
    int flag = 1;

    for (int i = 0; i < len; i++) {
        char ch = str[i];

        if (ch == ' ' || ch == '\t' || ch == '\n') {
            if (!flag) { 
                result[j++] = ' '; 
                flag = 1;     
            }
        } 
        else {
            result[j++] = ch; 
            flag = 0;     
        }
    }
    result[j] = '\0'; 
    return result;
}

char *my_strcasestr( char *haystack,  char *needle)
{
    int i = 0;
    needle=lowercase(needle);
    haystack=lowercase(haystack);
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
void most_frequent_word(const char *text, const char **stopwords, int stopcount)
{
    hashTable<string, int> *obj = new hashTable<string, int>();
    int i = 0;
    char sample[20][30];
    int flag = 0, count = 0, wordIndex = 0, charIndex = 0;
    while (text[i] != '\0')
    {
        if (text[i] != ' ')
        {
            if (flag == 0)
            {
                flag = 1;
                charIndex = 0;
            }
            sample[wordIndex][charIndex++] = text[i];
        }
        else if (flag == 1)
        {
            sample[wordIndex][charIndex] = '\0';
            wordIndex++;
            flag = 0;
        }
        i++;
    }
    if (flag == 1)
    {
        sample[wordIndex][charIndex] = '\0';
        wordIndex++;
    }

    for (int k = 0; k < wordIndex; k++)
    {
        flag = 0;
        for (int j = 0; j < stopcount; j++)
        {
            if (my_strcmp(sample[k], stopwords[j]))
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            if (obj->checkisPresent(sample[k]))
            {
                Node<string, int> *isPresent = obj->searching(sample[k]);

                if (isPresent != NULL)
                    obj->changevalue(sample[k], isPresent->value + 1);
            }
            else
            {
                obj->insertion(sample[k], 1);
            }
        }
    }

    char mostWord[30] = "";
    int maxCount = 0;
    for (int b = 0; b < obj->hashSize; b++)
    {
        Node<string, int> *temp = obj->hashmap[b];
        while (temp)
        {
            if (temp->value > maxCount)
            {
                maxCount = temp->value;
                my_strcpy(mostWord, (char *)temp->key.c_str());
            }
            temp = temp->next;
        }
    }

    cout << "\nfrequent word: " << mostWord << " " << maxCount << "\n";
}

char *placeholder(char *templates, const  char *data[], int size)
{
    int i = 0;
     static char result[1000];
    int valueindex=0;
    while (templates[i] != '\0')
    {
        if (templates[i] == '{' && templates[i + 1] == '{')
        {
            i+=2;
            int keyindex=0;
            char samplek[50];
            while(!(templates[i] == '}' && templates[i + 1] == '}') && templates[i] != '\0'){
                samplek[keyindex++]=templates[i];
                i++;
            }
            samplek[keyindex]='\0';
            i+=2;
            int flag=0;
            for(int j=0;j<size;j++){
                if(my_strcmp(samplek,data[j])){
                    my_strcpy(&result[keyindex],(char*)data[j+1]);
                    valueindex+=stringlength(data[j]);
                    flag=1;
                    break;
                }
            }
            if(flag==0){
                valueindex+=stringlength(samplek)+4;
            }
        }
        else {
            result[valueindex++]=templates[i];
        }
        i++;
    }
    result[valueindex]='\0';

   return result;      
}


// char *csvtoken(char *csvdata){
//     int 
// }