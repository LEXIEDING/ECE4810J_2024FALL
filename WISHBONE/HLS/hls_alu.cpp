#include <stdio.h>

#define ALU_ADD 0
#define ALU_SUB 1
#define ALU_SLT 2
#define ALU_SLTU 3
#define ALU_AND 4
#define ALU_OR 5
#define ALU_XOR 6
#define ALU_SLL 7
#define ALU_SRL 8
#define ALU_SRA 9
#define ALU_MUL 10
#define ALU_MULH 11
#define ALU_MULHSU 12
#define ALU_MULHU 13
#define ALU_DIV 14
#define ALU_DIVU 15
#define ALU_REM 16
#define ALU_REMU 17

unsigned int hls_top(unsigned int a, unsigned int b, unsigned char sel) {
   #pragma HLS INTERFACE s_axilite port=return bundle=CRTLS
   #pragma HLS INTERFACE s_axilite port=a bundle=CRTLS
   #pragma HLS INTERFACE s_axilite port=b bundle=CRTLS
   #pragma HLS INTERFACE s_axilite port=sel bundle=CRTLS

   unsigned int result;
   switch (sel) {
       case ALU_ADD: result = a + b; break;
       case ALU_SUB: result = a - b; break;
       case ALU_SLT: result = (int)a < (int)b; break;
       case ALU_SLTU: result = a < b; break;
       case ALU_AND: result = a & b; break;
       case ALU_OR: result = a | b; break;
       case ALU_XOR: result = a ^ b; break;
       case ALU_SLL: result = a << b; break;
       case ALU_SRL: result = a >> b; break;
       case ALU_SRA: result = (int)a >> b; break;
       case ALU_MUL: result = a * b; break;
       case ALU_MULH: result = ((long long)a * (long long)b) >> 32; break;
       case ALU_MULHSU: result = ((long long)(int)a * (unsigned long long)b) >> 32; break;
       case ALU_MULHU: result = ((unsigned long long)a * (unsigned long long)b) >> 32; break;
       case ALU_DIV: result = (int)a / (int)b; break;
       case ALU_DIVU: result = a / b; break;
       case ALU_REM: result = (int)a % (int)b; break;
       case ALU_REMU: result = a % b; break;
       default: result = 0; break;
   }
   return result;
}
