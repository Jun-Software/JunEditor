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
            cout << "> |";
            string command;
            int command_index = 0;
            while (ch = getch()) {
                system("cls");
                if (ch == esc) {
                    break;
                }
                else if (ch == enter) {
                    map<string, void(*)()>::iterator it;
                    it = functions.find(command);
                    if (it != functions.end()) {
                        functions[command]();
                    }
                    else {
                        functions["help"]();
                    }
                    command = "";
                    command_index = 0;
                }
                else if (ch == ' ') {
                    map<string, void(*)()>::iterator it;
                    it = functions.find(command);
                    if (it != functions.end()) {
                        functions[command]();
                    }
                    else {
                        functions["help"]();
                    }
                    command = "";
                    command_index = 0;
                }
                else if (ch == back) {
                    command.erase(command.begin() + command_index - 1);
                    command_index = max(command_index - 1, 0);
                }
                else if (ch == -32) {
                    ch = getch();
                    if (ch == 75) {
                        command_index = max(command_index - 1, 0);
                    }
                    else if (ch == 77) {
                        command_index = min(command_index + 1, int(command.size()));
                    }
                }
                else {
                    string str;
                    str += ch;
                    command.insert(command_index, str);
                    command_index = min(command_index + 1, int(command.size()));
                }
                cout << "> ";
                for (int i = 0; i <= command.size(); i++) {
                    if (i == command_index) {
                        cout << '|';
                    }
                    cout << command[i];
                }
            }
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
                index = min(index + 1, int(buffer.size()));
            }
            if (index == -1) {
                index = 1;
            }
        }
        else {
            string str;
            str += ch;
            buffer.insert(index, str);
            index = min(index + 1, int(buffer.size()));
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