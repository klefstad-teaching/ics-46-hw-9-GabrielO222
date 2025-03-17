#include "ladder.h"
#include <cassert>
#include <vector>

void error(string word1, string word2, string msg) {
    cerr << "Error: Word 1 is " << word1 << " and word 2 is " << word2 << ": " << msg << endl;
}

int levenshtein(string a, string b) {
    size_t sizeA = a.size(), sizeB = b.size();
    if (sizeB == 0) return sizeA;
    if (sizeA == 0) return sizeB;
    if (a[0] == b[0]) return levenshtein(a.substr(1), b.substr(1));
    return 1 + min(levenshtein(a.substr(1), b), min(levenshtein(a, b.substr(1)), levenshtein(a.substr(1), b.substr(1))));
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d) {
    return levenshtein(str1, str2) <= d;
}

bool is_adjacent(const string &word1, const string &word2) {
    int len_diff = std::abs(static_cast<int>(word1.size()) - static_cast<int>(word2.size()));
    if (len_diff > 1)
        return false;
    else if (len_diff == 0) {
        int diff_count = 0;
        size_t n = word1.size();
        for (size_t i = 0; i < n; ++i) {
            if (word1[i] != word2[i]) {
                ++diff_count;
                if (diff_count > 1)
                    return false;
            }
        }
        return diff_count <= 1;
    }

    string longer = (word1.size() > word2.size()) ? word1 : word2;
    string shorter = (word1.size() > word2.size()) ? word2 : word1;

    for (int i = 0, j = 0; i < longer.size() && j < shorter.size(); ++i, ++j) {
        if (longer[i] != shorter[j]) {
            return longer.substr(i + 1) == shorter.substr(j);
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string &begin_word, const string &end_word, const set<string> &word_list) {
    queue<vector<string>> ladder_queue;
    set<string> visited;
    vector<string> new_ladder;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];
        for (const string &word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder;
                    copy(ladder.begin(), ladder.end(), back_inserter(new_ladder));
                    new_ladder.push_back(word);
                    if (word == end_word)
                        return new_ladder;
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return vector<string>();
}

void load_words(set<string> &word_list, const string &file_name) {
    ifstream in(file_name);
    for (string word; in >> word;) {
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string> &ladder) {
    size_t n = ladder.size();
    if (n > 0) {
        for (int i = 0; i < n; ++i)
            cout << ladder[i] << " ";
    }
    else
        cout << "No word ladder found.";
    cout << endl;
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<vector<string>> results;
    results.push_back(generate_word_ladder("cat", "dog", word_list));
    results.push_back(generate_word_ladder("marty", "curls", word_list));
    results.push_back(generate_word_ladder("code", "data", word_list));
    results.push_back(generate_word_ladder("work", "play", word_list));
    results.push_back(generate_word_ladder("sleep", "awake", word_list));
    results.push_back(generate_word_ladder("car", "cheat", word_list));
    for (auto result : results) {
        print_word_ladder(result);
    }
}