string vedic(string a, string b) {
    //a must have same number/more digits than b
    if (b.length() > a.length()) {string t = b; b = a; a = t;}
    ll totalsteps = 2 * a.length() - 1;
    string ans = "";
    ll max = a.length() - 1, min = b.length() - 1;
    ll sum = 0, carry = 0;
    ll zeroes = a.length() - b.length(); //number of leading zeroes in b
    ll lines = 0; //number of multiplications on each step

    //Each step finds 1 digit of the answer
    for (ll step = 1;step <= totalsteps-zeroes;step++) {
        sum = 0; //reset sum
        if (min >= 0 || abs(min) <= zeroes) {lines++;}

        if (min < 0 && abs(min) > zeroes) { //end of string b and end of leading zeroes
                max--;
                min = -zeroes;
                lines--;
        }

        ll i = max, j = min;
        //LIMITATION : Unnecessary comparisons when there are leading zeroes in b. lines is too much.
        for (ll k = 0;k < lines;k++) {
            if (i>=0 && j>=0 && j<b.length() && i<a.length()) {
                sum += (a[i] - '0') * (b[j] - '0');
            }
            i--;j++;
        }
        sum += carry;
        carry = sum / 10;
        ans = to_string(sum % 10) + ans;
        min--;
    }
    if (carry != 0) { ans = to_string(carry) + ans;}
    return ans;
}

string ImprovedVedic(string a, string b) {
    if (b.length() > a.length()) { string t = b; b = a; a = t; } //remove later

    string ans = "";
    ll totalsteps = a.length() + b.length() - 1; //1st improvement
    ll max = a.length() - 1, min = b.length() - 1;
    ll sum = 0, carry = 0;
    ll lines = 0; //number of multiplications on each step
    ll zeroes = 0;
    //Each step finds 1 digit of the answer
    for (ll step = 1;step <= totalsteps;step++) {
        sum = 0; //reset sum
        if (min >= 0) { lines++; }
        else { zeroes++; max--; min = 0;lines -= zeroes;}

        ll i = max; // i: a and j:b
        ll j = min;
        for (ll k = 0;k < lines;k++) {
            sum += (a[i] - '0') * (b[j] - '0');
            i--; j++;
        }
        //while (j<b.length() && i >= 0) { //use for loop instead
        //    sum += (a[i] - '0') * (b[j] - '0');
        //    i--; j++;
        //}
        sum += carry;
        carry = sum / 10;
        ans = to_string(sum % 10) + ans;
        min--;
    }
    if (carry != 0) {ans = to_string(carry) + ans;}
    return ans;
}

string Easyvedic(string a, string b) {
    const ll asize = static_cast<ll>(a.size());
    const ll bsize = static_cast<ll>(b.size());
    ll totalsteps = 2*asize - 1;
    string ans = "";
    ll max = asize - 1, min = max;
    ll sum = 0, carry = 0;

    for (ll step = 1;step <= totalsteps; step++) {
        if (min < 0) {min = 0; max--;}

        sum = 0;
        ll i = max, j = min;
        while (j<b.length() && i >= 0) { 
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

string vedic1(string a, string b) {//BEST ALGO SO FAR
    //a must have same number/more digits than b

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
        else {
            lines= asize - (step- asize); // do not simplify as 2*asize might overflow
        }

        //at this point, lines = number of multiplications required for current step, assuming no leading zeroes in b
        //reduce this number further if there are leading zeroes in b
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
