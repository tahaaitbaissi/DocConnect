#include "Utils.h"
#include <sstream>

// Split a string by a delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Join a vector of strings with a delimiter
string join(const vector<string>& elements, const string& delimiter) {
    ostringstream result;
    for (size_t i = 0; i < elements.size(); ++i) {
        result << elements[i];
        if (i < elements.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}
