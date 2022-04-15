#include <bits/stdc++.h>
using namespace std;

// Input
int n;
vector<string> words;
// Global dominant ch
char CH_DOM;

void read_input() {
    ifstream fin("statistics.in");
    // ifstream fin("data.in");
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
    // ofstream fout("data.out");
    fout << max_words << "\n";
    fout.close();
}

int count_occ(string str, char ch) {
    double cnt = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ch)
            cnt++;
    }
    return cnt;
}

bool comparator(string s1, string s2) {
    int occ1 = count_occ(s1, CH_DOM);
    int occ2 = count_occ(s2, CH_DOM);

    int freq1 = occ1 - (s1.length() - occ1);
    int freq2 = occ2 - (s2.length() - occ2);

    // Sort descending by `freq` and ascending by `length`
    if (freq1 > freq2)
        return true;
    return false;
}

pair<int, int> get_dominant_ch(string word) {
    vector<int> chs_dom_word(26, 0);
    for (int i = 0; i < word.length(); ++i) {
        chs_dom_word[word[i] - 'a']++;
    }

    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (chs_dom_word[i] > max_freq) {
            max_freq = chs_dom_word[i];
            max_idx = i;
        }
    }

    // Check `dominant character` condition
    if (max_freq <= word.length() / 2)
        max_freq = 0;
    else
        max_freq = 1;
    return make_pair(max_idx, max_freq);
}

bool has_dominant_ch(string word) {
    pair<int, int> dominant = get_dominant_ch(word);
    // cout << word << ":" << dominant.first << "**" << dominant.second << "\n";
    return (dominant.second != 0) && ((char) (dominant.first + 'a') == CH_DOM);
}

int get_result() {
    // Letters from `a` to `z`
    vector<int> global_dom_ch(26, 0);

    // For each `word`
    for (int i = 0; i < n; ++i) {
        //   idx  count
        pair<int, int> curr_dom = get_dominant_ch(words[i]);
        global_dom_ch[curr_dom.first] += curr_dom.second;
    }

    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (global_dom_ch[i] > max_freq) {
            max_freq = global_dom_ch[i];
            max_idx = i;
        }
    }

    // We determined the most `dominant global ch` over all words
    CH_DOM = (char) (max_idx + 'a');

    sort(words.begin(), words.end(), comparator);

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
