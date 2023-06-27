#include <algorithm>
#include <stdexcept>
#include <string>
#define ll long long
using std::string;

class Mul {
 private:
  string multiplicand;  // first number
  string multiplier;    // second number

  /**
   * @brief Checks if string is valid. To be valid
   * a string must contain only numeric characters and must not be empty
   *
   * @param k input string
   * @return true string is valid
   * @return false string is invalid
   */
  bool validate(string k);

  /**
   * @brief Removes spaces and leading zeroes from string
   *
   * @param n Input numeric string
   * @return string Final string
   */
  string sanitize(string n);

  string add(string n1, string n2);

  string subtract(string n1, string n2);

  string karatsuba(string n1, string n2);

  string vedic(string n1, string n2);

 public:
  Mul(string n1, string n2);

  /**
   * @brief Performs criss-cross multiplication on two integers.
   *
   * @return string
   */
  string vedic();

  /**
   * @brief Performs multiplication using schoolboy algorithm
   *
   * @return string
   */
  string naive();

  /**
   * @brief Performs multiplication using karatsuba algorithm
   *
   * @return string
   */
  string karatsuba();

  /**
   * @brief Returns first integer part of multiplication
   *
   * @return string
   */
  string getMultiplicand();

  /**
   * @brief Returns second integer part of multiplication
   *
   * @return string
   */
  string getMultiplier();
};