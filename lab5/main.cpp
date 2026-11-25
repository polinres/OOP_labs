#include <iostream>
#include <stack>
#include <string>
#include "AdapterContainerDemo.h"

using namespace std;

struct Step {
    string name;
    void (*func)();
};

void printCalls(stack<Step> s) {
    if (s.empty()) { cout << "Стек вызовов пуст.\n"; return; }
    cout << "Стек вызовов (сверху вниз):\n";
    while (!s.empty()) {
        cout << "  " << s.top().name << "\n";
        s.pop();
    }
}

int main() {
    system("chcp 1251 > nul");
    system("cls");

    stack<Step> calls; 
    int choice;
    do {
        cout << "\n--- ГЛАВНОЕ МЕНЮ (стек вызовов, размер: " << calls.size() << ") ---\n"
            << "1. Положить в стек: STACK\n"
            << "2. Положить в стек: QUEUE\n"
            << "3. Положить в стек: PRIORITY_QUEUE\n"
            << "4. Показать стек вызовов\n"
            << "5. Выполнить вызов с вершины стека (top + pop)\n"
            << "6. Выполнить все вызовы из стека\n"
            << "0. Выход\n"
            << "Выбор: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: calls.push({ "STACK", demoStack });
            cout << "push: STACK. Размер стека: " << calls.size() << "\n"; break;
        case 2: calls.push({ "QUEUE", demoQueue });
            cout << "push: QUEUE. Размер стека: " << calls.size() << "\n"; break;
        case 3: calls.push({ "PRIORITY_QUEUE", demoPriorityQueue });
            cout << "push: PRIORITY_QUEUE. Размер стека: " << calls.size() << "\n"; break;
        case 4: printCalls(calls); break;
        case 5: {
            if (calls.empty()) { cout << "Стек вызовов пуст!\n"; break; }
            Step s = calls.top();
            calls.pop();
            cout << "pop: " << s.name << ". Осталось в стеке: " << calls.size() << "\n";
            s.func();
            break;
        }
        case 6: {
            if (calls.empty()) { cout << "Стек вызовов пуст!\n"; break; }
            while (!calls.empty()) {
                Step s = calls.top();
                calls.pop();
                cout << "\npop: " << s.name << ". Осталось в стеке: " << calls.size() << "\n";
                s.func();
            }
            break;
        }
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);

    return 0;
}