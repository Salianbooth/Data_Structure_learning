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

    //第一个是默认构造函数，第二个是带参数的构造函数，用于初始化成员变量
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
     * 保证不修改成员变量
       允许在 const 对象上调用
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
    //友元函数，友元函数使这些操作能够访问 Book 类的私有成员，从而能够读写所有属性。
    friend ostream& operator<<(ostream& os, const Book& book);
    friend istream& operator>>(istream& is, Book& book);
};

//重载 operator<<，我们可以将 Book 对象的所有属性写入文件
/**
 *
 * @param os:这是输出流对象的引用，用于将数据输出到流中。
 * @param book
 * @param << 使用 << 操作符：定义如何将 Book 对象的内容输出到流中。
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
//重载 operator>>，我们可以从文件中读取所有属性并创建一个 Book 对象
/*istream& operator>>(istream& is, Book& book) {
    getline(is, book.title);
    getline(is, book.author);
    getline(is, book.genre);
    getline(is, book.purchaseDate);
    is >> book.price;
    is.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略换行符
    getline(is, book.isbn);
    return is;
}*/
istream& operator>>(istream& is, Book& book) {
    if (!getline(is, book.title)) return is;
    if (!getline(is, book.author)) return is;
    if (!getline(is, book.genre)) return is;
    if (!getline(is, book.purchaseDate)) return is;
    if (!(is >> book.price)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略换行符
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
     * books.begin() 和 books.end() 分别返回 books 容器的开始和结束迭代器，表示要处理的范围。
       remove_if 函数遍历这个范围的每个 Book 对象，并应用 lambda 表达式。
       如果 book.getISBN() == isbn 返回 true，则这个 Book 对象将被标记为“移除”。
       remove_if 返回一个迭代器 it，该迭代器指向第一个被标记为“移除”的元素。

       这个lambda表达式捕获了外部作用域中的变量 isbn（通过引用 &isbn），并接受一个 Book 对象作为参数。
       如果 book 对象的 ISBN 与传入的 isbn 相等，lambda表达式返回 true；否则返回 false。
     */

    void removeBookByISBN(const string& isbn) {
        //匿名函数
        /**
         * remove_if 是一个标准库算法，它对给定范围内的每个元素应用一个谓词（即一个返回布尔值的函数对象）。
         * 对于每个元素，如果谓词返回 true，则该元素将被“移除”（实际上是被移动到容器的末尾
         */
        auto it = remove_if(books.begin(), books.end(),
                            [&isbn](const Book& book) {
                                return book.getISBN() == isbn;
                            });
        //这行代码用于确保 it 指向有效的 Book 对象。
        // 只有在 it 不等于 books.end() 时，it 才指向一个有效的 Book 对象，可以安全地解引用并调用其成员函数。
        //这并不是在用指针，这是迭代器
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
        // 先保证容器里面没有之前剩下的
        books.clear();
        Book book;
        while (ifs >> book) {
            books.push_back(book);
            cout << "Loaded book: " << book.getTitle() << endl; // 增加调试输出
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
        cout << "==== 图书管理系统 ====" << endl;
        cout << "1. 添加书籍" << endl;
        cout << "2. 显示所有书籍" << endl;
        cout << "3. 保存书籍到文件" << endl;
        cout << "4. 从文件加载书籍" << endl;
        cout << "5. 查找书籍" << endl;
        cout << "6. 删除书籍" << endl;
        cout << "7. 退出" << endl;
        cout << "请输入您的选择: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区
        switch (choice) {
            case 1: {
                string title, author, genre, purchaseDate, isbn;
                double price;
                cout << "请输入书名: ";
                getline(cin, title);
                cout << "请输入作者: ";
                getline(cin, author);
                cout << "请输入类别: ";
                getline(cin, genre);
                cout << "请输入购买日期: ";
                getline(cin, purchaseDate);
                cout << "请输入价格: ";
                cin >> price;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区
                cout << "请输入ISBN: ";
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
                cout << "请输入要查找的书名: ";
                cin >> title;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区
                library.findBookByTitle(title);
                break;
            }
            case 6: {
                string isbn;
                cout << "请输入要删除的书籍ISBN: ";
                cin >> isbn;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清除缓冲区
                library.removeBookByISBN(isbn);
                break;
            }
            case 7:
                cout << "感谢使用图书管理系统！" << endl;
                return 0;
            default:
                cout << "无效的选择！" << endl;
        }
    }


   /* // 添加书籍
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

    // 显示所有书籍
    cout << "All books in the library:" << endl;
    library.displayAllBooks();

    // 保存书籍到文件
    library.saveToFile("D:\\library.txt");

    // 清空当前书籍
    library = Library();

    // 从文件中加载书籍
    library.loadFromFile("D:\\library.txt");

    // 显示所有书籍
    cout << "\nAll books in the library after loading from file:" << endl;
    library.displayAllBooks();

    // 查找书籍
    cout << "\nFinding book with title '1984':" << endl;
    library.findBookByTitle("1984");

    // 删除书籍
    cout << "\nRemoving book with ISBN '9780061120084':" << endl;
    library.removeBookByISBN("9780061120084");

    // 显示所有书籍
    cout << "\nAll books in the library after deletion:" << endl;
    library.displayAllBooks();

    // 保存修改后的书籍到文件
    library.saveToFile("D:\\library.txt");*/

    return 0;
}