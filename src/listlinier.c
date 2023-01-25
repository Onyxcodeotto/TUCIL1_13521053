#include "stdlib.h"


typedef struct {
    int x[4];
    char op[3];
    int bracket;
} ElType;
typedef struct node* Address;
typedef struct node {
    ElType info;
    Address next;
} Node;
typedef Address List;
#define INFO(p) (p)->info
#define NEXT(p) (p)->next
#define FIRST(l) (l)

// belum implementasi bawah
Address newNode(ElType val){
    Address p = (Address)malloc(sizeof(Node));
    if(p!= NULL){
        INFO(p) = val;
        NEXT(p) = NULL;
    }
    return p;
}

void CreateList(List *l){
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
    FIRST(*l) = NULL;
}

boolean isEmpty(List l){return FIRST(l)==NULL;}

void insertFirst(List *l, int x1, int x2, int x3, int x4, int b, char op1, char op2, char op3){
    /*KAMUS LOKAL*/
    Address p, k; 
    ElType val;
    /*ALGORITMA*/
    val.x[0] = x1;
    val.x[1] = x2;
    val.x[2] = x3;
    val.x[3] = x4;
    val.op[0] = op1;
    val.op[1] = op2;
    val.op[2] = op3;
    val.bracket = b;
    p = newNode(val);
    if(p!=NULL){
        NEXT(p) = FIRST(*l);
        FIRST(*l) = p;
    }
}

void deleteFirst(List *l){
    /*KAMUS LOKAL*/
    Address p;
    /*ALGORITMA*/
    p=FIRST(*l);
    FIRST(*l)=NEXT(p);
    free(p);
}

int len(List l){
    int i;
    Address p;
    i=0;
    p=FIRST(l);
    while(p!=NULL){
        i++;
        p = NEXT(p);
    }
    return i;
}
void printall(List l){
    Address p;
    ElType exp;
    p = FIRST(l);
    if(len(l)==0){
        printf("Tidak ada solusi!\n");
    }else{
    printf("Banyak Solusi: %d\n", len(l));
    while(p!=NULL){
        exp = INFO(p);
        switch (exp.bracket)
        {
        //1. ((a op1 b) op2 c) op3 d
        //2. (a op1 (b op2 c)) op3 d
        //3. a op1 ((b op2 c) op3 d)
        //4. a op1 (b op2 (c op3 d))
        case 1:
            printf("((%d %c %d) %c %d) %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        case 2:
            printf("(%d %c (%d %c %d)) %c %d\n",exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        case 3:
            printf("%d %c ((%d %c %d) %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        case 4:
            printf("%d %c (%d %c (%d %c %d))\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*twin case*/
        //5. (a op1 b) op2 (c op3 d)
        case 5:
            printf("(%d %c %d) %c (%d %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*One bracket, 3 integers*/
        /*6.(a op1 b op2 c) op3 d*/ 
        case 6:
            printf("(%d %c %d %c %d) %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*7.a op1 (b op2 c op3 d)*/
        case 7:
            printf("%d %c (%d %c %d %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*one bracket, 2 integers*/
        /*8.(a op1 b) op2 c op3 d*/
        case 8:
            printf("(%d %c %d) %c %d %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*9.a op1 (b op2 c) op3 d*/
        case 9:
            printf("%d %c (%d %c %d) %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*10.a op1 b op2 (c op3 d)*/
        case 10:
            printf("%d %c %d %c (%d %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        /*No brackets*/
        /*11.(a op1 b) op2 c op3 d*/
        case 11:
            printf("%d %c %d %c %d %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
            break;
        default:
            printf("case error\n");
            break;
        }
        p = NEXT(p);
    }
    }
}


void clear_list(List *l){
    Address p;
    while(!isEmpty(*l)){
        deleteFirst(l);
    }
}

boolean sameEQ(ElType eq1, ElType eq2){
    return (eq1.x[0]==eq2.x[0]) && (eq1.x[1]==eq2.x[1]) && 
    (eq1.x[2]==eq2.x[2]) && (eq1.x[3]==eq2.x[3]) && (eq1.op[0]==eq2.op[0]) && 
    (eq1.op[1]==eq2.op[1]) && (eq1.op[2]==eq2.op[2]) && (eq1.bracket==eq2.bracket);
}

void delete_duplicate(List *l){
    Address p, q, r, dump;
    p = FIRST(*l);
    while(p!= NULL){
        q = NEXT(p);
        r = p;
        while(q != NULL){
            if(sameEQ(INFO(p), INFO(q))){
                NEXT(r) = NEXT(q);
                dump = q;
                q = NEXT(q);
                free(dump);

            }else{
            r = q;
            q = NEXT(q);
            }
        }
        p = NEXT(p);
    }
}
void card(int d){

    switch(d){
        case 1:
            printf("A");
            break;
        case 11:
            printf("J");
            break;
        case 12:
            printf("Q");
            break;
        case 13:
            printf("K");
            break;
        default:
            printf("%d", d);

    }
}
    void cardfile(int d, FILE *ptr){
    switch(d){
        case 1:
            fprintf(ptr, "A");
            break;
        case 11:
            fprintf(ptr, "J");
            break;
        case 12:
            fprintf(ptr, "Q");
            break;
        case 13:
            fprintf(ptr, "K");
            break;
        default:
            fprintf(ptr, "%d", d);

    }
}   
void writeFile(List l, int x1, int x2, int x3, int x4, double time){
    FILE *ptr;
    Address p;
    ElType exp;
    p = FIRST(l);
    ptr = fopen("../test/output.txt","w");
    fprintf(ptr, "24 Game\n");
    fprintf(ptr, "Kartu: ");
    cardfile(x1, ptr); fprintf(ptr, " ");
    cardfile(x2, ptr); fprintf(ptr, " ");
    cardfile(x3, ptr); fprintf(ptr, " ");
    cardfile(x4, ptr); fprintf(ptr, "\n");
    fprintf(ptr, "Execution time %.2f\n", time);
    if(len(l)==0){
        fprintf(ptr, "\nTidak ada solusi!");
    }else{
        fprintf(ptr, "\nBanyak Solusi: %d\n", len(l));
        while(p!=NULL){
            exp = INFO(p);
            switch (exp.bracket){
            //1. ((a op1 b) op2 c) op3 d
            //2. (a op1 (b op2 c)) op3 d
            //3. a op1 ((b op2 c) op3 d)
            //4. a op1 (b op2 (c op3 d))
            case 1:
                fprintf(ptr,"((%d %c %d) %c %d) %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            case 2:
                fprintf(ptr,"(%d %c (%d %c %d)) %c %d\n",exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            case 3:
                fprintf(ptr,"%d %c ((%d %c %d) %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            case 4:
                fprintf(ptr,"%d %c (%d %c (%d %c %d))\n",exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*twin case*/
            //5. (a op1 b) op2 (c op3 d)
            case 5:
                fprintf(ptr,"(%d %c %d) %c (%d %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*One bracket, 3 integers*/
            /*6.(a op1 b op2 c) op3 d*/ 
            case 6:
                fprintf(ptr,"(%d %c %d %c %d) %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*7.a op1 (b op2 c op3 d)*/
            case 7:
                fprintf(ptr,"%d %c (%d %c %d %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*one bracket, 2 integers*/
            /*8.(a op1 b) op2 c op3 d*/
            case 8:
                fprintf(ptr,"(%d %c %d) %c %d %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*9.a op1 (b op2 c) op3 d*/
            case 9:
                fprintf(ptr,"%d %c (%d %c %d) %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*10.a op1 b op2 (c op3 d)*/
            case 10:
                fprintf(ptr,"%d %c %d %c (%d %c %d)\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            /*No brackets*/
            /*11.(a op1 b) op2 c op3 d*/
            case 11:
                fprintf(ptr,"%d %c %d %c %d %c %d\n", exp.x[0], exp.op[0], exp.x[1], exp.op[1], exp.x[2], exp.op[2], exp.x[3]);
                break;
            default:
                printf("case error\n");
                break;
            }
            p = NEXT(p);
        }
    }
            
    fclose(ptr);
}

