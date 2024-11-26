module WBI_SHRD_08 #(
    parameter WB_CD_AWIDTH_g = 16,                  // Coarse Decoder Address WIDTH
    parameter WB_N_SLAVES_g = 4,                   // Number of slaves
    parameter WB_MEMMAP_g = '{                     // Memory map
        '{16'h0000, 16'h0F}, 
        '{16'h0010, 16'h0F}, 
        '{16'h0020, 16'h0F}, 
        '{16'h0030, 16'h0F}
    }
) (
    input wire CLK_i,
    input wire RST_i,
    input wire CLK_EN_i,
    
    // Wishbone Master Interface
    input wire [WB_CD_AWIDTH_g-1:0] WBM_ADR_i,
    input wire [7:0] WBM_DAT_i,
    output reg [7:0] WBM_DAT_o,
    input wire WBM_WE_i,
    input wire WBM_STB_i,
    output reg WBM_ACK_o,
    input wire WBM_CYC_i,
    output reg WBM_ERR_o,
    output reg WBM_RTY_o,

    // Wishbone Slaves Interface
    output reg [WB_CD_AWIDTH_g-1:0] WBS_ADR_o,
    input wire [7:0] WBS_DAT_i[WB_N_SLAVES_g-1:0],
    output reg [7:0] WBS_DAT_o,
    output reg WBS_WE_o,
    output reg [WB_N_SLAVES_g-1:0] WBS_STB_o,
    input wire [WB_N_SLAVES_g-1:0] WBS_ACK_i,
    output reg [WB_N_SLAVES_g-1:0] WBS_CYC_o,
    input wire [WB_N_SLAVES_g-1:0] WBS_ERR_i,
    input wire [WB_N_SLAVES_g-1:0] WBS_RTY_i
);

// Internal Signals
reg [WB_CD_AWIDTH_g-1:0] ADR_s;
reg [WB_CD_AWIDTH_g-1:0] BASEADDR_s[WB_N_SLAVES_g-1:0];
reg [WB_N_SLAVES_g-1:0] CS_s;
reg [WB_N_SLAVES_g-1:0] SSTB_s;
reg [WB_N_SLAVES_g-1:0] SCYC_s;
reg [WB_CD_AWIDTH_g-1:0] OFFSET_s;

// Address Decoder
always @(*) begin
    ADR_s = WBM_ADR_i[WB_CD_AWIDTH_g-1:0];
    for (int i = 0; i < WB_N_SLAVES_g; i = i + 1) begin
        BASEADDR_s[i] = ADR_s & ~(WB_MEMMAP_g[i].size - 1);
        CS_s[i] = (BASEADDR_s[i] == WB_MEMMAP_g[i].baseaddr) ? 1'b1 : 1'b0;
    end
end

// Address Multiplexing
always @(*) begin
    OFFSET_s = 0;
    for (int i = 0; i < WB_N_SLAVES_g; i = i + 1) begin
        if (CS_s[i]) begin
            OFFSET_s = WB_MEMMAP_g[i].size - 1;
        end
    end
    WBS_ADR_o = WBM_ADR_i & OFFSET_s;
end

// Master-to-Slave Signal Routing
always @(*) begin
    for (int i = 0; i < WB_N_SLAVES_g; i = i + 1) begin
        SSTB_s[i] = CS_s[i] & WBM_STB_i;
        SCYC_s[i] = CS_s[i] & WBM_CYC_i;
    end
    WBS_STB_o = SSTB_s;
    WBS_CYC_o = SCYC_s;
    WBS_DAT_o = WBM_DAT_i;
    WBS_WE_o = WBM_WE_i;
end

// Slave-to-Master Multiplexing
always @(*) begin
    WBM_DAT_o = 8'h00;
    WBM_ACK_o = 1'b0;
    WBM_ERR_o = 1'b0;
    WBM_RTY_o = 1'b0;
    for (int i = 0; i < WB_N_SLAVES_g; i = i + 1) begin
        if (CS_s[i]) begin
            WBM_DAT_o = WBS_DAT_i[i];
            WBM_ACK_o = WBM_ACK_o | WBS_ACK_i[i];
            WBM_ERR_o = WBM_ERR_o | WBS_ERR_i[i];
            WBM_RTY_o = WBM_RTY_o | WBS_RTY_i[i];
        end
    end
end

endmodule
