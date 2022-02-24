# VedicMultiplicationAlgorithm
Criss-Cross multiplication algorithm for multiplying large string numbers. It takes atleast 90% LESS time than Karatsuba algorithm and can multiply 1000-digit numbers almost instantly.
## Time complexity ##
![image](https://user-images.githubusercontent.com/65414576/155485833-6879c3a5-96af-46da-8bd8-24ec270fc61a.png)

Worst case scenario is when the 2 digits have the same number of digits. 
## Function call ##
```cpp
vedic(a, b)
``` 
where a,b are **positive integers in string format**.

# Criss-Cross multiplication # 

Unlike the Karatsuba algorithm, the Criss-Cross algorithm can also be used to manually multiply numbers in a SINGLE line using pen and paper. And obviously, it is faster than the grade-school algorithm for multiplying numbers.

For more explanations on the algorithm refer to :
1. Page 27 in this book
2. https://www.youtube.com/watch?v=iNQ9Mj_zS-I&ab_channel=SumanTVEducation
# How my code works #

# How testing was carried out #
There are 1000 test cases.

Each test case generates a set of 2 random numbers whose lengths vary between 100 and 1000 digits.

A counter is incremented each time, the vedic algorithm performs better than the karatsuba algorithm.

In the end, the success rate is calculated.

# Source of other algorithms #
The Karatsuba algorithm used for testing was copied from user LogicalX : https://www.codewars.com/kata/reviews/59d4a77792836c2ee100048b/groups/5f46c09915fbdc0001312497

I also tested other versions of the Karatsuba algorithm but the result was same.
