/* 
 * File:   NCN.cpp
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 * 
 * 
 */

#include "NCN.h"

/**
 * Αλγόριθμος για την εύρεση των κοινών γειτόνων με την μέθοδο των κινούμενων δεικτών.
 * @param m1 σωρός ελαχίστων με τους γείτονες του πρώτου κόμβου.
 * @param m2 σωρός ελαχίστων με τους γείτονες του δεύτερου κόμβου.
 */
int NCN::findCN(MinHeap m1, MinHeap m2) {
    int p1 = 0, p2 = 0, same = 0;
    nodeptr node1 = heapSort(m1);
    nodeptr node2 = heapSort(m2);
    /*
     * Ένας δείκτης προχωράει οταν είναι μεγαλύτερος του άλλου ή οταν είναι ίσος με τον άλλο.
     */
    while (p1 < m1.getSize() && p2 < m2.getSize()) {
        if (node1[p1].getId() < node2[p2].getId()) {
            p2++;
        } else if (node1[p1].getId() > node2[p2].getId()) {
            p1++;
        } else if (node1[p1].getId() == node2[p2].getId()) {//κοινό στοιχείο, μετακίνησε και τους 2 δείκτες
            same++;
            p1++;
            p2++;
        }
    }
    return same;
}

/**
 * Συνάρτηση που υλοποιεί την HeapSort φθίνουσα ταξινόμησημη με πολυπλοκότητα O(nlogn)
 * @param m Ο σωρός ελαχίστων που θα ταξινομηθεί
 * @return pointer στον πίνακα της ταξινομημένης σωρού ελαχίστων
 */
nodeptr NCN::heapSort(MinHeap m) {
    nodeptr head = m.head;
    int i = m.getSize();
    while (i > 1) {
        //Αντάλαξε το πρώτο στοιχείο με το τελευταίο
        Node tempNode;
        tempNode = head[0];
        head[0] = head[i-1];
        head[i-1] = tempNode;
        i--;
        /* Με την συνάρτηση Heapify θα επαναφερθεί ο σωρός στην αρχική του
         * λειτουργία. Έτσι με αυτό τον τρόπο στην πρώτη θέση του πίνακα θα έχουμε το ελάχιστο του σωρού.
         */
        Heapify(0, head, i);
    }
    return head;
}

/**
 * Sυνάρτηση για τον επαναφορά της λειτουργίας του σωρού ελαχίστων.
 * @param curr θέση του κόμβου που θέλουμε να ελεγχθεί(στην περίπτωση της ταξινόμησης ο κομβος 0)
 * @param head ο πίνακας του σωρού ελαχίστων
 * @param size το μεγεθος του υποσυνόλου του σορού.
 */
void NCN::Heapify(int curr, nodeptr head, int size) {
    if (curr != size - 1) {
        int chld1 = 2 * curr + 1; //ευρεση του δεξιου παιδιου
        int chld2 = 2 * curr + 2; //ευρεση του αριστερου παιδιου
        if (chld1 <= size - 1) {// εαν το αριστερο παιδι δεν ξεπερνάει το μεγεθος του σορου
            if (chld2 <= size - 1) { // εαν το δεξι παιδι δεν ξεπερνάει το μεγεθος του σορου
                if (head[chld1].getId() < head[chld2].getId()) {// εάν το αριστερό παιδί είναι μικρότερο το δεξί
                    if (head[curr].getId() > head[chld1].getId()) { // εάν ο τρέχον κόμβος είναι μεγαλύτερος από το παιδί
                        // αντάλλαξε τον κόμβο
                        Node tempNode;
                        tempNode = head[chld1];
                        head[chld1] = head[curr];
                        head[curr] = tempNode;
                        Heapify(chld1, head, size); //τρεξε αναδρομικα την συνάρτηση
                    }
                } else { // εάν το δεξί παιδί είναι μικρότερο το αριστερό
                    if (head[curr].getId() > head[chld2].getId()) { // εάν Ο τρέχον κόμβος είναι μεγαλύτερος από το παιδί
                        // αντάλλαξε το κόμβο
                        Node tempNode;
                        tempNode = head[chld2];
                        head[chld2] = head[curr];
                        head[curr] = tempNode;
                        Heapify(chld2, head, size); //τρεξε αναδρομικα την συνάρτηση
                    }
                }
            } else {
                if (head[curr].getId() > head[chld1].getId()) { // εάν Ο τρέχον κόμβος είναι μεγαλύτερος από το αριστερο παιδί
                    // αντάλλαξε το κόμβο
                    Node tempNode;
                    tempNode = head[chld1];
                    head[chld1] = head[curr];
                    head[curr] = tempNode;
                    Heapify(chld1, head, size); //τρεξε αναδρομικα την συνάρτηση
                }
            }
        }
    }
}

