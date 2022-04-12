#include <bits/stdc++.h>
using namespace std;

// Input
int n;
vector<string> words;

// global dominant ch
char CH_DOM;
int  CH_DOM_OCC;

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

double count_occ(string str, char ch) {
    double cnt = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ch)
            cnt++;
    }
    return cnt;
}

bool comparator(string s1, string s2) {
    // double freq1 = count_occ(s1, CH_DOM) / (1.0 * s1.length());
    // double freq2 = count_occ(s2, CH_DOM) / (1.0 * s2.length());

    double freq1 = count_occ(s1, CH_DOM) - (s1.length() - count_occ(s1, CH_DOM));
    double freq2 = count_occ(s2, CH_DOM) - (s2.length() - count_occ(s2, CH_DOM));

    // Sort descending by `freq` and ascending by `length`
    if (freq1 > freq2)
        return true;
    if (freq1 < freq2)
        return false;
    // eq freq
    if (s2.length() > s1.length())
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
    return make_pair(max_idx, max_freq);
}

bool has_dominant_ch(string word) {
    pair<int, int> dominant = get_dominant_ch(word);
    // cout << word << ":" << dominant.first << "**" << dominant.second << "\n";
    return (dominant.second != 0) && ((char) (dominant.first + 'a') == CH_DOM);
}

int get_result() {
    // letters from `a` to `z`
    vector<int> global_dom_ch(26, 0);
    for (int i = 0; i < n; ++i) {
        //  idx  count
        pair<char, int> curr_dom = get_dominant_ch(words[i]);
        // cout << words[i] << "-" << (char) (curr_dom.first + 'a') << "\n";
        global_dom_ch[curr_dom.first] += curr_dom.second;
    }

    // return -1;

    int max_idx  = -1;
    int max_freq = -1;
    for (int i = 0; i < 26; ++i) {
        if (global_dom_ch[i] > max_freq) {
            max_freq = global_dom_ch[i];
            max_idx = i;
        }
    }

    // we determined the most `dominant global ch`
    CH_DOM = (char) (max_idx + 'a') ;
    // cout << CH_DOM << " " << global_dom_ch[max_idx] << "\n\n";

    sort(words.begin(), words.end(), comparator);

    // for (int i = 0; i < n; ++i)
    //     cout << words[i] << ":" << (double) get_dominant_ch(words[i]).second / (double) words[i].length() << "\n";

    // for (int i = 0; i < n; ++i)
    //     cout << words[i] << "\n";

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
    int res = get_result();
    // cout << "res:" << res << "\n";
    print_output(get_result());
    return 0;
}