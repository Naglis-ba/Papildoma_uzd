#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

string trimEndPunct(string s) {
    while (!s.empty() && ispunct((unsigned char)s.back()) && s.back() != '/')
        s.pop_back();
    return s;
}

bool startsWith(const string& s, const string& prefix) {
    return s.rfind(prefix, 0) == 0;
}

int main() {
    std::string failas;
    failas = "input2.txt";
    ifstream in(failas);
    if (!in) {
        cout << "Cannot open " << failas << "\n";
        return 1;
    }

    vector<string> urls;
    string w;

    while (in >> w) {
        w = trimEndPunct(w);

        if (startsWith(w, "http://") || startsWith(w, "https://") || startsWith(w, "www.")) {
            urls.push_back(w);
        }
    }

    cout << "Found URLs:\n";
    for (int i = 0; i < (int)urls.size(); i++) {
        cout << i + 1 << ". " << urls[i] << "\n";
    }
}