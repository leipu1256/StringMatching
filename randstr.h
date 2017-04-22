//
// Created by Lei Pu on 2016-04-09.
//

#ifndef STRINGMATCHING_RANDSTR_H
#define STRINGMATCHING_RANDSTR_H
const int MAXSIZE = 10000;
class RandomString {
public:
    RandomString(int maxlen, int minlen);
    ~RandomString();

    char* getX(int index);
    char* getY(int index);

private:
    char* strA[MAXSIZE];
    char* strB[MAXSIZE];

    int getRandomInt(int max, int min = 0);
    char* getRandomString(int len);
};
#endif //STRINGMATCHING_RANDSTR_H
