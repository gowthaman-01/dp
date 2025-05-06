#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

/*
 * 1. Unbounded recursion
 * - Time Complexity:  O(numbers.size()^target * target)
 * - Space Complexity: O(target) [result vector] + O(target^2) [stack]
 */
std::optional<std::vector<int>> best_sum_unbounded(int target, const std::vector<int>& numbers) {
    if (target < 0) {
        return std::nullopt;
    }
    
    if (target == 0) {
        return std::vector<int>{};
    }
    
    // nullopt vector
    std::optional<std::vector<int>> smallest{};
    
    for (int num: numbers) {
        auto candidate = best_sum_unbounded(target - num, numbers);
        if (candidate) {
            candidate->push_back(num);
            if (!smallest || candidate->size() < smallest->size()) {
                smallest = candidate;
            }
        }
    }

    return smallest;
}

/*
 * 2. Unbounded recursion with memoization
 * - Time Complexity:  O(numbers.size() * target^2)
 * - Space Complexity: O(target^2) [memo] + O(target) [result vector] + O(target^2) [stack]
 */
std::optional<std::vector<int>> best_sum_unbounded_memo(
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
    
    std::optional<std::vector<int>> smallest{};
    
    for (int num: numbers) {
        auto candidate = best_sum_unbounded_memo(target - num, numbers, memo);
        if (candidate) {
            candidate->push_back(num);
            if (!smallest || candidate->size() < smallest->size()) {
                smallest = candidate;
            }
        }
    }
    
    memo[target] = std::move(smallest);
    return memo[target];
}

/*
 * 3. Bounded recursion
 * - Time Complexity:  O(2^numbers.size() * numbers.size())
 * - Space Complexity: O(numbers.size()) [result vector] + O(numbers.size()) [stack]
 */
std::optional<std::vector<int>> best_sum_bounded(int target, int i, const std::vector<int>& numbers) {
    if (target == 0) {
        return std::vector<int>{};
    }
    
    if (target < 0 || i >= numbers.size()) {
        return std::nullopt;
    }
    
    auto skip = best_sum_bounded(target, i + 1, numbers);
    auto include = best_sum_bounded(target - numbers[i], i + 1, numbers);
    
    if (!include && !skip) {
        return std::nullopt;
    }
    
    if (!include) {
        return skip;
    }
    
    include->push_back(numbers[i]);

    if (!skip) {
        return include;
    }
    
    return skip->size() < include->size() ? skip : include;
}

/*
 * 4. Bounded recursion with memoisation
 * - Time Complexity:  O(numbers.size()^2 * target)
 * - Space Complexity: O(numbers.size()^2 * target) [memo] + O(numbers.size()) [result vector] + O(numbers.size()) [stack]
 */
std::optional<std::vector<int>> best_sum_bounded_memo(
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
    
    auto skip = best_sum_bounded_memo(target, i + 1, numbers, memo);
    auto include = best_sum_bounded_memo(target - numbers[i], i + 1, numbers, memo);
    
    if (!skip && !include) {
        memo[key] = std::nullopt;
        return std::nullopt;
    }
    
    if (!include) {
        memo[key] = std::move(skip);
        return memo[key];
    }

    include->push_back(numbers[i]);
    
    if (!skip) {
        memo[key] = std::move(include);
        return memo[key];
    }
    
    memo[key] = skip->size() < include->size() ? std::move(skip) : std::move(include);
    return memo[key];
}

