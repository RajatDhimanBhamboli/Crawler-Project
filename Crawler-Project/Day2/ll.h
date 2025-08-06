#include <iostream>
using namespace std;

template <typename valType>
class llNode
{
public:
    valType val;
    llNode<valType> *next;
    llNode(valType val);
};

template <typename valType>
class LL
{
private:
    int count = 0;
    llNode<valType> *head;
    llNode<valType> *getNode(valType val);

    // for matching various type of data structure for all operations
    bool isMatched(const string &val1, const string &val2);
    bool isMatched(const char *val1, const char *val2);
    bool isMatched(int val1, int val2);

public:
    LL();
    ~LL();
    // insertion
    void insertionAtBegin(valType val);
    void insertionAtMiddle(int index, valType val);
    void insertionAtEnd(valType val);
    llNode<valType> *gethead()
    {
        return head;
    }
    // deletion
    void deletionAtBegin();
    void deletionAtMiddle(valType val);
    void deletionAtEnd();

    // searching
    llNode<valType> *isPresent(int index);

    // display
    void display();

    // clear whole linked list
    void clear();

    // operator overloading for creating new obj
    LL<valType> operator=(LL<valType> *obj);
};

template <typename valType>
llNode<valType>::llNode(valType val)
{
    this->val = val;
    this->next = nullptr;
}

template <typename valType>
LL<valType>::LL()
{
    head = nullptr;
}

template <typename valType>
LL<valType>::~LL()
{
    clear();
}

template <typename valType>
void LL<valType>::clear()
{
    llNode<valType> *deleteNode = nullptr;
    while (head)
    {
        deleteNode = head;
        head = head->next;
        deleteNode->next = nullptr;
        delete deleteNode;
        deleteNode = nullptr;
    }
}

template <typename valType>
llNode<valType> *LL<valType>::getNode(valType val)
{
    llNode<valType> *current = head, *before = nullptr;
    while (current)
    {
        if (isMatched(val, current->val))
        {
            return before;
        }
        before = current;
        current = current->next;
    }
    return nullptr;
}

template <typename valType>
void LL<valType>::insertionAtBegin(valType val)
{
    cout << "\n";
    llNode<valType> *newNode = new llNode(val);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    count++;
}

template <typename valType>
void LL<valType>::insertionAtMiddle(int index, valType val)
{
    cout << "\n";
    if (count < index || index < 0 || !head)
    {
        cout << "Index is out of range";
        return;
    }
    llNode<valType> *traverse = head, *newNode = new llNode(val);
    while (traverse && index > 1)
    {
        index--;
        traverse = traverse->next;
    }
    newNode->next = traverse->next;
    traverse->next = newNode;
    count++;
}

template <typename valType>
void LL<valType>::insertionAtEnd(valType val)
{
    cout << "\n";
    llNode<valType> *newNode = new llNode(val);
    if (!head)
    {
        head = newNode;
    }
    else if (!head->next)
    {
        head->next = newNode;
    }
    else
    {
        llNode<valType> *traverse = head;
        while (traverse->next)
        {
            traverse = traverse->next;
        }
        traverse->next = newNode;
    }
    count++;
}

template <typename valType>
void LL<valType>::deletionAtBegin()
{
    cout << "\n";
    if (!head)
    {
        cout << "\nListNode is empty";
        return;
    }
    else if (!head->next)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        llNode<valType> *deleteNode = head;
        head = head->next;
        deleteNode->next = nullptr;
        delete deleteNode;
        deleteNode = nullptr;
    }
    cout << "Element deleted";
    count--;
}

template <typename valType>
void LL<valType>::deletionAtMiddle(valType val)
{
    cout << "\n";
    if (!head)
    {
        cout << "\nListNode is empty";
        return;
    }
    if (isMatched(val, head->val))
    {
        if (!head->next)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            llNode<valType> *deleteNode = head;
            head = head->next;
            deleteNode->next = nullptr;
            delete deleteNode;
        }
        count--;
        cout << "Element deleted";
        return;
    }
    llNode<valType> *nodeBeforeMatched = getNode(val);
    if (!nodeBeforeMatched)
    {
        cout << "Element not found";
    }
    else
    {
        llNode<valType> *temp = nodeBeforeMatched->next;
        nodeBeforeMatched->next = nodeBeforeMatched->next->next;
        temp->next = nullptr;
        delete temp;
        temp = nullptr;
        cout << "Element deleted";
        count--;
    }
}

template <typename valType>
void LL<valType>::deletionAtEnd()
{
    cout << "\n";
    if (!head)
    {
        cout << "\nListNode is empty";
        return;
    }
    else if (!head->next)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        llNode<valType> *traverse = head, *deleteNode = nullptr;
        while (traverse->next)
        {
            deleteNode = traverse;
            traverse = traverse->next;
        }
        deleteNode->next = nullptr;
        delete traverse;
        traverse = nullptr;
    }
    cout << "Element deleted";
    count--;
}

template <typename valType>
llNode<valType> *LL<valType>::isPresent(int index)
{
    if (count < index || index < 0 || !head)
    {
        cout << "Index is out of range";
        return nullptr;
    }
    llNode<valType> *traverse = head;
    while (traverse && index > 1)
    {
        index--;
        traverse = traverse->next;
    }
    return traverse;
}

template <typename valType>
void LL<valType>::display()
{
    llNode<valType> *traverse = head;
    cout << "\n";
    while (traverse)
    {
        cout << traverse->val << " -> ";
        traverse = traverse->next;
    }
    cout << "nullptr";
}

template <typename valType>
bool LL<valType>::isMatched(const string &val1, const string &val2)
{
    if (val1.size() != val2.size())
    {
        return false;
    }
    int i = 0;
    while (val1[i] != '\0' && val2[i] != '\0')
    {
        if (val1[i] != val2[i])
        {
            return false;
        }
        i++;
    }
    return val1[i] == '\0' && val2[i] == '\0';
}

template <typename valType>
bool LL<valType>::isMatched(const char *val1, const char *val2)
{
    int i = 0;
    while (val1[i] != '\0' && val2[i] != '\0')
    {
        if (val1[i] != val2[i])
        {
            return false;
        }
        i++;
    }
    return val1[i] == '\0' && val2[i] == '\0';
}

template <typename valType>
bool LL<valType>::isMatched(int val1, int val2)
{
    return val1 == val2;
}