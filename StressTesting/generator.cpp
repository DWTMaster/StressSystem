#include <bits/stdc++.h>
#include "randobjects.hpp"

using namespace std;
#define all(x) (x).begin(), (x).end()


template<typename T1, typename T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) {
    out << p.first << ' ' << p.second;
    return out;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &vec) {
    for (const auto &elem: vec) {
        out << elem << ' ';
    }
    return out;
}


int main(int argc, char *argv[]) {
#ifdef STRESS
    if (argc == 2) {
        freopen(argv[1], "w", stdout);
    }
#endif

    {
        cout << randint(1, 5e4) << '\n';
    }

    return 0;
}
