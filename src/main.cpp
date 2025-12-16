#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

int main() {
    ifstream in("data/input.txt");
    if (!in) {
        cerr << "Nepavyko atidaryti data/input.txt" << endl;
        return 1;
    }

    map<string, int> wordCount;

    string line;
    while (getline(in, line)) {
        for (char& c : line) {
            if (!isalnum(static_cast<unsigned char>(c))) c = ' ';
        }

        stringstream ss(line);
        string word;

        while (ss >> word) {
            wordCount[word]++;
        }
    }

    ofstream out("outputs/words.txt");
    if (!out) {
        cerr << "Nepavyko sukurti outputs/words.txt" << endl;
        return 1;
    }

    for (const auto& p : wordCount) {
        if (p.second > 1) {
            out << p.first << " : " << p.second << "\n";
        }
    }

    cout << "Rezultatai issaugoti i outputs/words.txt" << endl;
    return 0;
}
