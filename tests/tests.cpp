#include "tests.hpp"

#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

using ll = long long;

void print_vector(const std::vector<int>& v) {
    std::cout << "{";
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "}\n";
}

void run_fibonacci_tests() {
    // 1, 2, 3, 4, 5, 6, 7,  8,  9  ... 50
    // 1, 1, 2, 3, 5, 8, 13, 21, 34 ... 12586269025
    assert(fib(6) == 8);
    assert(fib(7) == 13);
    assert(fib(8) == 21);
    
    std::unordered_map<int, ll> memo;
    assert(fib_memo(50, memo) == 12586269025);
}

void run_grid_traveller_tests() {
    assert(grid_traveller(3, 3) == 6);
    
    std::unordered_map<std::string, ll> memo;
    assert(grid_traveller_memo(18, 18, memo) == 2333606220);
}

void run_can_sum_tests() {
    assert(can_sum_unbounded(7, {2, 3}) == true);
    assert(can_sum_unbounded(7, {5, 3, 4, 7}) == true);
    assert(can_sum_unbounded(7, {2, 4}) == false);
    assert(can_sum_unbounded(8, {2, 3, 5}) == true);
    
    std::unordered_map<int, bool> memo;
    assert(can_sum_unbounded_memo(300, {7, 14}, memo) == false);
    
    assert(can_sum_bounded(0, 7, {2, 3}) == false);
    assert(can_sum_bounded(0, 7, {5, 3, 4, 7}) == true);
    assert(can_sum_bounded(0, 7, {2, 4}) == false);
    assert(can_sum_bounded(0, 8, {2, 3, 5}) == true);
    
    std::unordered_map<std::string, bool> memo_bounded;
    assert(can_sum_bounded_memo(0, 300, {7, 14}, memo_bounded) == false);
}

void run_how_sum_tests() {
    auto result = how_sum_unbounded(7, std::vector<int>{2, 3});
    auto expected = std::vector<int>{3, 2, 2};
    assert(result && result.value() == expected);

    result = how_sum_unbounded(7, std::vector<int>{5, 3, 4, 7});
    expected = {4, 3};
    assert(result && result.value() == expected);

    result = how_sum_unbounded(8, std::vector<int>{2, 3, 5});
    expected = {2, 2, 2, 2};
    assert(result && result.value() == expected);

    result = how_sum_unbounded(7, std::vector<int>{2, 4});
    assert(!result);
    
    std::unordered_map<int, std::optional<std::vector<int>>> memo{};
    result = how_sum_unbounded_memo(300, std::vector<int>{7, 14}, memo);
    assert(!result);
    
    memo.clear();
    expected = {25, 25, 25, 25};
    result = how_sum_unbounded_memo(100, std::vector<int>{7, 14, 25}, memo);
    assert(result && result.value() == expected);

    expected = {5, 3};
    result = how_sum_bounded(8, 0, std::vector<int>{2, 3, 5});
    assert(result && result.value() == expected);
    
    std::unordered_map<std::string, std::optional<std::vector<int>>> memo_bounded;
    expected = {25, 25, 25, 25};
    result = how_sum_bounded_memo(100, 0, std::vector<int>{25, 25, 25, 25}, memo_bounded);
    assert(result && result.value() == expected);
    
    memo_bounded.clear();
    result = how_sum_bounded_memo(300, 0, std::vector<int>{7, 14}, memo_bounded);
    assert(!result);
    
    
    
}

void run_best_sum_tests() {
    auto expected = std::vector<int>{5, 3};
    auto result = best_sum_unbounded(8, std::vector<int>{2, 3, 5});
    assert(result && result.value() == expected);
    
    expected = {7};
    result = best_sum_unbounded(7, std::vector<int>{5, 3, 4, 7});
    assert(result && result.value() == expected);
    
    expected = {10, 10};
    result = best_sum_unbounded(20, std::vector<int>{2, 3, 4, 5, 10});
    assert(result && result.value() == expected);
    
    expected = {25, 25, 25, 25};
    std::unordered_map<int, std::optional<std::vector<int>>> memo;
    result = best_sum_unbounded_memo(100, std::vector<int>{1, 2, 5, 25}, memo);
    assert(result && result.value() == expected);
    
    result = best_sum_bounded(10, 0, std::vector<int>{2, 3});
    assert(!result);
    
    expected = {10, 5, 3, 2};
    result = best_sum_bounded(20, 0, std::vector<int>{2, 3, 4, 5, 10});
    assert(result && result.value() == expected);
    
    std::unordered_map<std::string, std::optional<std::vector<int>>> memo_bounded;
    result = best_sum_bounded_memo(100, 0, std::vector<int>{1, 2, 5, 25}, memo_bounded);
    assert(!result);
    
    std::vector<int> big_numbers;
    for (int i = 1; i <= 50; ++i) {
        big_numbers.push_back(i);
    }
    memo_bounded.clear();
    expected = {50, 49, 1};
    result = best_sum_bounded_memo(100, 0, big_numbers, memo_bounded);
    assert(result && result.value() == expected);
}
