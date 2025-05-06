#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

/*
 * 1. Unbounded recursion
 * - Time Complexity:  O(numbers.size()^target)
 * - Space Complexity: O(target) [result vector] + O(target) [stack]
 */
std::optional<std::vector<int>> how_sum_unbounded(int target, const std::vector<int>& numbers) {
    if (target < 0) {
        return std::nullopt;
    }
    
    if (target == 0) {
        return std::vector<int>{};
    }
    
    for (int num: numbers) {
        auto candidate = how_sum_unbounded(target - num, numbers);
        
        if (candidate) {
            candidate->push_back(num);
            return candidate;
        }
    }
    
    return std::nullopt;
}

/*
 * 2. Unbounded recursion with memoization
 * - Time Complexity:  O(numbers.size() * target + target^2) -> vector copying
 * - Space Compelxity: O(target^2) [memo] + O(target) [result vector] + O(target) [stack]
 */
std::optional<std::vector<int>> how_sum_unbounded_memo(
    int target,
    const std::vector<int>& numbers,
    std::unordered_map<int, std::optional<std::vector<int>>>& memo
) {
    if (target < 0) {
        return std::nullopt;
    }
    
    if (target == 0) {
        return std::vector<int>{};
    }
    
    auto it = memo.find(target);
    if (it != memo.end()) {
        return it->second;
    }
    
    for (int num: numbers) {
        auto candidate = how_sum_unbounded_memo(target - num, numbers, memo);
        if (candidate) {
            candidate->push_back(num);
            memo[target] = std::move(candidate);
            return memo[target];
        }
    }
    
    memo[target] = std::nullopt;
    return std::nullopt;
}

/*
 3. Bounded recursion
 - Time Complexity:  O(2^numbers.size())
 - Space Complexity: O(numbers.size()) [result vector] + O(numbers.size()) [stack]
 */
std::optional<std::vector<int>> how_sum_bounded(int target, int i, const std::vector<int>& numbers) {
    if (target == 0) {
        return std::vector<int>{};
    }
    
    if (target < 0 || i >= numbers.size()) {
        return std::nullopt;
    }
    
    auto skip = how_sum_bounded(target, i + 1, numbers);
    if (skip) {
        return skip;
    }
    
    auto include = how_sum_bounded(target - numbers[i], i + 1, numbers);
    if (include) {
        include->push_back(numbers[i]);
        return include;
    }
    
    return std::nullopt;
}

/*
 4. Bounded recursion with memoization
 - Time Complexity:  O(numbers.size()^2 * target)
 - Space Complexity: O(numbers.size()^2 * target) [memo] + O(numbers.size()) [result vector] + O(numbers.size()) [stack]
 */
std::optional<std::vector<int>> how_sum_bounded_memo(
    int target,
    int i,
    const std::vector<int>& numbers,
    std::unordered_map<std::string, std::optional<std::vector<int>>>& memo
) {
    if (target == 0) {
        return std::vector<int>{};
    }
    
    if (target < 0 || i >= numbers.size()) {
        return std::nullopt;
    }
    
    std::string key = std::to_string(target) + "," + std::to_string(i);
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
    
    auto skip = how_sum_bounded_memo(target, i + 1, numbers, memo);
    if (skip) {
        memo[key] = std::move(skip);
        return memo[key];
    }
    
    auto include = how_sum_bounded_memo(target - numbers[i], i + 1, numbers, memo);
    if (include) {
        include->push_back(numbers[i]);
        memo[key] = std::move(include);
        return memo[key];
    }
    
    memo[key] = std::nullopt;
    return std::nullopt;
}



