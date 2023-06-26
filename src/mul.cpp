#include "mul.h"

Mul::Mul(string n1, string n2) {
  // remove spaces from strings : https://stackoverflow.com/a/83481/17627866
  std::string::iterator end_pos = std::remove(n1.begin(), n1.end(), ' ');
  n1.erase(end_pos, n1.end());

  end_pos = std::remove(n2.begin(), n2.end(), ' ');
  n2.erase(end_pos, n2.end());

  // validate strings
  if (!validate(n1) || !validate(n2)) {
    throw std::invalid_argument("Invalid string inputs");
  }
}

bool Mul::validate(string k) {
  // reject empty strings
  if (k.length() == 0) {
    return 0;
  }

  // reject strings containing non-numeric characters
  // https://stackoverflow.com/a/8889045/17627866
  if (k.find_first_not_of("0123456789") != std::string::npos) {
    return 0;
  }

  return 1;
}

string Mul::vedic() {
  if (a == "0" || b == "0")
    return "0";
  // a must have same number/more digits than b
  if (b.length() > a.length()) {
    string t = b;
    b = a;
    a = t;
  }

  const ll asize = static_cast<ll>(a.size());
  const ll bsize = static_cast<ll>(b.size());
  ll totalsteps = asize + bsize - 1;
  string ans = "";
  ll max = asize - 1, min = bsize - 1;
  ll sum = 0, carry = 0;
  ll lines = 0;  // number of multiplications on each step

  // Each step finds 1 digit of the answer
  for (ll step = 1; step <= totalsteps; step++) {
    sum = 0;  // reset sum

    if (step <= asize) {
      lines = step;
    } else {
      lines = asize - (step - asize);
    }

    // at this point, lines = number of multiplications required for current
    // step, assuming no leading zeroes in b reduce this number further if there
    // are leading zeroes in b
    if (min < 0) {
      min = 0;
      max--;
      if (step < asize) {
        lines -= step - bsize;
      } else {
        lines -= asize - bsize;
      }
    }

    // cross-multiply
    ll i = max, j = min;
    for (ll k = 0; k < lines; k++) {
      sum += (a[i] - '0') * (b[j] - '0');
      i--;
      j++;
    }
    sum += carry;
    carry = sum / 10;
    ans = std::to_string(sum % 10) + ans;
    min--;
  }
  if (carry != 0) {
    ans = std::to_string(carry) + ans;
  }
  return ans;
}