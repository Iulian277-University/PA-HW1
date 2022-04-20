#include <bits/stdc++.h>
using namespace std;

// Input
int n; // number of cities
vector<int> coord; // coordinates of each city (in ascending order)
int q; // number of questions
vector<int> dealers;

// Helper vector
vector<int> costs;

// Ouput
vector<int> res;
vector<int> max_line;

void read_input() {
    // ifstream fin("data.in");
    ifstream fin("regele.in");
    fin >> n;

    // 1-indexing
    coord.push_back(-1);
    int x;
    for (int i = 1; i <= n; ++i) {
        fin >> x;
        coord.push_back(x);
    }

    fin >> q;
    for (int i = 0; i < q; ++i) {
        fin >> x;
        dealers.push_back(x);
    }

    fin.close();
}

void print_output() {
    // ofstream fout("data.out");
    ofstream fout("regele.out");
    for (int i = 0; i < q; ++i)
        fout << res[i] << "\n";
    fout.close();
}

void compute_activation_costs() {
    // 1-indexing
    costs.push_back(-1);

    // first cost
    costs.push_back(coord[2] - coord[1]);

    for (int i = 2; i < n; ++i)
        costs.push_back((coord[i] - coord[i - 1]) + (coord[i + 1] - coord[i]));
    
    // last cost
    costs.push_back(coord[n] - coord[n - 1]);
}

void compute_dp_efficient() {
    // 1-indexing
    int v[n + 1];
    int old[n + 1];

    max_line.push_back(-1);

    int curr_max = -1;
    // first row (line) of the matrix
    for (int i = 1; i <= n; ++i) {
        v[i] = costs[i];
        old[i] = v[i];
        curr_max = max(curr_max, v[i]);
    }
    max_line.push_back(curr_max);

    // from second row, going down (line by line)
    int i = 2;
    for (; i <= n / 2; ++i) { // after n/2 the rows are repeting

        int max_ans  = -1;
        int curr_max = -1;
        for (int j = n; j >= 1; --j) {
            if (j == n || j == n - 1)
                continue;
            
            max_ans = max(max_ans, old[j + 2]);
            v[j] = costs[j] + max_ans;

            curr_max = max(curr_max, v[j]);
        }
        max_line.push_back(curr_max);

        // Update `old` vector
        for (int j = 1; j <= n; ++j)
            old[j] = v[j];
    }

    for (int j = i; j <= n; ++j)
        max_line.push_back(max_line[i - 1]);

//     for (int i = 1; i <= n; ++i)
//         cout << max_line[i] << " ";
//     cout << "\n";
}

int NextLargestBinSearch( int key, int data[], const int len )
{
    int low  = 1;
    int high = len;

    while( low <= high)
    {
        // To convert to Javascript:
        // var mid = low + ((high - low) / 2) | 0;
        int mid = low + ((high - low) / 2);

        if (data[mid] < key)      low  = mid + 1;
        else if (data[mid] > key) high = mid - 1;
        else return                      mid + 1;
    }

    if( high < 0 )
        return 0;   // key < data[0]
    else if( low > (len-1))
        return len; // key >= data[len-1]
    else
        return (low < high)
            ? low  + 1
            : high + 1;
}


int main() {
    read_input();

    compute_activation_costs();

    compute_dp_efficient();

    for (int i = 0; i < q; ++i)
        res.push_back(-1);


    // // Compute the results
    // for (int i = 0; i < q; ++i) {
    //     int idx = 0;
    //     for (int j = 1; j <= n; ++j) {
    //         if (max_line[j] <= dealers[i])
    //             idx = j;
    //     }
    //     res.push_back(idx);
    // }

    print_output();
    return 0;
}



// void compute_dp() {
//     // 1-indexed
//     int dp[n + 1][n + 1] = {{0}};

//     // complete the first row (line)
//     for (int j = 1; j <= n; ++j)
//         dp[1][j] = costs[j];

//     // from second row, going down (line by line)
//     for (int i = 2; i <= n; ++i) {
//         for (int j = 1; j <= n; ++j) {
//             if (j == n - 1 || j == n) {
//                 dp[i][j] = dp[i - 1][j];
//             } else {
//                 int max_ans = -1;
//                 for (int k = j + 2; k <= n; ++k)
//                     max_ans = max(max_ans, dp[i - 1][k]);
//                 dp[i][j] = costs[j] + max_ans;
//             }
//         }
//     }
// }
