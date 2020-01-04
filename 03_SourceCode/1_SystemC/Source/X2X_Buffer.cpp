/**
 * X2X_BUFFER ip
 */

#include "X2X_BUFFER.h"

 /**
  * Constructor
  */
X2X_BUFFER::X2X_BUFFER( )
{
    // Process registration
    SC_HAS_PROCESS(X2X_BUFFER);
    mFIFO_AW_DIWTH = C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN
        + PRAM_AXI_AxSIZE
        + PRAM_AXI_AxBURST
        + PRAM_AXI_AxCACHE
        + PRAM_AXI_AxPROT
        + PRAM_AXI_AxREGION
        + PRAM_AXI_AxQOS
        + C_S_AXI_AWUSER_WIDTH
        + 1;
    mFIFO_W_DIWTH = C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + C_S_AXI_DATA_WIDTH
        + C_S_AXI_WUSER_WIDTH
        + 1;
    mFIFO_AR_DIWTH = C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN
        + PRAM_AXI_AxSIZE
        + PRAM_AXI_AxBURST
        + PRAM_AXI_AxCACHE
        + PRAM_AXI_AxPROT
        + PRAM_AXI_AxREGION
        + PRAM_AXI_AxQOS
        + C_S_AXI_ARUSER_WIDTH
        + 1;

    SC_METHOD(mFIFOAWPush_Method)
        sensitive<< S_AXI_AWVALID;
        sensitive<< mFIFO_AW.Full;
        dont_initialize( );
    SC_METHOD(mFIFOWPush_Method)
        sensitive << S_AXI_WVALID;
        sensitive << mFIFO_W.Full;
        dont_initialize( );
    SC_METHOD(mFIFOARPush_Method)
        sensitive << S_AXI_ARVALID;
        sensitive << mFIFO_AR.Full;
        dont_initialize( );

    // connect clock and reset
    mFIFO_W.Clock(ACLK);
    mFIFO_AW.Clock(ACLK);
    mFIFO_AR.Clock(ACLK);
    mFIFO_W.Reset(ARESETN);
    mFIFO_AW.Reset(ARESETN);
    mFIFO_AR.Reset(ARESETN);
    mFIFO_W.Pop(WPop);
    mFIFO_AW.Pop(AwPop);
    mFIFO_AR.Pop(ArPop);
    AwFull(mFIFO_W.Full);
    WFull(mFIFO_AW.Full);
    ARFull(mFIFO_AR.Full);
    // R channel
    for (unsigned int index =0; index < C_S_AXI_ID_WIDTH; index++){
        M_AXI_RID[index](S_AXI_RID[index]);
    }
    for (unsigned int index = 0; index < C_S_AXI_DATA_WIDTH; index++) {
        M_AXI_RDATA[index](S_AXI_RDATA[index]);
    }
    for (unsigned int index = 0; index < PRAM_AXI_RRESP; index++) {
        M_AXI_RRESP[index](S_AXI_RRESP[index]);
    }
    for (unsigned int index = 0; index < C_S_AXI_RUSER_WIDTH; index++) {
        M_AXI_RUSER[index](S_AXI_RUSER[index]);
    }
    M_AXI_RLAST(S_AXI_RLAST);
    M_AXI_RVALID(S_AXI_RVALID);
    S_AXI_RREADY(M_AXI_RREADY);
    // B channel
    for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++) {
        M_AXI_BID[index](S_AXI_BID[index]);
    }
    for (unsigned int index = 0; index < PRAM_AXI_RRESP; index++) {
        M_AXI_BRESP[index](S_AXI_BRESP[index]);
    }
    M_AXI_BUSER(S_AXI_BUSER);
    M_AXI_BVALID(S_AXI_BVALID);
    S_AXI_BREADY(M_AXI_BREADY);

    // AW channel
    for (unsigned int index = 0; index < mFIFO_AW_DIWTH; index++){
        if (index < C_S_AXI_ID_WIDTH){
            mFIFO_AW.In[index](S_AXI_AWID[index]);
        }
        else if (C_S_AXI_ID_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH){
            mFIFO_AW.In[index](S_AXI_AWADDR[index]);
        } 
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN) {
            mFIFO_AW.In[index](S_AXI_AWLEN[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE) {
            mFIFO_AW.In[index](S_AXI_AWSIZE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST) {
            mFIFO_AW.In[index](S_AXI_AWBURST[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE) {
            mFIFO_AW.In[index](S_AXI_AWCACHE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT) {
            mFIFO_AW.In[index](S_AXI_AWPROT[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION) {
            mFIFO_AW.In[index](S_AXI_AWREGION[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS) {
            mFIFO_AW.In[index](S_AXI_AWQOS[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_AWUSER_WIDTH) {
            mFIFO_AW.In[index](S_AXI_AWUSER[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_AWUSER_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_AWUSER_WIDTH + 1) {
            mFIFO_AW.In[index](S_AXI_AWLOCK);
        }
    }

    for (unsigned int index = 0; index < mFIFO_AW_DIWTH; index++) {
        if (index < C_S_AXI_ID_WIDTH) {
            mFIFO_AW.Out[index](M_AXI_AWID[index]);
        }
        else if (C_S_AXI_ID_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH) {
            mFIFO_AW.Out[index](M_AXI_AWADDR[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN) {
            mFIFO_AW.Out[index](M_AXI_AWLEN[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE) {
            mFIFO_AW.Out[index](M_AXI_AWSIZE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST) {
            mFIFO_AW.Out[index](M_AXI_AWBURST[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE) {
            mFIFO_AW.Out[index](M_AXI_AWCACHE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT) {
            mFIFO_AW.Out[index](M_AXI_AWPROT[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION) {
            mFIFO_AW.Out[index](M_AXI_AWREGION[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS) {
            mFIFO_AW.Out[index](M_AXI_AWQOS[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_AWUSER_WIDTH) {
            mFIFO_AW.Out[index](M_AXI_AWUSER[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_AWUSER_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_AWUSER_WIDTH + 1) {
            mFIFO_AW.Out[index](M_AXI_AWLOCK);
        }
    }
    // W channel
    for (unsigned int index = 0; index < mFIFO_AW_DIWTH; index++) {
        if (index <  C_S_AXI_ID_WIDTH){
            mFIFO_W.In[index](S_AXI_WID[index]);
        }
        else if (C_S_AXI_ID_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH){
            mFIFO_W.In[index](S_AXI_WDATA[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8)) {
            mFIFO_W.In[index](S_AXI_WSTRB[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) + C_S_AXI_WUSER_WIDTH) {
            mFIFO_W.In[index](S_AXI_WUSER[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) + C_S_AXI_WUSER_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) + C_S_AXI_WUSER_WIDTH + 1) {
            mFIFO_W.In[index](S_AXI_WLAST);
        }
    }

    for (unsigned int index = 0; index < mFIFO_AW_DIWTH; index++) {
        if (index < C_S_AXI_ID_WIDTH) {
            mFIFO_W.Out[index](M_AXI_WID[index]);
        }
        else if (C_S_AXI_ID_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH) {
            mFIFO_W.Out[index](M_AXI_WDATA[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8)) {
            mFIFO_W.Out[index](M_AXI_WSTRB[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) + C_S_AXI_WUSER_WIDTH) {
            mFIFO_W.Out[index](M_AXI_WUSER[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) + C_S_AXI_WUSER_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_DATA_WIDTH + (C_S_AXI_DATA_WIDTH / 8) + C_S_AXI_WUSER_WIDTH + 1) {
            mFIFO_W.Out[index](M_AXI_WLAST);
        }
    }

    // AR
    for (unsigned int index = 0; index < mFIFO_AW_DIWTH; index++) {
        if (index < C_S_AXI_ID_WIDTH) {
            mFIFO_AR.In[index](S_AXI_ARID[index]);
        }
        else if (C_S_AXI_ID_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH) {
            mFIFO_AR.In[index](S_AXI_ARADDR[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN) {
            mFIFO_AR.In[index](S_AXI_ARLEN[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE) {
            mFIFO_AR.In[index](S_AXI_ARSIZE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST) {
            mFIFO_AR.In[index](S_AXI_ARBURST[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE) {
            mFIFO_AR.In[index](S_AXI_ARCACHE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT) {
            mFIFO_AR.In[index](S_AXI_ARPROT[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION) {
            mFIFO_AR.In[index](S_AXI_ARREGION[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS) {
            mFIFO_AR.In[index](S_AXI_ARQOS[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_ARUSER_WIDTH) {
            mFIFO_AR.In[index](S_AXI_ARUSER[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_ARUSER_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_ARUSER_WIDTH + 1) {
            mFIFO_AR.In[index](S_AXI_ARLOCK);
        }
    }
    for (unsigned int index = 0; index < mFIFO_AW_DIWTH; index++) {
        if (index < C_S_AXI_ID_WIDTH) {
            mFIFO_AR.Out[index](M_AXI_ARID[index]);
        }
        else if (C_S_AXI_ID_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH) {
            mFIFO_AR.Out[index](M_AXI_ARADDR[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN) {
            mFIFO_AR.Out[index](M_AXI_ARLEN[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE) {
            mFIFO_AR.Out[index](M_AXI_ARSIZE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST) {
            mFIFO_AR.Out[index](M_AXI_ARBURST[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE) {
            mFIFO_AR.Out[index](M_AXI_ARCACHE[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT) {
            mFIFO_AR.Out[index](M_AXI_ARPROT[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION) {
            mFIFO_AR.Out[index](M_AXI_ARREGION[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS) {
            mFIFO_AR.Out[index](M_AXI_ARQOS[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_ARUSER_WIDTH) {
            mFIFO_AR.Out[index](M_AXI_ARUSER[index]);
        }
        else if (C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_ARUSER_WIDTH <= index && index < C_S_AXI_ID_WIDTH + C_S_AXI_ADDR_WIDTH + PRAM_AXI_AxLEN + PRAM_AXI_AxSIZE + PRAM_AXI_AxBURST + PRAM_AXI_AxCACHE + PRAM_AXI_AxPROT + PRAM_AXI_AxREGION + PRAM_AXI_AxQOS + C_S_AXI_ARUSER_WIDTH + 1) {
            mFIFO_AR.Out[index](M_AXI_ARLOCK);
        }
    }
}   

/**
 * Desctructor
 */
X2X_BUFFER::~X2X_BUFFER() {
}
/**
 * mFIFOAWPush_Method
 */
void X2X_BUFFER::mFIFOAWPush_Method( ){
    mFIFO_AW_Push_Signal.write((!mFIFO_AW.Full.read()) & S_AXI_AWVALID.read());
    mFIFO_AW.Push(mFIFO_AW_Push_Signal);
    S_AXI_AWREADY.write(!mFIFO_AW.Full.read());
}
/**
 * mFIFOWPush_Method
 */
void X2X_BUFFER::mFIFOWPush_Method( ){
    mFIFO_W_Push_Signal.write((!mFIFO_W.Full.read( )) & S_AXI_WVALID.read( ));
    mFIFO_W.Push(mFIFO_W_Push_Signal);
    S_AXI_WREADY.write(!mFIFO_W.Full.read( ));
}
/**
 * mFIFOARPush_Method
 */
void X2X_BUFFER::mFIFOARPush_Method( ){
    mFIFO_AR_Push_Signal.write((!mFIFO_AR.Full.read( )) & S_AXI_ARVALID.read( ));
    mFIFO_AR.Push(mFIFO_AR_Push_Signal);
    S_AXI_ARREADY.write(!mFIFO_AR.Full.read( ));
}