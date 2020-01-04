#ifndef _AXI_INTERCONNECTION_H
#define _AXI_INTERCONNECTION_H

#define C_S_AXI_ID_WIDTH 8
#define C_S_AXI_ADDR_WIDTH 40
#define C_S_AXI_AWUSER_WIDTH 10
#define C_S_AXI_WUSER_WIDTH 10
#define C_S_AXI_ARUSER_WIDTH 10
#define C_S_AXI_RUSER_WIDTH 10
// default bus_width
#define C_S_AXI_DATA_WIDTH 32

//define parameter width
#define PRAM_AXI_AxLEN 8
#define PRAM_AXI_AxSIZE  3
#define PRAM_AXI_AxBURST  2
#define PRAM_AXI_AxCACHE  4
#define PRAM_AXI_AxPROT  3
#define PRAM_AXI_AxREGION  4
#define PRAM_AXI_AxQOS  4
#define PRAM_AXI_RRESP  2


#endif //_AXI_INTERCONNECTION_H