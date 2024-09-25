#include <unistd.h>
#include <stdio.h>

 int main()
 {
   printf("Teste\n");
  
   fork();
   fork();
  
   return 0;
 }
