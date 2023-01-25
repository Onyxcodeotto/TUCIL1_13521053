
#include "boolean.h"

#define ENTER '\n'
#define BLANK ' '
char currentChar;
boolean endWord;
boolean signal;
#define NMax 2

typedef struct {
    char tab[NMax];
    int length;
} input_type;

typedef struct{
    char tab[13];
} equation;

#define ELMT(a,b) (a).tab[b]
input_type input;

void adv(){
    scanf("%c", &currentChar);
}
void start(){
    signal = true;
    adv();
}
void ignoreBlanks()
{
    while (currentChar == BLANK)
    {
        adv();
    }
}

void copyWord(){
    input.length = 0;
    while (currentChar != BLANK && currentChar != ENTER){
        if (input.length <  NMax){
            input.tab[input.length++] = currentChar;
            adv();
        }else{
            //input salah
            while(currentChar !=ENTER){
                adv();
                
            }
            signal = false;
        }
    }
}

void STARTWORD(){
    start();
    ignoreBlanks();
    if (currentChar == ENTER){
        endWord = true;
    }else{
        endWord = false;
        copyWord();
    }
    
}

void forceEnd(){
    while(currentChar!=ENTER){
        adv();
    }
}
void ADVWORD()
{

    ignoreBlanks();
    if (currentChar == ENTER)
    {
        endWord = true;
    }
    else
    {
        copyWord();
        ignoreBlanks();
    }
}

void uppercase(input_type *x){
    for(int i = 0; i< x->length; i++){
        if (x->tab[i]>=97 && x->tab[i]<=122){
            x->tab[i] -= 32;
        }
    }
}

int transformWtoInt(input_type x){
    uppercase(&x);
    switch (x.length)
    {
    case 1:
        if(x.tab[0]=='A'){
            return 1;
        }
        else if(x.tab[0]=='J'){    
            return 11;
        }
        else if(x.tab[0]=='Q'){    
            return 12;
        }
        else if(x.tab[0]=='K'){    
            return 13;
        }
        else if(x.tab[0]>48 && x.tab[0]<58){
            return  x.tab[0]-48;
        }
        else{
            return -1;
        }
    case 2:
        if(x.tab[0]=='1' && x.tab[1]=='0'){
            return 10;
        }else if(x.tab[0]=='1' && x.tab[1]=='1'){
            return 11;
        }else if(x.tab[0]=='1' && x.tab[1]=='2'){
            return 12;
        }else if(x.tab[0]=='1' && x.tab[1]=='3'){
            return 13;
        }
        else{
            return -1;
        }
    default:
        return -1;
    }
}

boolean get_input1(int *x){
    STARTWORD();
    if(!endWord && input.length==1 && input.tab[0]>=48 && input.tab[0]<=50){
        *x = input.tab[0] - 48;
        ADVWORD();
        if(endWord){
        return true;}
        else{forceEnd();return false;}
    }else{
        forceEnd();
        return false;
    }
}


boolean get_input2(int *x1, int *x2, int *x3, int *x4){
    STARTWORD();
    if(endWord){return false;} 
    *x1 = transformWtoInt(input);
    ADVWORD();
    if(endWord){return false;}
    *x2 = transformWtoInt(input);

    ADVWORD();
    if(endWord){return false;}
    *x3 = transformWtoInt(input);
    ADVWORD();
    if(endWord){ return false;} 
    *x4 = transformWtoInt(input);
    ADVWORD();
    if(endWord){
        if(*x1==-1 || *x2==-1||*x3==-1||*x4==-1){
            return false;
        }else{
            return true;
        }
    }else{
        forceEnd();
        return false;
    }
}
boolean get_input3(int *x){
    STARTWORD();
    if(!endWord && input.length==1 && input.tab[0]>=48 && input.tab[0]<=49){
        *x = input.tab[0] - 48;
        ADVWORD();
        if(endWord){
        return true;}
        else{forceEnd();return false;}
    }else{
        forceEnd();
        return false;
    }
}