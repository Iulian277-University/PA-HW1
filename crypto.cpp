#include <bits/stdc++.h>
using namespace std;

// K = key (e.g: ?x?y)
// S = subsqeuence (e.g.: xy)

// S included in K
// K contains only characters from S

// N = len(K)
// L = len(S)

// Input
int N, L;
string K, S;
// Helper variables
vector<string> S_combinations;
vector<string> K_combinations; // posible keys

void read_input() {
    // ifstream fin("data.in");
    ifstream fin("crypto.in");
    fin >> N >> L;
    fin >> K;
    fin >> S;
    fin.close();
}

void print_output(int res) {
    // ofstream fout("data.out");
    ofstream fout("crypto.out");
    fout << res << "\n";
    fout.close();
}

int get_number_of_unknown_chs() {
    int cnt = 0;
    for (int i = 0; i < K.size(); ++i) {
        if (K[i] == '?')
            cnt++;
    }
    return cnt;
}

/**
 * Backtracking
 */
void get_S_combinations(string set, string prefix, int n, int k) {
    // Base case: k is 0,
    // print prefix
    if (k == 0)
    {
        S_combinations.push_back(prefix);
        return;
    }
 
    // One by one add all characters
    // from set and recursively
    // call for k equals to k-1
    for (int i = 0; i < n; i++)
    {
        string newPrefix;
         
        // Next character of input added
        newPrefix = prefix + set[i];
         
        // k is decreased, because
        // we have added a new character
        get_S_combinations(set, newPrefix, n, k - 1);
    }
}

void generate_K_combinations() {
    // For each `S_combination`
    for (int i = 0; i < S_combinations.size(); ++i) {
        int pos = 0;
        string key = K;
        // Complete the `key`
        for (int j = 0; j < N; ++j) {
            if (key[j] == '?') {
                key[j] = S_combinations[i][pos++];
            }
        }
        K_combinations.push_back(key);
    }
}

// Iterative DP function to find the number of times
// the second string occurs in the first string,
// whether continuous or discontinuous
// a = big string
// b = small string
int count(string a, string b)
{
    int m = a.length();
    int n = b.length();
 
    // Create a table to store results of sub-problems
    int lookup[m + 1][n + 1] = {{0}};
 
    // If first string is empty
    for (int i = 0; i <= n; ++i)
        lookup[0][i] = 0;
 
    // If second string is empty
    for (int i = 0; i <= m; ++i)
        lookup[i][0] = 1;
 
    // Fill lookup[][] in bottom up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // If last characters are same, we have two options:
            // 1. consider last characters of both strings in solution
            // 2. ignore last character of first string
            if (a[i - 1] == b[j - 1])
                lookup[i][j] = lookup[i - 1][j - 1] + lookup[i - 1][j];
            else // If last character are different, ignore last character of first string
                lookup[i][j] = lookup[i - 1][j];
        }
    }
 
    return lookup[m][n];
}

int get_result() {
    int unknown_chs = get_number_of_unknown_chs();
    // Check if the number of `?` is 0
    get_S_combinations(S, "", L, unknown_chs);
    // for (int i = 0; i < S_combinations.size(); ++i)
    //     cout << S_combinations[i] << "\n";

    // Generate all `K_combinations` (all posible keys)
    generate_K_combinations();

    sort(K_combinations.begin(), K_combinations.end());
    vector<string>::iterator ip = unique(K_combinations.begin(), K_combinations.end());
    K_combinations.resize(distance(K_combinations.begin(), ip));
    // for (int i = 0; i < K_combinations.size(); ++i)
        // cout << K_combinations[i] << "\n";

    int cnt = 0;
    for (int i = 0; i < K_combinations.size(); ++i) {
        cnt += count(K_combinations[i], S);
    }

    return cnt;
}

int main() {
    read_input();
    print_output(get_result());
    return 0;
}
