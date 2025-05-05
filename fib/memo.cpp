#include <unordered_map>

using ll = long long;

/*
 * 1. Recursion
 * - Time Complexity:  O(2^n)
 * - Space Complexity: O(n)
 */
int fib(int n) {
    if (n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

/*
 * 2. Recursion with memoization
 * - Time Complexity:  O(n)
 * - Space Complexity: O(n)
 */
ll fib_memo(int n, std::unordered_map<ll, ll>& memo) {
    if (n <= 2) {
        return 1;
    }
    
    auto it = memo.find(n);
    if (it != memo.end()) {
        return it->second;
    }
    
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
}
