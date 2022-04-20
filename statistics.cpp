#include <bits/stdc++.h>
using namespace std;

// Input
int n;
vector<string> words;
// Global dominant ch
char CH_DOM;

void read_input() {
    ifstream fin("statistics.in");
    fin >> n;
    string word;
    for (int i = 0; i < n; ++i) {
        fin >> word;
        words.push_back(word);
    }
    fin.close();
}

void print_output(int max_words) {
    ofstream fout("statistics.out");
    fout << max_words << "\n";
    fout.close();
}

/**
 * This function counts the number of occurences
 * of a given character `ch` in a string `str`
 * Time complexity:  O(n)
 * Space complexity: O(1)
 */
int count_occ(string str, char ch) {
    double cnt = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ch)
            cnt++;
    }
    return cnt;
}

/**
 * This is a comparator used for sorting the strings
 * desending by `freq` and ascending by `length`
 * `freq` is defined as being the difference between
 * (the occurences of the dominant character) and (other characters) 
 * Time complexity:  O(n)
 * Space complexity: O(1)
 */
bool comparator(string s1, string s2) {
    int occ1 = count_occ(s1, CH_DOM);
    int occ2 = count_occ(s2, CH_DOM);

    int freq1 = occ1 - (s1.length() - occ1);
    int freq2 = occ2 - (s2.length() - occ2);

    // Sort descending by `freq`
    if (freq1 > freq2)
        return true;
    else if (freq1 < freq2)
        return false;

    // Then ascending by `length`
    return s1.length() < s2.length();
}

/**
 * This function computes the dominant character from a given string
 * Time complexity:  O(ALPHABET_SIZE)
 * Space complexity: O(1)
 */ 
pair<int, int> get_dominant_ch(string word) {
    // Create a vector of frequencies
    vector<int> chs_dom_word(26, 0);
    for (int i = 0; i < word.length(); ++i) {
        chs_dom_word[word[i] - 'a']++;
    }

    // Get the most frequent chracter from the given `word`
    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (chs_dom_word[i] > max_freq) {
            max_freq = chs_dom_word[i];
            max_idx = i;
        }
    }

    // Check `dominant character` condition
    int is_dominant;
    if (max_freq <= word.length() / 2)
        is_dominant = 0;
    else
        is_dominant = 1;

    return make_pair(max_idx, is_dominant);
}

/**
 * This function checks if a given `word` has the 
 * global dominant character `CH_DOM` present in it
 * Time complexity:  O(n)
 * Space complexity: O(1)
 */ 
bool has_dominant_ch(string word) {
    pair<int, int> dominant = get_dominant_ch(word);
    return (dominant.second != 0) && ((char) (dominant.first + 'a') == CH_DOM);
}

int get_result() {
    // Letters from `a` to `z`
    vector<int> global_dom_ch(26, 0);

    // Compute the `global_dominant_character` (over all words)
    for (int i = 0; i < n; ++i) {
        //   idx  count
        pair<int, int> curr_dom = get_dominant_ch(words[i]);
        global_dom_ch[curr_dom.first] += curr_dom.second;
    }

    // Get the most frequent chracter over all words
    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (global_dom_ch[i] > max_freq) {
            max_freq = global_dom_ch[i];
            max_idx = i;
        }
    }

    // We determined the most `global_dominant_character` over all words
    CH_DOM = (char) (max_idx + 'a');

    // Sort the words using this `comparator`
    sort(words.begin(), words.end(), comparator);

    // Concatenate words until we run out of a dominant character
    int max_words = 0;
    string max_str = "";
    for (int i = 0; i < n; ++i) {
        max_str += words[i];
        max_words++;
        if (!has_dominant_ch(max_str))
            return max_words - 1;
    }

    return n;
}


int main() {
    read_input();
    print_output(get_result());
    return 0;
}
