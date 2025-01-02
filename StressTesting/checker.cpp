#include <bits/stdc++.h>

using namespace std;

// Input data
long long n;

int check(const string &tsol_path, const string &rsol_path) {
    // There is scanned data
    long long sol_res, res;

    ifstream testing_solution(tsol_path);
#define cin testing_solution
    {
        // scanning testing solution output
        cin >> sol_res;
    }
    testing_solution.close();

    ifstream right_solution(rsol_path);
#define cin right_solution
    {
        // scanning right solution output
        cin >> res;
    }
    right_solution.close();
#undef cin

    {
        // comparing outputs
        if (sol_res != res) {
            cout << "WA\n";
            cout << "Expected: " << res << '\n';
            cout << "Found: " << sol_res << '\n';
            return 1;
        }
    }
    cout << "OK\n";
    return 0;
}

int main(int argc, char *argv[]) {
#ifndef STRESS
    exit(-1);
#endif
    /*
     arguments:
     1) Input file path
     2) Output file path
     3) Testing solution output file path
     4) Right solution output file path
    */

    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    {
        // There you can scan input data if it's necessary
        cin >> n;
    }

    return check(argv[3], argv[4]);
}
