/**
 * X2X Decoder Implementation
 */

#include "X2X_DECODER.h"

/**
 * X2X_DECODER constructor
 */
X2X_DECODER::X2X_DECODER() {
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++){
        isAWAddressMatch[index] = false;
        isARAddressMatch[index] = false;
        start_Address[index] = 0x0;
        end_Address[index] = 0x0;
    }
    m_AXI_ARADDR = 0x0;
    m_AXI_AWADDR = 0x0;
    // Process registration
    SC_HAS_PROCESS(X2X_DECODER);
    SC_METHOD(InsertAWMasterIDMethod)
        for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++){
            sensitive << S_AXI_AWID[index];
        }
        dont_initialize( );
    SC_METHOD(InsertARMasterIDMethod)
        for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH;index++){
            sensitive << S_AXI_ARID[index];
        }
        dont_initialize( );
    SC_METHOD(InsertWMasterIDMethod)
        for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH;index++){
            sensitive << S_AXI_WID[index];
        }
        dont_initialize( );
    SC_METHOD(BChannelHandlerMethod)
        sensitive << M_AXI_BVALID;
        dont_initialize( );
    SC_METHOD(RChannelHandlerMethod)
        sensitive << M_AXI_RVALID;
        dont_initialize( );
    SC_METHOD(AwPopOutMethod)
        sensitive << S_AXI_AWVALID;
        for(unsigned int index = 0 ; index < PRAM_SLAVE_NUM ; index++)
        {
            sensitive << M_AXI_AWREADY[index];
        }
        dont_initialize( );
    SC_METHOD(WPopOutMethod)
        sensitive << S_AXI_WVALID;
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
        {
            sensitive << M_AXI_WREADY[index];
        }
        dont_initialize( );
    SC_METHOD(ArPopOutMethod)
        sensitive << S_AXI_ARVALID;
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++)
        {
            sensitive << M_AXI_ARREADY[index];
        }
        dont_initialize( );
        // blind port
    S_AXI_BREADY(M_AXI_BREADY);
    S_AXI_RREADY(M_AXI_RREADY);
    SC_METHOD(AWSelectorMethod)
        for (unsigned int index = 0; index< C_S_AXI_ID_WIDTH; index++){
            sensitive << S_AXI_AWID[index];
        }
        for (unsigned int index = 0; index < C_S_AXI_ADDR_WIDTH; index++) {
            sensitive << S_AXI_AWADDR[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxLEN; index++) {
            sensitive << S_AXI_AWLEN[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxSIZE; index++) {
            sensitive << S_AXI_AWSIZE[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxBURST; index++) {
            sensitive << S_AXI_AWBURST[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxCACHE; index++) {
            sensitive << S_AXI_AWCACHE[index];
        }
        sensitive << S_AXI_AWLOCK;                      
        for (unsigned int index = 0; index < PRAM_AXI_AxPROT; index++) {
            sensitive << S_AXI_AWPROT[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxREGION; index++) {
            sensitive << S_AXI_AWREGION[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxQOS; index++) {
            sensitive << S_AXI_AWQOS[index];
        }
        for (unsigned int index = 0; index < C_S_AXI_AWUSER_WIDTH; index++) {
            sensitive << S_AXI_AWUSER[index];
        }
        sensitive << S_AXI_AWVALID;                     
        dont_initialize();
    SC_METHOD(WSelectorMethod)
        for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++) {
            sensitive << S_AXI_WID[index];
        }
        for (unsigned int index = 0; index < C_S_AXI_DATA_WIDTH; index++) {
            sensitive << S_AXI_WDATA[index];
        }
        for (unsigned int index = 0; index < C_S_AXI_DATA_WIDTH/8; index++) {
            sensitive << S_AXI_WSTRB[index];
        }
        sensitive << S_AXI_WLAST;
        for (unsigned int index = 0; index < C_S_AXI_WUSER_WIDTH; index++) {
            sensitive << S_AXI_WUSER[index];
        }
        sensitive << S_AXI_WVALID;
        dont_initialize();
    SC_METHOD(ARSelectorMethod)
        for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++) {
            sensitive << S_AXI_ARID[index];
        }
        for (unsigned int index = 0; index < C_S_AXI_ADDR_WIDTH; index++) {
            sensitive << S_AXI_ARADDR[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxLEN; index++) {
            sensitive << S_AXI_ARLEN[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxSIZE; index++) {
            sensitive << S_AXI_ARSIZE[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxBURST; index++) {
            sensitive << S_AXI_ARBURST[index];
        }
        sensitive << S_AXI_ARLOCK;
        for (unsigned int index = 0; index < PRAM_AXI_AxCACHE; index++) {
            sensitive << S_AXI_ARCACHE[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxPROT; index++) {
            sensitive << S_AXI_ARPROT[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxREGION; index++) {
            sensitive << S_AXI_ARREGION[index];
        }
        for (unsigned int index = 0; index < PRAM_AXI_AxQOS; index++) {
            sensitive << S_AXI_ARQOS[index];
        }
        for (unsigned int index = 0; index < C_S_AXI_ARUSER_WIDTH; index++) {
            sensitive << S_AXI_ARUSER[index];
        }
        sensitive << S_AXI_ARVALID;
        dont_initialize();
}
/**
 * X2X_DECODER constructor
 */
X2X_DECODER::~X2X_DECODER() {

}
/**
 * InsertAWMasterIDMethod
 */
void X2X_DECODER::InsertAWMasterIDMethod() {
    for (unsigned int index = C_S_AXI_ID_WIDTH - PRAM_BIT_INSERTID; index  < C_S_AXI_ID_WIDTH; index++){
        m_AXI_AWID[index] |= (masterID >> (index - (C_S_AXI_ID_WIDTH - PRAM_BIT_INSERTID)))&0x1;
    }
}
/**
 * InsertWMasterIDMethod
 */
void X2X_DECODER::InsertWMasterIDMethod( ) {
    for (unsigned int index = C_S_AXI_ID_WIDTH - (PRAM_BIT_INSERTID + 1); index < C_S_AXI_ID_WIDTH; index++) {
        m_AXI_WID[index] |= (masterID >> (index - (C_S_AXI_ID_WIDTH - PRAM_BIT_INSERTID))) & 0x1;
    }
}
/**
 * InsertARMasterIDMethod
 */
void X2X_DECODER::InsertARMasterIDMethod( ) {
    for (unsigned int index = C_S_AXI_ID_WIDTH - (PRAM_BIT_INSERTID + 1); index < C_S_AXI_ID_WIDTH; index++) {
        m_AXI_ARID[index] |= (masterID >> (index - (C_S_AXI_ID_WIDTH - PRAM_BIT_INSERTID))) & 0x1;
    }
}
/**
 * JudgmentARAddressMethod
 */
void X2X_DECODER::JudgmentARAddressMethod() {
    m_AXI_ARADDR = 0x0;
    // get address
    for (unsigned int index = 0; index < C_S_AXI_ADDR_WIDTH; index++){
        m_AXI_ARADDR |= S_AXI_ARADDR[index].read( )<< index;
    }
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index ++){
        if (start_Address[index] <= m_AXI_ARADDR 
            && m_AXI_ARADDR <= end_Address[index]){
            isARAddressMatch[index] = true;
        } else {
            isARAddressMatch[index] = false;
        }
    }
}
/**
 * JudgmentAWAddressMethod
 */
void X2X_DECODER::JudgmentAWAddressMethod( ) {
    m_AXI_AWADDR = 0x0;
    // get address
    for (unsigned int index = 0; index < C_S_AXI_ADDR_WIDTH; index++) {
        m_AXI_AWADDR |= S_AXI_ARADDR[index].read( ) << index;
    }
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
        if (start_Address[index] <= m_AXI_AWADDR
            && m_AXI_AWADDR <= end_Address[index]) {
            isAWAddressMatch[index] = true;
        }
        else {
            isAWAddressMatch[index] = false;
        }
    }
}
/**
 * BChannelHandlerMethod
 */
void X2X_DECODER::BChannelHandlerMethod() {
    bool isMasterID = false;
    if (M_AXI_BVALID.read() != false){
        for (unsigned int index = C_S_AXI_ID_WIDTH - (PRAM_BIT_INSERTID + 1); index < C_S_AXI_ID_WIDTH; index++) {
            isMasterID |= ((masterID >> (index - (C_S_AXI_ID_WIDTH - PRAM_BIT_INSERTID))) & 0x1) ^ M_AXI_BID[index]->read();
        }
        if (isMasterID != true){    
            for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index ++)
            {
                S_AXI_BID[index].write(M_AXI_BID[index].read());        // AXI Read data response ID
            }
            for (unsigned int index = 0; index < PRAM_AXI_RRESP; index++)
            {
                S_AXI_BRESP[index].write(M_AXI_BRESP[index]->read());        // AXI Read response code.
            }
            S_AXI_BUSER.write(M_AXI_BUSER->read());   // User-defined R Channel signals.
            S_AXI_RLAST.write(M_AXI_RLAST->read( ));                            // AXI Read data last signal.
            S_AXI_BVALID.write(M_AXI_BVALID.read( ));
        }
    } else {
        S_AXI_BVALID.write(M_AXI_BVALID.read( ));
        // not thing
    }
}
/**
 * RChannelHandlerMethod
 */
void X2X_DECODER::RChannelHandlerMethod( ) {
    bool isMasterID = false;
    if (M_AXI_RVALID.read( ) != false) {
        for (unsigned int index = C_S_AXI_ID_WIDTH - (PRAM_BIT_INSERTID + 1); index < C_S_AXI_ID_WIDTH; index++) {
            isMasterID |= ((masterID >> (index - (C_S_AXI_ID_WIDTH - PRAM_BIT_INSERTID))) & 0x1) ^ M_AXI_RID[index]->read( );
        }
        if (isMasterID != true) {
            for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++)
            {
                S_AXI_RID[index].write(M_AXI_RID[index].read( ));        // AXI Read data response ID
            }
            for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++)
            {
                S_AXI_RDATA[index].write(M_AXI_RDATA->read( ));    // AXI Read data.
            }
            for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++)
            {
                S_AXI_RRESP[index].write(M_AXI_RRESP->read( ));        // AXI Read response code.
            }
            for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++)
            {
                S_AXI_RUSER[index].write(M_AXI_RUSER->read( ));   // User-defined R Channel signals.
            }
            S_AXI_RLAST.write(M_AXI_RLAST->read( ));                            // AXI Read data last signal.
            S_AXI_RVALID.write(M_AXI_RVALID.read( ));
        }
    }
    else {
        S_AXI_RVALID.write(M_AXI_RVALID.read( ));
    }
}
/**
 * AwPopOutMethod
 */
void X2X_DECODER::AwPopOutMethod( ) {
    bool mAwPopOut = false;
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++){
        bool mValid = (M_AXI_AWREADY[index].read() & isAWAddressMatch[index] & S_AXI_AWVALID.read());
        mAwPopOut |= mValid;
    }
    S_AXI_AWPOPOUT.write(mAwPopOut);
}
/**
 * WPopOutMethod
 */
void X2X_DECODER::WPopOutMethod( ) {
    bool mWPopOut = false;
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
        bool mValid = (M_AXI_WREADY[index].read( ) & S_AXI_WVALID.read( ));
        mWPopOut |= mValid;
    }
    S_AXI_WPOPOUT.write(mWPopOut);
}
/**
 * ArPopOutMethod
 */
void X2X_DECODER::ArPopOutMethod( ) {
    bool mArPopOut = false;
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
        bool mValid = (M_AXI_ARREADY[index].read( ) & isARAddressMatch[index] & S_AXI_ARVALID.read( ));
        mArPopOut |= mValid;
    }
    S_AXI_ARPOPOUT.write(mArPopOut);
}
/**
 * AWSelectorMethod
 */
void X2X_DECODER::AWSelectorMethod( ) {
    if (S_AXI_AWVALID.read() != false) { // valid
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
            if (isAWAddressMatch[index]) { // correct address
                for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                    M_AXI_AWID[index][index_port].write(m_AXI_AWID[index_port]);
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
                    M_AXI_AWADDR[index][index_port].write(S_AXI_AWADDR[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
                    M_AXI_AWLEN[index][index_port].write(S_AXI_AWLEN[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
                    M_AXI_AWSIZE[index][index_port].write(S_AXI_AWSIZE[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
                    M_AXI_AWBURST[index][index_port].write(S_AXI_AWBURST[index_port].read( ));
                }
                    M_AXI_AWLOCK[index].write(S_AXI_AWLOCK.read( ));
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
                    M_AXI_AWCACHE[index][index_port].write(S_AXI_AWCACHE[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
                    M_AXI_AWPROT[index][index_port].write(S_AXI_AWPROT[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
                    M_AXI_AWREGION[index][index_port].write(S_AXI_AWREGION[index_port].read());
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
                    M_AXI_AWQOS[index][index_port].write(S_AXI_AWQOS[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
                    M_AXI_AWUSER[index][index_port].write(S_AXI_AWUSER[index_port].read( ));
                }
                M_AXI_AWVALID[index].write(S_AXI_AWVALID.read());
            } else {
                M_AXI_AWVALID[index].write(0x0);
            }
        }        
    } else { // not valid
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
            M_AXI_AWVALID[index].write(0x0);
        }
    }
}
/**
 * WSelectorMethod
 */
void X2X_DECODER::WSelectorMethod( ) {
    if (S_AXI_WVALID.read( ) != false) { // valid
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
            if (isAWAddressMatch[index]) { // correct address
                for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                    M_AXI_WID[index][index_port].write(S_AXI_WID[index_port].read());
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++) {
                    M_AXI_WDATA[index][index_port].write(S_AXI_WDATA[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++) {
                    M_AXI_WSTRB[index][index_port].write(S_AXI_WSTRB[index_port].read( ));
                }
                M_AXI_WLAST[index].write(S_AXI_WLAST.read());
                for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++) {
                    M_AXI_WUSER[index][index_port].write(S_AXI_WUSER[index_port].read( ));
                }
                M_AXI_WVALID[index].write(S_AXI_WVALID.read());
            } else {
                M_AXI_WVALID[index].write(0x0);
            }
        }
    }
    else { // not valid
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
            M_AXI_WVALID[index].write(0x0);
        }
    }
}
/**
 * ARSelectorMethod
 */
void X2X_DECODER::ARSelectorMethod( ) {
    if (S_AXI_ARVALID.read( ) != false) { // valid
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
            if (isARAddressMatch[index]) { // correct address
                for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                    M_AXI_ARID[index][index_port].write(m_AXI_ARID[index_port]);
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
                    M_AXI_ARADDR[index][index_port].write(S_AXI_ARADDR[index_port].read());
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
                    M_AXI_ARLEN[index][index_port].write(S_AXI_ARLEN[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
                    M_AXI_ARSIZE[index][index_port].write(S_AXI_ARSIZE[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
                    M_AXI_ARBURST[index][index_port].write(S_AXI_ARBURST[index_port].read( ));
                }
                M_AXI_ARLOCK[index].write(S_AXI_ARLOCK.read( ));
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
                    M_AXI_ARCACHE[index][index_port].write(S_AXI_ARCACHE[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
                    M_AXI_ARPROT[index][index_port].write(S_AXI_ARPROT[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
                    M_AXI_ARREGION[index][index_port].write(S_AXI_ARREGION[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
                    M_AXI_ARQOS[index][index_port].write(S_AXI_ARQOS[index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_ARUSER_WIDTH; index_port++) {
                    M_AXI_ARUSER[index][index_port].write(S_AXI_ARUSER[index_port].read( ));
                }
                M_AXI_ARVALID[index].write(S_AXI_ARVALID.read( ));
            } else {
                for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
                    M_AXI_ARVALID[index].write(0x0);
                }
            }
        }
    }
    else { // not valid
        for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
            M_AXI_ARVALID[index].write(0x0);
        }
    }
}