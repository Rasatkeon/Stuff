//
// Created by timecat on 10/4/16.
//

#include <sys/types.h>
#include <iostream>
#include "TypeManipulations.h"

using namespace std;

void printLnRawUint(const uint &num) {
    for (int i = 0; i < sizeof(num) * 8; ++i) {
        cout << ((num >> sizeof(num) * 8 - i - 1) & 1);
    }
    cout << endl;
}

void printLnRawDouble(const double &num) {
    long long int* cheat = (long long int*) &num;
    for (int i = 0; i < sizeof(*cheat) * 8; ++i) {
        cout << ((*cheat >> sizeof(*cheat) * 8 - i - 1) & 1);
    }
    cout << endl;
}

/*
 * |number|\0| <- don't touch the last one
 */
char* convertUintToRaw(const uint &num) {
    char* result = new char[sizeof(num)*8 + 1];
    for (int i = 0; i < sizeof(num) * 8; i++) {
        result[i] = ((num >> sizeof(num) * 8 - i - 1) & 1) ? '1' : '0';
    }
    result[sizeof(num)*8] = '\0';
    return result;
}

char* convertDoubleToRaw(const double &num) {
    long long int* cheat = (long long int*) &num;
    char* result = new char[sizeof(cheat)];
    for (int i = 0; i < sizeof(*cheat) * 8; i++) {
        result[i] = ((*cheat >> sizeof(*cheat)*8 - i - 1) & 1) ? '1' : '0';
    }
    result[sizeof(*cheat)*8] = '\0';
    return result;
}

uint setUintBits(uint inp, uint start, uint num, uint state) {
    uint res = inp;
    if (state > 0) {
        state = 1;
        for (int i = start; (i < start + num) && (i <= 32); ++i) {
            res |= (state << i);
        }
    } else {
        state = 0;
        for (int i = start; (i < start + num) && (i <= 32); ++i) {
            res &= (state << i);
        }
    }
    return res;
}

uint setUintBit(const uint &input, const uint &pos, const uint &state) {
    uint res = input;
    if (state == 0 || state == 1) {
        if (pos < sizeof(res) * 8) {
            if (state == 1) {
                res |= (1 << pos);
            }
            if (state == 0) {
                res &= ~(1 << pos);
            }
        }
    }
    return res;
}

double setDoubleBits(double inp, uint start, uint num, uint state) {
    double res = inp;
    for (uint i = start; i < start + num; ++i) {
        res = setDoubleBit(inp, i, state);
    }
    return res;
}

double setDoubleBit(const double &input, const uint &pos, const uint &state) {
    union {
        char* foo = new char[sizeof(double)];
        double* bar;
    } cheat;
    *cheat.bar = input;
    if (state == 0 || state == 1) {
        if (pos < sizeof(cheat.bar) * 8) {
            int charp = pos / 8;
            int charip = pos % 8;
            if (state == 1) {
                cheat.foo[charp] |= (1 << charip);
            }
            if (state == 0) {
                cheat.foo[charp] &= ~(1 << charip);
            }
        }
    }
    double res = *(cheat.bar);
    //delete cheat.foo;  // WHY THE HELL THIS ONE DOESN'T WORK?!
    return res;
}
