#include "platform.h"
#include "xbasic_types.h"
#include "xparameters.h" // Contains definitions for all peripherals
#include "xhls_alu.h" // Contains hls_alu macros and functions

// we will use the Base Address of the RTL_ALU
Xuint32 *baseaddr_rtl_alu = (Xuint32 *) XPAR_RTL_ALU_0_S00_AXI_BASEADDR;

int main() {
    init_platform();

    ////////////////////////////////////////////////////////////////////////////////////////
    // RTL ALU TEST
    xil_printf("Performing a test of the RTL_ALU... \r\n");

    // Write ALU inputs and function code to register 0
    // Assuming the format is: {func[4:0], opb[31:0], opa[31:0]}

    // Write ALU operand A to register 0
    *(baseaddr_rtl_alu + 0) = 0x0000000a; // opa=10

    // Write ALU operand B to register 1
    *(baseaddr_rtl_alu + 1) = 0x00000003; // opb=3

    // Write ALU function code to register 2
    *(baseaddr_rtl_alu + 2) = 0x00; // ALU_ADD

    xil_printf("Wrote to register 0: 0x%08x \r\n", *(baseaddr_rtl_alu + 0));
    xil_printf("Wrote to register 1: 0x%08x \r\n", *(baseaddr_rtl_alu + 1));
    xil_printf("Wrote to register 2: 0x%08x \r\n", *(baseaddr_rtl_alu + 2));

    // Read ALU output from register 3
    xil_printf("Read from register 3: 0x%08x \r\n", *(baseaddr_rtl_alu + 3));

    xil_printf("End of test RTL_ALU \r\n");

    ////////////////////////////////////////////////////////////////////////////////////////
    // HLS ALU TEST
    xil_printf("Performing a test of the HLS_ALU... \r\n");

    int status;
    // Create hls_alu pointer
    XHls_alu do_hls_alu;
    XHls_alu_Config *do_hls_alu_cfg;
    do_hls_alu_cfg = XHls_alu_LookupConfig(XPAR_HLS_ALU_0_DEVICE_ID);

    if (!do_hls_alu_cfg) {
        xil_printf("Error loading configuration for do_hls_alu_cfg \r\n");
    }

    status = XHls_alu_CfgInitialize(&do_hls_alu, do_hls_alu_cfg);
    if (status != XST_SUCCESS) {
        xil_printf("Error initializing for do_hls_alu \r\n");
    }

    unsigned int a, b, p;
    unsigned char func;

    a = 10;
    b = 3;
    func = 0; // ALU_ADD
    p = 0;

    // Write ALU inputs and function code
    XHls_alu_Set_a(&do_hls_alu, a);
    XHls_alu_Set_b(&do_hls_alu, b);
    XHls_alu_Set_sel(&do_hls_alu, func);
    xil_printf("Write a: 0x%08x \r\n", a);
    xil_printf("Write b: 0x%08x \r\n", b);
    xil_printf("Write func: 0x%02x \r\n", func);

    // Start hls_alu
    XHls_alu_Start(&do_hls_alu);
    xil_printf("Started hls_alu \r\n");

    // Wait until it's done (optional here)
    while (!XHls_alu_IsDone(&do_hls_alu));

    // Get hls_alu returned value
    p = XHls_alu_Get_return(&do_hls_alu);

    xil_printf("Read p: 0x%08x \r\n", p);

    xil_printf("End of test HLS_ALU \r\n");

    cleanup_platform();
    return 0;
}
