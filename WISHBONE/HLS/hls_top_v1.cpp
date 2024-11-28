#include <stdio.h>

#define ADDR_WIDTH 32
#define DATA_WIDTH 32

struct WishboneInterface {
    bool cyc;    // Cycle signal
    bool stb;    // Strobe signal
    bool we;     // Write enable
    unsigned int addr;  // Address
    unsigned int data;  // Data
    bool ack;    // Acknowledge signal
};

class WishboneMaster {
public:
    WishboneInterface wb;

    void write(unsigned int addr, unsigned int data) {
        wb.cyc = true;
        wb.stb = true;
        wb.we = true;
        wb.addr = addr;
        wb.data = data;
        // 等待从设备响应
        while (!wb.ack);
        wb.cyc = false;
        wb.stb = false;
    }

    unsigned int read(unsigned int addr) {
        wb.cyc = true;
        wb.stb = true;
        wb.we = false;
        wb.addr = addr;
        // 等待从设备响应
        while (!wb.ack);
        wb.cyc = false;
        wb.stb = false;
        return wb.data;
    }
};

class WishboneSlave {
public:
    WishboneInterface wb;
    unsigned int memory[256];  // 简单的内存模型

    void process() {
        if (wb.cyc && wb.stb) {
            if (wb.we) {
                // 写操作
                memory[wb.addr] = wb.data;
            } else {
                // 读操作
                wb.data = memory[wb.addr];
            }
            wb.ack = true;
        } else {
            wb.ack = false;
        }
    }
};

class WishboneArbiter {
public:
    WishboneMaster* master;
    WishboneSlave* slave0;
    WishboneSlave* slave1;

    void arbitrate() {
        // 地址解码
        bool s0_sel = (master->wb.addr >> 28) == 0x0;
        bool s1_sel = (master->wb.addr >> 28) == 0x1;

        if (s0_sel) {
            slave0->wb.cyc = master->wb.cyc;
            slave0->wb.stb = master->wb.stb;
            slave0->wb.we = master->wb.we;
            slave0->wb.addr = master->wb.addr;
            slave0->wb.data = master->wb.data;
            slave0->process();
            if (slave0->wb.ack) {
                master->wb.data = slave0->wb.data;
                master->wb.ack = slave0->wb.ack;
            }
        } else if (s1_sel) {
            slave1->wb.cyc = master->wb.cyc;
            slave1->wb.stb = master->wb.stb;
            slave1->wb.we = master->wb.we;
            slave1->wb.addr = master->wb.addr;
            slave1->wb.data = master->wb.data;
            slave1->process();
            if (slave1->wb.ack) {
                master->wb.data = slave1->wb.data;
                master->wb.ack = slave1->wb.ack;
            }
        }
    }
};

extern "C" void hls_top(unsigned int addr, unsigned int data, bool we, bool cyc, bool stb, unsigned int* data_out, bool* ack_out) {
    #pragma HLS INTERFACE s_axilite port=addr bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=data bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=we bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=cyc bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=stb bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=data_out bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=ack_out bundle=CRTLS
    #pragma HLS INTERFACE s_axilite port=return bundle=CRTLS

    WishboneMaster master;
    WishboneSlave slave0, slave1;
    WishboneArbiter arbiter;

    arbiter.master = &master;
    arbiter.slave0 = &slave0;
    arbiter.slave1 = &slave1;

    master.wb.addr = addr;
    master.wb.data = data;
    master.wb.we = we;
    master.wb.cyc = cyc;
    master.wb.stb = stb;

    arbiter.arbitrate();

    *data_out = master.wb.data;
    *ack_out = master.wb.ack;
}
