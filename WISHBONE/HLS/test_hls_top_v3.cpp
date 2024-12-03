#include <stdio.h>

extern "C" void hls_top(unsigned int addr, unsigned int data, bool we, bool cyc, bool stb, unsigned char sel, unsigned int* data_out, bool* ack_out);

void write_data(unsigned int addr, unsigned int data, unsigned char sel) {
    bool we = true;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    hls_top(addr, data, we, cyc, stb, sel, &data_out, &ack_out);
    if (ack_out) {
        printf("Write to 0x%x: 0x%x with sel 0x%x successful.\n", addr, data, sel);
    } else {
        printf("Write to 0x%x: 0x%x with sel 0x%x failed.\n", addr, data, sel);
    }
}

unsigned int read_data(unsigned int addr, unsigned char sel) {
    bool we = false;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    hls_top(addr, 0, we, cyc, stb, sel, &data_out, &ack_out);
    if (ack_out) {
        printf("Read from 0x%x with sel 0x%x: 0x%x successful.\n", addr, sel, data_out);
    } else {
        printf("Read from 0x%x with sel 0x%x failed.\n", addr, sel);
    }
    return data_out;
}

int main() {
    // 测试内存初始化
    printf("Initializing memory...\n");
    for (unsigned int addr = 0x00000000; addr < 0x00000400; addr += 4) {
        write_data(addr, addr, 0xF); // 写入所有字节
    }

    // 测试数据写入和读取
    printf("Testing data write and read...\n");
    write_data(0x00000010, 0x12345678, 0xF); // 写入所有字节
    unsigned int data = read_data(0x00000010, 0xF); // 读取所有字节
    if (data == 0x12345678) {
        printf("Data verification successful.\n");
    } else {
        printf("Data verification failed. Expected 0x12345678, got 0x%x\n", data);
    }

    // 测试部分字节写入和读取
    printf("Testing partial byte write and read...\n");
    write_data(0x00000014, 0x000000AB, 0x1); // 只写入最低字节
    data = read_data(0x00000014, 0xF); // 读取所有字节
    if ((data & 0x000000FF) == 0x000000AB) {
        printf("Partial byte write and read successful.\n");
    } else {
        printf("Partial byte write and read failed. Expected 0x000000AB, got 0x%x\n", data & 0x000000FF);
    }

    write_data(0x00000018, 0x0000CD00, 0x2); // 只写入第二个字节
    data = read_data(0x00000018, 0xF); // 读取所有字节
    if ((data & 0x0000FF00) == 0x0000CD00) {
        printf("Partial byte write and read successful.\n");
    } else {
        printf("Partial byte write and read failed. Expected 0x0000CD00, got 0x%x\n", data & 0x0000FF00);
    }

    write_data(0x0000001C, 0x00EF0000, 0x4); // 只写入第三个字节
    data = read_data(0x0000001C, 0xF); // 读取所有字节
    if ((data & 0x00FF0000) == 0x00EF0000) {
        printf("Partial byte write and read successful.\n");
    } else {
        printf("Partial byte write and read failed. Expected 0x00EF0000, got 0x%x\n", data & 0x00FF0000);
    }

    write_data(0x00000020, 0xAB000000, 0x8); // 只写入第四个字节
    data = read_data(0x00000020, 0xF); // 读取所有字节
    if ((data & 0xFF000000) == 0xAB000000) {
        printf("Partial byte write and read successful.\n");
    } else {
        printf("Partial byte write and read failed. Expected 0xAB000000, got 0x%x\n", data & 0xFF000000);
    }

    // 测试边界条件
    printf("Testing boundary conditions...\n");
    write_data(0x000003FC, 0xDEADBEEF, 0xF); // 写入所有字节
    data = read_data(0x000003FC, 0xF); // 读取所有字节
    if (data == 0xDEADBEEF) {
        printf("Boundary condition test successful.\n");
    } else {
        printf("Boundary condition test failed. Expected 0xDEADBEEF, got 0x%x\n", data);
    }

    // 测试跨越从设备边界的情况
    printf("Testing crossing slave boundary...\n");
    write_data(0x00000400, 0xCAFEBABE, 0xF); // 写入所有字节
    data = read_data(0x00000400, 0xF); // 读取所有字节
    if (data == 0xCAFEBABE) {
        printf("Crossing slave boundary test successful.\n");
    } else {
        printf("Crossing slave boundary test failed. Expected 0xCAFEBABE, got 0x%x\n", data);
    }

    // 测试无效地址
    printf("Testing invalid address...\n");
    write_data(0x00000800, 0xBADADD, 0xF); // 写入所有字节
    data = read_data(0x00000800, 0xF); // 读取所有字节
    if (data == 0xBADADD) {
        printf("Invalid address test failed. Unexpectedly read 0x%x\n", data);
    } else {
        printf("Invalid address test successful. No data read.\n");
    }

    return 0;
}
