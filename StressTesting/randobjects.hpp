#ifndef RANDOBJECTS
#define RANDOBJECTS

#include <chrono>
#include <random>
#include <string>
#include <vector>


inline std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
inline std::mt19937_64 rng_64(std::chrono::steady_clock::now().time_since_epoch().count());

// Numbers

template<typename T1, typename T2>
int randint(const T1 &low, const T2 &high) {
    return static_cast<int>(low) + rng() % static_cast<int>(high - low + 1);
}

template<typename T1, typename T2>
long long randlong(const T1 &low, const T2 &high) {
    return static_cast<long long>(low) + rng() % static_cast<long long>(high - low + 1);
}

template<typename T, typename T1, typename T2>
T randnumber(const T1 &low, const T2 &high) {
    if constexpr (std::is_same_v<T, int>) {
        return randint(low, high);
    } else if constexpr (std::is_same_v<T, long long>) {
        return randlong(low, high);
    } else {
        static_assert(false, "Unsupported type for randnumber");
        return -1;
    }
}


// Strings

inline std::string randString(const int &len, const char &low, const char &high) {
    std::string result;
    for (int i = 0; i < len; ++i) {
        result += static_cast<char>(randint(low, high));
    }
    return result;
}

inline std::string randString(const int &len, const std::string &alphabet) {
    std::string result;
    for (int i = 0; i < len; ++i) {
        result += alphabet[randint(0, alphabet.length() - 1)];
    }
    return result;
}

// This string has alphabet a..zA..z + digits if you want
inline std::string randStandardString(const int &len, const bool &include_digits) {
    std::string alphabet;
    for (char c = 'a'; c <= 'z'; ++c) {
        alphabet += c;
        alphabet += static_cast<char>(c - 'a' + 'A');
    }
    if (include_digits) {
        for (char c = '0'; c <= '9'; ++c) {
            alphabet += c;
        }
    }
    return randString(len, alphabet);
}


// Structures

template<typename T1, typename T2, typename Tlow, typename Thigh>
std::pair<T1, T2> randPair(const Tlow &low, const Thigh &high) {
    return std::make_pair(randnumber<T1>(low, high), randnumber<T2>(low, high));
}

template<typename T, typename T1, typename T2>
std::vector<T> randVector(const int &len, const T1 &low, const T2 &high) {
    std::vector<T> result(len);
    std::generate(result.begin(), result.end(), [&]() { return randnumber<T>(low, high); });
    return result;
}

inline std::vector<std::pair<int, int> > randTree(const int &vertexes, const int &numeration_from, const int &root) {
    std::vector<int> order(vertexes);
    std::iota(order.begin(), order.end(), numeration_from);
    std::ranges::shuffle(order, rng); {
        const auto root_id = std::ranges::find(order, root) - order.begin();
        std::swap(order[0], order[root_id]);
    }

    std::vector<std::pair<int, int> > result(vertexes - 1);
    for (int i = 0; i < vertexes - 1; ++i) {
        result[i].first = order[i + 1];
        result[i].second = order[randint(0, i)];
    }
    return result;
}

inline std::vector<std::tuple<int, int, int> > randWeightedTree(const int &len, const int &low, const int &high,
                                                                const int &numeration_from, const int &root) {
    std::vector<std::tuple<int, int, int> > result;
    for (const auto &[u, v]: randTree(len, numeration_from, root)) {
        result.emplace_back(u, v, randint(low, high));
    }
    return result;
}

inline std::vector<std::pair<int, int> > randGraph(const int &len, const int &edges, const int &numeration_from) {
    std::vector<std::pair<int, int> > result(edges);
    for (auto &[u, v]: result) {
        u = randint(numeration_from, numeration_from + len - 1);
        v = randint(numeration_from, numeration_from + len - 1);
    }
    return result;
}

inline std::vector<std::tuple<int, int, int> > randWeightedGraph(const int &len, const int &edges, const int &low,
                                                                 const int &high, const int &numeration_from) {
    std::vector<std::tuple<int, int, int> > result;
    for (const auto &[u, v]: randGraph(len, edges, numeration_from)) {
        result.emplace_back(u, v, randint(low, high));
    }
    return result;
}

#endif
