/* 
 * File:   minHeap.cpp
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 */




#include "MinHeap.h"
#include "stdio.h"
#include "Node.h"

/**
 * Constructor της κλάσης.
 */
MinHeap::MinHeap() {
    size = 0;
    curSize=3000; //3000 επειδή μόλις γίνει εισαγωγή θα δημιουργηθούν 3000 θέσεις
}

/**
 * Copy constructor της κλάσης.
 * @param orig Το αντικείμενο από το οποίο θα αντιγραφεί
 */
MinHeap::MinHeap(const MinHeap& orig) {
    size = orig.size;
    head = orig.head;
}

/**
 * Επιστρέφει πόσα στοιχεία περιέχει ο σωρός.
 * @return 
 */
int MinHeap::getSize(){
    return size;
}

/**
 * Συνάρτηση που εισάγει έναν κόμβο στον σωρό
 * @param y Τιμή id που θα έχει ο κόμβος.
 * @param w Τιμή weight που θα έχει ο κόμβος.
 */
void MinHeap::insert(int y, int w) {
    if (isEmpty()) head = new Node[3000];  //αν είναι η πρώτη εισαγωγή δεσμεύει μνήμη
    if(size==curSize){       //Αν γεμίσει ο πίνακας δεσμεύει παραπάνω μνήμη
        nodeptr temp= head;
        head = new Node[curSize+3000];
        for(int i=0;i<size;i++){
            head[i]=temp[i];
        }
        curSize+=3000;
        delete[] temp;
    }
    Node t;
    t.setnode(y, w);
    head[size] = t;
    heapCtrl(size); //Έλεγχος του σωρού.
    size++;
    return;

}

/**
 * Συνάρτηση που εισάγει μια ακμή στον σωρό
 * @param from Κόμβος 1
 * @param to Κόμβος 2
 * @param w Βάρος ακμής
 */
void MinHeap::insert(int from,int to, int w){
    if (isEmpty()) head = new Node[3000]; //αν είναι η πρώτη εισαγωγή δεσμεύει μνήμη
    if(size==curSize){          //Αν γεμίσει ο πίνακας δεσμεύει παραπάνω μνήμη
        nodeptr temp= head;
        head = new Node[curSize+3000];
        for(int i=0;i<size;i++){
            head[i]=temp[i];
        }
        curSize+=3000;
        delete[] temp;
    }
    Node t;
    t.setnode(from,to, w);
    head[size] = t;
    heapCtrl(size); //Έλεγχος του σωρού.
    size++;
    return;
}

/**
 * Ελέγχει αν ο πίνακας είναι άδειος.
 * @return True αν είναι άδειος. False αν όχι.
 */
bool MinHeap::isEmpty(){
    if (size==0){
        return true;
    }
    return false;
}

/**
 * Εξάγει το πρώτο στοιχείο από τον σωρό και βάζει στην θέση του το τελευταίο.
 * Έπειτα κάνει τις απαραίτητες μεταθέσεις.
 * @return Το πρώτο στοιχείο του σωρού.
 */
Node MinHeap::extractMin(){
    Node tempNode = head[0];
    if (!(head[size - 1].getSecondId() == head[0].getSecondId())) {
        int i = 0;
        for (i = 0; i < size; i++) {
            if (head[i].getSecondId() == head[0].getSecondId()) break;
        }
        head[i] = head[size -1];
        delCtrl(i);
    }
    size--;
    return tempNode;
}

/**
 * Συνάρτηση για την εύρεση ενος στοιχείου στον σωρο. Χρησιμοποιείται μόνο από το
 * Prim γι αυτό ελέγχει το secondID (βλ σχόλια για Prim).
 * @param x Η τιμή που θα ελέγξουμε αν υπάρχει.
 * @return True αν υπάρχει. False αν όχι.
 */
bool MinHeap::contains(int x){
    for (int i=0;i<size;i++){
        if (head[i].getSecondId() == x){
            return true;
        }
    }
    return false;
}

/**
 * Συνάρτηση για τον έλεχγο του σωρού κατα την εισαγωγή στοιχείου.
 * @param curr θέση στον πίνακα
 */
void MinHeap::heapCtrl(int curr) {
    if (curr != 0) {
        int par = (curr - 1) / 2;
        if (head[curr].getId() < head[par].getId()) { //Εάν το στοιχείο είναι μικρότερο απο τον πρόγονό του.
            //Αντάλαξε τα στοιχεία τους
            Node tempNode;
            tempNode = head[par];
            head[par] = head[curr];
            head[curr] = tempNode;
            heapCtrl(par); //εκτέλεσε αναδρομικά την συνάρτηση.
        }
    }
}

/**
 * Αλλάζει τις τιμές ενώς κόμβου στο σωρό. Χρησιμοποιείται μόνο από το Prim.
 * @param id H νέα τιμή.
 * @param secondId H νέα τιμή.
 * @param w H νέα τιμή.
 */
void MinHeap::edit(int id,int secondId,int w){
    int j = -1;
    for (int i=0;i<size;i++){
        if (head[i].getSecondId() == secondId){
            j = i;
            break;
        }
    }
    head[j].setId(id);
    head[j].setSecondId(secondId);
    head[j].setWeight(w);
    delCtrl(j);
    heapCtrl(j);
}


/**
 * Συνάρτηση για τον επαναφορά της λειτουργίας του σωρού ελαχίστων.
 * @param curr curr θέση του κόμβου που θέλουμε να ελεγχθεί
 */
void MinHeap::delCtrl(int curr) {
    if (curr != size - 1) {
        int chld1 = 2 * curr + 1; //ευρεση του δεξιου παιδιου
        int chld2 = 2 * curr + 2; //ευρεση του αριστερου παιδιου
        if (chld1 <= size - 1) {// εαν το αριστερο παιδι δεν ξεπερνάει το μεγεθος του σορου
            if (chld2 <= size - 1) {// εαν το δεξί παιδι δεν ξεπερνάει το μεγεθος του σορου
                if (head[chld1].getId() < head[chld2].getId()) {// εάν το αριστερό παιδί είναι μικρότερο το δεξί
                    if (head[curr].getId() > head[chld1].getId()) {// εάν ο τρέχον κόμβος είναι μεγαλύτερος από το παιδί
                         // αντάλλαξε το κόμβο
                        Node tempNode;
                        tempNode = head[chld1];
                        head[chld1] = head[curr];
                        head[curr] = tempNode;
                        delCtrl(chld1);//τρεξε αναδρομικα την συνάρτηση
                    }
                } else { // εάν το δεξί παιδί είναι μικρότερο το αριστερό
                    if (head[curr].getId() > head[chld2].getId()) { // εάν Ο τρέχον κόμβος είναι μεγαλύτερος από το παιδί
                         // αντάλλαξε το κόμβο
                        Node tempNode;
                        tempNode = head[chld2];
                        head[chld2] = head[curr];
                        head[curr] = tempNode;
                        delCtrl(chld2);//τρεξε αναδρομικα την συνάρτηση
                    }
                }
            } else {
                if (head[curr].getId() > head[chld1].getId()) { // εάν Ο τρέχον κόμβος είναι μεγαλύτερος από το αριστερο παιδί
                     // αντάλλαξε το κόμβο
                    Node tempNode;
                    tempNode = head[chld1];
                    head[chld1] = head[curr];
                    head[curr] = tempNode;
                    delCtrl(chld1);//τρεξε αναδρομικα την συνάρτηση
                }
            }
        }
    }

}

/**
 * Διαγραφή ενός κόμβου από τον σωρό.
 * @param y Η τιμή που έχει ο κόμβος που θέλουμε να διαγραφεί.
 */
void MinHeap::del(int y) {
    if (head[size - 1].getId() == y) {
        size--;
        return;
    }
    int i = 0;
    for (i = 0; i < size; i++) {
        if (head[i].getId() == y) break;
    }
    /*
     * Διαφράφετε ο κόμβος και τοποθετείτε ο τελευταίος απο τον σωρό
     */
    Node tempNode;
    head[i] = head[size -1];
    delCtrl(i); //Έλεγχός του σωρού.
    size--;
}