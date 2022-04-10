#include <bits/stdc++.h>
using namespace std;

// Input
int n;
vector<string> words;
// Output
int MAX_WORDS = -1;

// letters from `a` to `z`
vector<int> chs_dom(26, 0);
// global dominant ch
char CH_DOM;
//

void read_input() {
    ifstream fin("data.in");
    fin >> n;
    string word;
    for (int i = 0; i < n; ++i) {
        fin >> word;
        words.push_back(word);
    }
    fin.close();
}

void print_output() {
    ofstream fout("data.out");
    fout << MAX_WORDS << "\n";
    fout.close();
}

char get_dominant_ch(string word) {
    vector<int> chs_dom_word(26, 0);
    for (int i = 0; i < word.length(); ++i) {
        chs_dom_word[word[i] - 'a']++;
    }

    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (max_freq < chs_dom_word[i]) {
            max_freq = chs_dom_word[i];
            max_idx = i;
        }
    }

    return (max_idx + 'a');
}

double count_occ(string str, char ch) {
    double cnt = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ch)
            cnt++;
    }
    return cnt;
}

bool comparator(string s1, string s2) {
    double freq1 = 1.0 * count_occ(s1, CH_DOM) / (1.0 * s1.length());
    double freq2 = 1.0 * count_occ(s2, CH_DOM) / (1.0 * s2.length());

    // sort descending by `freq` and ascending by `length`
    // if (freq1 == freq2)
        // return (s1.length() - s2.length());
    // return (freq2 - freq1);
    if (freq1 > freq2)
        return true;
    return false;
}

int get_result() {
    vector<int> global_dom_ch(26, 0);
    for (int i = 0; i < n; ++i) {
        char curr_ch_dom = get_dominant_ch(words[i]);
        global_dom_ch[curr_ch_dom - 'a']++;
    }

    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (max_freq < global_dom_ch[i]) {
            max_freq = global_dom_ch[i];
            max_idx = i;
        }
    }

    // we determined the most dominant global ch
    CH_DOM = (char) (max_idx + 'a');

    sort(words.begin(), words.end(), comparator);

    for (int i = 0; i < n; ++i)
        cout << words[i] << "\n";

    int max_words = 0;
    string max_str = "";
    for (int i = 0; i < n; ++i) {
        max_str += words[i];
        max_words++;
        if (get_dominant_ch(max_str) != CH_DOM)
            return max_words - 1;
    }
}

int main() {
    read_input();
    MAX_WORDS = get_result();
    print_output();
    return 0;
}
