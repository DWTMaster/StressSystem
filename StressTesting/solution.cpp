#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
#ifdef STRESS
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    cout << n * n << '\n';
}
