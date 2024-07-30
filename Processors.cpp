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


StatusCode parse( ByteArray* pin, ByteArray* pout ) {
    
    CircularBuffer* pinCB = (CircularBuffer*)pin;
    
    uint8_t maxi = pinCB->count();
    if ( 20 < ( pout->count() + maxi ) ) {
        maxi = 20 - pout->count();
    }
    for ( uint8_t i = 0; i < maxi; i++ ) {
        pout->append( pinCB->get() );
    }

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
    if ( 20 > maxi ) {
        printf("TO:");
    } else {
        printf("   ");
    }
    if ( maxi ) {
        pin->print();
    }
    printf("\r\n");

    return StatusCode::OK;
}
