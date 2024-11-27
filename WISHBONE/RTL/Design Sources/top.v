module top (
    input wire clk,
    input wire rst,
    inout wire [3:0] btn_tri_io,
    inout wire [3:0] led
);

    // Internal signals
    wire [31:0] m_adr_i;
    wire [31:0] m_dat_o;
    wire [31:0] m_dat_i;
    wire m_we_i;
    wire [1:0] m_sel_i;
    wire m_stb_i;
    wire m_ack_o;
    wire m_cyc_i;

    wire [31:0] s0_adr_o;
    wire [31:0] s0_dat_i;
    wire [31:0] s0_dat_o;
    wire s0_we_o;
    wire [1:0] s0_sel_o;
    wire s0_stb_o;
    wire s0_ack_i;
    wire s0_cyc_o;

    wire [31:0] s1_adr_o;
    wire [31:0] s1_dat_i;
    wire [31:32] s1_dat_o;
    wire s1_we_o;
    wire [1:0] s1_sel_o;
    wire s1_stb_o;
    wire s1_ack_i;
    wire s1_cyc_o;

    // Instantiate the processing system
    test_v1_processing_system7_0_0 processing_system7_0 (
        .DDR_Addr(),
        .DDR_BankAddr(),
        .DDR_CAS_n(),
        .DDR_CKE(),
        .DDR_CS_n(),
        .DDR_Clk(),
        .DDR_Clk_n(),
        .DDR_DM(),
        .DDR_DQ(),
        .DDR_DQS(),
        .DDR_DQS_n(),
        .DDR_DRSTB(),
        .DDR_ODT(),
        .DDR_RAS_n(),
        .DDR_VRN(),
        .DDR_VRP(),
        .DDR_WEB(),
        .FCLK_CLK0(clk),
        .MIO(),
        .M_AXI_GP0_ACLK(clk),
        .M_AXI_GP0_ARREADY(1'b0),
        .M_AXI_GP0_AWREADY(1'b0),
        .M_AXI_GP0_BID(),
        .M_AXI_GP0_BRESP(),
        .M_AXI_GP0_BVALID(),
        .M_AXI_GP0_RDATA(m_dat_i),
        .M_AXI_GP0_RID(),
        .M_AXI_GP0_RLAST(),
        .M_AXI_GP0_RRESP(),
        .M_AXI_GP0_RVALID(),
        .M_AXI_GP0_WREADY(),
        .PS_CLK(),
        .PS_PORB(),
        .PS_SRSTB(),
        .USB0_VBUS_PWRFAULT()
    );

    // Instantiate the WISHBONE interconnect
    wishbone_interconnect interconnect (
        .clk(clk),
        .rst(rst),
        .m_adr_i(m_adr_i),
        .m_dat_o(m_dat_o),
        .m_dat_i(m_dat_i),
        .m_we_i(m_we_i),
        .m_sel_i(m_sel_i),
        .m_stb_i(m_stb_i),
        .m_ack_o(m_ack_o),
        .m_cyc_i(m_cyc_i),
        .s0_adr_o(s0_adr_o),
        .s0_dat_i(s0_dat_i),
        .s0_dat_o(s0_dat_o),
        .s0_we_o(s0_we_o),
        .s0_sel_o(s0_sel_o),
        .s0_stb_o(s0_stb_o),
        .s0_ack_i(s0_ack_i),
        .s0_cyc_o(s0_cyc_o),
        .s1_adr_o(s1_adr_o),
        .s1_dat_i(s1_dat_i),
        .s1_dat_o(s1_dat_o),
        .s1_we_o(s1_we_o),
        .s1_sel_o(s1_sel_o),
        .s1_stb_o(s1_stb_o),
        .s1_ack_i(s1_ack_i),
        .s1_cyc_o(s1_cyc_o)
    );

    // Instantiate the GPIO buttons module
    wishbone_gpio_buttons gpio_buttons (
        .clk(clk),
        .rst(rst),
        .adr_i(s0_adr_o),
        .dat_i(s0_dat_o),
        .dat_o(s0_dat_i),
        .we_i(s0_we_o),
        .sel_i(s0_sel_o),
        .stb_i(s0_stb_o),
        .ack_o(s0_ack_i),
        .cyc_i(s0_cyc_o),
        .gpio_buttons(btn_tri_io)
    );

    // Instantiate the GPIO LEDs module
    wishbone_gpio_leds gpio_leds (
        .clk(clk),
        .rst(rst),
        .adr_i(s1_adr_o),
        .dat_i(s1_dat_o),
        .dat_o(s1_dat_i),
        .we_i(s1_we_o),
        .sel_i(s1_sel_o),
        .stb_i(s1_stb_o),
        .ack_o(s1_ack_i),
        .cyc_i(s1_cyc_o),
        .gpio_led(led)
    );

endmodule
