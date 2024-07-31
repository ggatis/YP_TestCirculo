/**
 * @file    Processors.cpp
 *
 * @brief   Functions for Processors
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#include "Processors.h"
#include "CircularBuffer.h"
#include "YP_TestCirculo.h"


StatusCode parser( ByteArray* pin, ByteArray* pout ) {
    
    CircularBuffer* pinCB = (CircularBuffer*)pin;
    //printf("parser pinCB->count(): %d\r\n", pinCB->count() );

    if ( pinCB->count() ) {

        uint8_t maxi = pinCB->count();
        if ( 20 < ( pout->count() + maxi ) ) {
            maxi = 20 - pout->count();
        }
        //printf("parser maxi:%d", maxi );
        for ( uint8_t i = 0; i < maxi; i++ ) {
            //printf(", %d", pinCB->count() );
            pout->append( pinCB->get() );
        }
        //printf("\r\n");

    }
    
    //printf("parser pout->count(): %d\r\n", pout->count() );

    if ( 20 > pout->count() ) {
        if ( ( lastIOtick + 2000 ) > mySysTick ) {
            return StatusCode::PENDING;
        }
    }

    return StatusCode::OK;
}


StatusCode process( ByteArray* pin, ByteArray* pout ) {

    uint8_t maxi = 20;
    if ( 20 > pin->count() ) {
        maxi = pin->count();
    }
    if ( maxi ) {
        if ( 20 > maxi ) {
            printf("process TO: ");
        } else {
            printf("process     ");
        }
        pin->printHEX();
        printf(" ");
        pin->print();
        pin->clear();
        printf("\r\n");
    }

    return StatusCode::OK;
}

void myErrorHandler( Processors* pProcessors, StatusCode ErrorCode ) {
    switch ( ErrorCode ) {
    case StatusCode::PENDING:
        if ( 1 != pProcessors->getFaultyPipe() ) {
            printf("Pending %d bytes in pipe: %d.\r\n",
                pProcessors->getFrontEnd()->count(),
                pProcessors->getFaultyPipe() );
        }
        break;
    case StatusCode::ERROR:
        printf("Processing failed in pipe: %d.\r\n", pProcessors->getFaultyPipe() );
        break;
    default:
        printf("Processing done OK.\r\n");
    }
}
