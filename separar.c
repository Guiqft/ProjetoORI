#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main (){
    
char a[64] = "banana:cor;verde:a;b:c";
char b[32], c[32], d[32], e[32], f[32], g[32];


sscanf(a, "%31[^:]:%31[^;];%31[^:]:%31[^;];%31[^:]:%31[^;];%31[^:]:%31[^;];", b, c, d, e, f, g);
printf("%s %s %s %s %s %sº\n", b, c, d, e, f, g);

}