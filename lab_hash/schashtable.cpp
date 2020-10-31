/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
#include <iostream>
using namespace hashes;
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     */
    unsigned int theHash = hash(key, size);
    std::list<std::pair<K, V>>& theList = table[theHash];
    std::pair<K, V> to_push;
    to_push.first = key;
    to_push.second = value;
    theList.push_front(to_push);
    elems++;
    if (shouldResize()) {
        resizeTable();
    }
}


template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    //typename std::list<std::pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    unsigned int theHash = hash(key, size);
    for (typename std::list<std::pair<K,V> >::iterator it = table[theHash].begin(); it != table[theHash].end(); it++) {
        if ((*it).first == key) {
            table[theHash].erase(it);
            elems--;
            break;
        }
    }
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{

    /**
     * @todo: Implement this function.
     */
    unsigned int theHash = hash(key, size);
    for (typename std::list<std::pair<K,V> >::iterator it = table[theHash].begin(); it != table[theHash].end(); it++) {
        if ((*it).first == key) {
            return (*it).second;
        }
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    //size = 
    size_t new_size = findPrime(size * 2);
    std::list<std::pair<K, V>>* new_table = new std::list<std::pair<K, V>>[new_size];
    for (iterator it = begin(); it != end(); it++) {
        unsigned int theHash = hash((*it).first, new_size);
        std::list<std::pair<K, V>>& theList = new_table[theHash];
        std::pair<K, V> to_push;
        to_push.first = (*it).first;
        to_push.second = (*it).second;
        theList.push_front(to_push);
    }
    std::list<std::pair<K, V>>* tmp = table;
    table = new_table;
    size = new_size;
    delete[] tmp;
}
