/**
 * X2X_FIFO IP
 */

#include "systemc.h"

#ifndef _X2X_FIFO_H
#define _X2X_FIFO_H

#define X2X_RESET_TYPE false
#define X2X_PUSH_TYPE true
#define X2X_BUF_POP_TYPE true
#define X2X_BUF_DATA_NUM 16

template<unsigned int DATA_WIDTH >
class X2X_FIFO : public sc_module {
private:
    struct DataStructure
    {
        bool mData [DATA_WIDTH];
        bool isEmpty;
        bool isReaden;
        bool isWritten;
        DataStructure() {
            for (unsigned int index = 0; index < DATA_WIDTH; index++){
                mData[index] = 0;
            }
            isEmpty = true;
            isReaden = false;
            isWritten = false;
        }
        void RemoveData() {
            isEmpty  = true;
            isReaden = true;
            for (unsigned int index = 0; index < DATA_WIDTH; index++) {
                mData[index] = false;
            }
        }
        void ResetRead(){
            isReaden = false;
        }
        void ResetWrite(){
            isWritten = false;
        }
    };
    DataStructure bufferData[X2X_BUF_DATA_NUM];
    bool isPush;
    bool isPop;
    // method 
    void PushHandlerMethod( );
    void PopHandlerMethod( );
    void ResetWritten( );
    void ResetReaden( );
    void SetData(unsigned int numElement);
    void GetData(unsigned int numElement);
    void BufferCoreHandlerMethod( );
    bool GetEmpty( );
    bool GetFull( );
public: 
    X2X_FIFO( );
    ~X2X_FIFO( );
    // input signal
    sc_in<bool> In[DATA_WIDTH];
    sc_in<bool> Push;
    sc_in<bool> Pop;
    sc_in<bool> Clock;
    sc_in<bool> Reset;
    // output signal
    sc_out<bool> Out[DATA_WIDTH];
    sc_out<bool> Empty;
    sc_out<bool> Full;

};

#endif //_X2X_FIFO_H