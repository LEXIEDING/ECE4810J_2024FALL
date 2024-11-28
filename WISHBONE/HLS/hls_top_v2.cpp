#include <stdio.h>

#define ADDR_WIDTH 32
#define DATA_WIDTH 32

const size_t memory_size = 0x00000400 / sizeof(unsigned int);
// const size_t memory_size = 256;

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
    unsigned int memory[memory_size];  // 简单的内存模型
    unsigned int baseaddr;     // 基地址
    unsigned int size;         // 地址空间大小

    void process() {
        if (wb.cyc && wb.stb) {  // 只有在 cyc 和 stb 都为高时才处理请求
            unsigned int offset = wb.addr - baseaddr; // 计算地址偏移
            if (offset < size) { // 地址在范围内
                if (wb.we) {
                    // 写操作
                    memory[offset / sizeof(unsigned int)] = wb.data;
                    printf("Writing data 0x%x to address 0x%x\n", wb.data, wb.addr);
                } else {
                    // 读操作
                    wb.data = memory[offset / sizeof(unsigned int)];
                    printf("Reading data 0x%x from address 0x%x\n", wb.data, wb.addr);
                }
                wb.ack = true; // 操作完成，设置 ack 信号
            } else {
                wb.ack = false; // 地址超出范围，设置 ack 信号为 false
            }
        } else {
            wb.ack = false; // 无效传输，设置 ack 信号为 false
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
        bool s0_sel = (master->wb.addr >= slave0->baseaddr) && (master->wb.addr < (slave0->baseaddr + slave0->size));
        bool s1_sel = (master->wb.addr >= slave1->baseaddr) && (master->wb.addr < (slave1->baseaddr + slave1->size));

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

    slave0.baseaddr = 0x00000000;
    slave0.size = 0x00000400; // 1KB
    slave1.baseaddr = 0x00000400;
    slave1.size = 0x00000400; // 1KB

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
