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
min and max kee keep track of region within which multiplication will take place.

When the numbers differ in the number of digits, the normal algorithm adds leading zeroes to the smaller number to make it the same length as the bigger number.
However, this process, when implemented programmatically, increases the execution time because at the end the answer might contain leading zeroes which must be removed.

To bypass this problem, I 
# How testing was carried out #
There are 1000 test cases.

Each test case generates a set of 2 random numbers whose lengths vary between 100 and 1000 digits.

A counter is incremented each time, the vedic algorithm performs better than the karatsuba algorithm.

In the end, the success rate is calculated.

# Current limitation #
The number of digits in both strings must be less than 2^63 (because of long long data type). This also means that ![image](https://user-images.githubusercontent.com/65414576/155576502-d5ba37c3-f39e-4775-9e05-2ba071b073e1.png)
