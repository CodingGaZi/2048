#include<iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include "Playboard.h"
using namespace std;
typedef long long int LL;
typedef unsigned long long int ULL;
bool Judge(ULL k) {
    if(k == 0 || k == 1) return false;
    for(ULL i = 2; i * i <= k; i++) {
        if(k % i == 0) return false;
    }
    return true;
}
int main() {
    for(;;) {
        printf("%lld",Random(time(0)).LLSeed());
       // printf("%lld", rand());
    }
}