#ifndef _HASHED_ENTRY
#define _HASHED_ENTRY

#include "Entry.h"

using namespace std;

template<class KeyType, class ItemType>
class HashedEntry: public Entry<KeyType,ItemType>
{
private:
    HashedEntry<KeyType,ItemType>* nextPtr;

public:
    HashedEntry();
    HashedEntry(ItemType newEntry,KeyType searchkey);
    HashedEntry(ItemType nextEntry,KeyType searchkey,HashedEntry<KeyType,ItemType>* nextEntryPtr);
    void setNext(HashedEntry<KeyType,ItemType>* nextEntryPtr) ;
    // return the address
    HashedEntry<KeyType,ItemType>* getNext() const;
    
};
template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry():nextPtr(nullptr),Entry<KeyType, ItemType>()
{
}

template<class KeyType, class ItemType>
HashedEntry<KeyType,ItemType>::HashedEntry(ItemType newEntry,KeyType searchkey):nextPtr(nullptr), Entry<KeyType,ItemType> (searchkey,newEntry)
{    
}

template<class KeyType, class ItemType>
HashedEntry<KeyType,ItemType>::HashedEntry(ItemType nextEntry,KeyType searchkey,HashedEntry<KeyType,ItemType>* nextEntryPtr)
{
    this = Entry<KeyType,ItemType>::Entry(nextEntry,searchkey);
    this->nextPtr = nextEntryPtr;
}

template<class KeyType, class ItemType>
HashedEntry<KeyType,ItemType>* HashedEntry<KeyType,ItemType>::getNext() const
{
    return nextPtr;
}

template<class KeyType, class ItemType>
void HashedEntry<KeyType,ItemType>::setNext(HashedEntry<KeyType,ItemType>* nextEntryPtr)
{
    this->nextPtr = nextEntryPtr;
}
#endif