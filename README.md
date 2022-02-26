# VedicMultiplicationAlgorithm
Also known as the Criss-Cross multiplication algorithm, this 50-lines long algorithm, requiring no advanced math knowledge,  multiplies large string numbers in at least 90% LESS time than the Karatsuba algorithm. 1000-digit string numbers can be multiplied almost instantly.

To my surprise, this method is not as popular as other multiplication algorithms despite being faster and easier to understand. The aim of this repository is give a brief explanation of the algorithm as well as my implementation of the algorithm using C++. Unlike the Karatsuba algorithm, the Criss-Cross algorithm can also be used to manually multiply numbers in a SINGLE line using pen and paper. And obviously, it is faster than the grade-school algorithm for multiplying numbers.

## Time complexity ##
![image](https://user-images.githubusercontent.com/65414576/155485833-6879c3a5-96af-46da-8bd8-24ec270fc61a.png)

Worst case scenario is when the 2 digits have the same number of digits. 
## Function call ##
```cpp
vedic(a, b)
``` 
where a,b are **positive integers in string format**.

# Criss-Cross multiplication explanation # 

Also, the method can be implemented from left to right as well. 

I don't have a formal proof of why this algorithm works but if we compare the grade-school algorithm and this algorithm side-by-side, it becomes obvious.  
![image](https://user-images.githubusercontent.com/65414576/155765960-2ec47174-1825-4c9d-8fa9-94a6a6086361.png)

The advantage of the criss-cross algorithm is that it remembers smaller numbers and 

For more explanations on the algorithm refer to :
1. Page 27 in this book
2. https://www.youtube.com/watch?v=iNQ9Mj_zS-I&ab_channel=SumanTVEducation
# How my code works #

```cpp
        ll i = max, j = min;

        for (ll k = 0;k < lines;k++) {
            sum += (a[i] - '0') * (b[j] - '0');
            i--; j++;
        }
```
```min``` and ```max``` keep keep track of region within which the cross-multiplication will take place.

Example :

![image](https://user-images.githubusercontent.com/65414576/155732674-d9b96441-29d1-42d6-99b4-a4a211b23a46.png)

`i` is the index used to iterate over `a` within region bounded by min,max.

`j` is the index used to iterate over `b` within region bounded by min,max.


## Case 1 : Both `a` and  `b` have `n` digits ## 
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
This case could be eliminated if we simply make both `a` and `b` the same length initially by adding leading zeroes. Then, before returning our answer, we remove any leading zeroes. However, this approach wastes a lot of time when both strings are very long.

To bypass this problem, we simply reduce the total number of steps and the number of single digit product at each step to eliminate cases where the 1-digit multiplication involves a leading zero.

# How testing was carried out #
There are 1000 test cases.

Each test case generates a set of 2 random numbers whose lengths vary between 100 and 1000 digits.

A counter is incremented each time, the vedic algorithm performs better than the karatsuba algorithm.

In the end, the success rate is calculated.

# Current limitation #

`a` and `b` must have less than 2^32 digits because string data type can only store 2^32 characters.
