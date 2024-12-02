`timescale 1ns / 1ps

module testbench;

    // Testbench Signals
    reg CLK_i;
    reg RST_i;

    // Instantiate the wishbone_top module
    wishbone_top #(
        .WB_WIDTH(16),      // Address width
        .WB_W_DATA(8)       // Data width
    ) uut (
        .CLK_i(CLK_i),
        .RST_i(RST_i)
    );

    // Generate clock signal
    always begin
        #5 CLK_i = ~CLK_i; // Period of 10ns
    end

    // Initialize signals and simulate
    initial begin
        // Initialize signals
        CLK_i = 0;
        RST_i = 0;

        // Apply reset
        #10 RST_i = 1;   // Assert reset for 10ns
        #10 RST_i = 0;   // Deassert reset

        // Wait for some time to simulate a few clock cycles
        #50;
        
        // Simulation of a Write cycle to slave 0
        $display("Writing to slave 0");
        uut.u_wishbone_master.address = 16'h0000;    // Address to write to
        uut.u_wishbone_master.data = 8'hAA;          // Data to write
        uut.u_wishbone_master.write_enable = 1'b1;   // Write enable
        uut.u_wishbone_master.strobe = 1'b1;         // Assert strobe
        uut.u_wishbone_master.cycle = 1'b1;          // Assert cycle
        #10;  // Wait for write to complete

        // Simulation of a Read cycle from slave 0
        $display("Reading from slave 0");
        uut.u_wishbone_master.address = 16'h0000; 
        uut.u_wishbone_master.write_enable = 1'b0;   // Set write enable to 0 for read
        uut.u_wishbone_master.strobe = 1'b1;         // Assert strobe
        uut.u_wishbone_master.cycle = 1'b1;          // Assert cycle
        #10;  // Wait for read to complete

        // Read the data after the read operation
        $display("Read data: %h", uut.u_wishbone_master.WBM_DAT_i);

        // End of simulation
        $stop;
    end

    // Optionally, monitor signals for debugging
    initial begin
        $monitor("Time: %0t | CLK_i: %b | RST_i: %b | WBM_ADR_o: %h | WBM_DAT_o: %h | WBM_ACK_i: %b|WBM_DAT_i: %h|(inter)WBM_DAT_o: %h|(inter)BASEADDR_s: %h", 
                 $time, CLK_i, RST_i, uut.u_wishbone_master.WBM_ADR_o, 
                 uut.u_wishbone_master.WBM_DAT_o, uut.u_wishbone_master.WBM_ACK_i,uut.u_wishbone_master.WBM_DAT_i,uut.u_wishbone_interface.WBM_DAT_o,
                 uut.u_wishbone_interface.BASEADDR_s);
    end

endmodule
