#define ll long long
#include <string>
using std::string;

class Mul {
 private:
  string a;
  string b;
  string result;

  /**
   * @brief Checks if string contains only valid characters
   *
   * @return true
   * @return false
   */
  bool validate();

  /**
   * @brief Sanitizes user input by removing spaces etc...
   *
   */
  void sanitize(string k);

 public:
  Mul(string n1, string n2);

  string vedic();

  string naive();

  string karatsuba();
};