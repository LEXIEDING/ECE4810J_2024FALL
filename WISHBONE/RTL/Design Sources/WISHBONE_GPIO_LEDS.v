module wishbone_gpio_leds (
    input wire clk,
    input wire rst,

    // WISHBONE Interface
    input wire [31:0] adr_i,
    input wire [31:0] dat_i,
    output wire [31:0] dat_o,
    input wire we_i,
    input wire [1:0] sel_i, // Byte select
    input wire stb_i,
    output wire ack_o,
    input wire cyc_i,

    // GPIO Interface
    inout wire [3:0] gpio_led
);

    // Internal signals
    wire [31:0] gpio_dat_o;
    wire gpio_ack_o;

    // Instantiate WISHBONE GPIO module for LEDs
    wishbone_gpio gpio_inst (
        .clk(clk),
        .rst(rst),
        .adr_i(adr_i),
        .dat_i(dat_i),
        .dat_o(gpio_dat_o),
        .we_i(we_i),
        .sel_i(sel_i),
        .stb_i(stb_i),
        .ack_o(gpio_ack_o),
        .cyc_i(cyc_i),
        .gpio({28'b0, gpio_led}) // Only use lower 4 bits for LEDs
    );

    // Connect WISHBONE signals
    assign dat_o = gpio_dat_o;
    assign ack_o = gpio_ack_o;

endmodule
