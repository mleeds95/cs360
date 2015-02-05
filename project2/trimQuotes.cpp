// File: trimQuotes.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-03

#include <string>

using namespace std;

// Trim " from both sides of a string, and replace instances of "" with ".
void StringData::trimQuotes(string& t) {
    if (t[0] == '"') t = t.substr(1);
    if (t[t.length() - 1] == '"') t = t.substr(0, t.length() - 1);
    size_t found = t.find("\"\"");
    while (found != string::npos) {
        t = t.erase(found, 1);
        found = t.find("\"\"");
    }
}
