#include "Classes.h"
using namespace std;

string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

int readInt(const string& prompt) {
    cout << prompt;
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка ввода, повторите: ";
    }
    cin.ignore(10000, '\n');
    return x;
}

void PrintedProduct::input() {
    title = readLine("  Название: ");
    copies = readInt("  Тираж: ");
}

// Book
void Book::print() const {
    cout << "Книга | " << title << " | Тираж: " << copies << " | Автор: " << author << endl;
}
void Book::input() { PrintedProduct::input(); author = readLine("  Автор: "); }
void Book::save(ostream& os) const {
    os << "Книга;" << title << ";" << copies << ";" << author << "\n";
}

// Magazine
void Magazine::print() const {
    cout << "Журнал | " << title << " | Тираж: " << copies << " | Номер выпуска: " << issue << endl;
}
void Magazine::input() { PrintedProduct::input(); issue = readInt("  Номер выпуска: "); }
void Magazine::save(ostream& os) const {
    os << "Журнал;" << title << ";" << copies << ";" << issue << "\n";
}

// Newspaper
void Newspaper::print() const {
    cout << "Газета | " << title << " | Тираж: " << copies << " | Город: " << city << endl;
}
void Newspaper::input() { PrintedProduct::input(); city = readLine("  Город издания: "); }
void Newspaper::save(ostream& os) const {
    os << "Газета;" << title << ";" << copies << ";" << city << "\n";
}

// Brochure
void Brochure::print() const {
    cout << "Брошюра | " << title << " | Тираж: " << copies << " | Тема: " << topic << endl;
}
void Brochure::input() { PrintedProduct::input(); topic = readLine("  Тема: "); }
void Brochure::save(ostream& os) const {
    os << "Брошюра;" << title << ";" << copies << ";" << topic << "\n";
}

// Poster
void Poster::print() const {
    cout << "Плакат | " << title << " | Тираж: " << copies << " | Формат: " << format << endl;
}
void Poster::input() { PrintedProduct::input(); format = readLine("  Формат (например, A2): "); }
void Poster::save(ostream& os) const {
    os << "Плакат;" << title << ";" << copies << ";" << format << "\n";
}