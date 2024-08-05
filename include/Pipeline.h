/**
 * @file    Pipeline.h
 *
 * @brief   Declaration of Pipeline
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "Pipe.h"

#include <vector>


class Pipeline {

public:
    Pipeline( uint16_t buffersize = 128 );
    Pipeline( ByteArray* pBAin );
    ~Pipeline();

    StatusCode AddProcessor( Pipe::ProcessorFunc processor, int outputBufferSize = -1 );

    ByteArray* getInputBuffer() const;
    ByteArray* getFrontEnd() const;
    ByteArray* getOutputBuffer() const;
    ByteArray* getBackEnd() const;
    ByteArray* getBuffer( uint8_t index ) const;

    StatusCode processStep( uint8_t i );
    StatusCode processAll( void );

    uint8_t getFaultyPipe( void ) const;
    uint8_t getBufferCount( void ) const;
    uint8_t getPipeCount( void ) const;

    void swapBuffers( uint16_t x, uint16_t y );
    void swapIO( void );

    void setErrorHandler( void (*ErrorHandler)( Pipeline* pPipeline, StatusCode ErrorCode ) );

private:

    uint8_t     _faultyPipe         = 0;
    uint16_t    _defaultBufferSize  = 128;
    void      (*_ErrorHandler)( Pipeline* pPipeline, StatusCode ErrorCode ) = nullptr;

    std::vector<ByteArray*> buffers;
    std::vector<Pipe*> pipes;
};

#endif // _PIPELINE_H_
