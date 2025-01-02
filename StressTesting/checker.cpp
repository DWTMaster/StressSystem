#define _GLIBCXX_DEBUG
#define debug(x) cerr << __LINE__ << ": " << (#x) << " = " << (x) << endl

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef __int128 LL;
#define all(x) (x).begin(), (x).end()

template<typename T>
istream& operator >>(istream& in, vector<T>& a) {
    for (auto& i : a)
        in >> i;
    return in;
}

template<typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
    for (const auto& i : a)
        out << i << ' ';
    return out;
}


// Input data

int check(const string &tsol_path, const string &rsol_path) {
    // There is scanned data
    ll sol_res, res;

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
    }

    return check(argv[3], argv[4]);
}
