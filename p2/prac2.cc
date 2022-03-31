// Programación 2 - Práctica 2
// DNI: 74379872B
// Nombre: Judit Serrano Espinosa
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <string.h>

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
    getline(cin,name);
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
    cout << "Enter publication year: ";
    getline(cin,stringyear);

    if(stringyear.length()==0){//Comprueba que el usuario ha metido algo
      error(ERR_BOOK_DATE);
      right=false;
    }
    else{
      year=atoi(stringyear.c_str());
      if(year<1440 || year>2022){//comprueba si esta entre 1440 y 2022 
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
    cout << "Enter price: ";
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

string generateSlug(string title){//crea el slug a partir del title
  string slug;
  bool guion;//comprueba si se ha puesto guion en la posicion anterior

  for(int i=0; i<(int)title.length();i++){
    if(isalnum(title[i])){//si es un numero o una letra
      guion=false;
      slug +=  tolower(title[i]);//lo añade a slug en minuscula
    }
    else if(i==(int)title.length()-1){
      /*si la ultima posicion tiene algo que no sea
      *un numero o una letra no añade nada
      */
    }
    else if(!guion){//si no la posicion anterior no tiene guion pone un guion
      guion=true;
      slug += '-';
    }
  }
  return slug;
}

void addBook(BookStore &bookStore) {
  Book book;
  
  askName(book.title,"Enter book title: ",ERR_BOOK_TITLE);//pide el titulo y comprueba si es correcto
  askName(book.authors,"Enter author(s): ",ERR_BOOK_AUTHORS);//pide el autor y comprueba si es correcto
  askyearPublication(book.year);//pide el año de publicacion y comprueba si es correcto
  setprice(book.price);//pide el precio y si es menor o igual a 0 o cadena vacia lanza un error
  book.slug=generateSlug(book.title);

  book.id=bookStore.nextId;
  bookStore.nextId++;

  bookStore.books.push_back(book);
}

void deleteBook(BookStore &bookStore) {
  string stringid;
  int id = 0;
  bool found = false;

  cout << "Enter book id: ";
  getline(cin,stringid);

  if(bookStore.books.size() == 0 || stringid.length() == 0){//comprueba si el vector esta vacio o si no ha introducido nada el usuario
    error(ERR_ID);//lanza error
  }
  else{ 
    id=atoi(stringid.c_str());
    if(id < 0){//comprueba si id > el id del ultimo libro almacenado
    error(ERR_ID);//lanza error
    }
    else{
      for(int i = 0; i < (int)bookStore.books.size()&&!found; i++){
        if(id == (int)bookStore.books[i].id){
          bookStore.books.erase(bookStore.books.begin()+i);
          found = true;
        }
      }
      if(!found){
        error(ERR_ID);
      }
    }
  }
}

void showMenuExportImport(){
  cout << "[Import/export options]" << endl;
  cout << "1- Import from CSV" << endl;
  cout << "2- Export to CSV" << endl;
  cout << "3- Load data" << endl;
  cout << "4- Save data" << endl;
  cout << "b- Back to main menu" << endl;
  cout << "Option: ";
}

bool checkbook(Book book){ //encarga de gestionar todos los errores del libro 
  bool right=true;//devuelve true si todo está correcto

  if(!stringIsRight(book.title)){
    right=false;
    error(ERR_BOOK_TITLE);
  }
  if(!stringIsRight(book.authors)){
    right=false;
    error(ERR_BOOK_AUTHORS);
  }
  if(book.year<1440||book.year>2022){
    right=false;
    error(ERR_BOOK_DATE);
  }
  if(book.price<=0){
    right=false;
    error(ERR_BOOK_PRICE);
  }

  return right;
}

void addbookofFile(string &bookdetails,BookStore &bookstore){//se encarga de separar el string en las partes del libro
  Book book;
  string year,price;
  stringstream ss(bookdetails);

  ss.get();
  getline(ss,book.title,'\"');
  ss.get();//lee la coma seguida del titulo
  ss.get();//lee la comilla al principio del autor
  getline(ss,book.authors,'\"');

  ss.get();//lee la coma delante del año
  getline(ss,year,',');
  if(year.length()!=0){
    book.year=atoi(year.c_str());//convierte el año a int
  }
  else{
    book.year=-1;
  }

  getline(ss,book.slug,',');
  book.slug=book.slug.substr(1,book.slug.length()-2);//quita las comillas

  getline(ss,price);
  if(price.length()!=0){
    book.price=atof(price.c_str());//convierte el precio a float
  }
  else{
    book.price=-2;
  }

  if(checkbook(book)){//añade al vector de libros si los componentes son correctos
    book.id=bookstore.nextId;
    bookstore.nextId++;
    bookstore.books.push_back(book);
  }
}

void readTextfile(BookStore &bookStore, char name[],bool &open){//lee un fichero de texto y añade los libros leidos si son correctos
  ifstream fileRead;
  string bookdetails;
  fileRead.open(name);

  if(fileRead.is_open()){
    while(getline(fileRead,bookdetails)){//lee linea a linea cada libro
      addbookofFile(bookdetails,bookStore);//añade el libros si estan bien
    }
    fileRead.close();
  }
  else{
    error(ERR_FILE);//si no se abre el fichero lanza un error
    open=false;

  }
}

void importFromCsv(BookStore &bookStore){
  char namefile[KMAXSTRING];
  bool open=true;
 

  cout << "Enter filename: ";
  cin.getline(namefile,KMAXSTRING-1);

  readTextfile(bookStore,namefile,open);

  
}

void exportToCsv(const BookStore &bookStore){//se encaga de guardar los datos de bookStore en un fichero de texto
  ofstream filewrite;
  char filename[KMAXSTRING];

  cout << "Enter filename: ";
  cin.getline(filename,KMAXSTRING);

  filewrite.open(filename);

  if(filewrite.is_open()){
    if(bookStore.books.size()!=0){
      for(int i=0; i<(int)bookStore.books.size();i++){
        filewrite << "\"" << bookStore.books[i].title << "\",";
        filewrite << "\"" << bookStore.books[i].authors << "\",";
        filewrite << bookStore.books[i].year << ",";
        filewrite << "\"" << bookStore.books[i].slug << "\",";
        filewrite << bookStore.books[i].price << endl;
      }
    }

    filewrite.close();
  }
  else{
    error(ERR_FILE);
  }

}

Book RealBook(BinBook binBook){//convierte de binBook (lo leido dentro del fichero binario)
  Book book;//en libro para poder guardarlo en el vector de libros

  book.id=binBook.id;
  book.title=binBook.title;
  book.authors=binBook.authors;
  book.year=binBook.year;
  book.slug=binBook.slug;
  book.price=binBook.price;

  return book;
}

void readBinaryfile(char name[],bool &open,BookStore &bookStore){//lee un fichero binario y añade a la lista de libros
  BinBookStore binStore;
  BinBook binBooks;
  ifstream fileBinRead;

   fileBinRead.open(name, ios::binary);

      if(fileBinRead.is_open()){
        bookStore.books.clear();

        fileBinRead.read((char*)&binStore,sizeof(BinBookStore));
        bookStore.name = binStore.name;
        bookStore.nextId = binStore.nextId;

        fileBinRead.seekg((1)*sizeof(BinBookStore),ios::beg);
        while(fileBinRead.read((char*)&binBooks,sizeof(BinBook))){
          bookStore.books.push_back(RealBook(binBooks));
        }
        fileBinRead.close();
      }
      else{
        error(ERR_FILE);
        open = false;
      }

}

void loadData(BookStore &bookStore){//se asegura de borrar todo y pide el nombre del fichero a leer al usuario 
  bool right=true;
  char option;
  char namefile[KMAXSTRING];

  do{
    cout << "All data will be erased, do you want to continue (Y/N)?: ";
    cin >> option;

    if(option == 'Y' || option == 'y'){
      cout << "Enter filename: ";
      cin >> namefile;
      readBinaryfile(namefile,right,bookStore);
    }

  }while(option!='Y' && option!='y' && option!='N'&& option!='n');
}

void moreKMAXSTRING(string name, char charname[]){//se asegura de guarda en array de caracteres un string
  string sub;
    if(name.length()>KMAXSTRING-1){//si el tamaño del string es mayor
      sub=name.substr(0,KMAXSTRING-1);
      strcpy(charname,sub.c_str());//guarda solo hasta el tamaño del array de caracteres
    }
    else{
      strcpy(charname,name.c_str());
    }
}

BinBook BinaryBook(const Book &book){//convierte de libro a binbook
  BinBook binbook;

  binbook.id=book.id;
  binbook.price=book.price;
  binbook.year=book.year;
  moreKMAXSTRING(book.title,binbook.title);
  moreKMAXSTRING(book.authors,binbook.authors);
  moreKMAXSTRING(book.slug,binbook.slug);

  return binbook;
}

void saveData(const BookStore &bookStore){//escribe un fichero binario con los datos de bookStore
  ofstream filebinWrite;
  BinBook Binbook;
  BinBookStore Binstore;
  char filename[KMAXSTRING];
  string name;

  cout << "Enter filename: ";
  cin >> filename;

  filebinWrite.open(filename, ios::binary);

  if(filebinWrite.is_open()){
    if(bookStore.name.length()>KMAXSTRING-1){
      name=bookStore.name.substr(0,KMAXSTRING-1);
      strcpy(Binstore.name,name.c_str());
    }
    else{
      strcpy(Binstore.name,bookStore.name.c_str());
    }
    Binstore.nextId=bookStore.nextId;

    filebinWrite.write((const char *)&Binstore,sizeof(BinBookStore));
    filebinWrite.seekp((1)*sizeof(BinBookStore),ios::beg);

    if(bookStore.books.size()!=0){
      for(int i=0;i<(int)bookStore.books.size();i++){

        Binbook=BinaryBook(bookStore.books[i]);

        filebinWrite.write((const char*)&Binbook,sizeof(BinBook));
      }
    }

    filebinWrite.close();
  }
  else{
    error(ERR_FILE);
  }

}

void importExportMenu(BookStore &bookStore) {//muestra el menu y da elegir 
  char option;

  do{
    showMenuExportImport();
    cin >> option;
     cin.get();

    switch(option){
      case '1':
        importFromCsv(bookStore);
        break;
      case '2':
        exportToCsv(bookStore);
        break;
      case '3':
       loadData(bookStore);
       break;
      case '4':
        saveData(bookStore);
        break;
      case 'b':
        break;
      default:
        error(ERR_OPTION);
        break; 
    }

  }while(option != 'b');
}

int main(int argc, char *argv[]) {

  BookStore bookStore;
  bookStore.name = "My Book Store";
  bookStore.nextId = 1;
  bool binary=true,text=true;
  char option;

  if(argc==3){
    if(strcmp(argv[1],"-l")==0){
      readBinaryfile(argv[2],binary,bookStore);
    }
    else if(strcmp(argv[1],"-i")==0){
      readTextfile(bookStore,argv[2],text);
    }else{
      error(ERR_ARGS);
    }
  }
  else if(argc==5){
    if(strcmp(argv[1],"-i")==0 && strcmp(argv[4],"-l")==0){
      readBinaryfile(argv[5],binary,bookStore);
      readTextfile(bookStore,argv[2],text);
    }
    else if(strcmp(argv[1],"-l")==0&& strcmp(argv[4],"-i")==0){
      readBinaryfile(argv[2],binary,bookStore);
      readTextfile(bookStore,argv[5],text);
    }
    else{
      error(ERR_ARGS);
    }
  }
  else if(argc==1){}

  else{
    error(ERR_ARGS);
    binary=false;
    text=false;
  }
  if(binary && text){
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

  }
  return 0;
}
