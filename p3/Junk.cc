//Judit Serrano Espinosa 74379872B
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

char Junk::getTypeChar() const{
    char letter='0';
    switch (type){
        case WASTELAND:
            letter= 'W';
            break;
        case GOLD:
            letter='G';
            break;
        case METAL:
            letter='M';
            break;
        case FOOD:
            letter= 'F';
            break;
        case STONE:
            letter = 'S';
            break;
        default:
            break;
    }
    return letter;
}

int Junk::getValue() const{
    int value;

    switch (type){
        case WASTELAND:
            value=0;
            break;
        case GOLD:
            value=500;
            break;
        case METAL:
            value=100;
            break;
        case FOOD:
            value=50;
            break;
        case STONE:
            value=20;
            break;
        default:
            break;
    }
    return value*quantity;
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
        default:
            break;
    }

    os << "[" << name << ":" << junk.quantity <<"]";
    return os;

}

