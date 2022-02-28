#include <iostream>
#include <string>
#include <regex>
#include <chrono>
#define ll long long
using namespace std;
using namespace std::chrono;

string add(string a, string b)
{
    a = string(max(a.size(), b.size()) + 1 - a.size(), '0') + a;
    b = string(a.size() - b.size(), '0') + b;
    for (int i = a.size() - 1, carry = 0; i >= 0; i--)
    {
        int sum = a[i] + b[i] - 96 + carry;
        carry = sum / 10;
        a[i] = sum % 10 + '0';
    }
    int i = a.find_first_not_of('0');
    return 0 <= i ? a.substr(i) : a.substr(0, 1);
}
string subtract(string a, string b) {
    string str = "";
    int n1 = a.length(), n2 = b.length();
    int diff = n1 - n2;
    int carry = 0;

    for (int i = n2 - 1; i >= 0; i--) {
        int sub = ((a[i + diff] - '0') - (b[i] - '0') - carry);
        if (sub < 0) { sub = sub + 10; carry = 1; }
        else carry = 0;
        str.push_back(sub + '0');
    }

    // subtract remaining digits of str1[]
    for (int i = n1 - n2 - 1; i >= 0; i--) {
        if (a[i] == '0' && carry) {
            str.push_back('9');
            continue;
        }
        int sub = ((a[i] - '0') - carry);
        if (i > 0 || sub > 0) // remove preceding 0's
            str.push_back(sub + '0');
        carry = 0;
    }

    reverse(str.begin(), str.end());

    //remove leading zeroes
    int i = str.find_first_not_of('0');
    return 0 <= i ? str.substr(i) : str.substr(0, 1);
}
string karatsuba(string n1, string n2) {
    if (n1.length() < 2 && n2.length() < 2) { return to_string(stoi(n1) * stoi(n2)); }

    ll n = max(n1.length(), n2.length());
    ll half = n / 2;

    string a, b, c, d;
    if (n1.length() - half <= 0) { a = "0"; b = n1; }
    else {
        a = n1.substr(0, n1.length() - half);
        b = n1.substr(n1.length() - half, half);
    }

    if (n2.length() - half <= 0) { c = "0"; d = n2; }
    else {
        c = n2.substr(0, n2.length() - half);
        d = n2.substr(n2.length() - half, half);
    }

    string ac = karatsuba(a, c);
    string bd = karatsuba(b, d);
    string ad_plus_bc = karatsuba(add(a, b), add(c, d));
    ad_plus_bc = subtract(ad_plus_bc, ac);
    ad_plus_bc = subtract(ad_plus_bc, bd);

    ac += string(2 * half, '0');
    ad_plus_bc += string(half, '0');

    return add(add(ac, ad_plus_bc), bd);

}

string vedic1(string a, string b) {
    if (b.length() > a.length()) { string t = b; b = a; a = t; }

    const ll asize = static_cast<ll>(a.size());
    const ll bsize = static_cast<ll>(b.size());
    ll totalsteps = asize + bsize - 1;
    string ans = "";
    ll max = asize - 1, min = bsize - 1;
    ll sum = 0, carry = 0;
    ll lines = 0; //number of multiplications on each step

    //Each step finds 1 digit of the answer
    for (ll step = 1;step <= totalsteps; step++) {
        sum = 0; //reset sum

        if (step <= asize) {lines = step;}
        else {lines= asize - (step- asize);}

        if (min < 0) {
            min = 0;
            max--;
            if (step < asize) {
                lines -= step - bsize;
            }
            else {
                lines -= asize - bsize;
            }
        }

        ll i = max, j = min;

        for (ll k = 0;k < lines;k++) {
            sum += (a[i] - '0') * (b[j] - '0');
            i--; j++;
        }
        sum += carry;
        carry = sum / 10;
        ans = to_string(sum % 10) + ans;
        min--;
    }
    if (carry != 0) { ans = to_string(carry) + ans; }
    return ans;
}

ll TimeAlgorithm(int algorithm, string p, string q) {

    if (algorithm == 0) { //time vedic algorithm
        auto start = high_resolution_clock::now();
        vedic1(p, q);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        return   duration.count(); 

    }

    if (algorithm == 1) { //time karatsuba
        auto start = high_resolution_clock::now();
        karatsuba(p,q);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        return  duration.count();

    }
}

string GenerateRandomNumber(ll n) {
    //Generates a random positive integer having n digits. n > 0
    string num = "0"; 

    //first digit must be non-zero.
    while (num == "0") {
        num = to_string(rand() % 10);
    }
    n--;
    //other digits can be 0-9
    while (n--) {
        num += to_string(rand() % 10); 
    }
    return num;
}


int main() {   
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll t = 50; //number of test cases
    ll c = 0; //number of times vedic() took less time than karatsuba().
    ll vedictotal = 0;
    ll karatsubatotal = 0;

    double diff = 0;
    for (ll i = 0;i < t;i++) {
           if (i % 10 == 0) { cout <<i << "\n";}
            ll NumberOfDigits = 5000; //this number is varied
            string n1 = GenerateRandomNumber(NumberOfDigits); 
            string n2 = GenerateRandomNumber(NumberOfDigits);

            ll t0 = TimeAlgorithm(0, n1, n2); //time taken by algo 0
            ll t1 = TimeAlgorithm(1, n1, n2); //time taken algo 1
            vedictotal += t0;
            karatsubatotal += t1;

            if (t0<t1) {
                diff += (1 - (double(t0) / double(t1))); //by how much t0 is smaller
                c++;
            }
    }
    cout << "Averate time vedic() :" << vedictotal / t << "\n";
    cout << "Averate time karatsuba() :" << karatsubatotal / t << "\n";
    cout << "In "<< (100 * c) / (t)<< "% of test cases Algorithm 0 took less time than Algorithm 1. " << endl;
    cout << "On average, Algorithm 0 took " << (100 * diff) / double(t) << "% less time than Algorithm 1 \n";
}
