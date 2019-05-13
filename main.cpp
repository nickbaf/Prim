/* 
 * File:   main.cpp
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 *
 * Created on April 27, 2015, 12:41 AM
 */


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>


#include "HashMap.h"
#include "NCN.h"
#include "Prim.h"
#include "Node.h"
using namespace std;

/*
 * Διάβαζει τις εντολές από το commands.txt και τις εκτελεί.
 * Σταματάει όταν τελειώσουν οι εντολές.  
 * Χρησιμοποιεί την βιβλιοθήκη chrono για να μετρήσει τον χρόνο εκτέλεσεις του Prim
 * ΠΡΟΣΟΧΗ: Η chrono απαιτεί την εντολή -std=c++11 στον compiler για να λειτουργήσει.
 */
int main() {
    HashMap<MinHeap> map = HashMap<MinHeap>(100000); //το hashmap που θα χρησιμοποιείται.
    ifstream comIn, input; //stream γι το commands.txt και input.txt
    ofstream output; //stream για το output.txt
    string command; //η εντολή που διαβάστηκε
    int x, y, w; //τα δεδομένα που διαβάστηκαν
    comIn.open("commands.txt", ios::in);
    if (!comIn) {
        cout << "Failed opening commands.txt" << endl;
        return -1; // το αρχείο commands.txt δεν μπόρεσε να ανοιχτεί
    } else {
        input.open("input.txt", ios::in);
        if (!input) {
            cout << "Failed opening input.txt" << endl;
            return -2; // το αρχείο input.txt δεν μπόρεσε να ανοιχτεί
        }
        output.open("output.txt", ios::out);
        if (!output) {
            cout << "Failed opening output.txt" << endl;
            return -3; // το αρχείο output.txt δεν μπόρεσε να ανοιχτεί
        }  
        cout << "Reading file Data" << endl;
        while (input >> x >> y >> w) { // ανάγνωση κόμβων από αρχείο
               map.insert(x,y,w);
               map.insert(y,x,w);
        }
        input.close();
        comIn >> command>>command; //προσπερνάει την γραμμή READ_DATA input.txt
        cout << "Executing Commands" << endl;
        while (!comIn.eof()) {      //μέχρι να φτάσουμε στο τέλος του αρχείου
            comIn>>command;
            if (!comIn) break;
            if (command == "INSERT_LINK") { // εισαγωγή κόμβου
                comIn >> x>>y>>w;
                map.insert(x,y,w);
                map.insert(y,x,w);
            } else if (command == "DELETE_LINK") { // διαγραφή κόμβου
                comIn >> x>>y;
                map.remove(x,y);
                map.remove(y,x);
            } else if (command == "NCN") { // εκτέλεση NCN
                comIn >> x>>y;
                output<<"Number of Common neighbors between "<<x<<" and "<<y<<" : "<<NCN::findCN(map.get(x),map.get(y))<<endl<<endl;
            } else if (command == "MST") { // εκτέλεση Prim
                auto start = chrono::steady_clock::now();
                output<<"Prim's algorithm cost : "<<Prim::findMST(map)<<endl;
                auto end = chrono::steady_clock::now();
                auto diff = end - start;
                output<<"Prim's algorithm duration in milliseconds : "<< chrono::duration <double, milli> (diff).count()<<endl<<endl;
            }
        }
    }
    output.close();
    comIn.close(); // κλείσιμο αρχείων.
    return 0;
}

