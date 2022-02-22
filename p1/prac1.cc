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

void askFeatures(int &attack, int &defense){//pide el ataque y la defensa por porcentajes
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
    else{

    attack=(Attackporcien/100)*KPOINTS;
    defense=(Defenseporcien/100)*KPOINTS;
    }
  }while(!isRight);
}

void askName (char name[]){//pide el nombre del heroe y comprueba que sea correcto
  bool IsRight;

  do{
    IsRight =true;
    cout << "Enter hero name: ";
    cin.getline(name,KNAME-1);
    
    for(int i=0;IsRight&&i<(int)strlen(name);i++){
        if(!isalnum(name[i])&&name[i]!=' '){
            IsRight=false;
        }
    }

    if(!IsRight || strlen(name)==0||name[0]==' '||isdigit(name[0])){
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

Breed AssignBreed(int dice, string &name, Enemy &enemy){//Determina la raza según el valor del dado
  Breed breed;
  if(dice<=6){
    breed=AXOLOTL;
    name="Axolotl";
    enemy.features.attack=40;
    enemy.features.defense=40;
  }
  else if(6<dice&& dice<=11){
    breed=TROLL;
    name="Troll";
    enemy.features.attack=60;
    enemy.features.defense=80;
  }
  else if(11<dice&& dice<=15){
    breed=ORC;
    name="Orc";
    enemy.features.attack=80;
    enemy.features.defense=120;

  }
  else if(15<dice&& dice<=18){
    breed=HELLHOUND;
    name="Hellhound";
    enemy.features.attack=120;
    enemy.features.defense=100;
  }
  else{
    breed=DRAGON;
    name="Dragon";
    enemy.features.attack=160;
    enemy.features.defense=140;
  }
  return breed;
}

void printStatsEnemy(const Enemy &enemy, const string &breed){//Imprime las caracteristas del enemigo
  cout << "[Enemy]" << endl;
  cout << "Breed: " << breed << endl;
  cout << "Attack: " << enemy.features.attack << endl;
  cout << "Defense: " << enemy.features.defense << endl;
  cout << "Health points: " << enemy.features.hp << endl;
}

Enemy createEnemy(){
  int dice = rollDice();
  Enemy myenemy;
  string breed;

  myenemy.name=AssignBreed(dice, breed,myenemy);
  myenemy.features.hp=myenemy.features.defense*2;
  printStatsEnemy(myenemy,breed);
  
  return myenemy;
}

void calculateDamage(int attack, int defense, int &hp, string type){
  int dice, totalAttack, totalDefense, hitPoint;

  dice=rollDice();
  cout << "Attack: " << attack << " + " << dice*5 << endl;
  totalAttack=attack+dice*5;
  dice=rollDice();
  cout << "Defense: " << defense << " + " << dice*5 << endl;
  totalDefense=defense+dice*5;

  if(totalDefense>totalAttack){
    hitPoint=0;
  }
  else{
    hitPoint=totalAttack-totalDefense;
  }

  cout << "Hit points: " << hitPoint << endl;
  if(hp<0){
    hp=0;
  }
  cout << type  << " health points: " << hp << endl;
}

int AddExperience (Breed enemy){
  int experience=0;
  switch(enemy){
    case AXOLOTL: experience= 100;
                  break;
    case TROLL: experience= 150;
                break;
    case ORC: experience= 200;
              break;
    case HELLHOUND: experience= 300;
                    break;
    case DRAGON: experience= 400;
                 break;
    default: cout  << "Error to introduce parameter";
             break;
  }
  return experience;
}

void fight(Hero &hero,Enemy &enemy){

  cout << "[Hero -> Enemy]" << endl;
  calculateDamage(hero.features.attack,enemy.features.defense,enemy.features.hp,"Enemy");

  if(enemy.features.hp<=0){

    cout << "Enemy killed" << endl;
    hero.exp=hero.exp+AddExperience(enemy.name);
    hero.kills[enemy.name]++;
    enemy=createEnemy();

  }
  else{
    cout << "[Enemy -> Hero]" << endl;
    calculateDamage(enemy.features.attack,hero.features.defense,hero.features.hp,"Hero");
    if(hero.features.hp<=0){
      cout << "You are dead" << endl;
    }
  }

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

void ChooseOption(Hero &hero, Enemy &enemy){
  char option;

  do{
  showMenu();
  cin >> option;
  switch(option){
    case '1': fight(hero, enemy);
              break;
    case '2': cout << "Run away" << endl;
              break;
    case '3': cout << "Special Attack" << endl;
              break;
    case '4': report(hero);
              break;
    case 'q': break;
    default:  cout << "ERROR: wrong option";
              break;
  }
  }while(option!='q'&&hero.features.hp!=0);
}

int main(int argc,char *argv[]){
  if(argc!=2){ // Si los parámetros no son correctos, el programa termina inmediatamente
    cout << "Usage: " << argv[0] << " <seed>" << endl;
  }
  else{    
    srand(atoi(argv[1])); // Introducimos la semilla para generar números aleatorios
    Hero myhero;
    Enemy enemy;
    myhero=createHero();
    enemy=createEnemy();
    ChooseOption(myhero, enemy);


    // Aquí vendrá todo tu código del "main"...
  }
}
