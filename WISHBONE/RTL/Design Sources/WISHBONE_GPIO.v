module wishbone_gpio (
    input wire clk,
    input wire rst,

    // WISHBONE Interface
    input wire [31:0] adr_i,
    input wire [31:0] dat_i,
    output reg [31:0] dat_o,
    input wire we_i,
    input wire [1:0] sel_i, // Byte select
    input wire stb_i,
    output reg ack_o,
    input wire cyc_i,

    // GPIO Interface
    inout wire [31:0] gpio
);

    // Internal registers
    reg [31:0] gpio_data;
    reg [31:0] gpio_dir; // Direction register: 1 = output, 0 = input

    // Acknowledge logic
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            ack_o <= 1'b0;
        end else begin
            ack_o <= stb_i & cyc_i & ~ack_o; // Generate ack signal
        end
    end

    // Read and write logic
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            gpio_data <= 32'b0;
            gpio_dir <= 32'b0;
            dat_o <= 32'b0;
        end else if (stb_i & cyc_i & ~ack_o) begin
            if (we_i) begin
                // Write operation
                if (adr_i[3:2] == 2'b00) begin
                    gpio_data <= dat_i;
                end else if (adr_i[3:2] == 2'b01) begin
                    gpio_dir <= dat_i;
                end
            end else begin
                // Read operation
                if (adr_i[3:2] == 2'b00) begin
                    dat_o <= gpio_data;
                end else if (adr_i[3:2] == 2'b01) begin
                    dat_o <= gpio_dir;
                end
            end
        end
    end

    // GPIO logic
    genvar i;
    generate
        for (i = 0; i < 32; i = i + 1) begin : gpio_loop
            assign gpio[i] = gpio_dir[i] ? gpio_data[i] : 1'bz;
            always @(posedge clk or posedge rst) begin
                if (rst) begin
                    gpio_data[i] <= 1'b0;
                end else if (~gpio_dir[i]) begin
                    gpio_data[i] <= gpio[i];
                end
            end
        end
    endgenerate

endmodule
