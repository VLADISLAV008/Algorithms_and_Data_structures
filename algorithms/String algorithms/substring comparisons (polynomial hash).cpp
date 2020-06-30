#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#define N 100001
#define number_of_checks 500

using std::cin;
using std::cout;
using std::string;
using std::vector;

class Hash {
    const int p = 31;
    const int64_t mod = (int64_t) 1e9 + 123;

    string s;
    vector<int64_t> p_pow;
    vector<int64_t> prefix_hashes;

    vector<int64_t> get_powers_of_number_by_mod(int number, int max_power) {
        vector<int64_t> n_pow(N);
        int64_t value = 1;
        for (int i = 0; i <= max_power; i++) {
            n_pow[i] = value;
            value *= number;
            value %= mod;
        }
        return n_pow;
    }

    vector<int64_t> get_prefix_hashes(const string &s) {
        vector<int64_t> hashes(N);
        int64_t value = 0;
        for (int i = 0; i < s.length(); i++) {
            value += static_cast<int>(s[i]) * p_pow[i];
            value %= mod;
            hashes[i] = value;
        }
        return hashes;
    }

public:
    explicit Hash(string s) {
        this->s = s;
        p_pow = get_powers_of_number_by_mod(p, s.length());
        prefix_hashes = get_prefix_hashes(s);
    }

    int64_t hash() { return prefix_hashes[s.length()]; }

    bool equal_substrings(int left1, int right1, int left2, int right2) {
        if (right1 - left1 != right2 - left2) {
            return false;
        }

        int64_t hash1 = prefix_hashes[right1];
        if (left1 != 0) {
            hash1 = (hash1 - prefix_hashes[left1 - 1] + mod) % mod;
        }
        int64_t hash2 = prefix_hashes[right2];
        if (left2 != 0) {
            hash2 = (hash2 - prefix_hashes[left2 - 1] + mod) % mod;
        }

        hash1 = (hash1 * p_pow[left2]) % mod;
        hash2 = (hash2 * p_pow[left1]) % mod;

        if (hash1 != hash2) {
            return false;
        }

        if (right1 == left1) {
            return s[left1] == s[left2];
        }

        for (int i = 0; i <= std::min(number_of_checks, right1 - left1); i++) {
            if (s[left1 + i] != s[left2 + i] || s[right1 - i] != s[right2 - i]) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    string s;
    int count_queries;
    cin >> s >> count_queries;

    Hash hash(s);

    for (int i = 0; i < count_queries; i++) {
        int left1, right1, left2, right2;
        cin >> left1 >> right1 >> left2 >> right2;
        bool result =
                hash.equal_substrings(left1 - 1, right1 - 1, left2 - 1, right2 - 1);

        if (result) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
