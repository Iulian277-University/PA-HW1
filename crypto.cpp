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
// Output

void read_input() {
    ifstream fin("data.in");
    fin >> N >> L;
    fin >> K;
    fin >> S;
    fin.close();
}

void print_output(int res) {
    ofstream fout("data.out");
    fout << res << "\n";
    fout.close();
}

int get_result() {
    cout << N << " " << L << "\n";
    cout << K << "\n";
    cout << S << "\n";

    return -1;
}

int main() {
    read_input();
    print_output(get_result());
    return 0;
}
