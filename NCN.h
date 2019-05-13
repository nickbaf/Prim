/* 
 * File:   NCN.h
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 *
 * Created on 5 Ιουνίου 2015, 9:33 μμ
 * 
 * Η κλάση υλοποιεί τον αλγόριθμο που απαιτείται για την εύρεση του πλήθους
 * των κοινών γειτόνων μεταξύ 2 κόμβων.
 * 
 */

#ifndef NCN_H
#define	NCN_H

#include "MinHeap.h"

class NCN {
public:
    static int findCN(MinHeap m1,MinHeap m2);
private:
    static nodeptr heapSort(MinHeap m);
    static void Heapify(int curr,nodeptr head, int size);
};

#endif	/* NCN_H */

