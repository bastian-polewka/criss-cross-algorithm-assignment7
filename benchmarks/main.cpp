#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "../src/mul.h"
#include "timer.h"

#define ll long long
using namespace std;
using namespace std::chrono;

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
  string num = "0";

  // first digit must be non-zero.
  do {
    num = to_string(distr(gen));
  } while (num == "0");

  n--;

  // other digits can be 0-9
  while (n--) {
    num += to_string(distr(gen));
  }
  return num;
}

vector<vector<string>> getQuestions(ll n = 50, ll digitCount = 1000) {
  vector<vector<string>> result;

  for (ll i = 0; i < n; i++) {
    string multiplicand = getRandomNumber(1000);
    string multiplier = getRandomNumber(1000);
    result.push_back({multiplicand, multiplier});
  }
  return result;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  const ll test_cases_count =
      50;  // number of multiplications to be perfomed for each algorithm
  ll digitCount = 500;  // number of digits in multiplier and multiplicand
  vector<vector<string>> quests =
      getQuestions(50, digitCount);  // generate numbers to be multiplied
  vector<string> vResults;
  vector<string> kResults;

  ll vedic_win_count =
      0;  // number of times vedic() took less time than karatsuba()
  ll vedic_total_time = 0;
  ll karatsuba_total_time = 0;
  double diff = 0;

  string n1, n2, product;
  for (auto question : quests) {
    // get numbers are to be multiplied
    n1 = question[0];
    n2 = question[1];

    // initialise calculator
    Mul calc(n1, n2);

    // Initialise two timers, one for each algorithm
    Timer vTimer;
    Timer kTimer;

    // Perform vedic multiplication
    vTimer.start();
    product = calc.vedic();
    vTimer.stop();

    // save product to array
    vResults.push_back(product);

    // Perform karatsuba multiplication
    vTimer.start();
    product = calc.karatsuba();
    vTimer.stop();

    // save product to array
    kResults.push_back(product);
  }
}
