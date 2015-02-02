// File: trimQuotes.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-01
// Purpose: function to trim " from both sides of a string,
// and replace "" with ".

#include <string>

using namespace std;

void trimQuotes(string& t) {
    if (t[0] == '"') t = t.substr(1);
    if (t[t.length() - 1] == '"') t = t.substr(0, t.length() - 1);
    size_t found = t.find("\"\"");
    while (found != string::npos) {
        t = t.erase(found, 1);
        found = t.find("\"\"");
    }
}
