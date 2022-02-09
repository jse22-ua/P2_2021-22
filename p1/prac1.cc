// Programación 2 - Práctica 1
// DNI: 74379872B
// Nombre: Judit Serrano Espinosa
#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()

using namespace std;

const int KNAME=32;
const int KENEMIES=5;
const int KPOINTS=200;
const int KDICE=20; // Número de caras del dado

struct Core{
  int attack;
  int defense;
  int hp;
};

enum Breed{
  AXOLOTL,
  TROLL,
  ORC,
  HELLHOUND,
  DRAGON
};

struct Enemy{
  Breed name;
  Core features;
};

struct Hero{
  char name[KNAME];
  Core features;
  bool special;
  int runaways;
  int exp;
  int kills[KENEMIES];
};

int rollDice(){
  return rand()%KDICE+1;
}

void askName (char name[]){//arreglar
  bool IsRight;

  do{
    IsRight =true ;
    cout << "Enter hero name: ";
    cin.getline(name,31);
    
    for(int i=0;!IsRight&&i<(int)strlen(name);i++){
        if(!isalnum(name[i])){
            IsRight=false;
        }
    }

    if(!IsRight || strlen(name)==0){
      cout << "ERROR: wrong name" << endl;
      IsRight=false;
    }

  }while(!IsRight);
}

Hero createHero(){
  Hero myhero;
  askName(myhero.name);
}

Enemy createEnemy(){
  int dice = rollDice();
}

void fight(Hero &hero,Enemy &enemy){
}

void report(const Hero &hero){
}

void showMenu(){
  cout << "[Options]" << endl
       << "1- Fight" << endl
       << "2- Run away" << endl
       << "3- Special" << endl 
       << "4- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

int main(int argc,char *argv[]){
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{    
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    
    // Aquí vendrá todo tu código del "main"...
  }
}
