//
// Created by Lei Pu on 2016-04-09.
//

#include "randstr.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;

RandomString::RandomString(int maxlen, int minlen) {
    int lenA = 0, lenB = 0;
    srand((int)time(0));
    for (int i = 0; i < MAXSIZE; ++i)
    {
        lenA = getRandomInt(maxlen, minlen);
        lenB = getRandomInt(minlen, 1);
        strA[i] = getRandomString(lenA);
        strB[i] = getRandomString(lenB);
    }
}

RandomString::~RandomString() {
    for (int i = 0; i < MAXSIZE; ++i)
    {
        free(strA[i]);
        free(strB[i]);
    }
}

char* RandomString::getX(int index) {
    return strA[index];
}

char* RandomString::getY(int index) {
    return strB[index];
}

//generate a random integer between [min, max]
int RandomString::getRandomInt(int max, int min) {
    int x = rand() % (max - min + 1) + min;
    return x;
}

char* RandomString::getRandomString(int len) {
    char* res = (char*)malloc((len + 1)* sizeof(char));
    for (int i = 0; i < len; ++i)
        res[i] = char('0' + getRandomInt(1));
    res[len - 1] = 0;
    //std::cout << "produce\n" << res << std::endl;
    return res;
}