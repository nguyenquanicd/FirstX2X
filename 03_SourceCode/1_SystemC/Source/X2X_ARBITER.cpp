/**
 * X2X ARBITER Implementation
 */

#include "X2X_ARBITER.h"

/**
 * X2X_ARBITER constructor
 */
X2X_ARBITER::X2X_ARBITER() {
    SC_HAS_PROCESS(X2X_ARBITER);
    // R channel
    for (unsigned int index = 0; index < C_S_AXI_ID_WIDTH; index++) {
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
    // internal variable
    for (unsigned int index=0; index< PRAM_MASTER_NUM; index++)
    {
        // Aw channel
        AwCounterValue[index] = PRAM_MASTER_NUM-1;
        isAwValid[index] = false;
        isAwSelector[index] = false;
        // Ar channel
        ArCounterValue[index] = PRAM_MASTER_NUM-1;
        isArValid[index] = false;
        isArSelector[index] = false;
        // W channel
        WCounterValue[index] = PRAM_MASTER_NUM - 1;
        isWValid[index] = false;
        isWSelector[index] = false;
    }
    // Aw
    isAwInprocess = false;
    AWPriorityValid = PRAM_MASTER_NUM-1;
    // Ar
    isArInprocess = false;
    ARPriorityValid = PRAM_MASTER_NUM-1;
    // W
    isWInprocess = false;
    WPriorityValid = PRAM_MASTER_NUM - 1;
    // AW Method 
    SC_METHOD(AWRoundRobinMethod)
    for(unsigned int index=0; index<PRAM_MASTER_NUM; index++){
        sensitive << S_AXI_AWVALID[index];
    }
    dont_initialize();

    SC_METHOD(AWHandShackSlaveMethod)
    sensitive << M_AXI_AWREADY;
    dont_initialize( );

    // AR Method 
    SC_METHOD(ARRoundRobinMethod)
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        sensitive << S_AXI_ARVALID[index];
    }
    dont_initialize( );

    SC_METHOD(ARHandShackSlaveMethod)
    sensitive << M_AXI_ARREADY;
    dont_initialize( );
    
    // W Method
    SC_METHOD(WRoundRobinMethod)
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        sensitive << S_AXI_WVALID[index];
    }
    dont_initialize( );

    SC_METHOD(WHandShackSlaveMethod)
    sensitive << M_AXI_WREADY;
    dont_initialize( );
    // Method core
    SC_METHOD(ArbiterCoreMethod)
    sensitive << ACLK.pos();
    sensitive << ARESETN.neg();
    dont_initialize( );
}
/**
 * X2X_ARBITER constructor
 */
X2X_ARBITER::~X2X_ARBITER() {

}

void X2X_ARBITER::AWRoundRobinMethod(){
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index ++) {
        if (S_AXI_AWVALID[index].posedge() && (!isAwValid[index])){
            AwCounterValue[index] -= AWPriorityValid;
            isAwValid[index] = true;
            -- AWPriorityValid;
        } else if (S_AXI_AWVALID[index].negedge( ) && (isAwValid[index])){
            AwCounterValue[index] = (PRAM_MASTER_NUM-1);
            isAwValid[index] = false;
            for (unsigned int dec = 0; dec < PRAM_MASTER_NUM; dec++) {
                if (dec != index && isAwValid[dec]){
                    AwCounterValue[index] =- 1;
                }
            }
        }   
    }
}

void X2X_ARBITER::AWHandShackSlaveMethod( ) {
    if (M_AXI_AWREADY.negedge()){
        for (unsigned int index =0; index < PRAM_MASTER_NUM; index++){
            if (S_AXI_AWVALID[index].read() == true && AwCounterValue[index] == 0 
                && isAwValid[index] && isAwSelector[index]){
                S_AXI_AWREADY[index].write(true); // need have a internal variable to store it, 
                isAwSelector[index] = false;
            }
        }
    } else {
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (S_AXI_AWVALID[index].read( ) == true && AwCounterValue[index] == 0
                && isAwValid[index] && isAwSelector[index] != true) {
                isAwSelector[index] = true;
            }
        }
    }
}

void X2X_ARBITER::ArbiterCoreMethod( ) {
    if(ARESETN.negedge()){
        // reset internal value
        // internal variable
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++)
        {
            // Aw channel
            AwCounterValue[index] = PRAM_MASTER_NUM - 1;
            isAwValid[index] = false;
            isAwSelector[index] = false;
            // Ar channel
            ArCounterValue[index] = PRAM_MASTER_NUM - 1;
            isArValid[index] = false;
            isArSelector[index] = false;
            // W channel
            WCounterValue[index] = PRAM_MASTER_NUM - 1;
            isWValid[index] = false;
            isWSelector[index] = false;
        }
        // Aw
        isAwInprocess = false;
        AWPriorityValid = PRAM_MASTER_NUM - 1;
        // Ar
        isArInprocess = false;
        ARPriorityValid = PRAM_MASTER_NUM - 1;
        // W
        isWInprocess = false;
        WPriorityValid = PRAM_MASTER_NUM - 1;
        // AW Method 
    } else {
        // AW varaiable
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++){
            if (isAwValid[index] && isAwInprocess!=true){
                M_AXI_AWVALID.write(isAwValid[index]);
                isAwInprocess = true;
            } else if (isAwSelector[index]){
                for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                    M_AXI_AWID[index_port].write(S_AXI_AWID[index][index_port]);
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
                    M_AXI_AWADDR[index_port].write(S_AXI_AWADDR[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
                    M_AXI_AWLEN[index_port].write(S_AXI_AWLEN[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
                    M_AXI_AWSIZE[index_port].write(S_AXI_AWSIZE[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
                    M_AXI_AWBURST[index_port].write(S_AXI_AWBURST[index][index_port].read( ));
                }
                M_AXI_AWLOCK.write(S_AXI_AWLOCK[index].read( ));
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
                    M_AXI_AWCACHE[index_port].write(S_AXI_AWCACHE[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
                    M_AXI_AWPROT[index_port].write(S_AXI_AWPROT[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
                    M_AXI_AWREGION[index_port].write(S_AXI_AWREGION[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
                    M_AXI_AWQOS[index_port].write(S_AXI_AWQOS[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
                    M_AXI_AWUSER[index_port].write(S_AXI_AWUSER[index][index_port].read( ));
                }
            }
        }
        // AR varaiable
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (isArValid[index] && isArInprocess != true) {
                M_AXI_ARVALID.write(isArValid[index]);
                isArInprocess = true;
            }
            else if (isArSelector[index]) {
                for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                    M_AXI_ARID[index_port].write(S_AXI_ARID[index][index_port]);
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
                    M_AXI_ARADDR[index_port].write(S_AXI_ARADDR[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
                    M_AXI_ARLEN[index_port].write(S_AXI_ARLEN[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
                    M_AXI_ARSIZE[index_port].write(S_AXI_ARSIZE[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
                    M_AXI_ARBURST[index_port].write(S_AXI_ARBURST[index][index_port].read( ));
                }
                M_AXI_ARLOCK.write(S_AXI_ARLOCK[index].read( ));
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
                    M_AXI_ARCACHE[index_port].write(S_AXI_ARCACHE[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
                    M_AXI_ARPROT[index_port].write(S_AXI_ARPROT[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
                    M_AXI_ARREGION[index_port].write(S_AXI_ARREGION[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
                    M_AXI_ARQOS[index_port].write(S_AXI_ARQOS[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_ARUSER_WIDTH; index_port++) {
                    M_AXI_ARUSER[index_port].write(S_AXI_ARUSER[index][index_port].read( ));
                }
            }
        }
        // W varaiable
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (isArValid[index] && isArInprocess != true) {
                M_AXI_WVALID.write(isArValid[index]);
                isArInprocess = true;
            }
            else if (isArSelector[index]) {
                for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                    M_AXI_WID[index_port].write(S_AXI_WID[index][index_port]);
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH; index_port++) {
                    M_AXI_WDATA[index_port].write(S_AXI_WDATA[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_DATA_WIDTH / 8; index_port++) {
                    M_AXI_WSTRB[index_port].write(S_AXI_WSTRB[index][index_port].read( ));
                }
                for (unsigned int index_port = 0; index_port < C_S_AXI_WUSER_WIDTH; index_port++) {
                    M_AXI_WUSER[index_port].write(S_AXI_WUSER[index][index_port].read( ));
                }
                M_AXI_WLAST.write(S_AXI_WLAST[index].read( ));
            }
        }
    }
}

void X2X_ARBITER::ARRoundRobinMethod( ) {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        if (S_AXI_ARVALID[index].posedge( ) && (!isArValid[index])) {
            ArCounterValue[index] -= ARPriorityValid;
            isArValid[index] = true;
            --ARPriorityValid;
        }
        else if (S_AXI_ARVALID[index].negedge( ) && (isArValid[index])) {
            ArCounterValue[index] = (PRAM_MASTER_NUM - 1);
            isArValid[index] = false;
            for (unsigned int dec = 0; dec < PRAM_MASTER_NUM; dec++) {
                if (dec != index && isArValid[dec]) {
                    ArCounterValue[index] = -1;
                }
            }
        }
    }
}

void X2X_ARBITER::ARHandShackSlaveMethod( ) {
    if (M_AXI_ARREADY.negedge( )) {
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (S_AXI_ARVALID[index].read( ) == true && ArCounterValue[index] == 0
                && isArValid[index] && isArSelector[index]) {
                S_AXI_ARREADY[index].write(true); // need have a internal variable to store it, 
                isArSelector[index] = false;
            }
        }
    }
    else {
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (S_AXI_ARVALID[index].read( ) == true && ArCounterValue[index] == 0
                && isArValid[index] && isArSelector[index] != true) {
                isArSelector[index] = true;
            }
        }
    }
}

void X2X_ARBITER::WRoundRobinMethod( ) {
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        if (S_AXI_WVALID[index].posedge( ) && (!isArValid[index])) {
            ArCounterValue[index] -= WPriorityValid;
            isArValid[index] = true;
            --WPriorityValid;
        }
        else if (S_AXI_WVALID[index].negedge( ) && (isArValid[index])) {
            ArCounterValue[index] = (PRAM_MASTER_NUM - 1);
            isArValid[index] = false;
            for (unsigned int dec = 0; dec < PRAM_MASTER_NUM; dec++) {
                if (dec != index && isArValid[dec]) {
                    ArCounterValue[index] = -1;
                }
            }
        }
    }
}

void X2X_ARBITER::WHandShackSlaveMethod( ) {
    if (M_AXI_WREADY.negedge( )) {
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (S_AXI_WVALID[index].read( ) == true && ArCounterValue[index] == 0
                && isArValid[index] && isArSelector[index]) {
                S_AXI_WREADY[index].write(true); // need have a internal variable to store it, 
                isArSelector[index] = false;
            }
        }
    }
    else {
        for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
            if (S_AXI_WVALID[index].read( ) == true && ArCounterValue[index] == 0
                && isArValid[index] && isArSelector[index] != true) {
                isArSelector[index] = true;
            }
        }
    }
}