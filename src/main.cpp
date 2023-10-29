#include <iostream>
#include <map>
#include <windows.h>
#include <conio.h>
using namespace std;

string buffer = "\n\n";
#include "functions/quit.hpp"
#include "functions/help.hpp"
#include "functions/save.hpp"
map<string, void(*)()> functions;

void init_functions() {
    functions["quit"] = quit;
    functions["exit"] = quit;
    functions["help"] = help;
    functions["save"] = save;
}

int main() {
    init_functions();
    CONSOLE_CURSOR_INFO cursor_info = {20, false};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    char ch;
    int index = 1;
    char esc = '\e', back = '\b', enter = '\r';
    cout << '|';
    while (ch = getch()) {
        system("cls");
        if (ch == esc) {
            cout << "> ";
            string command;
            cin >> command;
            map<string, void(*)()>::iterator it;
            it = functions.find(command);
            if (it != functions.end()) {
                functions[command]();
            }
            else {
                functions["help"]();
            }
            Sleep(3000);
            system("cls");
        }
        else if (ch == enter) {
            buffer.insert(index, "\n");
            index = min(index + 1, int(buffer.size()));
        }
        else if (ch == back) {
            buffer.erase(buffer.begin() + index - 1);
            index = max(index - 1, 1);
        }
        else if (ch == -32) {
            ch = getch();
            if (ch == 72) {
                int new_index = (index - (buffer.rfind('\n', index) + 1)) + (buffer.rfind('\n', (buffer.rfind('\n', index) - 1)) + 1);
                int up_end = buffer.rfind('\n', index - 1);
                index = min(new_index, up_end);
            }
            else if (ch == 80) {
                int new_index = (index - (buffer.find('\n', index) + 1)) + (buffer.find('\n', (buffer.find('\n', index) - 1)) + 1);
                int next_end = buffer.find('\n', buffer.find('\n', index) + 1);
                index = min(new_index, next_end);
            }
            else if (ch == 75) {
                index = max(index - 1, 1);
            }
            else if (ch == 77) {
                index = min(index + 1, int(buffer.size()) - 1);
            }
            if (index == -1) {
                index = 1;
            }
        }
        else {
            string str;
            str += ch;
            buffer.insert(index, str);
            index = min(index + 1, int(buffer.size()) - 1);
        }
        for (int i = 1; i <= buffer.size(); i++) {
            if (i == index) {
                cout << '|';
            }
            cout << buffer[i];
        }
    }
    return 0;
}