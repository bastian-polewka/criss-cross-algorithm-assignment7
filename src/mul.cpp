#include "mul.h"

string Mul::sanitize(string n) {
  // remove spaces from string: https://stackoverflow.com/a/83481/17627866
  std::string::iterator end_pos = std::remove(n.begin(), n.end(), ' ');
  n.erase(end_pos, n.end());

  // remove leading zeroes from string:
  // https://stackoverflow.com/a/25726706/17627866
  size_t zeroCount = count(n.begin(), n.end(), '0');
  if (zeroCount == n.size() && n.size() != 0)
    n = "0";
  else {
    n.erase(0, n.find_first_not_of('0'));
  }
  return n;
}

Mul::Mul(string n1, string n2) {
  n1 = sanitize(n1);
  n2 = sanitize(n2);

  // validate strings
  if (!validate(n1) || !validate(n2)) {
    throw std::invalid_argument("Invalid string inputs");
  }

  multiplicand = n1;
  multiplier = n2;
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

string Mul::getMultiplicand() {
  return multiplicand;
}

string Mul::getMultiplier() {
  return multiplier;
}

string Mul::vedic(string a, string b) {
  // corner cases
  if (a == "0" || b == "0")
    return "0";
  if (a == "1")
    return b;
  if (b == "1")
    return a;

  // swap strings, if needed, so that `a` has the same number/more digits than b
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
  string sum = "0", carry = "0";
  ll lines = 0;  // number of multiplications on each step

  // Each step finds 1 digit of the answer
  for (ll step = 1; step <= totalsteps; step++) {
    sum = "0";  // reset sum

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
      const ll digitProd = (a[i] - '0') * (b[j] - '0');
      sum = add(sum, std::to_string(digitProd));
      i--;
      j++;
    }
    sum = add(sum, carry);
    carry = (sum.size() == 1) ? "0" : sum.substr(0, sum.size() - 1);
    ans = sum[sum.size() - 1] + ans;
    min--;
  }
  if (carry != "0") {
    ans = carry + ans;
  }
  return ans;
}

string Mul::vedic() {
  return vedic(multiplicand, multiplier);
}

string Mul::add(string n1, string n2) {
  // make n1 and n2 the same length
  n1 = string(std::max(n1.size(), n2.size()) + 1 - n1.size(), '0') + n1;
  n2 = string(n1.size() - n2.size(), '0') + n2;
  for (int i = n1.size() - 1, carry = 0; i >= 0; i--) {
    int sum = n1[i] + n2[i] - 96 + carry;
    carry = sum / 10;
    n1[i] = sum % 10 + '0';
  }
  // remove leading zeroes
  int i = n1.find_first_not_of('0');
  return 0 <= i ? n1.substr(i) : n1.substr(0, 1);
}

string Mul::subtract(string a, string b) {
  string str = "";
  int n1 = a.length(), n2 = b.length();
  int diff = n1 - n2;
  int carry = 0;

  for (int i = n2 - 1; i >= 0; i--) {
    int sub = ((a[i + diff] - '0') - (b[i] - '0') - carry);
    if (sub < 0) {
      sub = sub + 10;
      carry = 1;
    } else
      carry = 0;
    str.push_back(sub + '0');
  }

  // subtract remaining digits of str1[]
  for (int i = n1 - n2 - 1; i >= 0; i--) {
    if (a[i] == '0' && carry) {
      str.push_back('9');
      continue;
    }
    int sub = ((a[i] - '0') - carry);
    if (i > 0 || sub > 0)  // remove preceding 0's
      str.push_back(sub + '0');
    carry = 0;
  }

  reverse(str.begin(), str.end());

  // remove leading zeroes
  int i = str.find_first_not_of('0');
  return 0 <= i ? str.substr(i) : str.substr(0, 1);
}

string Mul::karatsuba(string lhs, string rhs) {
  // Reference: https://drawar.github.io/karatsuba-cpp/
  const ll s1 = lhs.size();
  const ll s2 = rhs.size();
  ll length = std::max(s1, s2);

  lhs = string(length - s1, '0') + lhs;
  rhs = string(length - s2, '0') + rhs;

  if (length == 1)
    return std::to_string((lhs[0] - '0') * (rhs[0] - '0'));

  string lhs0 = lhs.substr(0, length / 2);
  string lhs1 = lhs.substr(length / 2, length - length / 2);
  string rhs0 = rhs.substr(0, length / 2);
  string rhs1 = rhs.substr(length / 2, length - length / 2);

  string p0 = karatsuba(lhs0, rhs0);
  string p1 = karatsuba(lhs1, rhs1);
  string p2 = karatsuba(add(lhs0, lhs1), add(rhs0, rhs1));
  string p3 = subtract(p2, add(p0, p1));

  for (int i = 0; i < 2 * (length - length / 2); i++)
    p0.append("0");
  for (int i = 0; i < length - length / 2; i++)
    p3.append("0");

  string result = add(add(p0, p1), p3);

  return result.erase(
      0, std::min(result.find_first_not_of('0'), result.size() - 1));
}

string Mul::karatsuba() {
  return karatsuba(multiplicand, multiplier);
}

string Mul::basicVedic(string a, string b) {
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

string Mul::basicVedic() {
  return basicVedic(multiplicand, multiplier);
}