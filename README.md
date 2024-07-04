# Criss-Cross Multiplication 
![Badge for test workflow](https://github.com/creme332/criss-cross-algorithm/actions/workflows/test.yml/badge.svg)

A 50-lines algorithm for multiplying large positive integers in string format. For numbers having less than 100 digits, it outperforms the Karatsuba algorithm by as much as 50%.

<img src="3x3.gif"  width="300" height="300">

Read more about the algorithm in this [post](https://creme332.github.io/posts/criss-cross-multiplication/).

## Usage
Import `mul.h` in your program and initialise a `Mul` object as follows:
```cpp
Mul Multiplier("9912", "54564");
Multiplier.vedic(); // 540838368
```

The `Mul` class has  3 methods for multiplication:

| Method         | Description                                                                                                                                                     |
| -------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `basicVedic()` | A simpler and faster implementation of the criss-cross algorithm but is more limited since it uses basic arithmetic operators for addition and subtraction. |
| `vedic()`      | A version of `basicVedic()` that uses helper functions for  adding and subtracting large string numbers.                                                        |
| `karatsuba()`  | Uses the Karatsuba algorithm for multiplication. Algorithm uses helper functions for adding and subtracting large string numbers.                       |

## References

- [Criss cross algorithm](https://www.youtube.com/watch?v=JhGzbN5YuPo)
- [Karatsuba algorithm](https://drawar.github.io/karatsuba-cpp/)
- [Code for benchmarking](https://www.youtube.com/watch?v=YG4jexlSAjc&ab_channel=TheCherno)
