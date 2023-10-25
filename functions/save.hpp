#include <fstream>
void save() {
    string str;
    cout << "> save ";
    cin >> str;
    ofstream out_file;
    out_file.open(str.c_str());
    out_file << buffer;
    out_file.close();
}