#include <bits/stdc++.h>
using namespace std;

// Constants
#define MAX_N 2000

// Input
int n;  // Number of cities
vector<int> coord;  // Coordinates of each city (in ascending order)
int q;  // Number of questions
vector<int> dealers;

// Helper vectors
vector<int> costs;
vector<int> max_line;

// Ouput
vector<int> res;

void read_input() {
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
    ofstream fout("regele.out");
    for (int i = 0; i < q; ++i)
        fout << res[i] << "\n";
    fout.close();
}

/**
 * This function computes the activation cost for each city
 * Time complexity:  O(n)
 * Space complexity: O(n)
 */ 
void compute_activation_costs() {
    // 1-indexing
    costs.push_back(-1);

    // First cost
    costs.push_back(coord[2] - coord[1]);

    for (int i = 2; i < n; ++i)
        costs.push_back((coord[i] - coord[i - 1]) + (coord[i + 1] - coord[i]));

    // Last cost
    costs.push_back(coord[n] - coord[n - 1]);
}

/**
 * This function computes the dp "matrix" line by line
 * dp[i][j] = required dealers for activating `i` cities
 * starting from the `j` position in the array of cities
 * 
 * For each line (i-th line -> activate `i` cities),
 * compute the maximum element for that line, because we need to calculate
 * the required number of dealers for activating any combination of `i` cities
 * 
 * Time complexity:  O(n^2)
 * Space complexity: O(n)
 */ 
void compute_dp_efficient() {
    // 1-indexing
    int curr_v[MAX_N + 1];
    int old_v[MAX_N + 1];

    max_line.push_back(-1);

    int curr_max = -1;
    // First row (line) of the matrix
    for (int i = 1; i <= n; ++i) {
        curr_v[i] = costs[i];
        old_v[i] = curr_v[i];
        curr_max = max(curr_max, curr_v[i]);
    }
    max_line.push_back(curr_max);

    // From second row, going down (line by line)
    // After n/2 the rows are repeting
    int i = 2;
    for (; i <= n / 2; ++i) {
        // Complete the row, starting from right to left
        // This allows me to store the `max_ans` at each step
        // instead of calculating it each time for (j+2) to (n)
        int max_ans  = -1;
        int curr_max = -1;
        for (int j = n; j >= 1; --j) {
            if (j == n || j == n - 1)
                continue;

            max_ans = max(max_ans, old_v[j + 2]);
            curr_v[j] = costs[j] + max_ans;

            curr_max = max(curr_max, curr_v[j]);
        }
        max_line.push_back(curr_max);

        // Update `old` vector
        for (int j = 1; j <= n; ++j)
            old_v[j] = curr_v[j];
    }

    // After n/2 rows are repeting, so we can
    // automatically complete the `max` for each line
    for (int j = i; j <= n; ++j)
        max_line.push_back(max_line[i - 1]);
}

/**
 * This is a modified binary search with 2 cases:
 * If the `target` doesn't exist in the `arr`
 *   -> Return the idx of largest element smaller than `target`
 * Otherwise 
 *   -> Return the largest idx of the `target` ("rightmost `target`")
 * 
 * Time complexity:  O(n*log(n))
 * Space complexity: O(1)
 */
int find_max_dealers(vector<int> arr, int target) {
    int left = 1;  // 1-indexing
    int right = arr.size() - 1;
    int res = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return res;
}


int main() {
    read_input();

    compute_activation_costs();
    compute_dp_efficient();
    // Compute the answer for each question
    for (int i = 0; i < q; ++i)
        res.push_back(find_max_dealers(max_line, dealers[i]));

    print_output();
    return 0;
}
