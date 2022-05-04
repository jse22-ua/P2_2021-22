//Judit Serrano Espinosa, 74379872B
#include <iostream>
#include "Jankali.h"
#include "Util.h"

using namespace std;

Jankali::Jankali(string name){
    if(name.length()==0){
        throw EXCEPTION_NAME;
    }
    this->name=name;
    power=300;
}

void Jankali::hunt(vector<Betonski *> betonskis){
    if(traps.size()!=0||betonskis.size()!=0){

        for(int i=0;i<(int)betonskis.size();i++){

            for(int j=0;j<(int)traps.size();j++){

                if(betonskis[i]->getPosition().compare(traps[j])){

                    if(!betonskis[i]->isCaptured()){
                        betonskis[i]->capture();
                        subdued.push_back(betonskis[i]);
                    }
                }
            }
        }
    }
}

bool Jankali::setTrap(const Coordinate &coord){
   int charge; // coste de la trampa
   bool positioned=false;
   bool setTrap=false;

   for(int i=0;i<(int)traps.size();i++){
       if(coord.compare(traps[i])){
           positioned=true;
           break;
       }
   } 
   if(!positioned){
        charge=(coord.getColumn()+2)*(coord.getRow() + 2);

        if(charge>=power){
            power-=charge;
            traps.push_back(coord);
            setTrap=true;
        }   
   }
   return setTrap;
}

void Jankali::spoil(){
    for(int i=0;i<(int)subdued.size();i++){
        try{
            power+=subdued[i]->spoliation();
        }catch(...){
            subdued.erase(subdued.begin()+i);
        }

    }
}

void Jankali::spoil(JunkType type){
        for(int i=0;i<(int)subdued.size();i++){
        try{
            power+=subdued[i]->spoliation(type);
        }catch(...){
            subdued.erase(subdued.begin()+i);
        }

    }
}

void Jankali::spoil(int pos){
    try{
        if(pos<(int)subdued.size()){
            power+=subdued[pos]->spoliation();
        }
    }catch(...){
        subdued.erase(subdued.begin()+pos);
    }
}

ostream& operator<<(ostream &os, const Jankali &jankali){
    os << "Jankali \"" << jankali.name << "\" " << jankali.power << endl;

    for(int i=0;i<(int)jankali.subdued.size();i++){
        os << jankali.subdued[i];
        //terminar
    }
    return os;
}