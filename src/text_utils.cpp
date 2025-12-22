#include "text_utils.h"
#include <cctype>

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
