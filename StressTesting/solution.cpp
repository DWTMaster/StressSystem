#define _GLIBCXX_DEBUG
#define debug(x) cerr << __LINE__ << ": " << (#x) << " = " << (x) << endl

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef __int128 LL;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define all(x) (x).begin(), (x).end()

template<typename T>
istream &operator >>(istream &in, vector<T> &a) {
    for (auto &i: a)
        in >> i;
    return in;
}

template<typename T>
ostream &operator <<(ostream &out, const vector<T> &a) {
    for (const auto &i: a)
        out << i << ' ';
    return out;
}

ll n;

void solve() {
    cout << n * n << '\n';
}

int main(int argc, char *argv[]) {
#ifdef STRESS
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    solve();
}
