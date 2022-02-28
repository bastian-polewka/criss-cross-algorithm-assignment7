string AlternativeVedic(string a, string b) {
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
        else {lines= asize - (step- asize);}
        if (min < 0) {
            min = 0;
            max--;
            if (step < asize) {lines -= step - bsize;}
            else {lines -= asize - bsize;}
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
