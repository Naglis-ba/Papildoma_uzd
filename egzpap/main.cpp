#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

bool isWordChar(unsigned char c) {
    return std::isalnum(c) || c == '\'';
}

void countFrequencies(const std::string& str, std::unordered_map<std::string, int>& freq) {
    std::ifstream in (str);
    std::string line;
    while (getline(in, line)) {
        string word;
        for (char c : line) {
            if(isWordChar(c)) 
            {
                word += std::tolower(c);
            } 
            else if (!word.empty()) 
            {
                freq[word]++;
                word.clear();
            }
        }
        if (!word.empty()) {
            freq[word]++;
        }
    }
}

void CrossRef(const string& filename,
              const unordered_map<string, int>& freq,
              unordered_map<string, vector<int>>& linesByWord) {

                ifstream in (filename);
                string line;
                int lineNumber = 0;
                while (getline(in, line)) {
                    lineNumber++;
                    string word;
                    for (char c : line) {
                        if(isWordChar(c)) {
                            word += std::tolower(c);
                        } else if (!word.empty()) {
                            auto it = freq.find(word);
                            if (it != freq.end() && it->second > 1) {
                                auto &vec = linesByWord[word];
                                if (vec.empty() || vec.back() != lineNumber) {
                                    vec.push_back(lineNumber);
                                }
                            }
                            word.clear();
                        }
                    }
                    if (!word.empty()) {
                        auto it = freq.find(word);
                        if (it != freq.end() && it->second > 1) {
                            auto &vec = linesByWord[word];
                            if (vec.empty() || vec.back() != lineNumber) {
                                vec.push_back(lineNumber);
                            }
                        }
                    }
                }

              }

int main() {
    std::unordered_map<std::string, int> freq;
    
    countFrequencies("input.txt", freq);

    std::vector<std::pair<std::string, int>> items;
    items.reserve(freq.size());
    for (auto &kv : freq) {
        if (kv.second > 1) items.push_back(kv);
    }

    std::sort(items.begin(), items.end(),
          [](auto &a, auto &b){
              if (a.second != b.second) return a.second > b.second;
              return a.first < b.first;
          });


    std::unordered_map<std::string, std::vector<int>> linesByWord;
    CrossRef("input.txt", freq, linesByWord);


    std::ofstream out("rezultatai.txt");
    for (auto &p : items) {
        out << p.first << " " << p.second << ":";

        auto it = linesByWord.find(p.first);
        if (it != linesByWord.end()) {
            auto &vec = it->second;
            for (size_t i = 0; i < vec.size(); ++i) {
                out << vec[i];
                if (i + 1 < vec.size()) out << ", ";
            }
        }
        out << "\n";
    }

}