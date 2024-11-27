#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xhls_top.h" // Contains hls_top macros and functions
#include <stdbool.h>

int main() {
    init_platform();

    ////////////////////////////////////////////////////////////////////////////////////////
    // HLS TOP TEST
    xil_printf("Performing a test of the HLS_TOP... \r\n");

    int status;
    // Create hls_top pointer
    XHls_top do_hls_top;
    XHls_top_Config *do_hls_top_cfg;
    do_hls_top_cfg = XHls_top_LookupConfig(XPAR_HLS_TOP_0_DEVICE_ID);

    if (!do_hls_top_cfg) {
        xil_printf("Error loading configuration for do_hls_top_cfg \r\n");
    }

    status = XHls_top_CfgInitialize(&do_hls_top, do_hls_top_cfg);
    if (status != XST_SUCCESS) {
        xil_printf("Error initializing for do_hls_top \r\n");
    }

    unsigned int addr = 0x00000010;
    unsigned int data = 0x12345678;
    bool we = true;
    bool cyc = true;
    bool stb = true;
    unsigned int data_out;
    bool ack_out;

    // Write operation
    XHls_top_Set_addr(&do_hls_top, addr);
    XHls_top_Set_data(&do_hls_top, data);
    XHls_top_Set_we(&do_hls_top, we);
    XHls_top_Set_cyc(&do_hls_top, cyc);
    XHls_top_Set_stb(&do_hls_top, stb);
    xil_printf("Write addr: 0x%08x \r\n", addr);
    xil_printf("Write data: 0x%08x \r\n", data);
    xil_printf("Write we: %d \r\n", we);
    xil_printf("Write cyc: %d \r\n", cyc);
    xil_printf("Write stb: %d \r\n", stb);

    // Start hls_top
    XHls_top_Start(&do_hls_top);
    xil_printf("Started hls_top \r\n");

    // Wait until it's done (optional here)
    while (!XHls_top_IsDone(&do_hls_top));

    // Get hls_top returned values
    data_out = XHls_top_Get_data_out(&do_hls_top);
    ack_out = XHls_top_Get_ack_out(&do_hls_top);

    xil_printf("Read data_out: 0x%08x \r\n", data_out);
    xil_printf("Read ack_out: %d \r\n", ack_out);

    xil_printf("End of test HLS_TOP \r\n");

    cleanup_platform();
    return 0;
}
