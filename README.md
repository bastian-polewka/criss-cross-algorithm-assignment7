# Criss-Cross Multiplication 
![Badge for test workflow](https://github.com/creme332/criss-cross-algorithm/actions/workflows/test.yml/badge.svg)

A 50-lines algorithm for multiplying large positive integers in string format. For numbers having less than 100 digits, it outperforms the Karatsuba algorithm by as much as 50%.

<img src="3x3.gif"  width="300" height="300">

Read more about the algorithm in this [post](https://creme332.github.io/posts/criss-cross-multiplication/).


## Installation

To install project:
```
git clone git@github.com:creme332/criss-cross-algorithm.git
```

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

## Run benchmarks
To run benchmarks:
```
g++ benchmarks/main.cpp benchmarks/timer.cpp src/mul.cpp -W
./a.out
```
A folder `output` will be created inside the `benchmarks` folder. This new folder will contain the following files:

| File name     | Content                                                                                                                                      |
| ------------- | -------------------------------------------------------------------------------------------------------------------------------------------- |
| `input.txt`   | A list of multiplicands and multipliers which were generated during runtime.                                                                 |
| `time.txt`    | Each line contains 2 values representing the time taken for vedic and karatsuba algorithms respectively                                      |
| `product.txt` | Each line contains 2 values representing the product calculated by vedic and karatsuba algorithms respectively. These values should be same. |


## Run tests

```bash
g++ test_runner.cpp tests/tests.cpp src/mul.cpp -W
./a.out
```

## To-do

* [ ] Use Google Benchmark for benchmarks

## References

- [Criss cross algorithm](https://www.youtube.com/watch?v=JhGzbN5YuPo)
- [Karatsuba algorithm](https://drawar.github.io/karatsuba-cpp/)
- [Code for benchmarking](https://www.youtube.com/watch?v=YG4jexlSAjc&ab_channel=TheCherno)
