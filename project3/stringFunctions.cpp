// File: stringFunctions.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-04

#include <string>
#include <algorithm>

using namespace std;

// Trim " from both sides of a string, and replace instances of "" with ".
void trimQuotes(string& t) {
    if (t[0] == '"') t = t.substr(1);
    if (t[t.length() - 1] == '"') t = t.substr(0, t.length() - 1);
    size_t found = t.find("\"\"");
    while (found != string::npos) {
        t = t.erase(found, 1);
        found = t.find("\"\"");
    }
}

// a case insensitive string comparison function unaware of unicode
bool caseInsensitiveStrcmp(const string& str1, const string& str2) {
    if (str1.size() != str2.size()) 
        return false;
    for (unsigned int i = 0; i < str1.size(); i++) {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }
    return true;
}

string strToUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
