# Table of contents
1. [Introduction](#intro)
2. [Criss-Cross multiplication explanation](#Cross)
3. [Code implementation + explanation](#CodeImp)
4. [How testing was carried out + Results](#testing)
5. [Limitation](#limitation)
6. [Improvement](#improvement)



# Introduction  <a name="intro"></a>
Also known as the Criss-Cross multiplication algorithm, this 50-lines long algorithm, requiring no advanced math knowledge, multiplies large string numbers in at least 90% LESS time than the Karatsuba algorithm. 1000-digit string numbers (numbers greater than 10^100) can be multiplied in less than 30 seconds.

The aim of this repository is give a concise explanation of this unpopular algorithm as well as to explain my implementation of the algorithm using C++. 

The Criss-Cross algorithm comes from Vedic mathematics, a compendium of tricks for increasing the speed of mathematical calculations. Unlike the Karatsuba algorithm, the Criss-Cross algorithm can also be used to manually multiply any number in a SINGLE line using pen and paper or even mentally. And obviously, this algorithm is faster than the grade-school algorithm for multiplying numbers.

## Time complexity ##
![image](https://user-images.githubusercontent.com/65414576/155485833-6879c3a5-96af-46da-8bd8-24ec270fc61a.png)

Worst case scenario is when the 2 digits have the same number of digits. 

More explanation about the time complexity is found [below](#Case1).

## Function call ##
```cpp
vedic(a, b)
``` 
where a,b are **positive integers in string format**.

# Criss-Cross multiplication explanation <a name="Cross"></a>
Here are a few things to note :
- There's a specific pattern to follow. (More about this below)  .
- If `a` has `n` digits and `b` has `m` digits, where `n>=m`, then to compute `a*b`, there is at most `2*n - 1` single digit product to be carried out.

Steps  :
- At each step compute the sum of all the required single digit product.
- Add carry (if any) to this sum.
- The last digit of this result is concatenated to the left of our final answer.
- The remaing digits of our sum is our new carry.
- Repeat for all steps

### Pattern for 2-digit multiplication ###
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/cd05c87109f43e90a4fba7576bde68e94389349c/Media%20Files/2x2+pattern.gif)

Example :

![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/Example+1.gif)

### Pattern for 3-digit multiplication ###
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/3x3+pattern.gif)

### Pattern for 4-digit multiplication ###
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/4x4+pattern.gif)

The pattern continues indefinitely for any number of digits.

I don't have a formal proof of why this algorithm works but if we compare the grade-school algorithm and this algorithm side-by-side, it becomes obvious.  
![image](https://user-images.githubusercontent.com/65414576/155765960-2ec47174-1825-4c9d-8fa9-94a6a6086361.png)

The advantage of the criss-cross algorithm over the grade-school algorithm is that it works with smaller numbers (it adds single-digit products and resets the sum each time).

For more explanations/examples on the algorithm refer to :
1. Page 27 in this book
2. https://www.youtube.com/watch?v=iNQ9Mj_zS-I&ab_channel=SumanTVEducation

# Code implementation + explanation  <a name="CodeImp"></a>

```cpp
        ll i = max, j = min;

        for (ll k = 0;k < lines;k++) {
            sum += (a[i] - '0') * (b[j] - '0');
            i--; j++;
        }
```
```min``` and ```max``` keep keep track of region within which the cross-multiplication will take place.

Example :

![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/3x3+min+max%5B2975%5D.gif)

![image](https://user-images.githubusercontent.com/65414576/155732674-d9b96441-29d1-42d6-99b4-a4a211b23a46.png)

`i` is the index used to iterate over `a` within region `[min, max]`.

`j` is the index used to iterate over `b` within region `[min, max]`.

## Case 1 : Both `a` and  `b` have `n` digits ## <a name="Case1"></a>
This is the simplest case. The total number of steps required is `2n-1`. (There are `n` patterns +  `n` reflected patterns. However, the `n`th pattern is counted twice so we minus 1.)

The number of 1-digit multiplication (or the number of lines drawn) at each step can be found as follows :
```cpp
        if (currentstep <= n) {lines = currentstep;}
        else {lines = n - (currentstep - n);} // or 2*n - currentstep
```

| Step number | Number of single digit product required |
| :---        |    :----:   |
| 1      | 1       |
| 2   | 2        | 
| 3   | 3        | 
| 4   | 4        | 
| ...   | ...        | 
| n   | n        | 
| n+1  | n-1        | 
| n+2   | n-2        | 
| n+3   | n-3        | 
| ...   | ...        | 
| 2n-1   | 1        | 

At each step, we will compute the sum of all the 1-digit multiplications required. From this sum we will obtain the carry for the next step and a digit of our answer. 

The total number of single digit products is `n^2 + n - 1`  In comparison, the total number of single digit products for the Karatsuba algorithm is `n^(log(3))` where log is the log base 2.

![image](https://user-images.githubusercontent.com/65414576/155828159-ae742681-dace-43b3-b0f9-542745d9b108.png)

Even though, the time complexity of my algorithm seems to be worse, it actually performs better than the karatsuba algorithm when the number of digits is below 10,000. (assuming I correctly tested the algorithms)

However, when the number of digits is exponentially higher (1e100 digits for example), my guess is that the karatsuba algorithm will perform better (though no testing was done for such numbers).

### The pseudocode for Case 1 ###
```
Initialise the total number of steps
Initialise min and max to n-1

For each step
        Determine the number of 1-digit multiplication to be carried out
        Initialise sum to 0
        When the step number becomes > n (or when min becomes negative), set min to 0 and decrement max.
        
        For each 1-digit multiplication
                Increment sum
                Modify counters to move to next 1-digit multiplication
        
        Add previous carry to sum
        Update carry and answer
        Decrement min

If carry is non-zero, concatenate it to the left of answer.
Return answer

```

## Case 2 : `b` has fewer digits than `a` ## 
This case could be eliminated if we simply make both `a` and `b` the same length initially by adding leading zeroes to `b`. Then, before returning our answer, we remove any leading zeroes. However, this approach wastes a lot of time when both strings are very long.

To bypass this problem, we simply reduce the total number of steps and the number of single digit product at each step to eliminate cases where the 1-digit multiplication involves a leading zero.

The total number of steps is now found using :
```cpp
    const ll asize = static_cast<ll>(a.size());
    const ll bsize = static_cast<ll>(b.size());
    ll totalsteps = asize + bsize - 1;
```

For each step, we find the expected number of 1-digit multiplication if `a` and `b` were the same length :
```cpp
        if (step <= asize) {
             lines = step;
        }
        else {
            lines= asize - (step- asize); // do not simplify as 2*asize might overflow
        }
```

When all the digits of `b` have been traversed, `min` becomes negative. If `a` and `b` are the same length, we exit when `min` is negative. However, when they differ in length, we cannot exit. So, each time `min` reaches the start of `b`, we decrement `max` and keep `min` at index 0 of `b`.
```cpp
        if (min < 0) {
            min = 0;
            max--;
        }
```
The following gif shows how `min` and `max` changes with each step :
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/693d7c3bdc8f90d6fb8dfaf60001f69f688ff516/Media%20Files/5x3+min+max.gif)

Then we reduce the number of 1-digit multiplication as follows :

```cpp
        if (min < 0) {
            min = 0;
            max--;
            if (step < asize) {
                lines -= step - bsize;
            }
            else {
                lines -= asize - bsize;
            }
        }
```
The rest of the code is same as that in Case 1.

# How testing was carried out  <a name="testing"></a>
There are 1000 test cases.

Each test case generates a set of 2 random numbers whose lengths go up to 10000 digits.

A counter `c` is incremented each time, the vedic algorithm performs better than the karatsuba algorithm.

I also calculated the difference in times.

In the end, the success rate (number of times out of 1000 `vedic()` took less time) is calculated.

No testing was done beyond 10,000 digits because the karatsuba algorithm was taking too much time.

# Current limitation <a name="limitation"></a>
`a` and `b` must have less than 2^32 digits because string data type can only store 2^32 characters.

# Improvements <a name="improvement"></a>
- Do not use long long data type. Instead save the sum and the carry as strings.

