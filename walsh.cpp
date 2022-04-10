#include <bits/stdc++.h>
using namespace std;

struct Position
{
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

void get_result(int n, int x, int y) {
    res.push_back(-1);
}

int main() {
    read_input();
    for (int i = 0; i < k; ++i)
        get_result(n, positions[i].x, positions[i].y);
    print_output();
    return 0;
}
