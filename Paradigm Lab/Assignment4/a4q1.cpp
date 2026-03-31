#include <cstring>
#include <iostream>
using std::cin, std::cout, std::endl;

class Book {
  char *title;
  int pages;

public:
  // Default Constructor
  Book() : title(nullptr), pages(0) {}

  // Parameterized Constructor
  Book(const char *book_title, int no_pages) : pages(no_pages) {
    if (book_title) {
      title = new char[strlen(book_title) + 1];
      strcpy(title, book_title);
    } else
      title = nullptr;
  }

  // Copy Constructor
  Book(const Book &obj) : pages(obj.pages) {
    if (obj.title) {
      title = new char[strlen(obj.title) + 1];
      strcpy(title, obj.title);
    } else
      title = nullptr;
  }

  // Assignment Operator
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

  // Read data
  virtual int read(const char *title = nullptr, int pages = 0) {
    if (title == nullptr)
      return 1;

    this->pages = pages;
    delete[] this->title;
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);

    return 0;
  }

  // Display data
  virtual void Display() const {
    if (!title)
      cout << "Book name: No title" << endl;
    else {
      cout << "Book name:" << title << endl;
      cout << "Number of pages: " << pages << endl;
    }
  }

  // Destructor
  virtual ~Book() { delete[] title; }
};

class Ebook : public Book {
  double fileSizeMB;
  char *Format;

public:
  // Default Constructor
  Ebook() : Book(), fileSizeMB(0), Format(nullptr) {}

  // Parameterized Constructor
  Ebook(const char *title, int pages, double fileSizeMB, const char *format)
      : Book(title, pages), fileSizeMB(fileSizeMB) {
    if (format) {
      Format = new char[strlen(format) + 1];
      strcpy(Format, format);
    } else
      Format = nullptr;
  }

  // Copy Constructor
  Ebook(const Ebook &obj) : Book(obj), fileSizeMB(obj.fileSizeMB) {
    if (obj.Format) {
      Format = new char[strlen(obj.Format) + 1];
      strcpy(Format, obj.Format);
    } else
      Format = nullptr;
  }

  // Assignment operator
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

  // Read data
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

  // Display data
  void Display() const {
    Book::Display();
    if (Format)
      cout << "File format: " << Format << endl;
    else
      cout << "File format: [N/A]" << endl;
    cout << "File size: " << fileSizeMB << " MB" << endl;
  }

  // Destructor
  ~Ebook() { delete[] Format; }
};
