/**
 * X2X top module
 */

#include "X2X_BUFFER.h"
#include "X2X_DECODER.h"
#include "X2X_ARBITER.h"
#include "AXI_Interconnection.h"

#ifndef _X2X_H
#define _X2X_H

class X2X : public sc_module {
private:
    X2X_BUFFER x2x_buffer[PRAM_MASTER_NUM];
    X2X_DECODER x2x_decoder[PRAM_MASTER_NUM];
    X2X_ARBITER x2x_arbier[PRAM_SLAVE_NUM];
public: 
    X2X( );
    ~X2X( );
    // global port 
    sc_in<bool>      ACLK;                                // AXI bus clock.
    sc_in<bool>      ARESETN;                             // AXI active-Low reset
    //*****************************
    //********Slave side signal****
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_in<bool>      S_AXI_AWID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];        // AXI address Write ID.
    sc_in<bool>      S_AXI_AWADDR[PRAM_MASTER_NUM][C_S_AXI_ADDR_WIDTH];    // AXI Write address.
    sc_in<bool>      S_AXI_AWLEN[PRAM_MASTER_NUM][PRAM_AXI_AxLEN];         // AXI address Write burst length.
    sc_in<bool>      S_AXI_AWSIZE[PRAM_MASTER_NUM][PRAM_AXI_AxSIZE];       // AXI address Write burst size.
    sc_in<bool>      S_AXI_AWBURST[PRAM_MASTER_NUM][PRAM_AXI_AxBURST];     // AXI address Write burst type.
    sc_in<bool>      S_AXI_AWLOCK[PRAM_MASTER_NUM];                        // AXI Write address lock signal.
    sc_in<bool>      S_AXI_AWCACHE[PRAM_MASTER_NUM][PRAM_AXI_AxCACHE];     // AXI Write address cache control signal.
    sc_in<bool>      S_AXI_AWPROT[PRAM_MASTER_NUM][PRAM_AXI_AxPROT];       // AXI Write address protection signal.
    sc_in<bool>      S_AXI_AWREGION[PRAM_MASTER_NUM][PRAM_AXI_AxREGION];   // Channel address region index
    sc_in<bool>      S_AXI_AWQOS[PRAM_MASTER_NUM][PRAM_AXI_AxQOS];         // Channel Quality of Service (QoS).
    sc_in<bool>      S_AXI_AWUSER[PRAM_MASTER_NUM][C_S_AXI_AWUSER_WIDTH];  // User-defined AW Channel signals.
    sc_in<bool>      S_AXI_AWVALID[PRAM_MASTER_NUM];                       // AXI Write address valid.
    sc_out<bool>     S_AXI_AWREADY[PRAM_MASTER_NUM];                     // AXI Write address ready.
    // AXI Write Data Channel Signals (W)
    sc_in<bool>      S_AXI_WID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];         // AXI3 Write ID.
    sc_in<bool>      S_AXI_WDATA[PRAM_MASTER_NUM][C_S_AXI_DATA_WIDTH];     // AXI Write data.
    sc_in<bool>      S_AXI_WSTRB[PRAM_MASTER_NUM][C_S_AXI_DATA_WIDTH / 8]; // AXI Write data strobes.
    sc_in<bool>      S_AXI_WLAST[PRAM_MASTER_NUM];                         // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_in<bool>      S_AXI_WUSER[PRAM_MASTER_NUM][C_S_AXI_WUSER_WIDTH];    // User-defined W Channel signals.
    sc_in<bool>      S_AXI_WVALID[PRAM_MASTER_NUM];                        // AXI Write data valid.
    sc_out<bool>     S_AXI_WREADY[PRAM_MASTER_NUM];                        // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_out<bool>     S_AXI_BID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];         // AXI Write response ID.
    sc_out<bool>     S_AXI_BRESP[PRAM_MASTER_NUM][PRAM_AXI_RRESP];         // AXI Write response code.
    sc_out<bool>     S_AXI_BUSER[PRAM_MASTER_NUM];                         // User-defined B channel signals.
    sc_out<bool>     S_AXI_BVALID[PRAM_MASTER_NUM];                        // AXI Write response valid.
    sc_in<bool>      S_AXI_BREADY[PRAM_MASTER_NUM];
    // AXI Read Address Channel Signals (AR)
    sc_in<bool>      S_AXI_ARID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];        // AXI address Read ID.
    sc_in<bool>      S_AXI_ARADDR[PRAM_MASTER_NUM][C_S_AXI_ADDR_WIDTH];    // AXI Read address.
    sc_in<bool>      S_AXI_ARLEN[PRAM_MASTER_NUM][PRAM_AXI_AxLEN];         // AXI address Read burst length.
    sc_in<bool>      S_AXI_ARSIZE[PRAM_MASTER_NUM][PRAM_AXI_AxSIZE];       // AXI address Read burst size.
    sc_in<bool>      S_AXI_ARBURST[PRAM_MASTER_NUM][PRAM_AXI_AxBURST];     // AXI address Read burst type.
    sc_in<bool>      S_AXI_ARCACHE[PRAM_MASTER_NUM][PRAM_AXI_AxCACHE];     // AXI Read address cache control signal.
    sc_in<bool>      S_AXI_ARPROT[PRAM_MASTER_NUM][PRAM_AXI_AxPROT];       // AXI Read address protection signal.
    sc_in<bool>      S_AXI_ARREGION[PRAM_MASTER_NUM][PRAM_AXI_AxREGION];   // Channel address region index.
    sc_in<bool>      S_AXI_ARQOS[PRAM_MASTER_NUM][PRAM_AXI_AxQOS];         // Channel Quality of Service.
    sc_in<bool>      S_AXI_ARUSER[PRAM_MASTER_NUM][C_S_AXI_ARUSER_WIDTH];  // User-defined AR Channel signals.
    sc_in<bool>      S_AXI_ARLOCK[PRAM_MASTER_NUM];                        // AXI Read address lock signal.
    sc_in<bool>      S_AXI_ARVALID[PRAM_MASTER_NUM];                       // AXI Read address valid.
    sc_out<bool>     S_AXI_ARREADY[PRAM_MASTER_NUM];                       // AXI Read address ready.               
    // AXI Read Data Channel Signals (R)
    sc_out<bool>     S_AXI_RID[PRAM_MASTER_NUM][C_S_AXI_ID_WIDTH];         // AXI Read data response ID.
    sc_out<bool>     S_AXI_RDATA[PRAM_MASTER_NUM][C_S_AXI_DATA_WIDTH];     // AXI Read data.
    sc_out<bool>     S_AXI_RRESP[PRAM_MASTER_NUM][PRAM_AXI_RRESP];         // AXI Read response code.
    sc_out<bool>     S_AXI_RLAST[PRAM_MASTER_NUM];                         // AXI Read data last signal.
    sc_out<bool>     S_AXI_RUSER[PRAM_MASTER_NUM][C_S_AXI_RUSER_WIDTH];    // User-defined R Channel signals.
    sc_out<bool>     S_AXI_RVALID[PRAM_MASTER_NUM];                        // AXI Read valid.
    sc_in<bool>      S_AXI_RREADY[PRAM_MASTER_NUM];                        // Read ready.
    // output signal
    //*****************************
    //********Master side signal***
    //*****************************
    // AXI Write Address Channel Signals (AW)
    sc_out<bool>      M_AXI_AWID[PRAM_SLAVE_NUM][C_S_AXI_ID_WIDTH];       // AXI address Write ID.
    sc_out<bool>      M_AXI_AWADDR[PRAM_SLAVE_NUM][C_S_AXI_ADDR_WIDTH];   // AXI Write address.
    sc_out<bool>      M_AXI_AWLEN[PRAM_SLAVE_NUM][PRAM_AXI_AxLEN];        // AXI address Write burst length.
    sc_out<bool>      M_AXI_AWSIZE[PRAM_SLAVE_NUM][PRAM_AXI_AxSIZE];      // AXI address Write burst size.
    sc_out<bool>      M_AXI_AWBURST[PRAM_SLAVE_NUM][PRAM_AXI_AxBURST];    // AXI address Write burst type.
    sc_out<bool>      M_AXI_AWLOCK[PRAM_SLAVE_NUM];                       // AXI Write address lock signal.
    sc_out<bool>      M_AXI_AWCACHE[PRAM_SLAVE_NUM][PRAM_AXI_AxCACHE];    // AXI Write address cache control signal.
    sc_out<bool>      M_AXI_AWPROT[PRAM_SLAVE_NUM][PRAM_AXI_AxPROT];      // AXI Write address protection signal.
    sc_out<bool>      M_AXI_AWREGION[PRAM_SLAVE_NUM][PRAM_AXI_AxREGION];  // Channel address region index
    sc_out<bool>      M_AXI_AWQOS[PRAM_SLAVE_NUM][PRAM_AXI_AxQOS];        // Channel Quality of Service (QoS).
    sc_out<bool>      M_AXI_AWUSER[PRAM_SLAVE_NUM][C_S_AXI_AWUSER_WIDTH]; // User-defined AW Channel signals.
    sc_out<bool>      M_AXI_AWVALID[PRAM_SLAVE_NUM];                      // AXI Write address valid.
    sc_in<bool>       M_AXI_AWREADY[PRAM_SLAVE_NUM];                      // AXI Write data ready.

    // AXI Write Data Channel Signals (W)
    sc_out<bool>      M_AXI_WID[PRAM_SLAVE_NUM][C_S_AXI_ID_WIDTH];        // AXI3 Write ID.
    sc_out<bool>      M_AXI_WDATA[PRAM_SLAVE_NUM][C_S_AXI_DATA_WIDTH];    // AXI Write data.
    sc_out<bool>      M_AXI_WSTRB[PRAM_SLAVE_NUM][C_S_AXI_DATA_WIDTH / 8];// AXI Write data strobes.
    sc_out<bool>      M_AXI_WLAST[PRAM_SLAVE_NUM];                        // AXI Write data last signal. Indicates the last transfer in a Writeburst.
    sc_out<bool>      M_AXI_WUSER[PRAM_SLAVE_NUM][C_S_AXI_WUSER_WIDTH];   // User-defined W Channel signals.
    sc_out<bool>      M_AXI_WVALID[PRAM_SLAVE_NUM];                       // AXI Write data valid.
    sc_in<bool>       M_AXI_WREADY[PRAM_SLAVE_NUM];                       // AXI Write data ready.
    // AXI Write Response Channel Signals (B)
    sc_in<bool>       M_AXI_BID[PRAM_SLAVE_NUM][C_S_AXI_ID_WIDTH];        // AXI Write response ID.
    sc_in<bool>       M_AXI_BRESP[PRAM_SLAVE_NUM][PRAM_AXI_RRESP];        // AXI Write response code.
    sc_in<bool>       M_AXI_BUSER[PRAM_SLAVE_NUM];                        // User-defined B channel signals.
    sc_in<bool>       M_AXI_BVALID[PRAM_SLAVE_NUM];                       // AXI Write response valid.
    sc_out<bool>      M_AXI_BREADY[PRAM_SLAVE_NUM];                       // Write response ready.
    // AXI Read Address Channel Signals (AR)
    sc_out<bool>      M_AXI_ARID[PRAM_SLAVE_NUM][C_S_AXI_ID_WIDTH];       // AXI address Read ID.
    sc_out<bool>      M_AXI_ARADDR[PRAM_SLAVE_NUM][C_S_AXI_ADDR_WIDTH];   // AXI Read address.
    sc_out<bool>      M_AXI_ARLEN[PRAM_SLAVE_NUM][PRAM_AXI_AxLEN];        // AXI address Read burst length.
    sc_out<bool>      M_AXI_ARSIZE[PRAM_SLAVE_NUM][PRAM_AXI_AxSIZE];      // AXI address Read burst size.
    sc_out<bool>      M_AXI_ARBURST[PRAM_SLAVE_NUM][PRAM_AXI_AxBURST];    // AXI address Read burst type.
    sc_out<bool>      M_AXI_ARLOCK[PRAM_SLAVE_NUM];                       // AXI Read address lock signal.
    sc_out<bool>      M_AXI_ARCACHE[PRAM_SLAVE_NUM][PRAM_AXI_AxCACHE];    // AXI Read address cache control signal.
    sc_out<bool>      M_AXI_ARPROT[PRAM_SLAVE_NUM][PRAM_AXI_AxPROT];      // AXI Read address protection signal.
    sc_out<bool>      M_AXI_ARREGION[PRAM_SLAVE_NUM][PRAM_AXI_AxREGION];  // Channel address region index.
    sc_out<bool>      M_AXI_ARQOS[PRAM_SLAVE_NUM][PRAM_AXI_AxQOS];        // Channel Quality of Service.
    sc_out<bool>      M_AXI_ARUSER[PRAM_SLAVE_NUM][C_S_AXI_ARUSER_WIDTH]; // User-defined AR Channel signals.
    sc_out<bool>      M_AXI_ARVALID[PRAM_SLAVE_NUM];                      // AXI Read address valid.
    sc_in<bool>       M_AXI_ARREADY[PRAM_SLAVE_NUM];                      // AXI Read address ready.
    // AXI Read Data channel Signals (R)
    sc_in<bool>       M_AXI_RID[PRAM_SLAVE_NUM][C_S_AXI_ID_WIDTH];        // AXI Read data response ID.
    sc_in<bool>       M_AXI_RDATA[PRAM_SLAVE_NUM][C_S_AXI_DATA_WIDTH];    // AXI Read data.
    sc_in<bool>       M_AXI_RRESP[PRAM_SLAVE_NUM][PRAM_AXI_RRESP];        // AXI Read response code.
    sc_in<bool>       M_AXI_RLAST[PRAM_SLAVE_NUM];                        // AXI Read data last signal.
    sc_in<bool>       M_AXI_RUSER[PRAM_SLAVE_NUM][C_S_AXI_RUSER_WIDTH];   // User-defined R Channel signals.
    sc_in<bool>       M_AXI_RVALID[PRAM_SLAVE_NUM];                       // AXI Read valid.
    sc_out<bool>      M_AXI_RREADY[PRAM_SLAVE_NUM];                       // AXI Read ready.
};

#endif //_X2X_H