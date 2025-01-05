#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>

using namespace std;

// Split a string by a delimiter
vector<string> split(const string& s, char delimiter);

// Join a vector of strings with a delimiter
string join(const vector<string>& elements, const string& delimiter);

#endif // UTILS_H_
