#include <stdio.h>

unsigned int hls_top(unsigned int a, unsigned int b, unsigned char sel);

int main() {
   unsigned int a = 10, b = 3;
   unsigned char sel;
   unsigned int result;

   // test all 18 operations
   for (sel = 0; sel <= 17; sel++) {
       result = hls_top(a, b, sel);
       printf("Operation %d: Result = %u\n", sel, result);
   }

   return 0;
}
