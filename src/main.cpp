#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <set>

using namespace std;

bool isURL(const string& word) {
    if (word.find("http://") == 0) return true;
    if (word.find("https://") == 0) return true;
    if (word.find("www.") == 0) return true;

    size_t dotPos = word.find('.');
    if (dotPos != string::npos && dotPos > 0 && dotPos < word.size() - 1) {
        return true;
    }

    return false;
}

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

        string originalLine = line;

        for (char& c : line) {
            if (!isalnum(static_cast<unsigned char>(c)) && c != '.' && c != ':' && c != '/') {
                c = ' ';
            }
        }

        stringstream ss(line);
        string word;

        while (ss >> word) {
            if (isURL(word)) {
                urls.insert(word);
            }

            if (isalnum(static_cast<unsigned char>(word[0]))) {
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

    out << "Zodziai, kurie kartojasi daugiau nei 1 karta : \n";
    for (const auto& p : wordCount) {
        if (p.second > 1) {
            out << p.first << " (" << p.second << ") : ";
            for (int ln : wordLines[p.first]) {
                out << ln << " ";
            }
            out << "\n";
        }
    }

    out << "\nRasti URL : \n";
    for (const auto& u : urls) {
        out << u << "\n";
    }

    cout << "Analize baigta. Rezultatai: outputs/words.txt" << endl;
    return 0;
}
