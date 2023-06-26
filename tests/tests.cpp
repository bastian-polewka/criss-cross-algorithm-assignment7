#include "../src/mul.h"
#include "doctest.h"

TEST_CASE("Constructor") {
  SUBCASE("Empty strings") {
    CHECK_THROWS_WITH(Mul("", ""), "Invalid string inputs");
  }

  SUBCASE("String with minus sign") {
    CHECK_THROWS_WITH(Mul("-12443 ", "999"), "Invalid string inputs");
  }

  SUBCASE("String with non-numeric characters") {
    CHECK_THROWS_WITH(Mul("two ", "32jhl&"), "Invalid string inputs");
  }

  SUBCASE("Numeric strings with spaces") {
    CHECK_NOTHROW(Mul(" 1245 523 3443 ", "999 999 999"));
  }

  SUBCASE("Numeric strings with no spaces") {
    CHECK_NOTHROW(Mul("1442", "99"));
  }
  SUBCASE("Long numeric strings") {
    CHECK_NOTHROW(Mul(string(1000, '9'), string(1000, '5')));
  }
}