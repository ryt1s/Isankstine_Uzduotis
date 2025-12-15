#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    ifstream in("data/input.txt");
    if (!in) {
        cerr << "Nepavyko atidaryti input.txt" << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;

    while (getline(in, line)) {
        ++lineNumber;
        
        for (char& c : line) {
            if (!isalnum(static_cast<unsigned char>(c))) {
                c = ' ';
            }
        }

        stringstream ss(line);
        string word;

        while (ss >> word) {
            cout << "[" << word << "] (eilute " << lineNumber << ")" << endl;
        }
    }

    return 0;
}
