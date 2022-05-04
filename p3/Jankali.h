//Judit Serrano Espinosa 74379872B
#ifndef _Jankali_H
#define _Jankali_H
#include <iostream>
#include <vector>
#include "Coordinate.h"
#include "Betonski.h"
#include "Util.h"

class Jankali{
    protected:
        string name;
        int power;
        vector<Coordinate> traps;
        vector<Betonski*> subdued;
    public:
        Jankali(string name);
        string getName() const{ return name;}
        int getPower() const{ return power;}
        void hunt(vector<Betonski*> betonskis);
        bool setTrap(const Coordinate &coord);
        void spoil();
        void spoil(JunkType type);
        void spoil(int pos);
        friend ostream& operator<<(ostream &os, const Jankali &jankali);
};

#endif