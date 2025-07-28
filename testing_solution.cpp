#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
#ifdef STRESS
    if (argc == 3) {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
    }
#endif
    int n;
    cin >> n;
    cout << n * n << '\n';
}
