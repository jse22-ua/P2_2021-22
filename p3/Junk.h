#ifndef _Junk_H
#define _Junk_H
#include <iostream>
#include "Util.h"

using namespace std;

class Junk{
    protected:
        JunkType type;
        int quantity;
        const int values[5]={0,500,100,50,20};//WASTELAND,GOLD,METAL,FOOD,STONE
        const char letters[5]={'W','G','M','F','S'};//WASTELAND,GOLD,METAL,FOOD,STONE
    public:
        Junk();
        Junk(JunkType type, int quantity);
        JunkType getType() const{return type;}
        int getQuantity() const {return quantity;}
        char getTypeChar() const{return letters[type];}
        int getValue() const{return quantity*values[type];}
        friend ostream& operator << (ostream &os,const Junk &junk);
};

#endif