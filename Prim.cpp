/* 
 * File:   Prim.cpp
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 * 
 * Created on June 18, 2015, 9:15 PM
 */

#include <climits>

#include "Prim.h"

/**
 * Εύρεση του minimum spanning tree.
 * @param map hashmap που περιέχει όλα τα στοιχεία που χρειάζονται για τον γράφο.
 * @return Το κόστος του MST.
 */
int Prim::findMST(HashMap<MinHeap> &map){
    /*
     * Hashmap που αντιστοιχεί κάθε κόμβο με το index του στους πίνακες parent,
     * vertices και d για να διευκολυνθεί η εύρεση της κάθε τιμής.
     */
    HashMap<int> indexMap = HashMap<int>(map.getNumKeys());
    
    int vertices[map.getNumKeys()]; //πίνακας που περιέχει τους κόμβους
    int d[map.getNumKeys()];    //πίνακας που περιέχει το κόστος γι να πας στον κόμβο
    int parent[map.getNumKeys()]; //πίνακας που περιέχει τον κόμβο απο τον οποίο ήρθαμε σε αυτόν
    
    int verticesCount = 0;
    for (int i=0;i<map.getSize();i++){  //αρχικοποίηση των πινάκων
        if (map.getKey(i)!=-1){
            indexMap.insert(map.getKey(i),verticesCount);
            vertices[verticesCount] = map.getKey(i);
            d[verticesCount]= INT_MAX; 
            parent[verticesCount]=INT_MIN;
            verticesCount++;
        }       
    }
    
    //minheap που περιλμβάνει τους κόμβους ταξινομημένους σύμφωνα με τον πίνακα d.
    MinHeap Q = MinHeap();
    /* η εισαγωγή γίνεται ανάποδα απ ότι στα υπόλοιπα minheap επειδή το minheap 
     * είναι φτιαγμένο για να ταξινομεί βάση το id. Γι να καταφέρουμε ταξινόμηση 
     * με το βάρος χωρίς να περιπλέξουμε τον κώδικα της κλάσης MinHeap εισάγουμε
     * στην θέση του id το βάρος,στη θέση του secondID το πρώτο id  και στη θέση
     * του βάρους το secondID. Αυτή η αλλαγή συμβαίνει μόνο στην συνάρτηση findMST
     * και λαμβάνεται υπόψιν στην συνέχεια για την εξαγωγή σωστών αποτελεσμάτων.
     */
    for (int i=0;i<map.getNumKeys();i++){
        Q.insert(d[i],vertices[i],parent[i]);
    }
   
    Node u;
    MinHeap neighbors;
    while(!Q.isEmpty()){
        u = Q.extractMin();
        neighbors = map.get(u.getSecondId()); 
        if (neighbors.getSize()==0){
            u = Q.extractMin();
        }
        
        for (int i=0;i<neighbors.getSize();i++){ //για κάθε γείτονα του u
            //αν το βάρος για να πάμε απο το u στον i γείτονα είναι μικρότερο από το βάρος που έχει ήδη και αν ο γείτονας δεν έχει προσπελαθει ακόμη
            if ((neighbors.head[i].getWeight()<d[indexMap.get(neighbors.head[i].getId())]) && (Q.contains(neighbors.head[i].getId()))){
                //τότε ενημέρωσε της τιμές των πινάκων για τον γείτονα και ισορρόπησε το minheap με τα νέα δεδομένα
                d[indexMap.get(neighbors.head[i].getId())] = neighbors.head[i].getWeight();
                parent[indexMap.get(neighbors.head[i].getId())] = u.getId();
                Q.edit(d[indexMap.get(neighbors.head[i].getId())],neighbors.head[i].getId(),parent[indexMap.get(neighbors.head[i].getId())]);
            }
        }
    }
    //Εύρεση του κόστους
    int cost = 0;
    //ξεκινάει από το 1 επειδεί πάντα ο πρώτος κόμβος είναι αυτός από όπου θα ξεκινήσει
    for (int i=1;i<map.getNumKeys();i++){
        cost+=d[i];
    }
    return cost;
    
}
