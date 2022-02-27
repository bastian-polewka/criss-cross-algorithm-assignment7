/*DISCLAIMER
This code is not mine and was copied from https://www.codewars.com/kata/reviews/59d4a77792836c2ee100048b/groups/5f46c09915fbdc0001312497 
MUST CHANGE. 
*/
#include <iostream>
#include <string>

using namespace std;

string add(string x, string y);
string subtract(string x, string y);

// karatsuba's recursive algorithm
string multiply(string x, string y) {
  int length {max((int)x.size(), (int)y.size())};
  while ((int)x.size() < length)
    x.insert(0, "0");
  while ((int)y.size() < length)
    y.insert(0, "0");
  if (length == 1)
    return to_string((x[0]-'0')*(y[0]-'0'));
  string a {x.substr(0, length/2)}, b {x.substr(length/2, length-length/2)}, c {y.substr(0, length/2)}, d {y.substr(length/2, length-length/2)};
  string ac {multiply(a, c)}, bd {multiply(b, d)}, apbcpd {multiply(add(a, b), add(c, d))};
  string apbcpdm {subtract(apbcpd, add(ac, bd))};
  for (int i {}; i < 2*(length-length/2); i++)
    ac.append("0");
  for (int i {}; i < length-length/2; i++)
    apbcpdm.append("0");
  string ans {add(add(ac, bd), apbcpdm)};
  return ans.erase(0, min(ans.find_first_not_of("0"), ans.size()-1));
}

string add(string x, string y) {
  int length {max((int)x.size(), (int)y.size())}, carry {}, sum_col {};
  string ans;
  while ((int)x.size() < length)
    x.insert(0, "0");
  while ((int)y.size() < length)
    y.insert(0, "0");
  for (int i {length-1}; i >= 0; i--) {
    sum_col = (x[i]-'0') + (y[i]-'0') + carry;
    carry = sum_col/10;
    ans.insert(0, to_string(sum_col % 10));
  }
  if (carry)
    ans.insert(0, to_string(carry));
  ans.erase(0, min((int)ans.find_first_not_of('0'), (int)ans.size()-1));
  return (ans.size() > 0)? ans : "0";
}

string subtract(string x, string y) {
  int length {max((int)x.size(), (int)y.size())}, diff {};
  string ans {};
  while ((int)x.size() < length)
    x.insert(0, "0");
  while ((int)y.size() < length)
    y.insert(0, "0");
  for (int i {length-1}; i >= 0; i--) {
    diff = x[i] - y[i];
    if (diff >= 0)
      ans.insert(0, to_string(diff));
    else {
      int j {i-1};
      while (j >= 0) {
        x[j] = ((x[j]-'0')-1)%10+'0';
        if (x[j] != '9')
          break;
        else
          j--;
      }
      ans.insert(0, to_string(diff+10));
    }
  }
  return ans.erase(0, min((int)ans.find_first_not_of("0"), (int)ans.size()-1));
}
