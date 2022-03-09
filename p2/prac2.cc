// Programación 2 - Práctica 2
// DNI: 74379872B
// Nombre: Judit Serrano Espinosa
#include <iostream>
#include <vector>

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

void showCatalog(const BookStore &bookStore) {
  if(bookStore.books.size()!=0){
    for(int i=0;i<(int)bookStore.books.size();i++){
       cout << bookStore.books[i].id << ". ";
       cout << bookStore.books[i].title;
       cout << " (" << bookStore.books[i].year << "), ";
       cout << bookStore.books[i].price << endl;
    }
  }
}

void showExtendedCatalog(const BookStore &bookStore) {
  if(bookStore.books.size()!=0){
    for(int i=0; i<(int)bookStore.books.size();i++){
      cout << "\"" << bookStore.books[i].title << "\",";
      cout << "\"" << bookStore.books[i].authors << "\",";
      cout << bookStore.books[i].year << ",";
      cout << "\"" << bookStore.books[i].slug << "\",";
      cout << bookStore.books[i].price << "," << endl;

    }
  }
}

void askName(string name,bool title){
  bool right;
  name="";
  do{
    right=true;
    if(title){
      cout << "Enter book title" << endl;
    }
    else{
      cout << "Enter author(s):" << endl;
    }
    getline(cin,name);

    for(int i=0;i<(int)name.length();i++){
      if(!isalnum(name[i])&&name[i]!=' '&&name[i]!=':'&&name[i]!=','&&name[i]!='-'){
        if(title){
          error(ERR_BOOK_TITLE);
        }
        else{
          error(ERR_BOOK_AUTHORS);
        }
        right=false;
      }
    }
  }while(!right);
}

void addBook(BookStore &bookStore) {
  Book book;
  
  askName(book.title,true);
  askName(book.authors,false);

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
