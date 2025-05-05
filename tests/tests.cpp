#include "tests.hpp"

#include <cassert>
#include <string>
#include <unordered_map>

using ll = long long;

void run_fibonacci_tests() {
    // 1, 2, 3, 4, 5, 6, 7,  8,  9  ... 50
    // 1, 1, 2, 3, 5, 8, 13, 21, 34 ... 12586269025
    assert(fib(6) == 8);
    assert(fib(7) == 13);
    assert(fib(8) == 21);
    
    std::unordered_map<ll, ll> memo;
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
