#include <iostream>
#include <fstream>
#include "././library/seo.h"

using namespace std;

void most_frequent_word(char *text, const char **stopwords, int stopcount, char *url)
{
    ofstream visit("visited.txt", ios::app);

    if (visit.is_open())
    {
        visit << url<< "\n";
        visit.close();
    }
    char *lower_text = lowercase(text);
    if (!lower_text)
    {
        cout << "Error: Memory allocation failed for lower_text\n";
        return;
    }

    hashTable<char *, int> *obj = new hashTable<char *, int>();
    char sample[20000][100];
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
            if (wordIndex >= 20000)
            {
                cout << "Warning: Too many words\n";
                break;
            }
        }
    }

    if (flag == 1 && wordIndex < 20000)
    {
        sample[wordIndex][charIndex] = '\0';
        wordIndex++;
    }

    char **lower_stopwords = new char *[stopcount];
    for (int i = 0; i < stopcount; i++)
    {
        lower_stopwords[i] = lowercase(stopwords[i]);
        if (!lower_stopwords[i])
        {
            cout << "Error: Memory allocation failed for stopword\n";
            // Cleanup aur exit
            for (int j = 0; j < i; j++)
            {
                free(lower_stopwords[j]);
            }
            delete[] lower_stopwords;
            free(lower_text);
            delete obj;
            return;
        }
    }
    for (int k = 0; k < wordIndex; k++)
    {
        bool isStopword = false;
        for (int j = 0; j < stopcount; j++)
        {
            if (my_strcmp(sample[k], lower_stopwords[j]))
            {
                isStopword = true;
                break;
            }
        }

        if (!isStopword && stringlength(sample[k]) > 1)
        {
            char *wordCopy = new char[stringlength(sample[k]) + 1];
            if (!wordCopy)
            {
                cout << "Error: Memory allocation failed for wordCopy\n";
                continue;
            }
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

    char mostWord[100] = "";
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
    cout << "\nMost frequent word: " << mostWord << " (Count: " << maxCount << ")\n";
    ofstream out("seo_data.txt", ios::app);

    if (out.is_open())
    {
        out << "Url is : " << url << " , FrequentWord ->" << mostWord << ", Count : " << maxCount << "\n";
        out.close();
    }
    for (int i = 0; i < stopcount; i++)
    {
        free(lower_stopwords[i]);
    }
    delete[] lower_stopwords;
    free(lower_text);
    delete obj;
}
