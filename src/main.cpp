#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <cctype>

#include "text_utils.h"

using namespace std;

int main() {
    ifstream in("data/input.txt");
    if (!in) {
        cerr << "Nepavyko atidaryti data/input.txt" << endl;
        return 1;
    }

    map<string, int> wordCount;
    map<string, set<int>> wordLines;
    set<string> urls;

    string line;
    int lineNumber = 0;

    while (getline(in, line)) {
        ++lineNumber;

        for (char& c : line) {
            if (!isalnum(static_cast<unsigned char>(c)) &&
                c != '.' && c != ':' && c != '/') {
                c = ' ';
            }
        }

        stringstream ss(line);
        string word;

        while (ss >> word) {

            if (isURL(word)) {
                urls.insert(word);
                continue;
            }

            word = toLower(word);

            bool validWord = true;
            for (char c : word) {
                if (!isalpha(static_cast<unsigned char>(c))) {
                    validWord = false;
                    break;
                }
            }

            if (validWord) {
                wordCount[word]++;
                wordLines[word].insert(lineNumber);
            }
        }
    }

    ofstream out("outputs/words.txt");
    if (!out) {
        cerr << "Nepavyko sukurti outputs/words.txt" << endl;
        return 1;
    }

    out << "Zodziai, kurie kartojasi daugiau nei 1 karta:\n\n";
    for (const auto& p : wordCount) {
        if (p.second > 1) {
            out << p.first << " (" << p.second << " kartai)\n";
            out << "  eilutes: ";
            for (int ln : wordLines[p.first]) {
                out << ln << " ";
            }
            out << "\n\n";
        }
    }

    out << "Rasti URL:\n";
    for (const auto& u : urls) {
        out << u << "\n";
    }

    cout << "Analize baigta. Rezultatai: outputs/words.txt" << endl;
    return 0;
}
