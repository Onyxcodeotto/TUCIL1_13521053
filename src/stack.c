#include "boolean.h"
#include "fraction.c"
#define Nil -1
#define MaxEl 15
/* Nil adalah stack dengan elemen kosong . */
typedef char infotype;
typedef int address;   
typedef struct { 
  infotype T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty(Stack *S){
Top(*S) = Nil;
}
/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty(Stack S){
return Top(S) == Nil;
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack * S, infotype X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
if(IsEmpty(*S)){
    Top(*S) = 0;
}
else{
    Top(*S) +=1;
}
InfoTop(*S) = X;
}
/* ************ Menghapus sebuah elemen Stack ************ */
void Pop(Stack * S, infotype* X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
*X = InfoTop(*S);
if(Top(*S) == 0){
    Top(*S) = Nil;
}
else{
    Top(*S) -=1;
}
}

int rank(char c){
    switch (c){
        case '(':
            return 0;
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    }
}
typedef struct { 
  fraction T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} StackF;
/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyF(StackF *S){
Top(*S) = Nil;
}
/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyF(StackF S){
return Top(S) == Nil;
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushF(StackF * S, fraction X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
if(IsEmptyF(*S)){
    Top(*S) = 0;
}
else{
    Top(*S) +=1;
}
    NUM(InfoTop(*S)) = NUM(X);
    DENOM(InfoTop(*S)) = DENOM(X);
}
/* ************ Menghapus sebuah elemen Stack ************ */
void PopF(StackF * S, fraction* X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
NUM(*X)= NUM(InfoTop(*S));
DENOM(*X) = DENOM(InfoTop(*S));
if(Top(*S) == 0){
    Top(*S) = Nil;
}
else{
    Top(*S) -=1;
}
}

