#include <stdio.h>

extern "C" void hls_top(unsigned int addr, unsigned int data, bool we, bool cyc, bool stb, unsigned int* data_out, bool* ack_out);

void write_data(unsigned int addr, unsigned int data) {
    bool we = true;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    hls_top(addr, data, we, cyc, stb, &data_out, &ack_out);
    if (ack_out) {
        printf("Write to 0x%x: 0x%x successful.\n", addr, data);
    } else {
        printf("Write to 0x%x: 0x%x failed.\n", addr, data);
    }
}

unsigned int read_data(unsigned int addr) {
    bool we = false;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    hls_top(addr, 0, we, cyc, stb, &data_out, &ack_out);
    if (ack_out) {
        printf("Read from 0x%x: 0x%x successful.\n", addr, data_out);
    } else {
        printf("Read from 0x%x failed.\n", addr);
    }
    return data_out;
}

int main() {
    // 测试内存初始化
    printf("Initializing memory...\n");
    for (unsigned int addr = 0x00000000; addr < 0x00000400; addr += 4) {
        write_data(addr, addr);
    }

    // 测试数据写入和读取
    printf("Testing data write and read...\n");
    write_data(0x00000010, 0x12345678);
    unsigned int data = read_data(0x00000010);
    if (data == 0x12345678) {
        printf("Data verification successful.\n");
    } else {
        printf("Data verification failed. Expected 0x12345678, got 0x%x\n", data);
    }

    // 测试边界条件
    printf("Testing boundary conditions...\n");
    write_data(0x000003FC, 0xDEADBEEF);
    data = read_data(0x000003FC);
    if (data == 0xDEADBEEF) {
        printf("Boundary condition test successful.\n");
    } else {
        printf("Boundary condition test failed. Expected 0xDEADBEEF, got 0x%x\n", data);
    }

    // 测试跨越从设备边界的情况
    printf("Testing crossing slave boundary...\n");
    write_data(0x00000400, 0xCAFEBABE);
    data = read_data(0x00000400);
    if (data == 0xCAFEBABE) {
        printf("Crossing slave boundary test successful.\n");
    } else {
        printf("Crossing slave boundary test failed. Expected 0xCAFEBABE, got 0x%x\n", data);
    }

    // 测试无效地址
    printf("Testing invalid address...\n");
    write_data(0x00000800, 0xBADADD);
    data = read_data(0x00000800);
    if (data == 0xBADADD) {
        printf("Invalid address test failed. Unexpectedly read 0x%x\n", data);
    } else {
        printf("Invalid address test successful. No data read.\n");
    }

    return 0;
}
