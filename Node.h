/* 
 * File:   node.h
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 *
 * Created on 4 Ιουνίου 2015, 7:05 μμ
 * 
 * Η κλάση υλοποιεί έναν κόμβο της σωρού ελαχίστων. Μπορεί να αποθηκεύει δύο ή 
 * τρία στοιχεία.
 */

#ifndef NODE_H
#define	NODE_H

typedef struct Node *nodeptr;

class Node {
public:
    void setnode(int id,int w);
    void setnode(int id,int secondID,int w);
    void setId(int id);
    void setSecondId(int secondId);
    void setWeight(int weight);
    int getId();
    int getSecondId();
    int getWeight();
    Node();
    Node(const Node& orig);
private:
    int id;
    int secondId; 
    int weight;
};

#endif	/* NODE_H */

