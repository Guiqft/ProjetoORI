#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void maiuscula(char str1[], int tam){

    for( int i = 0; i <= tam; i++ ){

        if( ( str1[i] >= 65 ) && ( str1[i] <= 90 ) )

            str1[i] = str1[i] + 32;

        else if( ( str1[i] >= 97 ) && ( str1[i] <= 132 ) )

            str1[i] = str1[i] - 32;

    }

}
int main() {
   char str[] = "asokaoks";
   maiuscula(str, 10);
   printf("%s", str);
   return 0;
}