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
  float Attackporcien,Defenseporcien;//Los porcentajes se guardarán estas variables
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

    attack=(Attackporcien/100)*KPOINTS;//una vez comprobado calcula el ataque
    defense=(Defenseporcien/100)*KPOINTS;//y la defensa
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

  askName(myhero.name);//llama a la funcion que pide el nombre
  askFeatures(myhero.features.attack, myhero.features.defense);//llama a la funcion que pide la defensa y el ataque
  myhero.features.hp=myhero.features.defense*2;//calcula los puntos de vida
  myhero.special=true;//inicializa el resto de elementos de el struct hero
  myhero.exp=0;
  myhero.runaways=3;

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

Enemy createEnemy(){//llama a los anteriores 
  int dice = rollDice();
  Enemy myenemy;
  string breed;

  myenemy.name=AssignBreed(dice, breed,myenemy);
  myenemy.features.hp=myenemy.features.defense*2;
  printStatsEnemy(myenemy,breed);
  
  return myenemy;
}

void calculateDamage(int attack, int defense, int &hp, string type,bool special){//calcula el daño hecho por cualquier cosa a cualquier cosa
  int dice, totalAttack, totalDefense, hitPoint;

  dice=rollDice();
  if(special){
    dice=dice*3;
  }
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
  hp=hp-hitPoint;
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

void fight(Hero &hero,Enemy &enemy, bool special){

  cout << "[Hero -> Enemy]" << endl;
  calculateDamage(hero.features.attack,enemy.features.defense,enemy.features.hp,"Enemy",special);

  if(enemy.features.hp<=0){

    cout << "Enemy killed" << endl;
    hero.exp=hero.exp+AddExperience(enemy.name);
    hero.kills[enemy.name]++;
    enemy=createEnemy();

  }
  else{
    cout << "[Enemy -> Hero]" << endl;
    calculateDamage(enemy.features.attack,hero.features.defense,hero.features.hp,"Hero",false);
    if(hero.features.hp<=0){
      cout << "You are dead" << endl;
    }
  }

}

void RunAway(int &numRunaway, bool &RanAway, Enemy &enemy){
  if(RanAway||numRunaway==0){
    cout << "ERROR: cannot run away";
  }
  else{
    cout << "You run away" << endl;
    RanAway=true;
    numRunaway--;
    enemy=createEnemy();

  }
}

void Special (Hero &hero, Enemy &enemy){
  if(!hero.special){
    cout << "ERROR: special not available" << endl;
  }
  else{
    fight(hero,enemy,true);
    hero.special=false;
  }
}

void PrintenemysDied(const int kills[]){
  int total=0;
  cout << "Enemies killed: " << endl;
  cout << "- Axolotl: " << kills[0] << endl;
  cout << "- Troll: " << kills[1] << endl;
  cout << "- Orc: " << kills[2] << endl;
  cout << "- Hellhound: " << kills[3] << endl;
  cout << "- Dragon: " << kills[4] << endl;

  for(int i=0;i<5;i++){
    total=total+kills[i];
  }
  cout << "Total: " << total << endl;
}

void report(const Hero &hero){
  cout << "[Report]" << endl;
  cout << "Name: " << hero.name << endl;
  cout << "Attack: " << hero.features.attack << endl;
  cout << "Defense: " << hero.features.defense << endl;
  cout << "Health points: " << hero.features.hp << endl;
  cout << "Special: ";
  if(hero.special){
    cout <<"yes" << endl;
  }
  else{
    cout << "no" << endl;
  }
  cout << "Runaways: " << hero.runaways << endl;
  cout << "Exp: " << hero.exp << endl;
  PrintenemysDied(hero.kills);

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
  bool ranAway=false;

  do{
    showMenu();
    cin >> option;
    switch(option){
      case '1': fight(hero, enemy,false);
               ranAway=false;
                break;
      case '2': RunAway(hero.runaways,ranAway,enemy);
                break;
      case '3': Special(hero,enemy);
                ranAway=false;
                break;
      case '4': report(hero);
                break;
      case 'q':break;
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
    if(myhero.features.hp==0){
      report(myhero);
    }


    // Aquí vendrá todo tu código del "main"...
  }
}
