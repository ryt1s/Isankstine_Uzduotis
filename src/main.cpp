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

    if (word.empty() || word[0] == '.') return false;

    size_t dotPos = word.find('.');
    if(dotPos == string::npos) return false;
      
    string before = word.substr(0, dotPos);
    string after = word.substr(dotPos + 1);

    for (char c : before) {
        if (!isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    if (after.length() <2) return false;
    for (char c : after) {
        if (!isalpha(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return true;
}

string toLower(const string& s) {
    string result = s;
    for (char& c : result) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return result;
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
                continue;
            }
            word = toLower(word);

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
            out << p.first << " (" << p.second << " kartai)\n ";
            out << " eiutes: ";
            for (int ln : wordLines[p.first]) {
                out << ln << " ";
            }
            out << "\n\n";
        }
    }

    out << "\nRasti URL : \n";
    for (const auto& u : urls) {
        out << u << "\n";
    }

    cout << "Analize baigta. Rezultatai: outputs/words.txt" << endl;
    return 0;
}
