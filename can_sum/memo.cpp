#include <string>
#include <unordered_map>
#include <vector>

/*
 * 1. Unbounded recursion
 * - Time Complexity:  O(numbers.size()^target)
 * - Space Complexity: O(target)
 */
bool can_sum_unbounded(int target, const std::vector<int>& numbers) {
    if (target == 0) {
        return true;
    }
    
    for (int num: numbers) {
        if (num <= target && can_sum_unbounded(target - num, numbers)) {
            return true;
        }
    }
    
    return false;
}

/*
 * 2. Unbounded recursion with memoization
 * Time Complexity:  O(target * numbers.size())
 * Space Complexity: O(target)
 */
bool can_sum_unbounded_memo(int target, const std::vector<int>& numbers, std::unordered_map<int, bool>& memo) {
    if (target == 0) {
        return true;
    }
    
    auto it = memo.find(target);
    if (it != memo.end()) {
        return it->second;
    }
    
    for (int num: numbers) {
        if (num <= target && can_sum_unbounded_memo(target - num, numbers, memo)) {
            memo[target] = true;
            return true;
        }
    }
    
    memo[target] = false;
    return false;
}

/*
 * 3. Bounded recursion
 * Time Complexity:  O(2^numbers.size()) - i increases during every recursive call
 * Space Complexity: O(numbers.size())
 */
bool can_sum_bounded(int i, int target, const std::vector<int>& numbers) {
    if (target == 0) {
        return true;
    }
    
    if (i == numbers.size() || target < 0) {
        return false;
    }

    return can_sum_bounded(i + 1, target - numbers[i], numbers) ||
           can_sum_bounded(i + 1, target, numbers);
}

/*
 * 4. Bounded recursion with memoization
 * Time Complexity:  O(target * numbers.size())
 * Space Complexity: O(numbers.size()) [stack] + O(target * numbers.size()) [memo]
 */
bool can_sum_bounded_memo(int i, int target, const std::vector<int>& numbers, std::unordered_map<std::string, bool>& memo) {
    if (target == 0) {
        return true;
    }
    
    if (target < 0 || i >= numbers.size()) {
        return false;
    }
    
    auto key = std::to_string(i) + "," + std::to_string(target);
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
    
    bool res = can_sum_bounded_memo(i + 1, target - numbers[i], numbers, memo) ||
                  can_sum_bounded_memo(i + 1, target, numbers, memo);

    memo[key] = res;
    return res;
}


