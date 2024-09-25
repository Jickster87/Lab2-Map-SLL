#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
    currentElem = map.headNode;
}


void MapIterator::first() {
    currentElem = map.headNode;
}


void MapIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentElem = currentElem->nextAddress;
}


TElem MapIterator::getCurrent(){
    if (!valid()) {
        throw exception();
    }
	return currentElem->dataPair;
}


bool MapIterator::valid() const {
	return currentElem != nullptr;
}



