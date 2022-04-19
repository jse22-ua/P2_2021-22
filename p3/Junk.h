#ifndef _Junk_H
#define _Junk_H
#include <iostream>
#include "Util.h"

using namespace std;

class Junk{
    protected:
        JunkType type;
        int quantity;
    public:
        Junk();
        Junk(JunkType type, int quantity);
        JunkType getType() const{return type;}
        int getQuantity() const {return quantity;}
        char getTypeChar() const;
        int getValue() const;
        friend ostream& operator << (ostream &os,const Junk &junk);
};

#endif