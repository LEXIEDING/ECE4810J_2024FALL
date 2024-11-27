module wishbone_interconnect (
    input wire clk,
    input wire rst,

    // Master Interface
    input wire [31:0] m_adr_i,
    output wire [31:0] m_dat_o,
    input wire [31:0] m_dat_i,
    input wire m_we_i,
    input wire [1:0] m_sel_i, // Byte select
    input wire m_stb_i,
    output wire m_ack_o,
    input wire m_cyc_i,

    // Slave 0 Interface
    output wire [31:0] s0_adr_o,
    input wire [31:0] s0_dat_i,
    output wire [31:0] s0_dat_o,
    output wire s0_we_o,
    output wire [1:0] s0_sel_o, // Byte select
    output wire s0_stb_o,
    input wire s0_ack_i,
    output wire s0_cyc_o,

    // Slave 1 Interface
    output wire [31:0] s1_adr_o,
    input wire [31:0] s1_dat_i,
    output wire [31:0] s1_dat_o,
    output wire s1_we_o,
    output wire [1:0] s1_sel_o, // Byte select
    output wire s1_stb_o,
    input wire s1_ack_i,
    output wire s1_cyc_o
);

    // Address decoding
    wire s0_sel = (m_adr_i[31:28] == 4'h0); // Address range for slave 0
    wire s1_sel = (m_adr_i[31:28] == 4'h1); // Address range for slave 1

    // Master to Slave connections
    assign s0_adr_o = m_adr_i;
    assign s0_dat_o = m_dat_i;
    assign s0_we_o = m_we_i;
    assign s0_sel_o = m_sel_i;
    assign s0_stb_o = m_stb_i & s0_sel;
    assign s0_cyc_o = m_cyc_i & s0_sel;

    assign s1_adr_o = m_adr_i;
    assign s1_dat_o = m_dat_i;
    assign s1_we_o = m_we_i;
    assign s1_sel_o = m_sel_i;
    assign s1_stb_o = m_stb_i & s1_sel;
    assign s1_cyc_o = m_cyc_i & s1_sel;

    // Slave to Master connections
    assign m_dat_o = s0_sel ? s0_dat_i : (s1_sel ? s1_dat_i : 32'h00000000);
    assign m_ack_o = s0_sel ? s0_ack_i : (s1_sel ? s1_ack_i : 1'b0);

endmodule
