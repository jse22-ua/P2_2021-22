// Programación 2 - Práctica 1
// DNI: 74379872B
// Nombre: Judit Serrano Espinosa
#include <iostream>
#include <cstdlib> // Para rand(), srand() y atoi()
#include <string.h> 

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

void askFeatures(int &attack, int &defense){
  bool isRight;
  float Attackporcien,Defenseporcien;
  char slash;
  do{
    isRight=true;
    cout << "Enter attack/defense: ";
    cin >> Attackporcien;
    slash=cin.get();
    cin >> Defenseporcien;

    if(Attackporcien==0||Defenseporcien==0 || Defenseporcien+Attackporcien!=100||slash!='/'){
      cout << "ERROR: wrong distribution" << endl;
      isRight=false;
    }
    attack=(Attackporcien/100)*KPOINTS;
    defense=(Defenseporcien/100)*KPOINTS;
  }while(!isRight);
}

void askName (char name[]){
  bool IsRight;

  do{
    IsRight =true ;
    cout << "Enter hero name: ";
    cin.getline(name,KNAME-1);
    
    for(int i=0;IsRight&&i<(int)strlen(name);i++){
        if(!isalnum(name[i])){
            IsRight=false;
        }
    }

    if(!IsRight || strlen(name)==0||name[0]==' '){
      cout << "ERROR: wrong name" << endl;
      IsRight=false;
    }

  }while(!IsRight);
}

Hero createHero(){
  Hero myhero;

  askName(myhero.name);
  askFeatures(myhero.features.attack, myhero.features.defense);
  myhero.features.hp=myhero.features.defense*2;
  myhero.special=true;
  myhero.exp=0;

  for(int i=0;i<KENEMIES;i++){

    myhero.kills[i]=0;
  }

  return myhero;
}

Breed AssignBreed(int dice){
  Breed breed;
  if(dice<=6){
    breed=AXOLOTL;
  }
  else if(6<dice<=11){
    breed=TROLL;
  }
  else if(11<dice<=15){
    breed=ORC;
  }
  else if(15<dice<=18){
    breed=HELLHOUND;
  }
  else{
    breed=DRAGON;
  }
  return breed;
}

void GiveStatsEnemy(Enemy &enemy){
  switch(enemy.name){
    case AXOLOTL: enemy.features.attack=40;
                  enemy.features.defense=40;
                  break;
    case TROLL: enemy.features.attack=60;
                enemy.features.defense=80;
                break;
    case ORC: enemy.features.attack=80;
              enemy.features.defense=120;
              break;
    case HELLHOUND: enemy.features.attack=120;
                    enemy.features.defense=100;
                    break;
    default: enemy.features.attack=160;
             enemy.features.defense=140;
             break;
  }
}

Enemy createEnemy(){
  int dice = rollDice();
  Enemy myenemy;

  myenemy.name=AssignBreed(dice);
  GiveStatsEnemy(myenemy);
  myenemy.features.hp=myenemy.features.defense*2;
  
  return myenemy;
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
