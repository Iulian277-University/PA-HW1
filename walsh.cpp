#include <bits/stdc++.h>
using namespace std;

// Position in the matrix: (x, y) coordinates
struct Position {
    int x;
    int y;

    Position(int _x, int _y)
    : x(_x)
    , y(_y) { }
};

// Input
int n, k;
vector<Position> positions;
// Output
vector<int> res;

void read_input() {
    int x, y;
    ifstream fin("walsh.in");
    fin >> n >> k;
    for (int i = 0; i < k; ++i) {
        fin >> x >> y;
        positions.push_back(Position(x, y));
    }
    fin.close();
}

void print_output() {
    ofstream fout("walsh.out");
    for (int i = 0; i < k; ++i)
        fout << res[i] << "\n";
    fout.close();
}

/**
 * Functions to determine the position of a given point (x, y)
 * relative to the center of the big matrix
 * (top_left, top_right, bottom_left, bottom_right)
 * Time complexity:  O(1)
 * Space complexity: O(1)
 */
bool is_upper_left(int n, int x, int y) {
    return (x < n / 2 && y < n / 2);
}

bool is_upper_right(int n, int x, int y) {
    return (x < n / 2 && y >= n / 2);
}

bool is_lower_left(int n, int x, int y) {
    return (x >= n / 2 && y < n / 2);
}

bool is_lower_right(int n, int x, int y) {
    return (x >= n / 2 && y >= n / 2);
}

/**
 * This function recursively computes the desired result
 * Time complexity:  [TODO]
 * Space complexity: O(1)
 */ 
int walsh(int n, int x, int y) {
    // Base case: W_1 = [0]
    if (n == 1)
        return 0;

    // Choose a smaller matrix and recursively call the function
    if (is_upper_left(n, x, y))
        return walsh(n / 2, x, y);
    else if (is_upper_right(n, x, y))
        return walsh(n / 2, x, y - n / 2);
    else if (is_lower_left(n, x, y))
        return walsh(n / 2, x - n / 2, y);
    else if (is_lower_right(n, x, y))
        return 1 - walsh(n / 2, x - n / 2, y - n / 2);
}

void get_result(int n, int x, int y) {
    // Zero indexing
    x--, y--;
    res.push_back(walsh(n, x, y));
}

int main() {
    read_input();
    for (int i = 0; i < k; ++i)
        get_result(n, positions[i].x, positions[i].y);
    print_output();
    return 0;
}
