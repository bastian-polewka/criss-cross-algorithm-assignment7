#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../src/mul.h"
#include "timer.h"
#define ll long long

std::random_device rd;   // obtain a random number from hardware
std::mt19937 gen(rd());  // seed the generator

/**
 * @brief Generates a random positive integer having n digits.
 *
 * @param n Number of digits in n. n>0
 * @return string
 */
string getRandomNumber(ll n) {
  assert(n > 0);
  std::uniform_int_distribution<> distr(0, 9);  // inclusive range
  string num;

  // generate first non-zero digit.
  do {
    num = std::to_string(distr(gen));
  } while (num == "0");
  n--;

  // generate remaining digits which can be 0-9
  while (n--) {
    num += std::to_string(distr(gen));
  }

  return num;
}

std::vector<std::vector<string>> getQuestions(ll n = 50, ll digitCount = 1000) {
  std::vector<std::vector<string>> result;

  for (ll i = 0; i < n; i++) {
    string multiplicand = getRandomNumber(digitCount);
    string multiplier = getRandomNumber(digitCount);
    result.push_back({multiplicand, multiplier});
  }
  return result;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::cout << "Running benchmarks...\n";

  // initialise parameters of benchmark
  const ll totalTestCases =
      100;  // number of multiplications to be perfomed for each algorithm
  ll digitCount = 100;  // number of digits in multiplier and multiplicand

  ll win = 0;

  // generate numbers to be multiplied
  std::vector<std::vector<string>> quests =
      getQuestions(totalTestCases, digitCount);

  // create arrays to store products calculated by each algorithm
  std::vector<string> vResults;
  std::vector<string> kResults;

  // create arrays to store time taken by each algorithm for each product
  std::vector<double> vDuration;
  std::vector<double> kDuration;

  // Initialise timer
  Timer clock;

  string multiplicand, multiplier, product;
  for (auto question : quests) {
    // get numbers to be multiplied
    multiplicand = question[0];
    multiplier = question[1];
    // std::cout << "Calculating " << multiplicand << " x " << multiplier
    //           << std::endl;

    // initialise calculator
    Mul calc(multiplicand, multiplier);

    // Perform vedic multiplication
    clock.start();
    product = calc.vedic();
    clock.stop();

    // save product and time to array
    vResults.push_back(product);
    vDuration.push_back(clock.duration());

    // Perform karatsuba multiplication
    clock.start();
    product = calc.karatsuba();
    clock.stop();

    // save product and time to array
    kResults.push_back(product);
    kDuration.push_back(clock.duration());

    if (kDuration.back() > vDuration.back())
      win++;

    // products calculated by both algoritm should be equal
    assert(vResults.back() == kResults.back());
  }
  std::cout << "Vedic won " << win << " times\n";
  std::cout << "Saving results to file...\n";
}
