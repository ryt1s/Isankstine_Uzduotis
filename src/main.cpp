#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <set>

using namespace std;

int main() {
    ifstream in("data/input.txt");
    if (!in) {
        cerr << "Nepavyko atidaryti data/input.txt" << endl;
        return 1;
    }

    map<string, int> wordCount;
    map<string, set<int>> wordLines;

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
            wordCount[word]++;
            wordLines[word].insert(lineNumber);
        }
    }

    ofstream out("outputs/words.txt");
    if (!out) {
        cerr << "Nepavyko sukurti outputs/words.txt" << endl;
        return 1;
    }

    for (const auto& p : wordCount) {
        if (p.second > 1) {
            out << p.first << " (" << p.second << ") : ";
            for (int ln : wordLines[p.first]) {
                out << ln << " ";
            }
            out << "\n";
        }
    }

    cout << "Cross-reference lentele issaugota i outputs/words.txt" << endl;
    return 0;
}
