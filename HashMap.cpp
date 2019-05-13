/* 
 * File:   HashMap.cpp
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 * 
 * Created on June 12, 2015, 4:17 PM
 */

#include <math.h>

#include "HashMap.h"

/**
 * Specialization για int.
 * Κατασκευαστής της κλάσης που αρχικοποιεί έναν πίνακα μεγέθους newSize.
 * @param newSize το μέγεθος του πίνακα που θα χρησιμοποιηθεί.
 */
template <> HashMap<int>::HashMap(int newSize){
    table = new pair<int,int>[newSize];
    
    for (int i=0;i<newSize;i++){
        table[i].first=-1;
        table[i].second = -1;
    }
    
    this->size = newSize;
    numKeys = 0;
}

/**
 * Κατασκευαστής της κλάσης που αρχικοποιεί έναν πίνακα μεγέθους newSize.
 * @param newSize το μέγεθος του πίνακα που θα χρησιμοποιηθεί.
 */
template <class T> HashMap<T>::HashMap(int newSize) {
    table = new pair<int,T>[newSize];
    
    for (int i=0;i<newSize;i++){
        table[i].first=-1;
        table[i].second = T();
    }
    
    this->size = newSize;
    numKeys = 0;
}

/**
 * Destructor της κλάσης. Απελευθερώνει την μνήμη που έχει δεσμευθεί γι το table.
 */
template <class T> HashMap<T>::~HashMap() {
    delete[] table;
}

/**
 * Μέθοδος υπολογισμού του hashCode για το table
 * @param key Το κλειδί γι το οποίο θα υπολογιστεί το hashCode
 * @return Τον hashCode για το συγκεκριμένο key.
 */
template <class T> int HashMap<T>::hash(int key){
    int x = floor(4096 * (key*0.6180339887 - floor(key*0.6180339887)));  
    return x % size;
}

/**
 * Μέθοδος που δείχνει αν ο πίνακας είναι γεμάτος.
 * @return True αν είναι γεμάτος. False αν δεν είναι.
 */
template <class T> bool HashMap<T>::isFull(){
    for (int i=0;i<size;i++){
        if (table[i].first == -1){
            return false;
        }
    }
    return true;
}

/**
 * Μέθοδος για την αύξηση του μεγέθους του πίνακα.
 */
template <class T> void HashMap<T>::increaseSize(){
    pair<int,T> *tempTable = table;
    int tempN = size;
    size = 2*size;              //διπλασιασμός του μεγέθους
    table = new pair<int,T>[size];
    for (int i=0;i<size;i++){
        table[i].first=-1;
    }
    //εισαγωγή των τιμών που υπήρχαν ήδη στον πίνακα.
    for (int i=0;i<tempN;i++){
        if (tempTable[i].first != -1){
            insert(tempTable[i].first,tempTable[i].second);
        }
    }
    //διαγραφή του παλιού πίνακα
    delete[] tempTable;
}

/**
 * Μέθοδος για την εισαγωγή στοιχείου γι κάποιο συγκεκριμένο κλειδί.
 * @param key Το κλειδί όπου θα γίνει η εισαγωγή.
 * @param value Η τιμή που θα εισαχθεί.
 */
template <class T> void HashMap<T>::insert(int key, T value){
    if (isFull()){
        increaseSize();
    }
    int hashCode;
    find(key,hashCode);
    table[hashCode].first = key;
    table[hashCode].second = value;
}

/**
 * Μέθοδος για την εύρεση της θέσης κάποιου στοιχείου στον πίνακα.
 * Λειτουργεί σύμφωνα με το ότι ο πίνακας χρησιμοποιεί μέθοδο ανοικτής διεύθυνσης.
 * @param key Το κλειδί γι το οποίο ψάχνει.
 * @param hashCode Η θέση του στοιχείου στον πίνακα (επιστρέφεται με αναφορά).
 * @return True αν βρέθηκε. False αν δεν βρέθηκε.
 */
template <class T> bool HashMap<T>::find(int key,int &hashCode){
    hashCode = hash(key);
    int temp = hashCode;
    while(table[hashCode].first != -1 && table[hashCode].first != key){ 
        hashCode = (hashCode + 1) % size;
        if (hashCode == temp) break;
    }
    if (table[hashCode].first == -1){
        return false;
    }
    else{
        return true;
    }
}

/**
 * Specialization για int.
 * Μέθοδος για να πάρουμε το στοιχείο που βρίσκεται αντιστοιχεί στο key.
 * @param key Το κλειδί στο οποίο αντιστοιχεί το στοιχείο που ψάχνουμε.
 * @return Το στοιχείο.
 */
template <> int HashMap<int>::get(int key){
    int hashCode;
    if (find(key,hashCode)){
        return table[hashCode].second;
    }
    else{
        return -1; //an epistrepsw keno minheap shmainei dn bre8hke
    }
}

/**
 * Μέθοδος για να πάρουμε το στοιχείο που βρίσκεται αντιστοιχεί στο key.
 * @param key Το κλειδί στο οποίο αντιστοιχεί το στοιχείο που ψάχνουμε.
 * @return Το στοιχείο.
 */
template <class T> T HashMap<T>::get(int key){
    int hashCode;
    if (find(key,hashCode)){
        return table[hashCode].second;
    }
    else{
        return T(); //an epistrepsw keno minheap shmainei dn bre8hke
    }
}

//Αυτή η εισαγωγή δεν πρόκειται να χρησιμοποιηθέι για στοιχεία int.
template <> void HashMap<int>::insert(int key, int y, int w){
    //do nothing
}

/**
 * Εισαγωγή των y και w στο minHeap που αντιστοιχεί στο κλειδί key.
 * @param key Το κλειδί όπου θα γίνει η εισαγωγή.
 * @param y Ο κόμβος γείτονας του key.
 * @param w Το βάρος μεταξύ των y και key κόμβων. 
 */
template <class T> void HashMap<T>::insert(int key, int y,int w){ //xrhsimopoieitai mono apo minHeap
    if (isFull()){
        increaseSize();
    }
    int hashCode;
    find(key,hashCode);
    if (table[hashCode].first != key){
        numKeys++;
    }
    
    table[hashCode].first = key;
    table[hashCode].second.insert(y,w);
    
}

// Αυτή η διαγραφή δεν πρόκειται να χρησιμοποιηθέι για στοιχεία int.
template <> void HashMap<int>::remove(int key, int y){
    //do nothing
}

/**
 * Μέθοδος για την διαγραφή ενώς στοιχείου y από το minHeap που αντιστοιχεί στο 
 * key.
 * @param key Το κλειδί γι το minHeap στο οποίο θα διαγραφεί το στοιχείο y.
 * @param y Το στοιχείο προς διαγραφή.
 */
template <class T> void HashMap<T>::remove(int key, int y){
    int hashCode;
    if (find(key,hashCode)) {
        table[hashCode].second.del(y);
        if (table[hashCode].second.getSize() == 0){
            removeFull(key);
        }
    }
    else{
        cout<<"Entry not found to remove"<<endl;
    }
}

/**
 * Specialization για int.
 * Διαγραφή του στοιχείου που αντιστοιχεί στο key από τον πίνακα του hashmap. 
 * @param key Το κλειδί στο οποίο αντιστοιχεί το στοιχείο που θα διαγραφεί.
 */
template <> void HashMap<int>::removeFull(int key){
    int hashCode;
    if (find(key,hashCode)){
        table[hashCode].first = -1;
        table[hashCode].second = -1;
        
        
        //αλλάζει τις θέσεις τον στοιχείων με τα οποία είχε συμβέι collision.
        int previous = hashCode;
        hashCode = (hashCode + 1) % size;
        if (table[hashCode].first != -1){
            do{
                if (hash(table[hashCode].first) != hashCode){
                    table[previous].first = table[hashCode].first;
                    table[previous].second = table[hashCode].second;

                    table[hashCode].first = -1;
                    table[hashCode].second = -1;

                    previous = hashCode;
                }
                hashCode = (hashCode + 1) % size;
            }while(table[hashCode].first != -1);
        }
        numKeys--;
    }
    else{
        cout<<"Entry not found to remove"<<endl;
    }
}

/**
 * Διαγραφή του στοιχείου που αντιστοιχεί στο key από τον πίνακα του hashmap. 
 * @param key Το κλειδί στο οποίο αντιστοιχεί το στοιχείο που θα διαγραφεί.
 */
template <class T> void HashMap<T>::removeFull(int key){
    int hashCode;
    if (find(key,hashCode)){
        table[hashCode].first = -1;
        table[hashCode].second = MinHeap();

        //αλλάζει τις θέσεις τον στοιχείων με τα οποία είχε συμβέι collision.
        int previous = hashCode;
        hashCode = (hashCode + 1) % size;
        if (table[hashCode].first != -1){
            do{
                if (hash(table[hashCode].first) != hashCode){
                    table[previous].first = table[hashCode].first;
                    table[previous].second = table[hashCode].second;

                    table[hashCode].first = -1;
                    table[hashCode].second = MinHeap();

                    previous = hashCode;
                }
                hashCode = (hashCode + 1) % size;
            }while(table[hashCode].first != -1);
        }
        numKeys--;
    }
    else{
        cout<<"Entry not found to remove"<<endl;
    }
    
}

/**
 * Επιστρέφει το πλήθος των κλειδιών που έχουν εισαχθεί.
 * @return 
 */
template <class T> int HashMap<T>::getNumKeys(){
    return numKeys;
}

/**
 * Επιστρέφει το κλείδι στη θέση index του πίνακα.
 * (χρησιμοποιείται γι προσπέλαση όλων των στοιχείων του πίνακα.
 * @param index Θέση του πίνακα.
 * @return το κλειδί.
 */
template <class T> int HashMap<T>::getKey(int index){
    return table[index].first;
}

/**
 * Επιστρέφει το μέγεθος του πίνακα
 * @return 
 */
template <class T> int HashMap<T>::getSize(){
    return size;
}

//Για να λειτουργήσει ο compiler.
template class HashMap<MinHeap>;
template class HashMap<int>;