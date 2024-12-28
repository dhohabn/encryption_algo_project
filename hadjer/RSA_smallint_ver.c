#include<stdio.h>
#include<stdbool.h>
#include <math.h>
#define max_s 200
//this is RAS algorithm:Ravist-Shemir-Adelman// 
void Ascii(char text[max_s],int ascii[max_s]){
    int i;
    for (i=0;i<max_s;i++){
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
int fact_totient(int E, int T){
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
    if (prime(E)==0 && E<=T && fact_totient(E,T)==1){
        return 0;
    }
    return 1;

}
int Generating_keys(int q,int p,int* n,int* T){
    if(prime(p)==1 || prime(q)==1){
        printf("the number you just antered is not prime try another one ");
    }
    *n=q*p; //semi prime number//
    *T=(p-1)*(q-1);//this totient is especially for semi prime numbers such that n=p*q with q!=p and q&p are prime numbers //
}
void Encrypt(int ascii[max_s],int ciphertext[max_s],int E,int T,int n){
    int i;
    if (public_key(E,T)==0){

    for(i=0;i<max_s;i++){
        ciphertext[i]=((int)pow(ascii[i],E))%n;
    }
    }

}
int private_key(int E, int T,int D){
    if ((D*E)%T==1){
        return 0;
    }
    return 1;
}
void decrypt(int ciphertext[max_s],int ascii[max_s],int D,int n,int T,int E){
    int i;
    if( private_key(E,T,D)==0){
        for(i=0;i<max_s;i++){
            ascii[i]=((int)pow(ciphertext[i],D))%n;
        }
    }


}


int main(){
    char text[max_s]="This is the text i want to encrypt";
    int i;
    int ascii_of_text[max_s];
    Ascii(text,ascii_of_text);
    for (i=0;i<40;i++){
        

    }


    return 0;
}