#include <algorithm>
#include <stdexcept>
#include <string>
#define ll long long
using std::string;

class Mul {
 private:
  string a;
  string b;
  string result;

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

 public:
  Mul(string n1, string n2);

  string vedic();

  string naive();

  string karatsuba();

  /**
   * @brief Returns first integer part of multiplication
   *
   * @return string
   */
  string getA();

  /**
   * @brief Returns second integer part of multiplication
   *
   * @return string
   */
  string getB();
};