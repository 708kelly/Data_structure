#ifndef _HASHED_Dictionary
#define _HASHED_Dictionary

#include <iostream>
#include <string>
#include <stdexcept>
#include "HashedEntry.h"


using namespace std;

template<class KeyType, class ItemType>
class HashedDictionary
{
private:
    HashedEntry<KeyType,ItemType>** hashTable;
    int itemCount;
    int hashTableSize;
    static const int DEFAULT_SIZE = 101;

public:
    HashedDictionary();
    ~HashedDictionary();
    bool add(const KeyType& searchKey,const ItemType& newItem);
    bool remove(const KeyType& searchKey);
    bool isEmpty() const;
    int getNumberOfItems() const;
    void clear() ;
    ItemType& getItem(const KeyType& searchKey ) const;
    // 可以直接得到裡面的東西，並修改裡面的東西
    bool constains(const KeyType& searchKey) const;
    void traverse(void visit(ItemType&)) const;
    int getHashIndex(string id) const;
    int getHashIndex(int id) const;
};
int convertToASCII(string letter)
{
    int total = 0;
    for(int i = 0;i< letter.size();i++)
    {
        char x = letter.at(i);
        //cout << int(x) << endl;
        total += int(x);
    }
    return total;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(string id) const
{
    
    return (convertToASCII(id) % hashTableSize);
}
template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>:: getHashIndex(int id) const
{
    return (id % hashTableSize);
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary():itemCount(0),hashTableSize(DEFAULT_SIZE),hashTable(0)
{
    hashTable = new HashedEntry<KeyType, ItemType>*[hashTableSize];
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>:: ~HashedDictionary()
{
    clear();
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
    for(int i = 0;i < hashTableSize;i++)
    {
        while(hashTable[i] != nullptr)
        {
            remove(hashTable[i]->getKey());
        }
    }
    
}

template <class KeyType, class ItemType>
ItemType& HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const
{
    
    int num = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType>* traverseNode = hashTable[num];
    while(traverseNode != nullptr)
    {
        if (traverseNode->getKey() == searchKey)
        {
            return traverseNode->getItem();
        }
        traverseNode = traverseNode->getNext();
    }
    
    throw logic_error("not exist");
    
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
    // Create entry to add to dictionary
    HashedEntry<KeyType, ItemType>* entryToAddPtr = new HashedEntry<KeyType, ItemType>(newItem, searchKey);
    
    // Compute the hashed index into the array
    int itemHashIndex = getHashIndex(searchKey);
    
    // Add the entry to the chain at itemHashIndex
    if (hashTable[itemHashIndex] == nullptr)
    {
        hashTable[itemHashIndex] = entryToAddPtr;
    }
    else
    {
        entryToAddPtr->setNext(hashTable[itemHashIndex]);
        hashTable[itemHashIndex] = entryToAddPtr;
    } // end if
    
    return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
    bool itemFound = false;
    
    // Compute the hashed index into the array
    int itemHashIndex = getHashIndex(searchKey);
    if (hashTable[itemHashIndex] != nullptr)
    {
        // Special case - first node has target
        if (searchKey == hashTable[itemHashIndex]->getKey())
        {
            HashedEntry<KeyType, ItemType>* entryToRemovePtr =
            hashTable[itemHashIndex];
            hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
            delete entryToRemovePtr;
            entryToRemovePtr = nullptr; // For safety
            itemFound = true;
        }
        else // Search the rest of the chain
        {
            HashedEntry<KeyType, ItemType>* prevPtr = hashTable[itemHashIndex];
            HashedEntry<KeyType, ItemType>* curPtr = prevPtr->getNext();
            while ((curPtr != nullptr) && !itemFound )
            {
                // Found item in chain so remove that node
                if (searchKey == curPtr->getKey())
                {
                    prevPtr->setNext(curPtr->getNext());
                    delete curPtr;
                    curPtr = nullptr; // For safety
                    itemFound = true;
                }
                else // Look at next entry in chain
                {
                    prevPtr = curPtr;
                    curPtr = curPtr->getNext();
                } // end if
            } // end while
        } // end if
    } // end if
    
    return itemFound;
} // end remove
template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const
{
    return (itemCount == 0);
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const
{
    return itemCount;
}
#endif
