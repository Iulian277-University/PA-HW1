#include <bits/stdc++.h>
using namespace std;

// Input
int n, k;
vector<int> target;
vector<int> points;
//
vector<int> operations;
vector<int> req_op;

void read_input() {
    // ifstream fin("data.in");
    ifstream fin("prinel.in");
    fin >> n >> k;

    int x;
    // target.push_back(-1); // for 1-indexing
    for (int i = 1; i <= n; ++i) {
        fin >> x;
        target.push_back(x);
    }

    // points.push_back(-1); // for 1-indexing
    for (int i = 1; i <= n; ++i) {
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

int get_max_of_vector(vector<int> arr) {
    int max = -1;
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

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

void compute_required_operations_dp() {
    int max_el_vect_a = get_max_of_vector(target);
    for (int i = 0; i <= max_el_vect_a; ++i)
        operations.push_back(0);
    // Base cases
    operations[0] = -1;
    operations[1] =  0;
    operations[2] =  1;
    // Complete the `operations` array (dp)
    for (int i = 3; i <= operations.size(); ++i) {
        int min_op = INT_MAX;
        vector <int> divisors = get_divisors(i);
        for (int j = 0; j < divisors.size(); ++j) {
            if (divisors[j] != i)
                min_op = min(min_op, operations[i - divisors[j]]);
        }
        operations[i] = 1 + min_op;
    }
}

int get_result() {
    return -1;    
}

// n   = numărul de obiecte din colecție
// W   = capacitatea maximă a rucsacului
// (w[i], p[i]) = caracteristicile obiectului i (i = 1 : n)
int rucsac(int n, int W, vector<int> &w, vector<int> &p) {
    // dp este o matrice de dimensiune (n + 1) x (W + 1)
    // pentru că folosim dp[0][*] pentru mulțimea vidă
    //                   dp[*][0] pentru situația în care ghiozdanul are capacitate 0
    vector< vector<int> > dp(n + 1, vector<int>(W + 1, 0));
 
    // cazul de bază
    for (int cap = 0; cap <= W; ++cap) {
        dp[0][cap] = 0;
    }
 
    // cazul general
    for (int i = 1; i <= n; ++i) {
        for (int cap = 0; cap <= W; ++cap) {
            // nu folosesc obiectul i => e soluția de la pasul i - 1
            dp[i][cap] = dp[i-1][cap];
 
            // folosesc obiectul i, deci trebuie să rezerv w[i] unități în rucsac
            // înseamnă ca înainte trebuie să ocup maxim cap - w[i] unități
            if (cap - w[i] >= 0)
                dp[i][cap] = max(dp[i][cap], dp[i-1][cap - w[i]] + p[i]);
        }
    }
 
    return dp[n][W];
}

// val[] is for storing maximum profit for each weight
// wt[] is for storing weights
// n number of item
// W maximum capacity of bag
// dp[W+1] to store final result
int KnapSack(vector<int> &val, vector<int> &wt, int n, int W)
{
    // array to store final result
    //dp[i] stores the profit with KnapSack capacity "i"
    int dp[W+1];
     
    //initially profit with 0 to W KnapSack capacity is 0
    memset(dp, 0, sizeof(dp));
 
    // iterate through all items
    for(int i=0; i<n; i++)
        //traverse dp array from right to left
        for(int j=W; j>=wt[i]; j--)
            dp[j] = max(dp[j] , val[i] + dp[j-wt[i]]);
    /*above line finds out maximum of  dp[j](excluding ith element value)
      and val[i] + dp[j-wt[i]] (including ith element value and the
      profit with "KnapSack capacity - ith element weight") */   
    return dp[W];
}

int main() {
    read_input();
    compute_required_operations_dp();

    // Vector of `required operations`
    // req_op.push_back(-1); // for 1-indexing
    for (int i = 0; i < n; ++i)
        req_op.push_back(operations[target[i]]);

    // for (int i = 0; i < n; ++i)
        // cout << target[i] << ":" << req_op[i] << "\n";

    // int res = rucsac(n, k, req_op, points);
    int res = KnapSack(points, req_op, n, k);
    print_output(res);

    return 0;
}
