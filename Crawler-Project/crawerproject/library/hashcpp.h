#ifndef HASHCPP_H
#define HASHCPP_H

#include <iostream>
using namespace std;
template <typename k, typename v>
class Node
{
public:
    k key;
    v value;
    Node<k, v> *next;
    Node(k ke, v va)
    {
        key = ke;
        value = va;
        next = nullptr;
    }
};
template <typename k, typename v>

class hashTable
{
public:
    int hashSize = 3;
    Node<k, v> **hashmap;
    int totalElements;

    hashTable()
    {
        hashmap = new Node<k, v> *[hashSize]();
        totalElements = 0;
    }
    ~hashTable()
    {
        clear();
        delete[] hashmap;
        hashmap = nullptr;
    }

    int hashfunction(k key)
    {
        return hash(key);
    }
    void insertion(k key, v value)
    {
        int hashposition = hashfunction(key);

        if (checkisPresent(key))
        {
            cout << "already present ";
            return;
        }

        else if (hashmap[hashposition] == nullptr)
        {
            hashmap[hashposition] = new Node<k, v>(key, value);
        }
        else
        {
            Node<k, v> *temp = hashmap[hashposition];
            Node<k, v> *newnode = new Node<k, v>(key, value);
            newnode->next = temp;
            hashmap[hashposition] = newnode;
        }
        totalElements++;
        if ((totalElements / hashSize) * 100 >= 50)
            resizehash();
    }
    int count(k key)
    {
        int number = key.length();
        int count = 0;
        for (int i = 0; i < number; i++)
        {
            count += (key[i] - 'a');
        }
        return count;
    }

    void deletenode(k key)
    {
        int hashposition = hashfunction(key);
        Node<k, v> *temp = hashmap[hashposition];
        if (!temp)
        {
            cout << "hashmap have no element";
            return;
        }

        Node<k, v> *prev = nullptr;
        while (temp)
        {
            if (temp->key == key)
            {
                if (!prev)
                {
                    hashmap[hashposition] = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }
                delete temp;
                totalElements--;
                cout << "Delete successfully \n";
                return;
            }

            prev = temp;
            temp = temp->next;
        }

        cout << " not found.\n";
    }
    void changevalue(k key, v value)
    {
        Node<k, v> *temp = nullptr;
        for (int i = 0; i < hashSize; i++)
        {
            temp = hashmap[i];
            while (temp)
            {
                if (isMatched(temp->key, key))
                {
                    temp->value = value;
                    return;
                }
                temp = temp->next;
            }
        }
    }
    Node<k, v> *searching(k key)
    {
        Node<k, v> *temp = nullptr;
        for (int i = 0; i < hashSize; i++)
        {
            temp = hashmap[i];
            while (temp)
            {
                if (isMatched(temp->key, key))
                {
                    return temp;
                }
                temp = temp->next;
            }
        }
        return NULL;
    }

    void clear()
    {
        if (!hashmap)
        {
            cout << "\nAlready empty hai ";
        }
        Node<k, v> *temp = nullptr, *deletenode = nullptr;
        for (int i = 0; i < hashSize; i++)
        {
            temp = hashmap[i];
            while (temp)
            {
                deletenode = temp;
                temp = temp->next;
                delete deletenode;
            }
            hashmap[i] = nullptr;
        }
        totalElements = 0;
        cout << "\nClear hash table successfully";
    }
    int total()
    {
        return totalElements;
    }
    void displayHash()
    {
        cout << "{";
        Node<k, v> *traverseEach = nullptr;
        for (int i = 0; i < hashSize; i++)
        {
            traverseEach = hashmap[i];
            if (traverseEach)
            {
                while (traverseEach)
                {
                    cout << endl
                         << "\n    {" << traverseEach->key << "," << traverseEach->value << "},";
                    traverseEach = traverseEach->next;
                }
            }
        }
        cout << "\n}";
    }
    void resizehash()
    {
        int newsize = hashSize;
        Node<k, v> **oldarray = hashmap;

        hashSize *= 2;
        hashmap = new Node<k, v> *[hashSize]();
        for (int i = 0; i < newsize; i++)
        {
            Node<k, v> *temp = oldarray[i];
            while (temp)
            {
                insertion(temp->key, temp->value);
                temp = temp->next;
            }
        }
    }
    bool checkisPresent(k key)
    {
        int hashposition = hashfunction(key);
        Node<k, v> *temp = hashmap[hashposition];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    int hash(int key)
    {
        return key % hashSize;
    }
    int hash(long key)
    {
        return key % hashSize;
    }
    int hash(float key)
    {
        return (int)key % hashSize;
    }
    int hash(string key)
    {
        int number = key.length();
        int count = 0;
        for (int i = 0; i < number; i++)
        {
            count += (key[i] - 'a');
        }
        return count % hashSize;
    }
    int hash(const char *key)
    {

        int count = 0;
        for (int i = 0; key[i] != '\0'; i++)
        {
            count += (int)key[i];
        }
        return count % hashSize;
    }
    bool isMatched(int stored, int key)
    {
        return stored == key;
    }
    bool isMatched(long stored, long key)
    {
        return stored == key;
    }
    bool isMatched(float stored, float key)
    {
        return stored == key;
    }
    bool isMatched(const char *stored, const char *key)
    {
        if (!stored || !key)
            return false;
        int i = 0;
        while (stored[i] != '\0' && key[i] != '\0')
        {
            if (stored[i] != key[i])
                return false;
            i++;
        }
        return stored[i] == '\0' && key[i] == '\0';
    }
    bool isMatched(string a, string b)
    {
        if (a.length() != b.length())
        {
            return false;
        }

        for (int i = 0; i < a.length(); i++)
        {
            if (a[i] != b[i])
            {
                return false;
            }
        }

        return true;
    }
};

#endif