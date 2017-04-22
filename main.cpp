#include <iostream>
#include <cmath>
#include "randstr.h"

using namespace std;
bool isPrime(int n); //judge n is a prime or not
int random_prime(int min, int max); // produce a prime
int KMP(char *s,char *t, int position);
int NaiveMatch(char *p, char *q);
int getFP(char *x, int len, int prime); //get fingerprint of x[0]...x[len-1]
int MonteCarlo(char* x, char*y, int position, int prime);


bool isPrime(int n){
    for(int i = 2; i <= sqrt((double)n); i++)
        if(n % i == 0)return false;
    return true;
}

int random_prime(int min, int max){
    int i;
   // srand((int)time(0));
    i = rand() % (max - min) + min;
    for(; i >=min; i--)
        if(isPrime(i))break;
    return i;
}

int KMP(char * s, char *t, int pos){
    int i,j;
    int s_len = (int)strlen(s);
    int t_len = (int)strlen(t);

    int *next = new int[t_len];
    i = 0;
    j = -1;
    next[0] = -1;
    while(i < t_len){
        if(j == -1){i ++; j ++; next[i] = j;}
        else
        {if(t[i] == t[j]){ i ++; j ++; next[i] = j;}
            else j = next[j];
        }
    }

    i = pos-1;
    j = 0;
    while(i < s_len && j < t_len){
        if(j == -1||s[i] == t[j]){i ++;j ++;}
        else j = next[j];
    }
    if(j >= t_len) return (i - t_len)+1;
    else return 0;
}

int getFP(char *x, int len, int p){
    int ip = 0;
    for (int k = 0; k <= len - 1; k++) {
        ip = (2 * ip + x[k] - '0') % p;
    }
    return ip;
}

int MonteCarlo(char* x, char* y, int pos, int p){
    int j = 0;
    int Ipx, Ipy, wp;
    int x_len = (int)strlen(x);
    int y_len = (int)strlen(y);

    Ipx = getFP(x + pos - 1, y_len, p);
    Ipy = getFP(y, y_len, p);
    //compute wp
    wp = 1;
    for (int i = 0; i < y_len ; i++) {
        wp = (wp * 2) % p;
    }
    while(j <= x_len - y_len - pos +1){
        if(Ipx == Ipy) return j+1;
        else{
            Ipx = (2 * Ipx - wp * (x[j] - '0')+(x[j + y_len] - '0'))%p;
            if(Ipx < 0) Ipx += p;
            if(Ipx >= p) Ipx -= p;
            j++;
        }
    }
    return 0;
}


int NaiveMatch(char *p, char *q){
    int n, m, i, j, count = 0, temp = 0;
    n = strlen(p);
    m = strlen(q);
    for (i = 0; i <= n - m; ++i) {
        temp++;
        for (j = 0; j < m; ++j) {
            if(p[i + j] == q[j]){
                count++;
            }
        }
        if(count == m)
            return temp;
        count = 0;
    }
    return 0;
}

int main() {
    char *x, *y;
    int index_MC[MAXSIZE],index_KMP[MAXSIZE],index_Naive[MAXSIZE];
    int prime[MAXSIZE];
    int m,n;
    int minlen, maxlen;
    double t_start, t_end, duration;


        cout << "maxlength of string"<<endl;
        cin >> maxlen;
        cout << "maxlength of pattern"<<endl;
        cin >>minlen;
        RandomString rs(maxlen,minlen);

        srand((int)time(0));
        for (int i = 0; i < MAXSIZE; ++i) {
            x = rs.getX(i);
            y = rs.getY(i);
            n = (int)strlen(x);
            m = (int) strlen(y);
            prime[i] = random_prime(2,pow(2,16));
        }
        cout << endl;
        cout <<"The run time of three string matching algorithms:"<<endl;
        cout<<"----------------------------------"<<endl;
        t_start = clock();
        for(int i = 0; i < MAXSIZE; i++){
            x = rs.getX(i);
            y = rs.getY(i);
            index_KMP[i] = KMP(x,y,1);
        }
        t_end = clock();

        duration = (t_end - t_start)/CLOCKS_PER_SEC*1000;
        cout << "KMP need the time:"<< duration<<endl;
        int mismatch = 0;
        t_start = clock();

        for(int i= 0; i < MAXSIZE; i++){
            x = rs.getX(i);
            y = rs.getY(i);
            index_MC[i] = MonteCarlo(x,y,1,prime[i]);
        }
        t_end = clock();
        duration = (t_end - t_start)/CLOCKS_PER_SEC*1000;
        cout << "MonteCarlo need the time:" << duration <<endl;

        t_start = clock();

        for(int i = 0; i < MAXSIZE; i++){
            y = rs.getX(i);
            x = rs.getY(i);
            index_Naive[i] = NaiveMatch(y,x);
        }
        t_end = clock();
        duration = (t_end - t_start)/CLOCKS_PER_SEC*1000;
        cout<<"NaiveMatch need the time:" <<duration <<endl;

        for(int i = 0; i < MAXSIZE; i++){
            if(index_MC[i]!=index_KMP[i])mismatch ++;
        }
        cout<<"----------------------------------"<<endl;
        double failure = (double)mismatch/MAXSIZE;
        cout<<"The error ratio of the MonteCarlo algorithm:"<<failure *100<<"%"<<endl;
        cout << endl;
}
