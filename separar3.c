#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main (){
char a[64] = "10: JOSE DA SILVA: jose_cert.cert";
char b[32], c[32], d[32];


sscanf(a, "%31[^:]:%31[^:]:%31[^:]:", b, c, d);
printf("%s %s %s\n", b, c, d);

}