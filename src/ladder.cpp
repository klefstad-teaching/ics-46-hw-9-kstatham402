#include "ladder.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error (" << word1 << " & " << word2 << "): " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.length(), len2 = str2.length();
    int minLen = std::min(len1, len2);
    if (abs(len1 - len2) > d) return false;
    int difference = 0;
    for (int i = 0; i < minLen; i++) {
        if (str1[i] != str2[i]) {
            difference++;
            if (difference > d) return false;
        }
    }
    difference += abs(len1 - len2);
    return difference <= d;

}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word,
    const string& end_word, const set<string>& word_list) {
    set<string> unvisited_words = word_list;
    queue<vector<string>> paths;
    paths.push({begin_word});
    while (!paths.empty()) {
        int level_size = paths.size();
        set<string> remove_words;
        for (int i = 0; i < level_size; i++) {
            vector<string> path = paths.front();
            paths.pop();
            string last_word = path.back();
            if (last_word == end_word) return path;
            for (const string& word : unvisited_words) {
                if (is_adjacent(last_word, word)) {
                    vector<string> new_path = path;
                    new_path.push_back(word);
                    paths.push(new_path);
                    remove_words.insert(word);
                }
            }
        }
        for (const string& word : remove_words) {
            unvisited_words.erase(word);
        }
    }
    return {};
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Cannot open file " << file_name << endl;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0) return;
    for(const auto &word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}
void verify_word_ladder() {
    //TODO: What should this even do?
}
