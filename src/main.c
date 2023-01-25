#include <stdio.h>
#include "boolean.h"
#include "fraction.c"
#include "listlinier.c"
#include "stdlib.h"
#include "time.h"
#include "input.c"
#include "stack.c"



/**/
boolean isOp(char a){
    return a=='+' || a=='-' || a=='/' || a=='*';
}
void infixToPost(char *a){
    int i=0;
    Stack s;
    int j= 0;
    char temp;
    char buffer[MaxEl];
    CreateEmpty(&s);
    Push(&s,'\n');
    while(*(a+i) != '\n'){
        if(*(a+i)=='('){
            Push(&s, '(');
        }
        else if(*(a+i) == ')'){
            while(InfoTop(s) != '('){
                Pop(&s,&temp);
                buffer[j] = temp;j++;
            }
            Pop(&s, &temp);
        }
        else if(*(a+i)>=48 && *(a+i)<=51){
            buffer[j] = *(a+i);
            j++;
        }else{
            while(rank(*(a+i))<= rank(InfoTop(s))){Pop(&s, &temp);buffer[j] = temp;j++;}
            Push(&s, *(a+i));
        }     
        i++;
    }
    while(!IsEmpty(s)){
        Pop(&s, &temp);
        buffer[j] = temp;j++;
    }
    for(i=0;i<j;i++){
        *(a+i) = buffer[i];
    }
}

boolean is24(char *EQ, fraction *in){
    //use array indexing
    Stack s;
    StackF SF;
    fraction result;
    fraction frac[4] = {in[0], in[1], in[2], in[3]};
    int i = 0;
    fraction x1, x2;
    CreateEmpty(&s);
    CreateEmptyF(&SF);
    /*change infix*/
    infixToPost(EQ);
    /*solve suffix*/
    while(EQ[i]!='\n'){
        if(isOp(EQ[i])){
            PopF(&SF,&x2);
            PopF(&SF,&x1);
            result = calc(x1, x2, EQ[i]);
            PushF(&SF, result);        
        }else{
            if(EQ[i]>='0' && EQ[i]<='3'){
                
                PushF(&SF,  frac[EQ[i]-48]);
            }
            
        }
        i++;
    }
    PopF(&SF, &result);
    simplify(&result);
/*    printf("%s",EQ);
    display(result);
    get_input3(&i);*/
    return (NUM(result) == 24) && (DENOM(result)==1);
}





//solution finder

void find_solution_alt(List *l, int x1, int x2, int x3, int x4){
    
    char EQ[MaxEl];
    fraction y1,y2,y3,y4, test;
    int i, j, k, a, b, c, d;
    //start timer

    //transform to frac
    y1 = transformItoF(x1);
    y2 = transformItoF(x2);
    y3 = transformItoF(x3);
    y4 = transformItoF(x4);
    char ops[4] = {'+', '-', '*', '/'};
    fraction y[4] = {y1, y2, y3, y4};
    
for(a=0;a<4;a++){
    for(b=0;b<4;b++){
        if(a==b){continue;}
        for(c=0;c<4;c++){
            if(a==c || b==c){continue;}
            d = 6-a-b-c;
                if(a==d || b==d || c==d){continue;}
                for(i=0;i<4;i++){
                    for(j=0;j<4;j++){
                        for(k=0;k<4;k++){
                            fraction temp[4] = {y[a], y[b], y[c], y[d]};
                            //case one by one
                            //bracket mode and its
                            //1. ((a op1 b) op2 c) op3 d
                            sprintf(EQ, "((%d%c%d)%c%d)%c%d\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 1,ops[i], ops[j], ops[k]);
                            }
                            
                            //2. (a op1 (b op2 c)) op3 d
                            sprintf(EQ, "(%d%c(%d%c%d))%c%d\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 2,ops[i], ops[j], ops[k]);
                            }
                            
                            //3. a op1 ((b op2 c) op3 d)
                            sprintf(EQ, "%d%c((%d%c%d)%c%d)\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 3,ops[i], ops[j], ops[k]);
                            }
                            
                            //4. a op1(b op2 (c op3 d))
                            sprintf(EQ, "%d%c(%d%c(%d%c%d))\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 4,ops[i], ops[j], ops[k]);
                            }

                            //case pair by pair
                            //5. (a op1 b) op2 (c op3 d)
                            sprintf(EQ, "(%d%c%d)%c(%d%c%d)\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 5,ops[i], ops[j], ops[k]);
                            }
                            /*One bracket, 3 integers*/
                            /*6.(a op1 b op2 c) op3 d*/ 
                            sprintf(EQ, "(%d%c%d%c%d)%c%d\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 6,ops[i], ops[j], ops[k]);
                            }
                            /*7.a op1 (b op2 c op3 d)*/
                            sprintf(EQ, "%d%c(%d%c%d%c%d)\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 7,ops[i], ops[j], ops[k]);
                            }
                            /*one bracket, 2 integers*/
                            /*8.(a op1 b) op2 c op3 d*/
                            sprintf(EQ, "(%d%c%d)%c%d%c%d\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 8,ops[i], ops[j], ops[k]);
                            }
                            /*9.a op1 (b op2 c) op3 d*/
                            sprintf(EQ, "%d%c(%d%c%d)%c%d\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 9,ops[i], ops[j], ops[k]);
                            }
                            /*10.a op1 b op2 (c op3 d)*/
                            sprintf(EQ, "%d%c%d%c(%d%c%d)\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 10,ops[i], ops[j], ops[k]);
                            }
                            
                            /*No brackets*/
                            /*11.a op1 b op2 c op3 d*/
                            sprintf(EQ, "%d%c%d%c%d%c%d\n", 0,ops[i],1,ops[j],2,ops[k],3);
                            if(is24(EQ,temp)){
                                insertFirst(l, NUM(y[a]), NUM(y[b]), NUM(y[c]), NUM(y[d]), 11,ops[i], ops[j], ops[k]);
                            }
                            
                        }
                }
            }
        }
        }
    }
}
boolean legit_input(char c){
    return (48<=c) || (c<=57) || (c==65) || (c==65+32) || (c==75) || (c==75+32) || (c==74) || (c==74+32) || (c==81) || (c==81+32);
}    

//main
int main(){
    int input;
    int x1,x2,x3,x4;
    boolean run;
    FILE *ptr;
    run = true;
    List l;
    CreateList(&l);
    while(run){
        //take input
        //perbaiki textnya bang
        printf("24 SOLVER\n");
        printf("\n\nKetik:\n");
        printf("(1) Masukan Keyboard\n");
        printf("(2) Random Generate\n");
        printf("(0) Exit\n");
        while(!get_input1(&input)){
            printf("Input tidak valid!\n");
        }
        
        if(input == 0){
            run = false;
        }else if (input == 1)
        {//ambil masukan keyboard
            printf("Masukan nilai kartu: ");
            while(!get_input2(&x1, &x2, &x3, &x4)){
                printf("Input tidak valid!\n");
                printf("Masukan nilai kartu: ");
            }
        }else if (input==2)
        {
            srand( time(NULL));
            x1 = rand()%13 + 1;
            x2 = rand()%13 + 1;
            x3 = rand()%13 + 1;
            x4 = rand()%13 + 1;
            printf("Kartu yang didapat:\n");
            card(x1); printf(" "); card(x2); printf(" "); card(x3); printf(" "); card(x4); printf("\n");
        }
        if(input == 1 || input ==2){
            // process
            clock_t begin = clock();
            find_solution_alt(&l, x1, x2, x3, x4);   
            delete_duplicate(&l);
            clock_t end = clock();
            double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
            printf("Execution time %.2f\n", time_spent);
            printall(l);

            //ask if output want to be saved
            printf("Simpan Jawaban dalam file?\n");
            printf("(1) YA\n");
            printf("(0) Tidak\n");
            while(!get_input3(&input)){
                printf("Input salah\n");
            }
            if(input==1){
                writeFile(l, x1, x2, x3, x4, time_spent);
            }
            //clear list
            clear_list(&l);
            printf("\n\n\n");
        }
        
        
    }
    return 0;
}