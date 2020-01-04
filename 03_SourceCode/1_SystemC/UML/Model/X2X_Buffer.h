/**
 * Project Untitled
 */


#ifndef _X2X_BUFFER_H
#define _X2X_BUFFER_H

template<unsigned int DATA_WIDTH >
class X2X_Buffer {
public: 
    sc_in<sc_dt::sc_uint<DATA_WIDTH> > In;
    sc_out<sc_dt::sc_uint<DATA_WIDTH> > Out;
    sc_in<bool> Push;
    sc_in<bool> Pop;
    sc_out<bool> Empty;
    sc_out<bool> Full;
    sc_in<bool> Clock;
    sc_in<bool> Reset;
    
void BufferInputHandler();
    
void BufferOutHandler();
    
void BufferCoreHandler();
};

#endif //_X2X_BUFFER_H