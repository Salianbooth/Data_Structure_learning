/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/6/1 19:49
* @version: 1.0
* @description: 
********************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

class Book {
private:
    string title;
    string author;
    string genre;
    string purchaseDate;
    double price;
    string isbn;

public:

    //��һ����Ĭ�Ϲ��캯�����ڶ����Ǵ������Ĺ��캯�������ڳ�ʼ����Ա����
    Book() {}

    Book(string title, string author, string genre, string purchaseDate, double price, string isbn) {
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->purchaseDate = purchaseDate;
        this->price = price;
        this->isbn = isbn;
    }


    /**
     * ��֤���޸ĳ�Ա����
       ������ const �����ϵ���
     */
    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    string getGenre() const {
        return genre;
    }

    string getPurchaseDate() const {
        return purchaseDate;
    }

    double getPrice() const {
        return price;
    }

    string getISBN() const {
        return isbn;
    }


    void display() const {
        cout << "Title: " << title
             << ", Author: " << author
             << ", Genre: " << genre
             << ", Purchase Date: " << purchaseDate
             << ", Price: " << price
             << ", ISBN: " << isbn << endl;
    }
    //��Ԫ��������Ԫ����ʹ��Щ�����ܹ����� Book ���˽�г�Ա���Ӷ��ܹ���д�������ԡ�
    friend ostream& operator<<(ostream& os, const Book& book);
    friend istream& operator>>(istream& is, Book& book);
};

//���� operator<<�����ǿ��Խ� Book �������������д���ļ�
/**
 *
 * @param os:�����������������ã����ڽ�������������С�
 * @param book
 * @param << ʹ�� << ��������������ν� Book �����������������С�
 * @return
 */
ostream& operator<<(ostream& os, const Book& book) {
    os << book.title << '\n'
       << book.author << '\n'
       << book.genre << '\n'
       << book.purchaseDate << '\n'
       << book.price << '\n'
       << book.isbn << '\n';
    return os;
}
//���� operator>>�����ǿ��Դ��ļ��ж�ȡ�������Բ�����һ�� Book ����
/*istream& operator>>(istream& is, Book& book) {
    getline(is, book.title);
    getline(is, book.author);
    getline(is, book.genre);
    getline(is, book.purchaseDate);
    is >> book.price;
    is.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Ի��з�
    getline(is, book.isbn);
    return is;
}*/
istream& operator>>(istream& is, Book& book) {
    if (!getline(is, book.title)) return is;
    if (!getline(is, book.author)) return is;
    if (!getline(is, book.genre)) return is;
    if (!getline(is, book.purchaseDate)) return is;
    if (!(is >> book.price)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Ի��з�
    if (!getline(is, book.isbn)) return is;
    return is;
}

class Library {
private:
    vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    /**
     *
     * @param isbn
     * books.begin() �� books.end() �ֱ𷵻� books �����Ŀ�ʼ�ͽ�������������ʾҪ����ķ�Χ��
       remove_if �������������Χ��ÿ�� Book ���󣬲�Ӧ�� lambda ���ʽ��
       ��� book.getISBN() == isbn ���� true������� Book ���󽫱����Ϊ���Ƴ�����
       remove_if ����һ�������� it���õ�����ָ���һ�������Ϊ���Ƴ�����Ԫ�ء�

       ���lambda���ʽ�������ⲿ�������еı��� isbn��ͨ������ &isbn����������һ�� Book ������Ϊ������
       ��� book ����� ISBN �봫��� isbn ��ȣ�lambda���ʽ���� true�����򷵻� false��
     */

    void removeBookByISBN(const string& isbn) {
        //��������
        /**
         * remove_if ��һ����׼���㷨�����Ը�����Χ�ڵ�ÿ��Ԫ��Ӧ��һ��ν�ʣ���һ�����ز���ֵ�ĺ������󣩡�
         * ����ÿ��Ԫ�أ����ν�ʷ��� true�����Ԫ�ؽ������Ƴ�����ʵ�����Ǳ��ƶ���������ĩβ
         */
        auto it = remove_if(books.begin(), books.end(),
                            [&isbn](const Book& book) {
                                return book.getISBN() == isbn;
                            });
        //���д�������ȷ�� it ָ����Ч�� Book ����
        // ֻ���� it ������ books.end() ʱ��it ��ָ��һ����Ч�� Book ���󣬿��԰�ȫ�ؽ����ò��������Ա������
        //�Ⲣ��������ָ�룬���ǵ�����
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book with ISBN " << isbn << " removed." << endl;
        } else {
            cout << "Book with ISBN " << isbn << " not found." << endl;
        }
    }

    void findBookByTitle(const string& title) const {
        auto it = find_if(books.begin(), books.end(),
                          [&title](const Book& book) {
                              return book.getTitle() == title;
                          });
        if (it != books.end()) {
            cout << "Book found: ";
            it->display();
        } else {
            cout << "Book with title \"" << title << "\" not found." << endl;
        }
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books in the library." << endl;
        } else {
            for (const auto& book : books) {
                book.display();
            }
        }
    }

    void saveToFile(const string& filename) const {
        ofstream ofs(filename);
        if (!ofs) {
            cout << "Could not open file for writing." << endl;
            return;
        }

        for (const auto& book : books) {
            ofs << book;
        }
        cout << "Library saved to " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream ifs(filename);
        if (!ifs) {
            cout << "Could not open file for reading." << endl;
            return;
        }
        // �ȱ�֤��������û��֮ǰʣ�µ�
        books.clear();
        Book book;
        while (ifs >> book) {
            books.push_back(book);
            cout << "Loaded book: " << book.getTitle() << endl; // ���ӵ������
        }
        if (books.empty()) {
            cout << "No books were loaded." << endl;
        } else {
            cout << "Library loaded from " << filename << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "==== ͼ�����ϵͳ ====" << endl;
        cout << "1. ����鼮" << endl;
        cout << "2. ��ʾ�����鼮" << endl;
        cout << "3. �����鼮���ļ�" << endl;
        cout << "4. ���ļ������鼮" << endl;
        cout << "5. �����鼮" << endl;
        cout << "6. ɾ���鼮" << endl;
        cout << "7. �˳�" << endl;
        cout << "����������ѡ��: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������
        switch (choice) {
            case 1: {
                string title, author, genre, purchaseDate, isbn;
                double price;
                cout << "����������: ";
                getline(cin, title);
                cout << "����������: ";
                getline(cin, author);
                cout << "���������: ";
                getline(cin, genre);
                cout << "�����빺������: ";
                getline(cin, purchaseDate);
                cout << "������۸�: ";
                cin >> price;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������
                cout << "������ISBN: ";
                getline(cin, isbn);
                library.addBook(Book(title, author, genre, purchaseDate, price, isbn));
                break;
            }
            case 2:
                library.displayAllBooks();
                break;
            case 3:
                library.saveToFile("library.txt");
                break;
            case 4:
                library.loadFromFile("library.txt");
                break;
            case 5: {
                string title;
                cout << "������Ҫ���ҵ�����: ";
                cin >> title;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������
                library.findBookByTitle(title);
                break;
            }
            case 6: {
                string isbn;
                cout << "������Ҫɾ�����鼮ISBN: ";
                cin >> isbn;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������
                library.removeBookByISBN(isbn);
                break;
            }
            case 7:
                cout << "��лʹ��ͼ�����ϵͳ��" << endl;
                return 0;
            default:
                cout << "��Ч��ѡ��" << endl;
        }
    }


   /* // ����鼮
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "Fiction", "2019-05-12", 7.99, "9780060935467"));
    library.addBook(Book("1984", "George Orwell", "Dystopian", "2021-11-15", 6.50, "9780451524935"));
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "Fiction", "2018-07-22", 10.00, "9780743273565"));
    library.addBook(Book("Pride and Prejudice", "Jane Austen", "Romance", "2020-09-10", 5.99, "9780141439518"));
    library.addBook(Book("The Hobbit", "J.R.R. Tolkien", "Fantasy", "2022-03-30", 8.45, "9780547928227"));
    library.addBook(Book("Brave New World", "Aldous Huxley", "Science Fiction", "2019-12-05", 9.99, "9780060850524"));
    library.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "Fiction", "2020-01-01", 10.99, "9780316769488"));
    library.addBook(Book("Moby-Dick", "Herman Melville", "Adventure", "2017-06-14", 11.50, "9781503280786"));
    library.addBook(Book("War and Peace", "Leo Tolstoy", "Historical", "2021-04-20", 12.99, "9780199232765"));
    library.addBook(Book("The Odyssey", "Homer", "Epic", "2016-08-09", 9.00, "9780140268867"));

    // ��ʾ�����鼮
    cout << "All books in the library:" << endl;
    library.displayAllBooks();

    // �����鼮���ļ�
    library.saveToFile("D:\\library.txt");

    // ��յ�ǰ�鼮
    library = Library();

    // ���ļ��м����鼮
    library.loadFromFile("D:\\library.txt");

    // ��ʾ�����鼮
    cout << "\nAll books in the library after loading from file:" << endl;
    library.displayAllBooks();

    // �����鼮
    cout << "\nFinding book with title '1984':" << endl;
    library.findBookByTitle("1984");

    // ɾ���鼮
    cout << "\nRemoving book with ISBN '9780061120084':" << endl;
    library.removeBookByISBN("9780061120084");

    // ��ʾ�����鼮
    cout << "\nAll books in the library after deletion:" << endl;
    library.displayAllBooks();

    // �����޸ĺ���鼮���ļ�
    library.saveToFile("D:\\library.txt");*/

    return 0;
}