# VedicMultiplicationAlgorithm
Also known as the Criss-Cross multiplication algorithm, this 50-lines long algorithm, requiring no advanced math knowledge,  multiplies large string numbers in atleast 90% LESS time than Karatsuba algorithm. 1000-digit long string numbers can be multiplied almost instantly.
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


# Case 1 : `a` and  `b` are of the same length # 

# Case 2 : `b` has fewer digits than `a` # 


To bypass this problem, I 
# How testing was carried out #
There are 1000 test cases.

Each test case generates a set of 2 random numbers whose lengths vary between 100 and 1000 digits.

A counter is incremented each time, the vedic algorithm performs better than the karatsuba algorithm.

In the end, the success rate is calculated.

# Current limitation #
The sum of the number of digits in both strings must be less than 2^63 (because of long long data type is used). 
