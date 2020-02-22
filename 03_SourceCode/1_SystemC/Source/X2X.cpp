/**
 * X2X ip
 */

#include "X2X.h"

 /**
  * Constructor
  */
X2X::X2X( )
{
    // Process registration
    SC_HAS_PROCESS(X2X);
    // assigne masterID
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++){
        x2x_decoder[index].masterID = index;
    }
    // connection
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        ACLK(x2x_buffer[index].ACLK);
        ACLK(x2x_arbier[index].ACLK);
        ARESETN(x2x_buffer[index].ARESETN);
        ARESETN(x2x_arbier[index].ARESETN);
    }
    // x2x_buffer to input port
    // AW
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        for (unsigned int index_port =0; index_port < C_S_AXI_ID_WIDTH; index_port++){
            S_AXI_AWID[index][index_port](x2x_buffer[index].S_AXI_AWID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
            S_AXI_AWADDR[index][index_port](x2x_buffer[index].S_AXI_AWADDR[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
            S_AXI_AWLEN[index][index_port](x2x_buffer[index].S_AXI_AWLEN[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
            S_AXI_AWSIZE[index][index_port](x2x_buffer[index].S_AXI_AWSIZE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
            S_AXI_AWBURST[index][index_port](x2x_buffer[index].S_AXI_AWBURST[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
            S_AXI_AWCACHE[index][index_port](x2x_buffer[index].S_AXI_AWCACHE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
            S_AXI_AWPROT[index][index_port](x2x_buffer[index].S_AXI_AWPROT[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
            S_AXI_AWREGION[index][index_port](x2x_buffer[index].S_AXI_AWREGION[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
            S_AXI_AWQOS[index][index_port](x2x_buffer[index].S_AXI_AWQOS[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
            S_AXI_AWUSER[index][index_port](x2x_buffer[index].S_AXI_AWUSER[index_port]);
        }
        S_AXI_AWLOCK[index](x2x_buffer[index].S_AXI_AWLOCK);
        S_AXI_AWVALID[index](x2x_buffer[index].S_AXI_AWVALID);
        S_AXI_AWREADY[index](x2x_buffer[index].S_AXI_AWREADY);
    }
    // x2x_buffer to x2x_decoder
    // AW
    for (unsigned int index = 0; index < PRAM_MASTER_NUM; index++) {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
            x2x_decoder[index].S_AXI_AWID[index_port](x2x_buffer[index].M_AXI_AWID[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
            x2x_decoder[index].S_AXI_AWADDR[index_port](x2x_buffer[index].M_AXI_AWADDR[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
            x2x_decoder[index].S_AXI_AWLEN[index_port](x2x_buffer[index].M_AXI_AWLEN[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
            x2x_decoder[index].S_AXI_AWSIZE[index_port](x2x_buffer[index].M_AXI_AWSIZE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
            x2x_decoder[index].S_AXI_AWBURST[index_port](x2x_buffer[index].M_AXI_AWBURST[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
            x2x_decoder[index].S_AXI_AWCACHE[index_port](x2x_buffer[index].M_AXI_AWCACHE[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
            x2x_decoder[index].S_AXI_AWPROT[index_port](x2x_buffer[index].M_AXI_AWPROT[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
            x2x_decoder[index].S_AXI_AWREGION[index_port](x2x_buffer[index].M_AXI_AWREGION[index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
            x2x_decoder[index].S_AXI_AWQOS[index_port](x2x_buffer[index].M_AXI_AWQOS[index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
            x2x_decoder[index].S_AXI_AWUSER[index_port](x2x_buffer[index].M_AXI_AWUSER[index_port]);
        }
        x2x_decoder[index].S_AXI_AWLOCK(x2x_buffer[index].M_AXI_AWLOCK);
        x2x_decoder[index].S_AXI_AWVALID(x2x_buffer[index].M_AXI_AWVALID);
        x2x_buffer[index].AwPop(x2x_decoder[index].S_AXI_AWPOPOUT);
    }
    // x2x_decoder to x2x_arbiter
    for (unsigned int index_slave=0;index_slave<PRAM_SLAVE_NUM; index_slave++){
        for (unsigned int index_master=0;index_master<PRAM_MASTER_NUM;index_master++){
            for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWID[index_master][index_port](x2x_decoder[index_master].M_AXI_AWID[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWADDR[index_master][index_port](x2x_decoder[index_master].M_AXI_AWADDR[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWLEN[index_master][index_port](x2x_decoder[index_master].M_AXI_AWLEN[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWSIZE[index_master][index_port](x2x_decoder[index_master].M_AXI_AWSIZE[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWBURST[index_master][index_port](x2x_decoder[index_master].M_AXI_AWBURST[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWCACHE[index_master][index_port](x2x_decoder[index_master].M_AXI_AWCACHE[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWPROT[index_master][index_port](x2x_decoder[index_master].M_AXI_AWPROT[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWREGION[index_master][index_port](x2x_decoder[index_master].M_AXI_AWREGION[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWQOS[index_master][index_port](x2x_decoder[index_master].M_AXI_AWQOS[index_slave][index_port]);
            }
            for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
                x2x_arbier[index_slave].S_AXI_AWUSER[index_master][index_port](x2x_decoder[index_master].M_AXI_AWUSER[index_slave][index_port]);
            }
            x2x_arbier[index_slave].S_AXI_AWLOCK[index_master](x2x_decoder[index_master].M_AXI_AWLOCK[index_slave]);
            x2x_arbier[index_slave].S_AXI_AWVALID[index_master](x2x_decoder[index_master].M_AXI_AWVALID[index_slave]);
            x2x_decoder[index_slave].M_AXI_AWREADY[index_master](x2x_arbier[index_slave].S_AXI_AWREADY[index_master]);
        }
    }
    // x2x_arbiter to output port
    for (unsigned int index = 0; index < PRAM_SLAVE_NUM; index++) {
        for (unsigned int index_port = 0; index_port < C_S_AXI_ID_WIDTH; index_port++) {
            x2x_arbier[index].M_AXI_AWID[index_port](M_AXI_AWID[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_ADDR_WIDTH; index_port++) {
            x2x_arbier[index].M_AXI_AWADDR[index_port](M_AXI_AWADDR[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxLEN; index_port++) {
            x2x_arbier[index].M_AXI_AWLEN[index_port](M_AXI_AWLEN[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxSIZE; index_port++) {
            x2x_arbier[index].M_AXI_AWSIZE[index_port](M_AXI_AWSIZE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxBURST; index_port++) {
            x2x_arbier[index].M_AXI_AWBURST[index_port](M_AXI_AWBURST[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxCACHE; index_port++) {
            x2x_arbier[index].M_AXI_AWCACHE[index_port](M_AXI_AWCACHE[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxPROT; index_port++) {
            x2x_arbier[index].M_AXI_AWPROT[index_port](M_AXI_AWPROT[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxREGION; index_port++) {
            x2x_arbier[index].M_AXI_AWREGION[index_port](M_AXI_AWREGION[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < PRAM_AXI_AxQOS; index_port++) {
            x2x_arbier[index].M_AXI_AWQOS[index_port](M_AXI_AWQOS[index][index_port]);
        }
        for (unsigned int index_port = 0; index_port < C_S_AXI_AWUSER_WIDTH; index_port++) {
            x2x_arbier[index].M_AXI_AWUSER[index_port](M_AXI_AWUSER[index][index_port]);
        }
        x2x_arbier[index].M_AXI_AWLOCK(M_AXI_AWLOCK[index]);
        x2x_arbier[index].M_AXI_AWVALID(M_AXI_AWVALID[index]);
        x2x_arbier[index].M_AXI_AWREADY(M_AXI_AWREADY[index]);
    }
}   

/**
 * Desctructor
 */
X2X::~X2X() {
}
