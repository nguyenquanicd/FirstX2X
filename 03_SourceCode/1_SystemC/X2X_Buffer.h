/////////////////////////////////////////////////
// Author: Tien Tran
// Date: 2019/10
// Describle: X2X
/////////////////////////////////////////////////

#include "systemc.h"

#ifndef __X2X__H_
#define __X2X__H_

#define DATA_WIDTH 64
#define RESET_TYPE false
#define WAIT_CYCLE wait()
#define PUSH_TYPE true
#define POP_TYPE true

class X2X: public sc_module
{
private:
    // variable
    sc_fifo<sc_dt::sc_uint<DATA_WIDTH> > fifo;
    // method
    void processHandlerMethod();
    void InputValue();
    void OutputHandler();
public:
    X2X(sc_module_name name);
    ~X2X( );
    // input signal
    sc_in<sc_dt::uint64> In;
    sc_in<bool> Push;
    sc_in<bool> Pop;
    sc_in<bool> Reset;
    sc_in<bool> Clock;
    // output signal
    sc_out<sc_dt::sc_uint<DATA_WIDTH> > Out;
    sc_out<bool> Empty;
    sc_out<unsigned int> Num;
};

#endif // !__X2X__H_
