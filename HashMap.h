/* 
 * File:   HashMap.h
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 *
 * Created on June 12, 2015, 4:17 PM
 * 
 * Η κλάση υλοποιεί ένα πίνακα κατακερματισμού ανοικτής διεύθυνσης που υποστηρίζει 
 * αποθήκευσει int κλειδιών και int ή minheap τιμών στον πίνακα. Ο πίνακας σε
 * περίπτωση που έιναι γεμάτος θα διπλασιάσει το μέγεθος του.
 */

#ifndef HASHMAP_H
#define	HASHMAP_H

#include <utility>
#include <iostream>

#include "MinHeap.h"

using namespace std;

template <class T> class HashMap {
public:
    HashMap(int newSize);
    virtual ~HashMap();
    int hash(int key);
    T get(int key);
    void insert(int key,int y,int w);
    void insert(int key,T value);
    void removeFull(int key);
    void remove(int key,int y);
    void increaseSize();
    bool isFull();
    bool find(int key,int &hashCode);
    int getNumKeys();
    int getKey(int index);
    int getSize();
private:
    int numKeys; //πλήθος των κλειδιών που έχουν εισαχθεί
    pair<int,T> *table; //πίνακας που έχει το κλειδί και την τιμή που του αντιστοιχεί
    int size; //μέγεθος του πίνακα
};

#endif	/* HASHMAP_H */

