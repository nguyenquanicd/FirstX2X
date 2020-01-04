/////////////////////////////////////////////////
// Author: Tien Tran
// Date: 2019/10
// Describle: X2X
/////////////////////////////////////////////////

#include "./../X2X/X2X_Buffer.h"

// constructor
X2X::X2X(sc_module_name name): sc_module(name)
{

    // Process registration
    SC_HAS_PROCESS(X2X);

    SC_METHOD(processHandlerMethod);
    sensitive << Clock.pos();
    sensitive << Reset.neg();
    dont_initialize( );
}

// destructor
X2X::~X2X( )
{    
}

// fifo
void X2X::processHandlerMethod()
{
    // Reset Handler
    if (Reset.read() == RESET_TYPE){
    	unsigned int index;
    	for(index=0;index<=16;index++){
            fifo.read( );
        }
        Num.write(fifo.num_available( ));
        Empty.write(true);
        Out.write(0x0);
    } else { // Clock Handler
        InputValue(); // check input
        OutputHandler(); // Set output
    
    }
}
// input
void X2X::InputValue( ){
    if (Push.read() == PUSH_TYPE)
    {
        fifo.write(In.read( ));
    } 
}
// output
void X2X::OutputHandler( ) {
    if (Pop.read() == POP_TYPE){
           Out.write(fifo.read());
    }
    if (fifo.num_available( ) <= 0)
    {
        Empty.write(true);
    }
    Num.write(fifo.num_available( ));
}
