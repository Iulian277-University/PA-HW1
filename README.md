## *Iulian-Marius Tăiatu (322CB)*
---

## Problem 1 - Walsh Tables (Divide and Conquer)

For this problem I recursively searched in one of the smaller squares (1/4), depending on the current position (x,y) in the matrix.
When recursively calling the function, I translated the indexes from (x,y) to (a,b) to match the indexes of the smaller matrix.

Time complexity:  O(log(n))

## Problem 2 - Encrypted words (Greedy)

The idea for this problem is to find the `global_dominant_character` over all words. Then, sort the words desending by `freq` and ascending by `length`.
`freq` is defined as being the difference (the occurences of the dominant character) - (the occurences of other characters).
At the end, concatenate the words until we ran out of a dominant character.

Time complexity:  O(n * log(n)) + O(n * ALPHABET_SIZE)

## Problem 3 - Target with minimum operations (Dynamic Programming)

First, I had to compute the minimum required operations for transforming `x` into a `y`, starting with x = 1 and using only the operation [x = x + div(x)], where `div(x)` is a divisor of the current number `x`. The recurrence that I found is op(x) = 1 + min::op(x - divisors_x), where `div_x` is a divisor of `x`, excluding itself

After that, I extracted only the operations I am interested in (for the numbers in the target array) and performed a `knapsack` algorithm in order to find the "maximum profit". I've used a variation of the classic `knapsack` algorithm (with only a vector instead of a matrix), because I don't need to reconstruct the solution, but only the maximum profit can be obtained.

Time complexity:  O(n * MAX_TARGET) + O(n * k)

## Problem 4 - Encrypted key (Backtracking + Dynamic Programming)

For this problem, I generated all the `S_combinations` using a backtracking. After that, I completed the `?` characters from the key `K` using the combinations generated above.
At the end, I constructed a `dp` matrix for counting the number of times a `small_string` subsequence occurs in a `big_string`. The general recursion rule is:
-> If last characters are the same:  dp[i][j] = dp[i-1][j] + dp[i-1][j-1]
-> If last characters are different: dp[i][j] = dp[i-1][j]

This problem can be solved using only dynamic programming, but I didn't manage to find the recurring relationship :(

Time complexity:  O(2^n)

## Problem 5 - Activate cities (Dynamic Programming)

The idea for this problem is to generate a matrix `dp`, where dp[i][j] represents the required number of dealers for activating `i` cities starting from the `j` position in the array of cities.
The general recursion rule is: dp[i][j] = cost_of_activation_city[j] + max(dp[i-1][j+2], dp[i-1][j+3], ...). The purpose of looking from `j+2` is to not count the same route twice. 

Instead of completing a matrix, I used only 2 vectors (last row and current row). I've also traversed each line from right to left to be able to store the maximum in a variable, instead of re-calculating it at each step.

Another interesting thing is that the "rows" from the matrix `dp` are repeting after n/2, so I stopped the algorithm after completing n/2 rows.

At the end, I computed the answers for each question by implementing a modified binary search:
If the `target` doesn't exist in the `arr`
    -> Return the idx of largest element smaller than `target`
Otherwise 
    -> Return the largest idx of the `target` ("rightmost `target`")

Time complexity:  O(n^2)

