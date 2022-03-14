// Programación 2 - Práctica 2
// DNI: 74379872B
// Nombre: Judit Serrano Espinosa
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>

using namespace std;

const int KMAXSTRING = 50;

enum Error {
  ERR_OPTION,
  ERR_BOOK_TITLE,
  ERR_BOOK_AUTHORS,
  ERR_BOOK_DATE,
  ERR_BOOK_PRICE,
  ERR_ID,
  ERR_FILE,
  ERR_ARGS
};

struct Book {
  unsigned int id;
  string title;
  string authors;
  int year;
  string slug;
  float price;
};

struct BinBook {
  unsigned int id;
  char title[KMAXSTRING];
  char authors[KMAXSTRING];
  int year;
  char slug[KMAXSTRING];
  float price;
};

struct BookStore {
  string name;
  vector<Book> books;
  unsigned int nextId;
};

struct BinBookStore {
  char name[KMAXSTRING];
  unsigned int nextId;
};

void error(Error e) {
  switch (e) {
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_BOOK_TITLE:
      cout << "ERROR: wrong book title" << endl;
      break;
    case ERR_BOOK_AUTHORS:
      cout << "ERROR: wrong author(s)" << endl;
      break;
    case ERR_BOOK_DATE:
      cout << "ERROR: wrong date" << endl;
      break;
    case ERR_BOOK_PRICE:
      cout << "ERROR: wrong price" << endl;
      break;
    case ERR_ID:
      cout << "ERROR: wrong book id" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_ARGS:
      cout << "ERROR: wrong arguments" << endl;
      break;
  }
}

void showMainMenu() {
  cout << "[Options]" << endl
       << "1- Show catalog" << endl
       << "2- Show extended catalog" << endl
       << "3- Add book" << endl
       << "4- Delete book" << endl
       << "5- Import/export" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showCatalog(const BookStore &bookStore) {//muestra los libros que hay dentro de la bookStore
  if(bookStore.books.size()!=0){
    for(int i=0;i<(int)bookStore.books.size();i++){
       cout << bookStore.books[i].id << ". ";
       cout << bookStore.books[i].title;
       cout << " (" << bookStore.books[i].year << "), ";
       cout << bookStore.books[i].price << endl;
    }
  }
}

void showExtendedCatalog(const BookStore &bookStore) {//hace lo mismo que showCatalog pero mas detalladamente
  if(bookStore.books.size()!=0){
    for(int i=0; i<(int)bookStore.books.size();i++){
      cout << "\"" << bookStore.books[i].title << "\",";
      cout << "\"" << bookStore.books[i].authors << "\",";
      cout << bookStore.books[i].year << ",";
      cout << "\"" << bookStore.books[i].slug << "\",";
      cout << bookStore.books[i].price << endl;

    }
  }
}

bool stringIsRight(string &name){//Comprueba si el nombre del autor o del titulo es correcto y devuelve true si lo  es
  bool right;
    right=true;
    getline(cin,name);

    if(name.length()==0){
      right=false;
    }
    else{
      for(int i=0;i<(int)name.length();i++){
        if(!isalnum(name[i])&&name[i]!=' '&&name[i]!=':'&&name[i]!=','&&name[i]!='-'){
          right=false;
        }
      }
    }
    return right;
}

void askName(string &name, const string &message, Error e){
    bool right;
  
  do{
    cout << message;//pide que introduzca el titulo o el autor dependiendo del mensaje pasado por parametro
    right=stringIsRight(name);//comprueba si es correcta

    if(!right){//si no lo es
      error(e);// lanza el error pedido por parametro
    }
  }while(!right);//y vuelve a pedirlo hasta que sea correcta
}

void askyearPublication(int &year){//pide año y comprobar si es correcto
  string stringyear;
  bool right;
  do{
    right=true;
    cout << "Enter publication year:";
    getline(cin,stringyear);

    if(stringyear.length()==0){//Comprueba que el usuario ha metido algo
      error(ERR_BOOK_DATE);
      right=false;
    }
    else{
      year=atoi(stringyear.c_str());
      if(year<1440 || year>2020){//comprueba si esta entre 1440 y 2022 
        error(ERR_BOOK_DATE);//si no es correcto el año lanza el error
        right=false;
      }
    }
  }while(!right);//y vuelve a pedirlo

}

void setprice(float &price){//pide el precio y comprueba si es correcto
  string stringprice;
  bool wrong;

  do{
    wrong=false;
    cout << "Enter price:";
    getline(cin,stringprice);

    if(stringprice.length()==0){//si el usuario no ha introducido nada
      error(ERR_BOOK_PRICE);//lanza un error
      wrong=true;
    }
    else{
      price=atof(stringprice.c_str());

      if(price<=0){//o si es menor o igual que 0
        wrong=true;
        error(ERR_BOOK_PRICE);//lanza un error
      }
    }
  }while(wrong);//vuelve a pedir el precio al usuario
}

string generateSlug(string title){
  string slug;
  bool guion;

  for(int i=0; i<(int)title.length();i++){
    if(isalnum(title[i])){
      guion=false;
      slug +=  tolower(title[i]);
    }
    else if(i==(int)title.length()-1){}
    else if(!guion){
      guion=true;
      slug += '-';
    }
  }
  return slug;
}

void addBook(BookStore &bookStore) {
  Book book;
  
  askName(book.title,"Enter book title:",ERR_BOOK_TITLE);//pide el titulo y comprueba si es correcto
  askName(book.authors,"Enter author(s):",ERR_BOOK_AUTHORS);//pide el autor y comprueba si es correcto
  askyearPublication(book.year);//pide el año de publicacion y comprueba si es correcto
  setprice(book.price);//pide el precio y si es menor o igual a 0 o cadena vacia lanza un error
  book.slug=generateSlug(book.title);

  book.id=bookStore.nextId;
  bookStore.nextId++;

  bookStore.books.push_back(book);
}

void deleteBook(BookStore &bookStore) {
}

void importExportMenu(BookStore &bookStore) {
}

void importFromCsv(BookStore &bookStore){
}

void exportToCsv(const BookStore &bookStore){
}

void loadData(BookStore &bookStore){
}

void saveData(const BookStore &bookStore){
}

int main(int argc, char *argv[]) {
  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;

  char option;
  do {
    showMainMenu();
    cin >> option;
    cin.get();

    switch (option) {
      case '1':
        showCatalog(bookStore);
        break;
      case '2':
        showExtendedCatalog(bookStore);
        break;
      case '3':
        addBook(bookStore);
        break;
      case '4':
        deleteBook(bookStore);
        break;
      case '5':
        importExportMenu(bookStore);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  } while (option != 'q');

  return 0;
}
