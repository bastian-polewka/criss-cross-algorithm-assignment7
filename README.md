# Table of contents
1. [Introduction](#intro)
2. [Criss-Cross multiplication algorithm](#Cross)
3. [Code implementation + explanation](#CodeImp)
4. [How testing was carried out + Results](#testing)
5. [Limitation](#limitation)
6. [Improvement](#improvement)



# 🔰 Introduction  <a name="intro"></a>
Also known as the Criss-Cross multiplication algorithm, this $50$-lines long algorithm, requiring no advanced math techniques, multiplies large positive integers in string format and returns the exact answer in string format. Multiplication of 1000-digit string numbers ($>10^{100}$) can be done almost instantly. This algorithm is nearly twice as fast as the Karatsuba algorithm when the number of digits is below 1000.

The aim of this repository is give a concise explanation of this unpopular algorithm as well as to explain my implementation of the algorithm using C++. 

The Criss-Cross algorithm comes from Vedic mathematics, a compendium of tricks for increasing the speed of mathematical calculations. Unlike the Karatsuba algorithm, the Criss-Cross algorithm can also be used to manually multiply any number in a SINGLE line using pen and paper or even mentally. And obviously, this algorithm is faster than the grade-school algorithm for multiplying numbers.

More details about Vedic math can be found [here](https://github.com/KVBharatBhushan/Vedic-Maths)

## Time complexity ##
Time complexity : $\mathbb O(n^2)$

Worst case scenario is when the 2 digits have the same number of digits. 

More explanation about the time complexity is found [below](#Case1).

## Function call ##
```cpp
vedic(a, b)
``` 
where $a, b$ are **positive integers in string format**.

# 📰 Criss-Cross multiplication algorithm <a name="Cross"></a>

Steps  :
- There's a specific set of patterns to follow when carrying out single digit products. (More about this below).
- For each pattern, compute the sum of all the required single digit product.
- Add carry (if any) to this sum.
- The last digit of this result is concatenated to the left of our final answer.
- The remaining digits of our sum is our new carry.
- Repeat until all patterns have been exhausted.

### Pattern for 2-digit multiplication ###
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/cd05c87109f43e90a4fba7576bde68e94389349c/Media%20Files/2x2+pattern.gif)

Example :

![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/Example+1.gif)

### Pattern for 3-digit multiplication ###
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/3x3+pattern.gif)

### Pattern for 4-digit multiplication ###
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/a2b8ccf5951fdeb7a31f31aa4754585d8ac21d32/Media%20Files/4x4+pattern.gif)

The pattern continues indefinitely for any number of digits.

There's no formal proof of why this algorithm works but if we compare the grade-school algorithm and this algorithm side-by-side, there are some similarities.  
![image](https://user-images.githubusercontent.com/65414576/155765960-2ec47174-1825-4c9d-8fa9-94a6a6086361.png)

The advantage of the criss-cross algorithm over the grade-school algorithm is that it works with smaller numbers (it adds single-digit products and resets the sum each time).

For more explanations/examples [click here](https://www.youtube.com/watch?v=iNQ9Mj_zS-I&ab_channel=SumanTVEducation)

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

## Case 1 : Both `a` and  `b` have `n` digits <a name="Case1"></a>
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
### Time complexity ###
The total number of single digit product is $n^2 + n - 1$  In comparison, the total number of single digit products for the Karatsuba algorithm is $n^{\log_2 3}.$

![image](https://user-images.githubusercontent.com/65414576/155828159-ae742681-dace-43b3-b0f9-542745d9b108.png)

As the number of digits in the integers being multiplied tends to infinity, the Karatsuba algorithm will perform better. However, for relatively small numbers (having less than 10,000 digits), the Karatsuba algorithm performs worse. 

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
This case could be eliminated if we simply make both `a` and `b` the same length initially by adding leading zeroes to `b`. However, this approach is time-consuming because there will be unnecessary and will introduce leading zeroes in our final answer which must be removed.

To bypass this problem, we simply reduce the total number of steps and the number of single digit product at each step to eliminate cases where the 1-digit multiplication involves a leading zero.

The total number of steps is now found using :
```cpp
    const ll asize = static_cast<ll>(a.size());
    const ll bsize = static_cast<ll>(b.size());
    ll totalsteps = asize + bsize - 1;
```

For each step, we first find the expected number of 1-digit multiplication if `a` and `b` were the same length :
```cpp
        if (step <= asize) {
             lines = step;
        }
        else {
            lines= asize - (step- asize); // do not simplify as 2*asize might overflow
        }
```

When all the digits of `b` have been traversed, `min` becomes negative. Previously when `a` and `b` were the same length, we exited when `min` is negative. However, when they differ in length, we cannot exit. Now, each time `min` reaches the start of `b`, we decrement `max` and keep `min` at index 0 of `b`.
```cpp
        if (min < 0) {
            min = 0;
            max--;
        }
```
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
![](https://github.com/creme332/VedicMultiplicationAlgorithm/blob/693d7c3bdc8f90d6fb8dfaf60001f69f688ff516/Media%20Files/5x3+min+max.gif)

The rest of the code is same as that in Case 1.

# 📊 How testing was carried out  <a name="testing"></a> #

- The number of test cases was atleast 100 to get statistically meaningful results. 

* For each test case
        
    *  A set of 2 random numbers with a pre-set number of digits is generated.

    * `vedic()` and `karatsuba()` take as parameter the **same** 2 random numbers.

    * The time taken by each function is calculated.

    * A counter `c` is incremented each time, the vedic algorithm takes less time.

    * The difference in times is also calculated.

Here are the resuls of testing. The average time per test case (in microseconds) is also included.

| Number of digits |Number of test cases | Avg time for vedic() | Avg time of karatsuba() | % difference |
| :---             |:----:                 |:----:                |:----:                                   |:----:        |
| 100              | 1000                  | 6033                  | 343458                                  |        98.2  |
| 500              | 100                   |  2263                 | 131762                                |     98.2           |
| 1000             | 200                   |  172990               | 5794911                                  | 97.0            |

# 🚫 Current limitation <a name="limitation"></a>
$a$ and $b$ must have less than $2^{32}$ digits because string data type can only store $2^{32}$ characters.

# 🔮 Improvements <a name="improvement"></a>
- Store `sum` and `carry` as strings instead of long long data type. 

