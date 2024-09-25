#include "Map.h"
#include "MapIterator.h"
#include <utility>
Map::Map() {
    headNode = nullptr;
    listSize = 0;
}

Map::~Map() {
    while (headNode != nullptr) {
        Node * temp = headNode;
        headNode = headNode->nextAddress;
        delete temp;
    }
}

TValue Map::add(TKey c, TValue v){
	//search for pair
    Node * nomadNode = headNode;
    while (nomadNode != nullptr) {
        //if found overwrite old value
        if (nomadNode->dataPair.first == c) {
            TValue oldValue = nomadNode->dataPair.second;
            nomadNode->dataPair.second = v;
            return oldValue;
        }
        nomadNode = nomadNode->nextAddress;
    }
    //else add new pair
    TElem newPair = std::make_pair(c, v);
    Node * newNode = new Node(newPair);
    newNode->nextAddress = headNode;
    headNode = newNode;
    
    listSize++;
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
    //if list empty - false
    if (headNode == nullptr) {
        return NULL_TVALUE;
    }
    //move to find
    Node * nomadNode = headNode;
    Node * prevNode = nullptr;
    
    while (nomadNode != nullptr && nomadNode->dataPair.first != c) {
        prevNode = nomadNode;
        nomadNode = nomadNode->nextAddress;
    }
    //not found - false
    if (nomadNode == nullptr) {
        return NULL_TVALUE;
    }
    
    // ELEM FOUND CASES
    TValue oldValue = nomadNode->dataPair.second;
    // 1. first in the list
    if (headNode != nullptr && prevNode == nullptr) {
        headNode = headNode->nextAddress;
    } else {
        // 2. last in the list // 3. in between
        prevNode->nextAddress = nomadNode->nextAddress;
    }
    delete nomadNode;
    listSize--;
    
    return oldValue;
}

TValue Map::search(TKey c) const{
    Node * nomadNode = headNode;
    while (nomadNode != nullptr) {
        if (nomadNode->dataPair.first == c) {
            return nomadNode->dataPair.second;
        }
        nomadNode = nomadNode->nextAddress;
    };
    return NULL_TVALUE;
}

int Map::size() const {
	return listSize;
}

bool Map::isEmpty() const{
	return listSize == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
