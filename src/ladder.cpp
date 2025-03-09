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
    if (abs(len1 - len2) > d) return false;
    int difference = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            difference++;
            if (difference > d) return false;
            if (len1 > len2) {++i;}
            else if (len2 > len1) {++j;}
            else {
                ++i;
                ++j;
            }
        } else {
            ++i;
            ++j;
        }
    }
    difference += abs(len1 - len2);
    return difference <= d;

}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1 == word2) return true;
    int len1 = word1.length(), len2 = word2.length(), i = 0, j = 0;
    if (abs(len1 - len2) > 1) return false;
    string shorter = (len1 < len2) ? word1 : word2;
    string longer = (len1 > len2) ? word1 : word2;
    bool difference = false;

    if (len1 == len2) {
        int difference_count = 0;
        for (int i = 0; i < len1; ++i) {
            if (word1[i] != word2[i]) {
                difference_count++;
                if (difference_count > 1) return false;
            }
        }
        return difference_count == 1;
    }
    while (i < shorter.length() && j < longer.length()) {
        if (shorter[i] != longer[j]) {
            if (difference) return false;
            difference = true;
            j++;
        } else {
            i++;
            j++;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word,
    const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (auto word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
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
    if (ladder.size() == 0) cout << "No ladder found" << endl;
    cout << "Word ladder found: ";
    for(const auto &word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}
