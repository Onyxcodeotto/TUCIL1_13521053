#ifndef FRACTION
#define FRACTION
#include <stdio.h>

typedef struct {
    int num;
    int denom;
} fraction;

#define NUM(f) (f).num
#define DENOM(f) (f).denom
fraction transformItoF(int x){

    fraction y;
    NUM(y) = x;
    DENOM(y) = 1;
    return y;
}
int transformFtoI(fraction x){
    //I.S. Denominator x = 1, Numerator sembarang
    //F.S. terbentuk x dalam bentuk int
    return NUM(x);
}
int gcd(int x1, int x2){
    if(x2 == 0){return x1;
    }else{return gcd(x2, x1%x2);}
}

void simplify(fraction *f){
    int g = gcd(NUM(*f), DENOM(*f));
    if(g==0){
        NUM(*f) = -9999;
        DENOM(*f) = 1;
    }else{
        NUM(*f) = NUM(*f)/g;
        DENOM(*f) = DENOM(*f)/g;
    }
}

fraction add(fraction f1, fraction f2){
    fraction result;
    NUM(result) = NUM(f1)*DENOM(f2) + NUM(f2)*DENOM(f1);
    DENOM(result) = DENOM(f1)*DENOM(f2);
    return result;
}

fraction subtract(fraction f1, fraction f2){
    fraction result;
    NUM(result) = NUM(f1)*DENOM(f2) - NUM(f2)*DENOM(f1);
    DENOM(result) = DENOM(f1)*DENOM(f2);
    return result;
}

fraction multiply(fraction f1, fraction f2){
    fraction result;
    NUM(result) = NUM(f1)*NUM(f2);
    DENOM(result) = DENOM(f1)*DENOM(f2);
    return result;
}

fraction divide(fraction f1, fraction f2){
    fraction result;
    NUM(result) = NUM(f1)*DENOM(f2);
    DENOM(result) = DENOM(f1)*NUM(f2);
    return result;
}

void display(fraction f1){
    printf("%d/%d\n",NUM(f1),DENOM(f1));
}


fraction calc(fraction x1, fraction x2, char op){
    switch(op){
        case '+':
            return add(x1, x2);
        case '-':
            return subtract(x1,x2);
        case '*':
            return multiply(x1, x2);
        case '/':
            return divide(x1,x2);
    }
}
#endif
