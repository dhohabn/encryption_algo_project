#include<stdio.h>
void Ascii(char text[40],int ascii[40]){
    int i;
    for (i=0;i<40;i++){
        ascii[i]=(int)text[i];
       
    }

}


int main(){
    char text[40]="This is the text i want to encrypt";
    int i;
    int ascii_of_text[40];
    Ascii(text,ascii_of_text);
    for (i=0;i<40;i++){
        printf("%d",ascii_of_text[i]);

    }


    return 0;
}