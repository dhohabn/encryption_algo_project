#include<stdio.h>
#include<stdbool.h>
#include <math.h>
void Ascii(char text[40],int ascii[40]){
    int i;
    for (i=0;i<40;i++){
        ascii[i]=(int)text[i];
       
    }


}
//verifies if the public key is prime //
int prime(int E){
    int i;
    if (E<=1){
        return 1;
    
    }
    for(i=2;i<=sqrt(E);i++){
        if (E%i==0){
            return 1;
        }
    }
    return 0;
}
//verifies if the public key is not a factor of the totient//
int fact_tot(int E, intT){
    if (T%E==0){
        return 0;
    }
    return 1;
}
/*function to check if the public key is valid
1* it has to be prime
2*it has to be less than the totient
3*it mustn't be a factor of the totient
*/
int public_key(int E,int T){
    if (prime(E)==0 && E<=T && fact_tot(E,T)==1){
        return 0;
    }
    return 1;

}
void Encrypt(int ascii[40],int ciphertext[40]){
    int p,q,n,T,i,E;
    p=7;
    q=13;
    n=p*q;
    scanf("%d",&E);
    T=(p-1)*(q-1);
    if (public_key(E,T)==0){

    for(i=0;i<40;i++){
        ciphertext[i]=ascii[i]^E%T;
    }
    }


}


int main(){
    char text[40]="This is the text i want to encrypt";
    int i;
    int ascii_of_text[40];
    Ascii(text,ascii_of_text);
    for (i=0;i<40;i++){
        

    }


    return 0;
}