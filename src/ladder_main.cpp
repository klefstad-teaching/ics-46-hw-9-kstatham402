#include "ladder.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
// g++ -std=c++17 -o ladder_main src/ladder_main.cpp src/ladder.cpp

void testLadder(const string &begin_word, const string &end_word, set<string> & word_list) {
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    cout << "Printing ladder list:" << endl;
    print_word_ladder(ladder);

}

void test_edit_distance_within() {
    std::cout << "Test 1: " << (edit_distance_within("apple", "bapple", 1) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 2: " << (edit_distance_within("apple", "appl", 1) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 3: " << (edit_distance_within("apple", "applz", 1) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 4: " << (edit_distance_within("apple", "apricot", 2) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 5: " << (edit_distance_within("apple", "apple", 0) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 6: " << (edit_distance_within("apple", "applz", 2) ? "Passed" : "Failed") << std::endl;
    std::cout << "Test 7: " << (edit_distance_within("apple", "banana", 3) ? "Passed" : "Failed") << std::endl;
}


int main() {
    test_edit_distance_within();
    // set<string> word_list;
    // load_words(word_list, "src/words.txt");
    // testLadder("car", "cheat", word_list);
    // testLadder("code", "data", word_list);
    // testLadder("cat", "dog", word_list);
    // testLadder("marty", "curls", word_list);
    // testLadder("work", "play", word_list);
    // testLadder("sleep", "awake", word_list);
    return 0;
}
