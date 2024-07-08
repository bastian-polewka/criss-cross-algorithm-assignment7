/*
 * Bastian Polewka Assignment 7
 * optimized the vedic method to be faster through vectors, integers and a different loop
 * mul.cpp and mul.h necessary for comparison, makefile in forked repo
 * use numbers with a high amount of digits to see the difference in execution time
 * forked gitHub repo: https://github.com/bastian-polewka/criss-cross-algorithm-assignment7
 * original gitHub repo: https://github.com/creme332/criss-cross-algorithm
*/
#define ll long long
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include "mul.h"

std::string optVedic(std::string a, std::string b) {
    if (a == "0" || b == "0")
        return "0";
    // a must have same number/more digits than b, use swap for better readability
    if (b.length() > a.length())
        std::swap(a, b);

    const ll a_size = static_cast<ll>(a.size());
    const ll b_size = static_cast<ll>(b.size());
    const ll totalsteps = a_size + b_size; // steps necessary to get the result
    std::vector<ll> int_result(totalsteps, 0); // intermediate result

    // convert characters to integers for faster processing and reverse order for easier loop in criss-cross computation
    std::vector<ll> a_digits(a_size), b_digits(b_size);
    std::transform(a.rbegin(), a.rend(), a_digits.begin(), [](char c) { return c - '0'; });
    std::transform(b.rbegin(), b.rend(), b_digits.begin(), [](char c) { return c - '0'; });

    for (ll step = 0; step < totalsteps; step++) {
        ll sum = 0;
        const ll start = (step >= b_size) ? (step - b_size + 1) : 0; // start digit for criss-cross
        const ll end = (step < a_size) ? step : (a_size - 1); // end digit for criss-cross

        for (ll i = start; i <= end; i++) {
            sum += a_digits[i] * b_digits[step - i];
        }
        int_result[step] += sum;
        int_result[step + 1] += int_result[step] / 10; //add carry to next step
        int_result[step] %= 10;
    }

    std::string result;
    result.reserve(totalsteps);
    // convert digits back to string and erase leading zeros
    bool leading_zero = true;
    for (ll i = totalsteps - 1; i >= 0; --i) {
        if (leading_zero && int_result[i] == 0) {
            continue;
        }
        leading_zero = false;
        result.push_back(int_result[i] + '0');
    }
    return result;
}

int main() {
    // use large numbers
    std::string num1 = "9384750984327509843273427889574320895704392570439275094327509483750934875300984354754367567852365773454354657567523423545534434543447623546345267457853467789876";
    std::string num2 = "38957034875983075423875837089573875893758943758943759834759834324234325436554327654745875213457098564370698734534567254554345654534441251351563545333443543212243554";
    Mul Multiplier(num1, num2);
    clock_t start_time, end_time;
    float diff;

    start_time = std::clock();
    Multiplier.vedic();
    end_time = std::clock();
    diff = static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Vedic: " << 1000*diff << " milliseconds \n";

    start_time = std::clock();
    Multiplier.basicVedic();
    end_time = std::clock();
    diff = static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "basicVedic: " << 1000*diff << " milliseconds \n";

    start_time = std::clock();
    optVedic(num1, num2);
    end_time = std::clock();
    diff = static_cast<float>(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "optVedic: " << 1000*diff << " milliseconds \n";

    return 0;
}
