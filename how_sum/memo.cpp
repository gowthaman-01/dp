#include <string>
#include <unordered_map>
#include <vector>

std::vector<int> how_sum_unbounded_helper(int target, const std::vector<int>& numbers, std::vector<int>& cur);
std::vector<int> how_sum_unbounded_memo_helper(int target, const std::vector<int>& numbers,
                                                    std::vector<int>& cur, std::unordered_map<int, std::vector<int>>& memo);
std::vector<int> how_sum_bounded_helper(int target, int i, const std::vector<int>& numbers, std::vector<int>& cur);
std::vector<int> how_sum_bounded_memo_helper(int target, int i, const std::vector<int>& numbers,
                                                    std::vector<int>& cur, std::unordered_map<std::string, std::vector<int>>& memo);

/*
 * Unbounded recursion
 * Time Complexity:  O(numbers.size()^target)
 * Space Complexity: O(target) [stack] O(target) [result vector]
 */
std::vector<int> how_sum_unbounded(int target, const std::vector<int>& numbers) {
    std::vector<int> cur{};
    return how_sum_unbounded_helper(target, numbers, cur);
}

/*
 * Unbounded recursion with memoization
 * Time Complexity:  O(target * numbers.size())
 * Space Complexity: O(target) [stack] O(target^2) [memo] O(target) [result vector]
 */
std::vector<int> how_sum_unbounded_memo(int target, const std::vector<int>& numbers) {
    std::vector<int> cur{};
    std::unordered_map<int, std::vector<int>> memo{};
    return how_sum_unbounded_memo_helper(target, numbers, cur, memo);
}

/*
 * Bounded recursion
 * Time Complexity:  O(2^numbers.size())
 * Space Compelxity: O(numbers.size()) [stack] O(numbers.size()) [result vector]
 */
std::vector<int> how_sum_bounded(int target, const std::vector<int>& numbers) {
    std::vector<int> cur{};
    return how_sum_bounded_helper(target, 0, numbers, cur);
}

/*
 * Bounded recursion with memoization
 * Time Complexity:  O(target * nums.size())
 * Space Complexity: O(nums.size()) [stack] O(target * nums.size()^2) [memo] O(nums.size()) [result vector]
 */
std::vector<int> how_sum_bounded_memo(int target, const std::vector<int>& numbers) {
    std::vector<int> cur{};
    std::unordered_map<std::string, std::vector<int>> memo;
    return how_sum_bounded_memo_helper(target, 0, numbers, cur, memo);
}

std::vector<int> how_sum_unbounded_helper(int target, const std::vector<int>& numbers, std::vector<int>& cur) {
    if (target == 0) {
        return cur;
    }
    
    if (target < 0) {
        return {};
    }
    
    for (int num: numbers) {
        cur.push_back(num);
        auto res = how_sum_unbounded_helper(target - num, numbers, cur);
        if (!res.empty()) {
            return res;
        }
        cur.pop_back();
    }
    
    return {};
}

std::vector<int> how_sum_unbounded_memo_helper(int target, const std::vector<int>& numbers, std::vector<int>& cur,
                                                    std::unordered_map<int, std::vector<int>>& memo)
{
    if (target == 0) {
        return cur;
    }
    
    if (target < 0) {
        return {};
    }
    
    auto it = memo.find(target);
    if (it != memo.end()) {
        return it->second;
    }
    
    for (int num: numbers) {
        cur.push_back(num);
        auto res = how_sum_unbounded_memo_helper(target - num, numbers, cur, memo);
        if (!res.empty()) {
            memo[target] = res;
            return res;
        }
        cur.pop_back();
    }
    
    memo[target] = {};
    return {};
}

std::vector<int> how_sum_bounded_helper(int target, int i, const std::vector<int>& numbers, std::vector<int>& cur) {
    if (target == 0) {
        return cur;
    }
    
    if (target < 0 || i >= numbers.size()) {
        return {};
    }
    
    // Skip ith element
    auto res = how_sum_bounded_helper(target, i + 1, numbers, cur);
    if (!res.empty()) {
        return res;
    }
    
    // Include ith element
    cur.push_back(numbers[i]);
    res = how_sum_bounded_helper(target - numbers[i], i + 1, numbers, cur);
    if (!res.empty()) {
        return res;
    }
    
    cur.pop_back();
    return {};
}

std::vector<int> how_sum_bounded_memo_helper(int target, int i, const std::vector<int>& numbers,
                                                    std::vector<int>& cur, std::unordered_map<std::string, std::vector<int>>& memo)
{
    if (target == 0) {
        return cur;
    }
    
    if (target < 0 || i >= numbers.size()) {
        return {};
    }
    
    std::string key = std::to_string(i) + "," + std::to_string(target);
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
    
    // Skip ith element
    auto res = how_sum_bounded_memo_helper(target, i + 1, numbers, cur, memo);
    if (!res.empty()) {
        memo[key] = res;
        return res;
    }
    
    cur.push_back(numbers[i]);
    // Include ith element
    res = how_sum_bounded_memo_helper(target - numbers[i], i + 1, numbers, cur, memo);
    if (!res.empty()) {
        memo[key] = res;
        return res;
    }
    cur.pop_back();
    
    memo[key] = {};
    return {};
}
