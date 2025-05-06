#include <string>
#include <unordered_map>

using ll = long long;

/*
 * 1. Recursion
 * - Time Complexity:  O(2^(m + n))
 * - Space Complexity: O(m + n)
 */
int grid_traveller(int m, int n) {
    if (m == 1 && n == 1) {
        return 1;
    }
    
    if (m <= 0 || n <= 0) {
        return 0;
    }
  
    return grid_traveller(m - 1, n) + grid_traveller(m, n - 1);
}

/*
 * 2. Recursion with memoization
 * - Time Complexity:  O(m * n)
 * - Space Complexity: O(m + n) [stack] + O(m * n) [memo]
 */
ll grid_traveller_memo(int m, int n, std::unordered_map<std::string, ll>& memo) {
    if (m == 1 && n == 1) {
        return 1;
    }
    
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    std::string key = m < n
        ? std::to_string(m) + "," + std::to_string(n)
        : std::to_string(n) + "," + std::to_string(m);
    
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
    
    auto res = grid_traveller_memo(m - 1, n, memo) + grid_traveller_memo(m, n - 1, memo);
    memo[key] = res;
    return res;
}
