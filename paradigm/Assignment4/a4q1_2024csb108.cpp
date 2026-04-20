#include <cstring>
#include <iostream>
using std::cin, std::cout, std::endl;

class Book {
  char *title;
  int pages;

public:
  Book() : title(nullptr), pages(0) {}

  Book(const char *book_title, int no_pages) : pages(no_pages) {
    if (book_title) {
      title = new char[strlen(book_title) + 1];
      strcpy(title, book_title);
    } else
      title = nullptr;
  }

  Book(const Book &obj) : pages(obj.pages) {
    if (obj.title) {
      title = new char[strlen(obj.title) + 1];
      strcpy(title, obj.title);
    } else
      title = nullptr;
  }

  Book &operator=(const Book &obj) {
    if (this == &obj)
      return *this;

    pages = obj.pages;
    delete[] title;

    if (obj.title) {
      title = new char[strlen(obj.title) + 1];
      strcpy(title, obj.title);
    } else
      title = nullptr;

    return *this;
  }

  virtual int read(const char *title = nullptr, int pages = 0) {
    if (title == nullptr)
      return 1;

    this->pages = pages;
    delete[] this->title;
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);

    return 0;
  }

  virtual void Display() const {
    if (!title)
      cout << "Book name: No title" << endl;
    else {
      cout << "Book name:" << title << endl;
      cout << "Number of pages: " << pages << endl;
    }
  }

  virtual ~Book() { delete[] title; }
};

class Ebook : public Book {
  double fileSizeMB;
  char *Format;

public:
  Ebook() : Book(), fileSizeMB(0), Format(nullptr) {}

  Ebook(const char *title, int pages, double fileSizeMB, const char *format)
      : Book(title, pages), fileSizeMB(fileSizeMB) {
    if (format) {
      Format = new char[strlen(format) + 1];
      strcpy(Format, format);
    } else
      Format = nullptr;
  }

  Ebook(const Ebook &obj) : Book(obj), fileSizeMB(obj.fileSizeMB) {
    if (obj.Format) {
      Format = new char[strlen(obj.Format) + 1];
      strcpy(Format, obj.Format);
    } else
      Format = nullptr;
  }

  Ebook &operator=(const Ebook &obj) {
    if (this == &obj)
      return *this;

    Book::operator=(obj);
    fileSizeMB = obj.fileSizeMB;
    delete[] Format;
    if (obj.Format) {
      Format = new char[strlen(obj.Format) + 1];
      strcpy(Format, obj.Format);
    } else
      Format = nullptr;
    return *this;
  }

  int read(const char *title, int pages, double fileSizeMB,
           const char *format) {
    if (Book::read(title, pages))
      return 1;
    this->fileSizeMB = fileSizeMB;

    delete[] Format;

    if (format) {
      Format = new char[strlen(format) + 1];
      strcpy(Format, format);
    } else
      Format = nullptr;

    return 0;
  }

  void Display() const {
    Book::Display();
    if (Format)
      cout << "File format: " << Format << endl;
    else
      cout << "File format: [N/A]" << endl;
    cout << "File size: " << fileSizeMB << " MB" << endl;
  }

  ~Ebook() { delete[] Format; }
};

int main() {
  Book *library[100];
  int count = -1;

  int choice;
  char title[100], format[50];
  int pages;
  double size;

  do {
    cout << "\nChoose an option: \n";
    cout << "1. Add Book\n";
    cout << "2. Add Ebook\n";
    cout << "3. Display All\n";
    cout << "4. Copy Object\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {

    case 1:
      if (count >= 100) {
        cout << "Library full.\n";
        break;
      }

      cout << "Enter title: ";
      cin.getline(title, 100);
      cout << "Enter pages: ";
      cin >> pages;
      cin.ignore();

      count++;
      library[count] = new Book();
      library[count]->read(title, pages);


      cout << "Book added.\n";
      break;

    case 2:
      if (count >= 100) {
        cout << "Library full.\n";
        break;
      }

      cout << "Enter title: ";
      cin.getline(title, 100);
      cout << "Enter pages: ";
      cin >> pages;
      cout << "Enter file size: ";
      cin >> size;
      cin.ignore();
      cout << "Enter format: ";
      cin.getline(format, 50);
      count++;
      library[count] = new Ebook();
      ((Ebook *)library[count])->read(title, pages, size, format);


      cout << "Ebook added.\n";
      break;

    case 3:
      if (count == -1) {
        cout << "No records.\n";
        break;
      }

      for (int i = 0; i <=count; i++) {
        cout << "\nItem Index " << i << ":\n";
        library[i]->Display();
      }
      break;

    case 4: {
      int src, dest;
      cout << "Enter source index: ";
      cin >> src;
      cout << "Enter destination index: ";
      cin >> dest;

      if (src < count && dest < count) {
        *(library[dest]) = *(library[src]);
        cout << "Copied.\n";
      } else
        cout << "Invalid index.\n";
      break;
    }

    case 0:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice.\n";
    }

  } while (choice != 0);

  for (int i = 0; i < count; i++)
    delete library[i];

  return 0;
}