/* 
 * File:   Prim.h
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 *
 * Created on June 18, 2015, 9:15 PM
 * 
 * Η κλάση υλοποιεί την λειτουργία του αλγορίθμου του Prim για την εύρεση 
 * minimum spanning tree.
 */

#ifndef PRIM_H
#define	PRIM_H

#include "HashMap.h"

class Prim {
public:
    static int findMST(HashMap<MinHeap> &map);
};

#endif	/* PRIM_H */

