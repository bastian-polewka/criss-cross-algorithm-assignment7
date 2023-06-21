// string add(string a, string b)
// {
//     a = string(max(a.size(), b.size()) + 1 - a.size(), '0') + a;
//     b = string(a.size() - b.size(), '0') + b;
//     for (int i = a.size() - 1, carry = 0; i >= 0; i--)
//     {
//         int sum = a[i] + b[i] - 96 + carry;
//         carry = sum / 10;
//         a[i] = sum % 10 + '0';
//     }
//     int i = a.find_first_not_of('0');
//     return 0 <= i ? a.substr(i) : a.substr(0, 1);
// }

// string subtract(string a, string b) {
//     string str = "";
//     int n1 = a.length(), n2 = b.length();
//     int diff = n1 - n2;
//     int carry = 0;

//     for (int i = n2 - 1; i >= 0; i--) {
//         int sub = ((a[i + diff] - '0') - (b[i] - '0') - carry);
//         if (sub < 0) { sub = sub + 10; carry = 1; }
//         else carry = 0;
//         str.push_back(sub + '0');
//     }

//     // subtract remaining digits of str1[]
//     for (int i = n1 - n2 - 1; i >= 0; i--) {
//         if (a[i] == '0' && carry) {
//             str.push_back('9');
//             continue;
//         }
//         int sub = ((a[i] - '0') - carry);
//         if (i > 0 || sub > 0) // remove preceding 0's
//             str.push_back(sub + '0');
//         carry = 0;
//     }

//     reverse(str.begin(), str.end());

//     //remove leading zeroes
//     int i = str.find_first_not_of('0');
//     return 0 <= i ? str.substr(i) : str.substr(0, 1);
// }

// string karatsuba(string n1, string n2) {
//     if (n1.length() < 2 && n2.length() < 2) { return to_string(stoi(n1) * stoi(n2)); }

//     ll n = max(n1.length(), n2.length());
//     ll half = n / 2;

//     string a, b, c, d;
//     if (n1.length() - half <= 0) { a = "0"; b = n1; }
//     else {
//         a = n1.substr(0, n1.length() - half);
//         b = n1.substr(n1.length() - half, half);
//     }

//     if (n2.length() - half <= 0) { c = "0"; d = n2; }
//     else {
//         c = n2.substr(0, n2.length() - half);
//         d = n2.substr(n2.length() - half, half);
//     }

//     string ac = karatsuba(a, c);
//     string bd = karatsuba(b, d);
//     string ad_plus_bc = karatsuba(add(a, b), add(c, d));
//     ad_plus_bc = subtract(ad_plus_bc, ac);
//     ad_plus_bc = subtract(ad_plus_bc, bd);

//     ac += string(2 * half, '0');
//     ad_plus_bc += string(half, '0');

//     return add(add(ac, ad_plus_bc), bd);

// }
