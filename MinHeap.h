/* 
 * File:   minHeap.h
 * Author: Nikos Panagopoulos(2393) & Nikos Bafatakis (2383)
 *
 * Created on 25 Μαΐου 2015, 6:41 μμ
 * 
 * Η κλάση υλοποιεί έναν σωρό ελαχίστων με την χρήση πίνακα που περιλαμβάνει
 * αντικείμενα τύπου Node για την αποθήκευση των δεδομένων. Ο σωρός λειτουργεί 
 * σύμφωνα με το στοιχείο id του κάθε Node.
 */

#ifndef MINHEAP_H
#define	MINHEAP_H

#include <climits>

#include "Node.h"

class MinHeap {
public:
    MinHeap();
    MinHeap(const MinHeap& orig);
    Node extractMin();
    void heapCtrl(int curr);
    void insert(int y, int w);
    void insert(int from,int to, int w);
    void del(int y);
    void delCtrl(int curr);
    bool isEmpty();
    bool contains(int x);
    void edit(int id,int secondId,int w);
    int getSize();
    nodeptr head;
private:
    int size; //Πλήθος στοιχείων που έχουν εισαχθέι.
    int curSize; //Το μέγεθος του πίνακα.
};

#endif	/* MINHEAP_H */

