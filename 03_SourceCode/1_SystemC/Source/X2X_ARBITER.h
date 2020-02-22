/**
 * X2X ARBITER IP
 */

#include "AXI_Interconnection.h"
#ifndef _X2X_ARBITER_H
#define _X2X_ARBITER_H

class X2X_ARBITER: public sc_module {
private: 
    void AWHandShackSlaveMethod();
    void AWRoundRobinMethod();
    void ARHandShackSlaveMethod();
    void ARRoundRobinMethod();
    void WHandShackSlaveMethod();
    void WRoundRobinMethod();
    void ArbiterCoreMethod();
    // Aw channel
    unsigned int AwCounterValue[PRAM_MASTER_NUM];
    bool isAwValid[PRAM_MASTER_NUM];
    bool isAwSelector[PRAM_MASTER_NUM];
    unsigned int AWPriorityValid;
    bool isAwInprocess;
    // Ar channel
    unsigned int ArCounterValue[PRAM_MASTER_NUM];
    bool isArValid[PRAM_MASTER_NUM];
    bool isArSelector[PRAM_MASTER_NUM];
    unsigned int ARPriorityValid;
    bool isArInprocess;
    // W channel
    unsigned int WCounterValue[PRAM_MASTER_NUM];
    bool isWValid[PRAM_MASTER_NUM];
    bool isWSelector[PRAM_MASTER_NUM];
    unsigned int WPriorityValid;
    bool isWInprocess;

public:
    unsigned int masterID;
    X2X_ARBITER( );
    ~X2X_ARBITER( );
    // global port 
    sc_in<bool>      ACLK;                                // AXI bus clock.
    sc_in<bool>      ARESETN;
    // port declare
    //*****************************
    //********Slave side signal****
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_out<bool>     S_AXI_AWREADY[PRAM_MASTER_NUM];                      // aw arbiter output ready out.
    sc_in<bool>      S_AXI_AWID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];       // AXI address Write ID.
    sc_in<bool>      S_AXI_AWADDR[PRAM_MASTER_NUM][C_S_AXI_ADDR_WIDTH];   // AXI Write address.
    sc_in<bool>      S_AXI_AWLEN[PRAM_MASTER_NUM][PRAM_AXI_AxLEN];        // AXI address Write burst length.
    sc_in<bool>      S_AXI_AWSIZE[PRAM_MASTER_NUM][PRAM_AXI_AxSIZE];      // AXI address Write burst size.
    sc_in<bool>      S_AXI_AWBURST[PRAM_MASTER_NUM][PRAM_AXI_AxBURST];    // AXI address Write burst type.
    sc_in<bool>      S_AXI_AWLOCK[PRAM_MASTER_NUM];                       // AXI Write address lock signal.
    sc_in<bool>      S_AXI_AWCACHE[PRAM_MASTER_NUM][PRAM_AXI_AxCACHE];    // AXI Write address cache control signal.
    sc_in<bool>      S_AXI_AWPROT[PRAM_MASTER_NUM][PRAM_AXI_AxPROT];      // AXI Write address protection signal.
    sc_in<bool>      S_AXI_AWREGION[PRAM_MASTER_NUM][PRAM_AXI_AxREGION];  // Channel address region index
    sc_in<bool>      S_AXI_AWQOS[PRAM_MASTER_NUM][PRAM_AXI_AxQOS];        // Channel Quality of Service (QoS).
    sc_in<bool>      S_AXI_AWUSER[PRAM_MASTER_NUM][C_S_AXI_AWUSER_WIDTH]; // User-defined AW Channel signals.
    sc_in<bool>      S_AXI_AWVALID[PRAM_MASTER_NUM];                      // AXI Write address valid.
    // AXI Write Data Channel Signals (W)
    sc_out<bool>     S_AXI_WREADY[PRAM_MASTER_NUM];                       // aw arbiter output ready out.
    sc_in<bool>      S_AXI_WID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];        // AXI3 Write ID.
    sc_in<bool>      S_AXI_WDATA[PRAM_MASTER_NUM][C_S_AXI_DATA_WIDTH];    // AXI Write data.
    sc_in<bool>      S_AXI_WSTRB[PRAM_MASTER_NUM][C_S_AXI_DATA_WIDTH / 8];// AXI Write data strobes.
    sc_in<bool>      S_AXI_WLAST[PRAM_MASTER_NUM];                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_in<bool>      S_AXI_WUSER[PRAM_MASTER_NUM][C_S_AXI_WUSER_WIDTH];   // User-defined W Channel signals.
    sc_in<bool>      S_AXI_WVALID[PRAM_MASTER_NUM];                       // AXI Write data valid.
    //sc_out<bool>       M_AXI_WREADY;                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_out<bool>     S_AXI_BID[C_S_AXI_ID_WIDTH];        // AXI Write response ID.
    sc_out<bool>     S_AXI_BRESP[PRAM_AXI_RRESP];        // AXI Write response code.
    sc_out<bool>     S_AXI_BUSER;                        // User-defined B channel signals.
    sc_out<bool>     S_AXI_BVALID;                       // AXI Write response valid.
    sc_in<bool>      S_AXI_BREADY;                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_in<bool>      S_AXI_ARID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];       // AXI address Read ID.
    sc_in<bool>      S_AXI_ARADDR[PRAM_MASTER_NUM][C_S_AXI_ADDR_WIDTH];   // AXI Read address.
    sc_in<bool>      S_AXI_ARLEN[PRAM_MASTER_NUM][PRAM_AXI_AxLEN];        // AXI address Read burst length.
    sc_in<bool>      S_AXI_ARSIZE[PRAM_MASTER_NUM][PRAM_AXI_AxSIZE];      // AXI address Read burst size.
    sc_in<bool>      S_AXI_ARBURST[PRAM_MASTER_NUM][PRAM_AXI_AxBURST];    // AXI address Read burst type.
    sc_in<bool>      S_AXI_ARLOCK[PRAM_MASTER_NUM];                       // AXI Read address lock signal.
    sc_in<bool>      S_AXI_ARCACHE[PRAM_MASTER_NUM][PRAM_AXI_AxCACHE];    // AXI Read address cache control signal.
    sc_in<bool>      S_AXI_ARPROT[PRAM_MASTER_NUM][PRAM_AXI_AxPROT];      // AXI Read address protection signal.
    sc_in<bool>      S_AXI_ARREGION[PRAM_MASTER_NUM][PRAM_AXI_AxREGION];  // Channel address region index.
    sc_in<bool>      S_AXI_ARQOS[PRAM_MASTER_NUM][PRAM_AXI_AxQOS];        // Channel Quality of Service.
    sc_in<bool>      S_AXI_ARUSER[PRAM_MASTER_NUM][C_S_AXI_ARUSER_WIDTH]; // User-defined AR Channel signals.
    sc_in<bool>      S_AXI_ARVALID[PRAM_MASTER_NUM];                      // AXI Read address valid.
    sc_out<bool>     S_AXI_ARREADY[PRAM_MASTER_NUM];                                      // axi arbiter AR ready out.
    // AXI Read Data channel Signals (R)
    sc_out<bool>     S_AXI_RID[C_S_AXI_ID_WIDTH];        // AXI Read data response ID.
    sc_out<bool>     S_AXI_RDATA[C_S_AXI_DATA_WIDTH];    // AXI Read data.
    sc_out<bool>     S_AXI_RRESP[PRAM_AXI_RRESP];        // AXI Read response code.
    sc_out<bool>     S_AXI_RLAST;                        // AXI Read data last signal.
    sc_out<bool>     S_AXI_RUSER[C_S_AXI_RUSER_WIDTH];   // User-defined R Channel signals.
    sc_out<bool>     S_AXI_RVALID;                       // AXI Read valid.
    sc_in<bool>      S_AXI_RREADY;                       // AXI Read ready.
    //*****************************
    //********Master side signal***
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_out<bool>      M_AXI_AWID[C_S_AXI_ID_WIDTH];       // AXI address Write ID.
    sc_out<bool>      M_AXI_AWADDR[C_S_AXI_ADDR_WIDTH];   // AXI Write address.
    sc_out<bool>      M_AXI_AWLEN[PRAM_AXI_AxLEN];        // AXI address Write burst length.
    sc_out<bool>      M_AXI_AWSIZE[PRAM_AXI_AxSIZE];      // AXI address Write burst size.
    sc_out<bool>      M_AXI_AWBURST[PRAM_AXI_AxBURST];    // AXI address Write burst type.
    sc_out<bool>      M_AXI_AWLOCK;                       // AXI Write address lock signal.
    sc_out<bool>      M_AXI_AWCACHE[PRAM_AXI_AxCACHE];    // AXI Write address cache control signal.
    sc_out<bool>      M_AXI_AWPROT[PRAM_AXI_AxPROT];      // AXI Write address protection signal.
    sc_out<bool>      M_AXI_AWREGION[PRAM_AXI_AxREGION];  // Channel address region index
    sc_out<bool>      M_AXI_AWQOS[PRAM_AXI_AxQOS];        // Channel Quality of Service (QoS).
    sc_out<bool>      M_AXI_AWUSER[C_S_AXI_AWUSER_WIDTH]; // User-defined AW Channel signals.
    sc_out<bool>      M_AXI_AWVALID;                      // AXI Write address valid.
    sc_in<bool>       M_AXI_AWREADY;                      // AXI Write data ready.

    // AXI Write Data Channel Signals (W)
    sc_out<bool>      M_AXI_WID[C_S_AXI_ID_WIDTH];        // AXI3 Write ID.
    sc_out<bool>      M_AXI_WDATA[C_S_AXI_DATA_WIDTH];    // AXI Write data.
    sc_out<bool>      M_AXI_WSTRB[C_S_AXI_DATA_WIDTH / 8];// AXI Write data strobes.
    sc_out<bool>      M_AXI_WLAST;                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_out<bool>      M_AXI_WUSER[C_S_AXI_WUSER_WIDTH];   // User-defined W Channel signals.
    sc_out<bool>      M_AXI_WVALID;                       // AXI Write data valid.
    sc_in<bool>       M_AXI_WREADY;                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_in<bool>       M_AXI_BID[C_S_AXI_ID_WIDTH];        // AXI Write response ID.
    sc_in<bool>       M_AXI_BRESP[PRAM_AXI_RRESP];        // AXI Write response code.
    sc_in<bool>       M_AXI_BUSER;                        // User-defined B channel signals.
    sc_in<bool>       M_AXI_BVALID;                       // AXI Write response valid.
    sc_out<bool>      M_AXI_BREADY;                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_out<bool>      M_AXI_ARID[C_S_AXI_ID_WIDTH];       // AXI address Read ID.
    sc_out<bool>      M_AXI_ARADDR[C_S_AXI_ADDR_WIDTH];   // AXI Read address.
    sc_out<bool>      M_AXI_ARLEN[PRAM_AXI_AxLEN];        // AXI address Read burst length.
    sc_out<bool>      M_AXI_ARSIZE[PRAM_AXI_AxSIZE];      // AXI address Read burst size.
    sc_out<bool>      M_AXI_ARBURST[PRAM_AXI_AxBURST];    // AXI address Read burst type.
    sc_out<bool>      M_AXI_ARLOCK;                       // AXI Read address lock signal.
    sc_out<bool>      M_AXI_ARCACHE[PRAM_AXI_AxCACHE];    // AXI Read address cache control signal.
    sc_out<bool>      M_AXI_ARPROT[PRAM_AXI_AxPROT];      // AXI Read address protection signal.
    sc_out<bool>      M_AXI_ARREGION[PRAM_AXI_AxREGION];  // Channel address region index.
    sc_out<bool>      M_AXI_ARQOS[PRAM_AXI_AxQOS];        // Channel Quality of Service.
    sc_out<bool>      M_AXI_ARUSER[C_S_AXI_ARUSER_WIDTH]; // User-defined AR Channel signals.
    sc_out<bool>      M_AXI_ARVALID;                      // AXI Read address valid.
    sc_in<bool>       M_AXI_ARREADY;                      // AXI Read address ready.
    // AXI Read Data channel Signals (R)
    sc_in<bool>       M_AXI_RID[C_S_AXI_ID_WIDTH];        // AXI Read data response ID.
    sc_in<bool>       M_AXI_RDATA[C_S_AXI_DATA_WIDTH];    // AXI Read data.
    sc_in<bool>       M_AXI_RRESP[PRAM_AXI_RRESP];        // AXI Read response code.
    sc_in<bool>       M_AXI_RLAST;                        // AXI Read data last signal.
    sc_in<bool>       M_AXI_RUSER[C_S_AXI_RUSER_WIDTH];   // User-defined R Channel signals.
    sc_in<bool>       M_AXI_RVALID;                       // AXI Read valid.
    sc_out<bool>      M_AXI_RREADY;                       // AXI Read ready.
};

#endif //_X2X_ARBITER_H