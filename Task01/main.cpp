#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Book {
    std::string title_;
    std::string author_;
    int copies_;
    static int checked(int n) { if (n < 0) throw std::invalid_argument("copies cannot be negative"); return n; }
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(std::string title) : Book(std::move(title), "Unknown", 1) {}
    Book(std::string title, std::string author, int copies)
        : title_(std::move(title)), author_(std::move(author)), copies_(checked(copies)) {}
    void print() const { std::cout << title_ << " | " << author_ << " | copies=" << copies_ << '\n'; }
};

int main() {
    Book empty;
    Book donated("The Hobbit");
    Book complete("Dune", "Frank Herbert", 4);
    empty.print(); donated.print(); complete.print();
    try { Book invalid("Bad", "Record", -2); (void)invalid; }
    catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}

