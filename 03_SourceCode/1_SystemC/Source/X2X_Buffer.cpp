/**
 * X2X_Buffer ip
 */

#include "X2X_Buffer.h"

 /**
  * Constructor
  */
template<unsigned int DATA_WIDTH >
X2X_Buffer<DATA_WIDTH>::X2X_Buffer(sc_module_name name)
{
    Empty.initialize(true);
    Full.initialize(false);
    for(unsigned int index = 0; index < DATA_WIDTH; index++){
        Out[index].initialize(false);
    }
    isPush = !X2X_PUSH_TYPE;
    isPop = !X2X_BUF_POP_TYPE;
    // Process registration
    SC_HAS_PROCESS(X2X_Buffer);

    SC_METHOD(PushHandler);
    sensitive << Push.pos();
    dont_initialize( );

    SC_METHOD(PopHandler);
    sensitive << Pop.pos();
    dont_initialize( );

    SC_METHOD(BufferCoreHandler);
    sensitive << Clock.pos( );
    sensitive << Reset.neg( );
    dont_initialize( );

}

/**
 * Desctructor
 */
template<unsigned int DATA_WIDTH >
X2X_Buffer<DATA_WIDTH>::~X2X_Buffer() {
}

/**
 * PushHandler 
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::PushHandler( )
{
    isPush = X2X_PUSH_TYPE;
}

/**
 * PopHandler
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::PopHandler( )
{
    isPop = X2X_PUSH_TYPE;
}
/**
 * GetEmpty
 */
template<unsigned int DATA_WIDTH >
bool X2X_Buffer<DATA_WIDTH>::GetEmpty( )
{
    for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++) {
        if (bufferData[index].isEmpty == false) {
            return false;
        }
    }
    return true;
}

/**
 * GetFull
 */
template<unsigned int DATA_WIDTH >
bool X2X_Buffer<DATA_WIDTH>::GetFull()
{
    bool result = false;
    for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++) {
            result |= bufferData[index].isEmpty;
    }
    return !result;
}

/**
 * SetData 
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::SetData(unsigned int numElement)
{
    for (unsigned int index = 0; index < DATA_WIDTH; index ++)
    {
        bufferData[numElement].mData[index] = In[index].read( );
    }
    bufferData[numElement].isWritten = true;
    bufferData[numElement].isEmpty = false;
    isPush = !X2X_PUSH_TYPE;
}

/**
 * GetData
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::GetData(unsigned int numElement)
{
    for (unsigned int index = 0; index < DATA_WIDTH; index++) {
        Out[index].write(bufferData[numElement].mData[index]);
    }
}
/**
 * ResetWritten
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::ResetWritten()
{
    for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++)
    {
        bufferData[index].ResetWrite();
    }
}

/**
 * ResetReaden
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::ResetReaden()
{
    for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++)
    {
        bufferData[index].ResetRead( );
    }
}

/**
 * BufferCoreHandler core control operation
 */
template<unsigned int DATA_WIDTH >
void X2X_Buffer<DATA_WIDTH>::BufferCoreHandler() {
    if (Reset.read( ) == X2X_RESET_TYPE) {    // Reset Handler
        for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++){
            bufferData[index].RemoveData();
            bufferData[index].ResetRead();
            bufferData[index].ResetWrite();
        }
        for (unsigned int index =0; index < DATA_WIDTH; index++){
            Out[index].write(0x0);
        }
    } else { // Clock Handler
        if ((Empty.read() == true) && (isPush == true)) {
            for (unsigned int index = 0; index < DATA_WIDTH; index++) {
                Out[index].write(In[index].read());
            }
            SetData(0);
        } else {
            if (isPush == true) {
                for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++) {
                    if(bufferData[index].isWritten == false && bufferData[index].isEmpty == true){
                        SetData(index);
                        // re-set when fifo was write all
                        if (index == X2X_BUF_DATA_NUM-1){
                            ResetWritten();
                        }
                        break;
                    }
                }
            } 
            if (isPop == true) {
                for (unsigned int index = 0; index < X2X_BUF_DATA_NUM; index++) {
                    if (bufferData[index].isReaden == false && bufferData[index].isEmpty == false) {
                        bufferData[index].RemoveData();
                        isPop = !X2X_BUF_POP_TYPE;
                        // re-set when fifo was write all
                        if (index == X2X_BUF_DATA_NUM-1) {
                            ResetReaden( );
                            if (bufferData[0].isEmpty != X2X_PUSH_TYPE){
                                GetData(0);
                            }
                        } else if (bufferData[index+1].isEmpty != X2X_PUSH_TYPE){
                            GetData(index+1);
                        }
                        break;
                    }
                }
            }
        }
        Empty.write(GetEmpty());
        Full.write(GetFull());
    }
}
