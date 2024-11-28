#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xhls_top.h" // Contains hls_top macros and functions
#include <stdbool.h>

void write_data(XHls_top* do_hls_top, unsigned int addr, unsigned int data) {
    bool we = true;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    XHls_top_Set_addr(do_hls_top, addr);
    XHls_top_Set_data(do_hls_top, data);
    XHls_top_Set_we(do_hls_top, we);
    XHls_top_Set_cyc(do_hls_top, cyc);
    XHls_top_Set_stb(do_hls_top, stb);

    XHls_top_Start(do_hls_top);
    while (!XHls_top_IsDone(do_hls_top));

    data_out = XHls_top_Get_data_out(do_hls_top);
    ack_out = XHls_top_Get_ack_out(do_hls_top);

    if (ack_out) {
        xil_printf("Write to 0x%08x: 0x%08x successful.\r\n", addr, data);
    } else {
        xil_printf("Write to 0x%08x: 0x%08x failed.\r\n", addr, data);
    }
}

unsigned int read_data(XHls_top* do_hls_top, unsigned int addr) {
    bool we = false;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    XHls_top_Set_addr(do_hls_top, addr);
    XHls_top_Set_data(do_hls_top, 0); // 写入 0 作为占位符
    XHls_top_Set_we(do_hls_top, we);
    XHls_top_Set_cyc(do_hls_top, cyc);
    XHls_top_Set_stb(do_hls_top, stb);

    XHls_top_Start(do_hls_top);
    while (!XHls_top_IsDone(do_hls_top));

    data_out = XHls_top_Get_data_out(do_hls_top);
    ack_out = XHls_top_Get_ack_out(do_hls_top);

    if (ack_out) {
        xil_printf("Read from 0x%08x: 0x%08x successful.\r\n", addr, data_out);
    } else {
        xil_printf("Read from 0x%08x failed.\r\n", addr);
    }
    return data_out;
}

int main() {
    init_platform();

    xil_printf("Performing a test of the HLS_TOP... \r\n");

    int status;
    XHls_top do_hls_top;
    XHls_top_Config *do_hls_top_cfg;
    do_hls_top_cfg = XHls_top_LookupConfig(XPAR_HLS_TOP_0_DEVICE_ID);

    if (!do_hls_top_cfg) {
        xil_printf("Error loading configuration for do_hls_top_cfg \r\n");
        return XST_FAILURE;
    }

    status = XHls_top_CfgInitialize(&do_hls_top, do_hls_top_cfg);
    if (status != XST_SUCCESS) {
        xil_printf("Error initializing for do_hls_top \r\n");
        return XST_FAILURE;
    }

    // 测试内存初始化
    xil_printf("Initializing memory...\r\n");
    for (unsigned int addr = 0x00000000; addr < 0x00000400; addr += 4) {
        write_data(&do_hls_top, addr, addr);
    }

    // 测试数据写入和读取
    xil_printf("Testing data write and read...\r\n");
    write_data(&do_hls_top, 0x00000010, 0x12345678);
    unsigned int data = read_data(&do_hls_top, 0x00000010);
    if (data == 0x12345678) {
        xil_printf("Data verification successful.\r\n");
    } else {
        xil_printf("Data verification failed. Expected 0x12345678, got 0x%08x\r\n", data);
    }

    // 测试边界条件
    xil_printf("Testing boundary conditions...\r\n");
    write_data(&do_hls_top, 0x000003FC, 0xDEADBEEF);
    data = read_data(&do_hls_top, 0x000003FC);
    if (data == 0xDEADBEEF) {
        xil_printf("Boundary condition test successful.\r\n");
    } else {
        xil_printf("Boundary condition test failed. Expected 0xDEADBEEF, got 0x%08x\r\n", data);
    }

    // 测试跨越从设备边界的情况
    xil_printf("Testing crossing slave boundary...\r\n");
    write_data(&do_hls_top, 0x00000400, 0xCAFEBABE);
    data = read_data(&do_hls_top, 0x00000400);
    if (data == 0xCAFEBABE) {
        xil_printf("Crossing slave boundary test successful.\r\n");
    } else {
        xil_printf("Crossing slave boundary test failed. Expected 0xCAFEBABE, got 0x%08x\r\n", data);
    }

    // 测试无效地址
    xil_printf("Testing invalid address...\r\n");
    write_data(&do_hls_top, 0x00000800, 0xBADADD);
    data = read_data(&do_hls_top, 0x00000800);
    if (data == 0xBADADD) {
        xil_printf("Invalid address test failed. Unexpectedly read 0x%08x\r\n", data);
    } else {
        xil_printf("Invalid address test successful. No data read.\r\n");
    }

    xil_printf("End of test HLS_TOP \r\n");

    cleanup_platform();
    return 0;
}
