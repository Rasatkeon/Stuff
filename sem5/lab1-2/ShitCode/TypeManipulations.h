//
// Created by timecat on 10/4/16.
//

#ifndef SHITCODE_TYPEMANIPULATIONS_H
#define SHITCODE_TYPEMANIPULATIONS_H

#include <sys/types.h>

void printLnRawUint (const uint &num);
char* convertUintToRaw(const uint &num);
void printLnRawDouble (const double &num);
char* convertDoubleToRaw(const double &num);
uint setUintBits(uint inp, uint start, uint num, uint state);
uint setUintBit(const uint &input, const uint &pos, const uint &state);
double setDoubleBits(double inp, uint start, uint num, uint state);
double setDoubleBit(const double &input, const uint &pos, const uint &state);

#endif //SHITCODE_TYPEMANIPULATIONS_H
