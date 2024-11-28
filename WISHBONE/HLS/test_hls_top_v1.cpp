#include <stdio.h>

extern "C" void hls_top(unsigned int addr, unsigned int data, bool we, bool cyc, bool stb, unsigned int* data_out, bool* ack_out);

int main() {
    unsigned int addr = 0x00000010;
    unsigned int data = 0x12345678;
    bool we = true;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    // 写操作
    hls_top(addr, data, we, cyc, stb, &data_out, &ack_out);

    // 读操作
    we = false;
    hls_top(addr, 0, we, cyc, stb, &data_out, &ack_out);

    printf("Read data: 0x%x\n", data_out);

    return 0;
}
