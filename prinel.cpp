#include <bits/stdc++.h>
using namespace std;

// Input
int n, k;
vector<int> target;
vector<int> points;
// Helper vectors
vector<int> operations;
vector<int> req_ops;

void read_input() {
    // ifstream fin("data.in");
    ifstream fin("prinel.in");
    fin >> n >> k;

    int x;
    for (int i = 0; i < n; ++i) {
        fin >> x;
        target.push_back(x);
    }

    for (int i = 0; i < n; ++i) {
        fin >> x;
        points.push_back(x);
    }

    fin.close();
}

void print_output(int res) {
    // ofstream fout("data.out");
    ofstream fout("prinel.out");
    fout << res << "\n";
    fout.close();
}

/**
 * This function returns the maximum element from a given vector
 * Time complexity:  O(n)
 * Space complexity: O(1)
*/
int get_max_of_vector(vector<int> arr) {
    int max = -1;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

/**
 * This function returns the divisors of a given number `x`
 * Time complexity:  O(sqrt(n))
 * Space complexity: O(n), but in practice we can consider it O(n^(1/3))
 * [https://codeforces.com/blog/entry/14463]
*/
vector<int> get_divisors(int x) {
    vector<int> divisors;
    for (int i = 1; i <= sqrt(x); ++i) {
        if (x % i == 0) {
            if (x / i == i)
                divisors.push_back(i);
            else {
                divisors.push_back(i);
                divisors.push_back(x / i);
            }            
        }
    }
    return divisors;
}

/**
 * [TODO]: Doc
*/
void compute_required_operations_dp() {
    // Initialize the `operations` array with zeros
    int max_el_vect_a = get_max_of_vector(target);
    for (int i = 0; i <= max_el_vect_a; ++i)
        operations.push_back(0);

    // Base cases
    operations[0] =  INT_MAX;
    operations[1] =  0;
    operations[2] =  1;

    // Complete the `operations` array, using the following recurence:
    // operations[i] = 1 + min(dp[i - div_i]), where `div_i` are all divisors of `i`,
    // excluding itself (that's the reason of setting operations[0] to `INT_MAX`)
    for (int i = 3; i <= operations.size(); ++i) {
        int min_op = INT_MAX;
        vector <int> divisors = get_divisors(i);
        for (int j = 0; j < divisors.size(); ++j)
            min_op = min(min_op, operations[i - divisors[j]]);
        operations[i] = 1 + min_op;
    }
}

/**
 * [TODO]: Doc
 * @param
 * @return
*/
int knap_sack(int n, int W, vector<int> &weights, vector<int> &prices)
{
    // dp[i] stores the profit with knapsack capacity `i`
    // Initially the profit with `0-to-W` capacity is 0 
    int dp[W + 1] = {0};
 
    // Iterate through all the items, then traverse `dp` array from right to left
    // This will find out the maximum of 2 things: (1) `dp[cap]` and (2) `dp[cap - weights[i]] + prices[i]`
    // (1) [Excluding the i-th item price]
    // (2) [Including the i-th item price] and [the profit with `knapsack_cap - ith element weight`]
    for(int i = 0; i < n; ++i)
        for(int cap = W; cap >= weights[i]; --cap)
            dp[cap] = max(dp[cap], dp[cap - weights[i]] + prices[i]);
    
    // Return the maximum profit
    return dp[W];
}

/* [TODO]: Doc */
int get_result() {
    compute_required_operations_dp();

    // Vector of `required operations` (only the numbers for the current testcase)
    for (int i = 0; i < n; ++i)
        req_ops.push_back(operations[target[i]]);

    return knap_sack(n, k, req_ops, points);
}


int main() {
    read_input();
    print_output(get_result());
    return 0;
}
