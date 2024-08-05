/**
 * @file    Pipe.h
 *
 * @brief   Declaration of class Pipe
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#ifndef _PIPE_H_
#define _PIPE_H_


#ifndef EXCEPTIONS_SUPPORTED
#define EXCEPTIONS_SUPPORTED 0
#endif


#include "ByteArray.h"


enum class StatusCode {
    OK,
    PENDING,
    ERROR
};


class Pipe {

    public:

        using ProcessorFunc = StatusCode (*)( ByteArray*, ByteArray* );

        Pipe( ByteArray* pInput_data, ByteArray* pOutput_data, ProcessorFunc processor );

        StatusCode process();

        ByteArray* getInputBuffer() const;
        ByteArray* getOutputBuffer() const;

        void swapBuffers();

    protected:

        ByteArray*      pInput_data;
        ByteArray*      pOutput_data;
        ProcessorFunc   processor;

};


#endif // PIPE_H
