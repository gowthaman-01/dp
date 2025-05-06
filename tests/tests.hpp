#pragma once

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

using ll = long long;

// Fibonacci
int fib(int n);
ll fib_memo(int n, std::unordered_map<int, ll>& memo);

// Grid Traveller
int grid_traveller(int m, int n);
ll grid_traveller_memo(int m, int n, std::unordered_map<std::string, ll>& memo);

// Can Sum
bool can_sum_unbounded(int target, const std::vector<int>& numbers);
bool can_sum_unbounded_memo(int target, const std::vector<int>& numbers, std::unordered_map<int, bool>& memo);
bool can_sum_bounded(int i, int target, const std::vector<int>& numbers);
bool can_sum_bounded_memo(int i, int target, const std::vector<int>& numbers, std::unordered_map<std::string, bool>& memo);

// How Sum
std::optional<std::vector<int>> how_sum_unbounded(int target, const std::vector<int>& numbers);
std::optional<std::vector<int>> how_sum_unbounded_memo(
    int target,
    const std::vector<int>& numbers,
    std::unordered_map<int, std::optional<std::vector<int>>>& memo
);
std::optional<std::vector<int>> how_sum_bounded(int target, int i, const std::vector<int>& numbers);
std::optional<std::vector<int>> how_sum_bounded_memo(
    int target,
    int i,
    const std::vector<int>& numbers,
    std::unordered_map<std::string, std::optional<std::vector<int>>>& memo
);

// Best Sum
std::optional<std::vector<int>> best_sum_unbounded(int target, const std::vector<int>& numbers);
std::optional<std::vector<int>> best_sum_unbounded_memo(
    int target,
    const std::vector<int>& numbers,
    std::unordered_map<int, std::optional<std::vector<int>>>& memo
);
std::optional<std::vector<int>> best_sum_bounded(int target, int i, const std::vector<int>& numbers);
std::optional<std::vector<int>> best_sum_bounded_memo(
    int target,
    int i,
    const std::vector<int>& numbers,
    std::unordered_map<std::string, std::optional<std::vector<int>>>& memo
);

// Tests
void run_fibonacci_tests();
void run_grid_traveller_tests();
void run_can_sum_tests();
void run_how_sum_tests();
void run_best_sum_tests();
