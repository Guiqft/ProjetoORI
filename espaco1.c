#include <stdio.h>

void removerSpacos(char str[]) { //remover espaços do meio
    int j = 1;
    for (int i = 1; str[i]; i++) {
        if (str[i] != ' ' || (str[i - 1] != ' ')) {
           str[j] = str[i];
           j++;
        }
    }
    str[j] = '\0';
}
int main() {
   char frase[] = "    Ola          Mundo! bb oi aaa ui  a a a a aaa             a  ";
   removerSpacos(frase);
   printf("%s", frase);
   return 0;
}