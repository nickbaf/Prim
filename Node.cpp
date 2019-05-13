/* 
 * File:   node.cpp
 * Author: Nikos Bafatakis(2383) & Nikos Panagopoulos(2393)
 * 
 * Η Κλάση αυτή υλοποιεί ενα κόβμο
 */

#include "Node.h"

/**
 *Constructor της κλάσης.
 */
Node::Node(){
    id=-1;
    weight=0; 
    secondId = -1;
}

/**
 * Copy constructor της κλάσης.
 * @param orig Το αντικείμενο από το οποίο θα αντιγραφεί
 */
Node::Node(const Node& orig){
    id = orig.id;
    weight = orig.weight;
    secondId = orig.secondId;
}

/**
 * Η συνάρτηση αυτή πέρνει τιμές και θέτει τις παραμέτρους του κόβμου.
 * @param id
 * @param w
 */
void Node::setnode(int id,int w) {
    this->id=id;
    weight=w;
}

/**
 * Η συνάρτηση αυτή πέρνει τιμές και θέτει τις παραμέτρους του κόβμου.
 * @param id
 * @param secondID
 * @param w
 */
void Node::setnode(int id,int secondID,int w){
    this->id = id;
    this->secondId = secondID;
    weight = w;
}


int Node::getId(){
    return id;
}

int Node::getSecondId(){
    return secondId;
}

int Node::getWeight(){
    return weight;
}

void Node::setId(int id){
    this->id = id;
}

void Node::setSecondId(int secondId){
    this->secondId = secondId;
}

void Node::setWeight(int weight){
    this->weight = weight;
}
