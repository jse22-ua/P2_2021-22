#include <iostream>
#include "Junk.h"

using namespace std;

Junk::Junk(){
    type=WASTELAND;
    quantity=0;
}

Junk::Junk(JunkType type, int quantity){
    if(quantity<0){
        throw EXCEPTION_QUANTITY;
    }
    this->type=type;
    this->quantity=quantity;
}


ostream& operator<<(ostream &os,const Junk &junk){
    string name;

    switch (junk.type){
        case WASTELAND:
            name="WASTELAND";
            break;
        case GOLD:
            name="GOLD";
            break;
        case METAL:
            name="METAL";
            break;
        case FOOD:
            name="FOOD";
            break;
        case STONE:
            name="STONE";
            break;
    }

    os << "[" << name << ":" << junk.quantity <<"]";

}

