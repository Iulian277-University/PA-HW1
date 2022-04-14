#include <bits/stdc++.h>
using namespace std;

struct Object {
    int weight; // operations
    int points; // price (reward)

    Object(int _weight, int _points)
    : weight(_weight)
    , points(_points) { }
};

// Input
int n, k;
vector<int> target;
vector<int> points;
//
vector<int> operations;
vector<int> req_op;

void read_input() {
    ifstream fin("data.in");
    // ifstream fin("prinel.in");
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
    ofstream fout("data.out");
    // ofstream fout("prinel.out");
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

/* [TODO]: Improve this function */
int get_largest_divisor(int x) {
    for (int i = 2; i <= x; ++i) {
        if (x % i == 0)
            return x / i;
    }
    return -1;
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
    for (int i = 3; i <= operations.size(); ++i)
        operations[i] = 1 + operations[i - get_largest_divisor(i)];
}

int get_result() {
    return -1;    
}

bool comparator(Object &a, Object &b) {
    return 1.0 * a.weight / a.points < 1.0 * b.weight / b.points;
}

int main() {
    read_input();
    compute_required_operations_dp();

    for (int i = 0; i < n; ++i)
        req_op.push_back(operations[target[i]]);

    // for (int i = 0; i < n; ++i)
    //     cout << target[i] << " : " << req_op[i] << "\n";

    // Create the objects
    vector<Object> objs;
    for (int i = 0; i < n; ++i)
        objs.push_back(Object(operations[target[i]], points[i]));

    // for (int i = 0; i < n; ++i) {
    //     cout << objs[i].weight << " : " << objs[i].points << "\n";
    // }


    /* [TODO]: Change to continous knapsack problem */
    /* https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-03 */

    // Sort ascending by the fraction `req_op / points`
    sort(objs.begin(), objs.end(), comparator);

    for (int i = 0; i < n; ++i)
        cout << objs[i].points << " ";
    cout << "\n";

    for (int i = 0; i < n; ++i)
        cout << objs[i].weight << " ";
    cout << "\n";

    for (int i = 0; i < n; ++i)
        cout << 1.0 * objs[i].points / objs[i].weight << " ";
    cout << "\n";

    // k - maximum operations (max capacity from the knapsack problem)
    int maximum = 0;
    for (int i = 0; i < n; ++i) {
        if (k == 0)
            break;
        
        if (objs[i].weight <= k) {
            maximum += objs[i].points;
            k -= objs[i].weight;
        }
    }

    // cout << maximum << "\n";

    print_output(maximum);
    return 0;
}



/* [TODO]: Change to `dp` instead of `recursion` */
// int required_operations(int x) {
//     if (x == 0)
//         return -1;
//     if (x == 1)
//         return 0;
//     if (x == 2)
//         return 1;

//     return 1 + required_operations(x - get_largest_divisor(x));
// }

