#include <bits/stdc++.h>

using namespace std;

class Book
{
public:
    // variables
    string title;
    string author;

    // Constructors
    Book()
    {
        title = "UnknownTitle";
        author = "UnknownAuthor";
        isbn = "ISBN";
        copiesAvailable = 0;
        totalCopies = 5;
    }

    Book(string Title, string Author, string ISBN, int Copies, int TC)
    {
        title = Title;
        author = Author;
        isbn = ISBN;
        copiesAvailable = Copies;
        totalCopies = TC;
    }

    Book(Book &B1, string ISBN)
    {
        title = B1.title;
        author = B1.author;
        isbn = ISBN;
        copiesAvailable = B1.copiesAvailable;
        totalCopies = B1.totalCopies;
    }

    // Getters
    string getISBN()
    {
        return isbn;
    }

    int getCopiesAvailable()
    {
        return copiesAvailable;
    }

    int getTotalCopies()
    {
        return totalCopies;
    }

    void updateCount(int count)
    {
        if (totalCopies + count < 0 || copiesAvailable + count < 0)
        {
            cout << "Invalid request! Count becomes negative" << endl;
            return;
        }
        else
        {
            totalCopies += count;
            copiesAvailable += count;
        }
    }

    bool borrowBook()
    {
        if (copiesAvailable == 0)
        {
            cout << "Invalid request! Copy of book not available" << endl;
            return false;
        }
        else
        {
            copiesAvailable--;
            return true;
        }
    }

    bool returnBook()
    {
        if (copiesAvailable == totalCopies)
        {
            cout << "Invalid request! Copy of book exceeds total copies" << endl;
            return false;
        }
        else
        {
            copiesAvailable++;
            return true;
        }
    }

    void printDetails()
    {
        cout << title << " " << author << endl;
    }

private:
    // variables
    string isbn;
    int copiesAvailable;
    int totalCopies;
};

class Member
{
public:
    string name;
    // Constructors
    Member(string MemberID, string NAME, int limit)
    {
        memberID = MemberID;
        name = NAME;
        borrowLimit = limit;
    }

    Member(string MemberID, string NAME)
    {
        memberID = MemberID;
        name = NAME;
        borrowLimit = 3;
    }

    // Member functions
    int getAvailable()
    {
        return borrowLimit - currentBorrowed;
    }

    bool borrowBook(string isbn)
    {
        if (currentBorrowed < borrowLimit)
        {
            borrowedBooks[isbn]++;
            currentBorrowed++;
            return true;
        }
        else
        {
            cout << "Invalid request! Borrow limit exceeded" << endl;
            return false;
        }
    }

    bool returnBook(string isbn)
    {
        if (borrowedBooks[isbn] == 0)
        {
            cout << "Invalid request! Book not borrowed" << endl;
            return false;
        }
        else
        {
            borrowedBooks[isbn]--;
            if (borrowedBooks[isbn] == 0)
            {
                borrowedBooks.erase(isbn);
            }
            currentBorrowed--;
            return true;
        }
    }

    void printDetails()
    {
        for (auto i : borrowedBooks)
        {
            if (i.second > 0)
                cout << memberID << " " << name << " " << i.first << " " << i.second << endl;
        }
    }

    // Getters
    string getMemberID()
    {
        return memberID;
    }

private:
    string memberID;
    map<string, int> borrowedBooks;
    int borrowLimit;
    int currentBorrowed = 0;
};

class Library
{
public:
    // Constructors
    Library()
    {
        books = {};
        members = {};
    }

    // Member functions
    bool addBook(Book &B1)
    {
        if (isbnCodes.find(B1.getISBN()) != isbnCodes.end())
        {
            cout << "Invalid request! Book with same isbn already exists" << endl;
            return false;
        }
        books.push_back(B1);
        isbnCodes.insert(B1.getISBN());
        return true;
    }

    bool registerMember(Member &m)
    {
        if (memberIDS.find(m.getMemberID()) != memberIDS.end())
        {
            cout << "Invalid request! Member with same id already exists" << endl;
            return false;
        }
        members.push_back(m);
        memberIDS.insert(m.getMemberID());
        return true;
    }

    bool borrowBook(string memberID, string isbn)
    {
        int memberIndex = -1;
        for (int i = 0; i < members.size(); i++)
        {
            if (members[i].getMemberID() == memberID)
            {
                memberIndex = i;
                break;
            }
        }
        if (memberIndex == -1)
        {
            cout << "Invalid request! Member not found" << endl;
        }
        int bookIndex = -1;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getISBN() == isbn)
            {
                bookIndex = i;
                break;
            }
        }
        if (bookIndex == -1)
        {
            cout << "Invalid request! Book not found" << endl;
        }

        if (bookIndex == -1 || memberIndex == -1)
        {
            return false;
        }
        if (books[bookIndex].getCopiesAvailable() > 0 && members[memberIndex].getAvailable() > 0)
        {
            books[bookIndex].borrowBook();
            members[memberIndex].borrowBook(isbn);
        }
        else if (books[bookIndex].getCopiesAvailable() == 0)
        {
            books[bookIndex].borrowBook();
        }
        else if (members[memberIndex].getAvailable() == 0)
        {
            members[memberIndex].borrowBook(isbn);
        }
        return true;
    }

    bool returnBook(string memberID, string isbn)
    {
        int memberIndex = -1;
        for (int i = 0; i < members.size(); i++)
        {
            if (members[i].getMemberID() == memberID)
            {
                memberIndex = i;
                break;
            }
        }
        if (memberIndex == -1)
        {
            cout << "Invalid request! Member not found" << endl;
        }
        int bookIndex = -1;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getISBN() == isbn)
            {
                bookIndex = i;
                break;
            }
        }
        if (bookIndex == -1)
        {
            cout << "Invalid request! Book not found" << endl;
        }

        if (bookIndex == -1 || memberIndex == -1)
        {
            return false;
        }

        if (books[bookIndex].getCopiesAvailable() == books[bookIndex].getTotalCopies())
        {
            cout << "Invalid request! Copy of book exceeds total copies" << endl;
            return false;
        }
        if (members[memberIndex].returnBook(isbn))
        {
            books[bookIndex].returnBook();
            return true;
        }
        return false;
    }

    void printLibraryDetails()
    {
        for (auto i : books)
        {
            cout << i.title << " " << i.author << " " << i.getCopiesAvailable() << endl;
        }
        for (auto i : members)
        {
            cout << i.getMemberID() << " " << i.name << endl;
        }
    }

    void addBookOld(string oldI, string newI)
    {
        int bookIndex = -1;
        bool flag = 0;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getISBN() == oldI)
            {
                bookIndex = i;
            }
            if (books[i].getISBN() == newI)
            {
                flag = 1;
                break;
            }
        }
        if (bookIndex == -1)
        {
            cout << "Invalid request! Book not found" << endl;
            return;
        }
        else if (flag)
        {
            cout << "Invalid request! Book with the same isbn exists" << endl;
            return;
        }

        Book b(books[bookIndex], newI);
        addBook(b);
    }

    void changeCount(string isbn, int newCount)
    {
        int bookIndex = -1;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getISBN() == isbn)
            {
                bookIndex = i;
                break;
            }
        }
        if (bookIndex == -1)
        {
            cout << "Invalid request! Book not found" << endl;
            return;
        }
        books[bookIndex].updateCount(newCount);
    }

    void printMember(string MemberID)
    {
        int memberIndex = -1;
        for (int i = 0; i < members.size(); i++)
        {
            if (members[i].getMemberID() == MemberID)
            {
                memberIndex = i;
                break;
            }
        }
        if (memberIndex == -1)
        {
            cout << "Invalid request! Member not found" << endl;
            return;
        }
        members[memberIndex].printDetails();
    }

    void printBook(string isbn)
    {
        int bookIndex = -1;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getISBN() == isbn)
            {
                bookIndex = i;
                break;
            }
        }
        if (bookIndex == -1)
        {
            cout << "Invalid request! Book not found" << endl;
            return;
        }
        books[bookIndex].printDetails();
    }

private:
    vector<Book> books;
    vector<Member> members;
    set<string> isbnCodes;
    set<string> memberIDS;
};

int main()
{
    string str;
    cin >> str;
    int a = 1;
    Library L;
    while (str != "Done")
    {
        if (str == "Book")
        {
            string case1;
            cin >> case1;
            if (case1 == "None")
            {
                Book b;
                L.addBook(b);
            }
            else if (case1 == "ExistingBook" || case1 == "ExisitingBook")
            {
                string old, newI;
                cin >> old >> newI;
                L.addBookOld(old, newI);
            }
            else
            {
                string aut, isb;
                int copA, tCop;
                cin >> aut >> isb >> copA >> tCop;
                Book b(case1, aut, isb, copA, tCop);
                L.addBook(b);
            }
        }
        else if (str == "UpdateCopiesCount")
        {
            string isb;
            int newCount;
            cin >> isb >> newCount;
            L.changeCount(isb, newCount);
        }
        else if (str == "Member")
        {
            string identifier;
            cin >> identifier;
            if (identifier == "NoBorrowLimit")
            {
                string a, b;
                cin >> a >> b;
                Member m(a, b);
                L.registerMember(m);
            }
            else
            {
                string a;
                int b;
                cin >> a >> b;
                Member m(identifier, a, b);
                L.registerMember(m);
            }
        }
        else if (str == "Borrow")
        {
            string MemberID, isbn;
            cin >> MemberID >> isbn;
            L.borrowBook(MemberID, isbn);
        }
        else if (str == "Return")
        {
            string MemberID, isbn;
            cin >> MemberID >> isbn;
            L.returnBook(MemberID, isbn);
        }
        else if (str == "PrintBook")
        {
            string isbn;
            cin >> isbn;
            L.printBook(isbn);
        }
        else if (str == "PrintMember")
        {
            string MemberID;
            cin >> MemberID;
            L.printMember(MemberID);
        }
        else if (str == "PrintLibrary")
        {
            L.printLibraryDetails();
        }
        cin >> str;
    }
}
