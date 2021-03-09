#ifndef _ENTRY
#define _ENTRY


template<class KeyType, class ItemType>
class Entry
{
    friend bool operator== (const Entry<KeyType,ItemType>& leftHandItem,const Entry<KeyType,ItemType>& rightHandItem) ;
    friend bool operator> (const Entry<KeyType,ItemType>& leftHandItem,const Entry<KeyType,ItemType>& rightHandItem) ;
private:
    ItemType item;
    KeyType searchkey;
protected:
    void setKey(const KeyType& searchkey);
public:
    Entry();
    Entry(const KeyType& searchKey,const ItemType& newEntry);
    // when get can change the real Item
    ItemType& getItem() ;
    KeyType getKey() const;
    void setItem(const ItemType& newEntry);
    
};
// protected
template<class KeyType, class ItemType>
void Entry<KeyType,ItemType>::setKey(const KeyType &searchkey)
{
    this->searchkey = searchkey;
}

// public
template<class KeyType, class ItemType>
Entry<KeyType, ItemType>::Entry()
{
}

template<class KeyType, class ItemType>
Entry<KeyType,ItemType>::Entry(const KeyType& searchKey,const ItemType& newEntry):item(newEntry),searchkey(searchKey)
{
}

template<class KeyType, class ItemType>
ItemType& Entry<KeyType,ItemType>::getItem()
{
    return item;
}

template<class KeyType, class ItemType>
KeyType Entry<KeyType,ItemType>::getKey() const
{
    return searchkey;
}
template<class KeyType, class ItemType>
void Entry<KeyType,ItemType>::setItem(const ItemType &newEntry)
{
    this->item = newEntry;
}


#endif
