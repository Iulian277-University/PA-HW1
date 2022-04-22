#include <bits/stdc++.h>
using namespace std;

#define MOD ((int)1e9 + 7)

// K = key (e.g: ?x?y)
// S = subsequence (e.g.: xy)

// S included in K
// K contains only characters from S

// N = len(K)
// L = len(S)

// Input
int N, L;
string K, S;
// Helper variables
vector<string> S_combinations;  // Combination of subsequences
vector<string> K_combinations;  // Possible keys

void read_input() {
    ifstream fin("crypto.in");
    fin >> N >> L;
    fin >> K;
    fin >> S;
    fin.close();
}

void print_output(int res) {
    ofstream fout("crypto.out");
    fout << res << "\n";
    fout.close();
}

/**
 * This function counts the number of `?` characters in a key `K`
 * Time complexity:  O(n)
 * Space complexity: O(1)
 */
int get_number_of_unknown_chs() {
    int cnt = 0;
    for (int i = 0; i < K.size(); ++i) {
        if (K[i] == '?')
            cnt++;
    }
    return cnt;
}

/**
 * This function generates all possible combinations of sequences (bkt)
 * Time complexity:  O(2^n)
 * Space complexity: O(1)
 */
void get_S_combinations(string domain, string prefix, int n, int k) {
    // Base case
    if (k == 0) {
        S_combinations.push_back(prefix);
        return;
    }

    // One by one add all characters from set and recursively call
    for (int i = 0; i < n; i++) {
        string prefix_aux;

        // Add next character from domain
        prefix_aux = prefix + domain[i];

        // k - 1 because we added a character
        get_S_combinations(domain, prefix_aux, n, k - 1);
    }
}

/**
 * This function completes the `?` of a key with characters of each sequence
 * Time complexity:  O(n * m)
 * Space complexity: O(n)
 */
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

/**
 * This function computes a dp matrix to find the number of times
 * the `small_string` subsequence occurs in the `big_string`
 * Time complexity:  O(n * m)
 * Space complexity: O(n * m)
 */
int count(string big_string, string small_string) {
    int m = big_string.length();
    int n = small_string.length();

    int dp[m + 1][n + 1] = {{0}};

    // First string empty
    for (int i = 0; i <= n; ++i)
        dp[0][i] = 0;

    // Second string empty
    for (int i = 0; i <= m; ++i)
        dp[i][0] = 1;

    // Complete the matrix
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // If last characters are the same
            // (1) Consider last characters of both strings
            // (2) Ignore   last character  of `big_string`
            if (big_string[i - 1] == small_string[j - 1])
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
            // If last chs are different -> Ignore last ch of `big_string`
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[m][n] % MOD;
}

int get_result() {
    // Generate all `S_combinations` (all possible subsequences)
    int unknown_chs = get_number_of_unknown_chs();
    get_S_combinations(S, "", L, unknown_chs);

    // Generate all `K_combinations` (all possible keys)
    generate_K_combinations();

    // Don't store duplicates in the `K_combinations` vector
    sort(K_combinations.begin(), K_combinations.end());
    vector<string>::iterator ip = unique(K_combinations.begin(),
                                         K_combinations.end());
    K_combinations.resize(distance(K_combinations.begin(), ip));

    // Generate the desired output
    int cnt = 0;
    for (int i = 0; i < K_combinations.size(); ++i)
        cnt = (cnt + count(K_combinations[i], S)) % MOD;
    return cnt % MOD;
}

int main() {
    read_input();
    print_output(get_result());
    return 0;
}
