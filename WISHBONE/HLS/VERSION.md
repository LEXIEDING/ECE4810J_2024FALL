## Version Document

### Previous Lab Implementation Reference

__code_path:__

```powershell
hls_alu.cpp
test_hls_alu.cpp
Vitis_HLS_Application\hls_rtl_alu.c
```

### Primitive Read/Write WISHBONE Master/Slave Implementation (v1) <img alt="Build Status" src="https://img.shields.io/badge/build-pass-brightgreen">

__code_path:__

```powershell
hls_top_v1.cpp
test_hls_top_v1.cpp
Vitis_HLS_Application\hls_top_v1.c
```

__v1_design_specification:__

![v1_design_specification](img/v1_design_specification.png)

__v1_block_design:__

![v1_block_design](img/v1_block_design.png)

__v1_vitis_application_outcome:__

![v1_vitis_application_outcome](img/v1_vitis_application_outcome.png)

### Read/Write WISHBONE Master/Slave Implementation with `BASEADDR`, `SIZE` and `OFFSET` (v2) <img alt="Build Status" src="https://img.shields.io/badge/build-pass-brightgreen">

__v2_vitis_hls_solution_report:__

![v2_vitis_hls_solution_report](img/v2_vitis_hls_solution_report.png)

```powershell
hls_top_v2.cpp
test_hls_top_v2.cpp
Vitis_HLS_Application\hls_top_v2.c
```
__v2_implemented_design_highlight:__

![v2_implemented_design_highlight](img/v2_implemented_design_highlight.png)

__v2_vitis_application_outcome:__

![v2_vitis_application_outcome](img/v2_vitis_application_outcome.png)
 
 ### Read/Write WISHBONE Master/Slave Implementation with `sel` Signal (v3) <img alt="Build Status" src="https://img.shields.io/badge/build-pass-brightgreen">

__v3_vitis_hls_solution_report:__

![v3_vitis_hls_solution_report](img/v3_vitis_hls_solution_report.png)

__v3_vitis_hls_co-simulation_report:__

![v3_vitis_hls_co-simulation_report](img/v3_vitis_hls_co-simulation_report.png)

__v3_block_design:__

![v3_block_design](img/v3_block_design.png)

__v3_implemented_design_highlight:__

![v3_implemented_design_highlight](img/v3_implemented_design_highlight.png)

__v3_Tcl Script:__

```Tcl
start_gui
open_project E:/SJTU/2024Fall/ECE4810J/Final_Project_HLS/WISHBONE/WISHBONE.xpr
delete_bd_objs [get_bd_intf_nets ps7_0_axi_periph_M00_AXI] [get_bd_cells hls_top_0]
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:hls_top:1.0 hls_top_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {/processing_system7_0/FCLK_CLK0 (100 MHz)} Clk_slave {Auto} Clk_xbar {/processing_system7_0/FCLK_CLK0 (100 MHz)} Master {/processing_system7_0/M_AXI_GP0} Slave {/hls_top_0/s_axi_CRTLS} ddr_seg {Auto} intc_ip {/ps7_0_axi_periph} master_apm {0}}  [get_bd_intf_pins hls_top_0/s_axi_CRTLS]
regenerate_bd_layout
save_bd_design
reset_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 20
open_run impl_1
open_bd_design {E:/SJTU/2024Fall/ECE4810J/Final_Project_HLS/WISHBONE/WISHBONE.srcs/sources_1/bd/wishbone_hls/wishbone_hls.bd}
write_hw_platform -fixed -include_bit -force -file E:/SJTU/2024Fall/ECE4810J/Final_Project_HLS/WISHBONE/wishbone_hls_wrapper.xsa
```
__v3_vitis_application_outcome:__

![v3_vitis_application_outcome](img/v3_vitis_application_outcome.png)

__v3_interface_specifications:__

```cpp
#define ADDR_WIDTH 32
#define DATA_WIDTH 32

const size_t memory_size = 0x00000400 / sizeof(unsigned int);

// Define the Wishbone interface signals
struct WishboneInterface {
    bool cyc;    // Cycle signal: indicates the start and end of a bus cycle
    bool stb;    // Strobe signal: indicates a valid transfer cycle
    bool we;     // Write enable: indicates a write operation when high
    unsigned int addr;  // Address: the address for the current operation
    unsigned int data;  // Data: the data to be written or read
    unsigned char sel;  // Byte select signal: indicates which bytes are valid
    bool ack;    // Acknowledge signal: indicates the completion of a transfer
};

// Define the Wishbone master class
class WishboneMaster {
public:
    WishboneInterface wb;  // Wishbone interface instance

    // Method to perform a write operation
    void write(unsigned int addr, unsigned int data, unsigned char sel) {
        ···
    }

    // Method to perform a read operation
    unsigned int read(unsigned int addr, unsigned char sel) {
        ···
    }
};

// Define the Wishbone slave class
class WishboneSlave {
public:
    WishboneInterface wb;  // Wishbone interface instance
    unsigned int memory[memory_size];  // Simple memory model
    unsigned int baseaddr;  // Base address of the slave
    unsigned int size;      // Address space size of the slave

    // Method to process read/write operations
    void process() {
        ···
    }
};

class WishboneArbiter {
public:
    WishboneMaster* master;  // Pointer to the Wishbone master
    WishboneSlave* slave0;   // Pointer to the first Wishbone slave
    WishboneSlave* slave1;   // Pointer to the second Wishbone slave

    // Method to perform arbitration and route the master's request to the appropriate slave
    void arbitrate() {
        // Address decoding to select the appropriate slave based on the address range
        bool s0_sel = (master->wb.addr >= slave0->baseaddr) && (master->wb.addr < (slave0->baseaddr + slave0->size));
        bool s1_sel = (master->wb.addr >= slave1->baseaddr) && (master->wb.addr < (slave1->baseaddr + slave1->size));

        // If the address falls within the range of slave0
        if (s0_sel) {
            ···
        }
        // If the address falls within the range of slave1
        else if (s1_sel) {
            ···
        }
    }
};

// Top-level function for HLS synthesis
extern "C" void hls_top(unsigned int addr, unsigned int data, bool we, bool cyc, bool stb, unsigned char sel, unsigned int* data_out, bool* ack_out) {
    #pragma HLS INTERFACE s_axilite port=addr bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=data bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=we bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=cyc bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=stb bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=sel bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=data_out bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=ack_out bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=return bundle=CRTLS

    WishboneMaster master;  // Instantiate Wishbone master
    WishboneSlave slave0, slave1;  // Instantiate two Wishbone slaves
    WishboneArbiter arbiter;  // Instantiate Wishbone arbiter

    // Initialize slave base addresses and sizes
    slave0.baseaddr = 0x00000000;
    slave0.size = 0x00000400; // 1KB
    slave1.baseaddr = 0x00000400;
    slave1.size = 0x00000400; // 1KB

    // Set arbiter connections
    arbiter.master = &master;
    arbiter.slave0 = &slave0;
    arbiter.slave1 = &slave1;

    // Set master interface signals
    master.wb.addr = addr;
    master.wb.data = data;
    master.wb.we = we;
    master.wb.cyc = cyc;
    master.wb.stb = stb;
    master.wb.sel = sel;

    // Perform arbitration and data transfer
    arbiter.arbitrate();

    // Output the results
    *data_out = master.wb.data;
    *ack_out = master.wb.ack;
}
```