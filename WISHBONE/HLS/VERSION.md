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
