/**
 * @file    CircularBuffer.cpp
 *
 * @brief   Implementation of class CircularBuffer
 *
 * @note    This example code is free software: you can redistribute it and/or modify it.
 *
 *          This program is provided by EDI on an "AS IS" basis without
 *          any warranties in the hope that it will be useful.
 * 
 * Gatis Gaigals, 2024
 */

#include <string>   //cpp string
#include <stdint.h>
//#include <stdio.h>  //c printf

#include "CircularBuffer.h"

/**
 * @brief   The CircularBuffer class provides methods for CircularBuffer.
 */

CircularBuffer::CircularBuffer( uint16_t size ) :
    ByteArray( size ), _head( 0 ), _tail( 0 ) {
}

        /**
          * @brief  class constructor, size, pointe to buffer
          *
          * @param  size  buffer size, it all contains data
          *         dataptr  pointer to buffer
          */
//                    CircularBuffer( uint16_t size, uint8_t* dataptr );

        /**
          * @brief  class constructor, all parameters
          *
          * @param  size  buffer size, it all contains data
          *         filled  useful data bytes count
          *         dataptr  pointer to buffer
          */
//                    CircularBuffer( uint16_t size, uint16_t filled, uint8_t* dataptr );

        /**
          * @brief  class constructor, initialised repeating a char
          *
          * @param  repeats  character repeat count
          *         c        character
          */
//                    CircularBuffer( uint16_t repeats, char c );

        /**
          * @brief  class constructor from string
          *
          * @param  aString
         */
//                    CircularBuffer( const std::string& aString );

        /**
          * @brief  class constructor from rvalue string
          *
          * @param  aString
         */
//                    CircularBuffer( std::string&& aString );

        /**
          * @brief  class copy constructor, initialised using const CircularBuffer,
          *
          * @param  aCircularBuffer   input CircularBuffer
          */
//                    CircularBuffer( const CircularBuffer& other );

        /**
          * @brief  move constructor
          *
          * @param  CircularBuffer& aCircularBuffer
          */
//                    CircularBuffer( CircularBuffer&& other ) noexcept;

        /**
          * @brief  class destructor
          *
          * @param  -
          */
//                   ~CircularBuffer( void );

        /**
          * @brief  copy assignment operator
          *
          * @param  const CircularBuffer& aCircularBuffer
          */
//        CircularBuffer& operator = ( const CircularBuffer& other );

        /**
          * @brief  move assignment operator
          *
          * @param  CircularBuffer& aCircularBuffer
          */
//        CircularBuffer& operator = ( CircularBuffer&& other ) noexcept;

        /**
         * @brief   returns data buffer
         *
         * @param   -
         *
         * @return  CircularBuffer data buffer
         */
//        uint8_t*    data( void ) const;

        /**
         * @brief   returns size of data in array
         *
         * @param   -
         *
         * @return  CircularBuffer data size
         */
/*
uint16_t
CircularBuffer::count( void ) const {
    return ByteArray::count();
}
*/

/**
 * @brief   returns size of buffer
 *
 * @param   -
 *
 * @return  CircularBuffer array size
 */
/*
uint16_t
CircularBuffer::size( void ) const {
    return ByteArray::size(); 
}
*/

/**
* @brief   effectively clears the content of the buffer
*
* @param   -
*
* @return  -
*/
void
CircularBuffer::clear( void ) {
    update_count( 0 );
    _head = _tail = 0;
}


        /**
         * @brief   extends the content to the _size
         *
         * @param   -
         *
         * @return  -
         */
//        void        extendo( void );

        /**
         * @brief   updates count of the data size in arrray
         *          in the case it is manipulated from outside
         *
         * @param   -
         *
         * @return  correctly updated count of the data size in arrray
         */
//        uint16_t    update_count( uint16_t newcount );

/**
 * @brief   returns flag indicating that bufer is empty
 *
 * @param   -
 *
 * @return  buffer is empty flag
 */
bool
CircularBuffer::isEmpty( void ) const {
    return 0 == ByteArray::count();
}


/**
 * @brief   returns flag indicating that bufer is full
 *
 * @param   -
 *
 * @return  buffer is full flag
 */
bool
CircularBuffer::isFull() const {
    return ByteArray::size() == ByteArray::count();
}


/**
 * @brief   returns oldest byte, advances tail
 *
 * @param   -
 *
 * @return  byte at tail
 */
uint8_t
CircularBuffer::get( void ) {
    if ( isEmpty() ) {
        //throw std::runtime_error("Buffer is empty");
        return 0;
    }
    uint8_t item = ByteArray::data()[_tail];
    //Move tail to next position
    ++_tail;
    if ( _tail >= ByteArray::size() ) {
        _tail = _tail - ByteArray::size();
    }
    update_count( ByteArray::count() - 1 );
    return item;
}


/**
 * @brief   return byte at index, does not change the object
 *
 * @param   index  array index
 *
 * @return  byte at position index
 */
uint8_t
CircularBuffer::at( uint16_t index ) const {
    if ( index >= ByteArray::count() ) {
        //throw std::out_of_range("Index out of range");
        return 0;
    }
    uint16_t pos = _tail + index;
    if ( pos > ByteArray::size() ) {
        pos -= ByteArray::size(); 
    };
    return ByteArray::data()[pos];
}


/**
 * @brief   return byte at index that wraps around ByteArray::size() from _tail
 *
 * @param   index  array index
 *
 * @return  byte at position index
 */
uint8_t
CircularBuffer::at( int index ) const {
    //if ( index >= ByteArray::count() ) {
    //    //throw std::out_of_range("Index out of range");
    //    return 0;
    //}
    int pos = _tail + index;
    while ( pos < 0 ) {
        pos += ByteArray::size();
    }
    while ( pos >= ByteArray::size() ) {
        pos -= ByteArray::size();
    }
    return ByteArray::data()[pos];
}

        /**
         * @brief   return byte at x*width+y
         *
         * @param   x       x
         * @param   y       y
         * @param   width   width
         * @param   height  height
         *
         * @return  byte at position if the position is valid
         */
//        uint8_t     peek( int x, int y, int width, int height ) const;

        /**
         * @brief   store a byte and return 0 for valid x*width+y
         *
         * @param   x       x
         * @param   y       y
         * @param   width   width
         * @param   height  height
         *
         * @return  0 if position was valid
         */
//        uint8_t     poke( uint8_t aByte, int x, int y, int width, int height );


/**
 * @brief   incoming CircularBuffer with added abyte
 *
 * @param   byte  byte to put in buffer
 *
 * @return  CircularBuffer
 */
CircularBuffer
CircularBuffer::put( uint8_t abyte ) {
    add( abyte );
    return *this;
}


/**
 * @brief   incoming CircularBuffer with added abyte
 *
 * @param   byte  byte to put in buffer
 *
 * @return  byte count in buffer
 */
CircularBuffer
CircularBuffer::append( uint8_t abyte ) {
    add( abyte );
    return *this;
}


        /**
         * @brief   incoming CircularBuffer with added abyte x repeats
         *
         * @param   repeats byte repeats
         *          byte    byte to append
         *
         * @return  byte count in array
         */
//        CircularBuffer  append( int repeats, uint8_t abyte );

        /**
         * @brief   returns mid
         *
         * @param   uint16_t index
         *          int size
         *
         * @return  CircularBuffer
         */
//        CircularBuffer   mid( uint16_t index, int size ) const;


/**
 * @brief   Removes n bytes from the end of the byte array.
 *          If n is greater than ByteArray::size(), the result is an empty byte array.
 *
 * @param   n   bytes to remove rom the end
 *
 * @return  CircularBuffer
 */
CircularBuffer
CircularBuffer::chop( int n ) {
    if ( n > ByteArray::count() ) {
        n = ByteArray::count();
    }
    if ( n < ( ByteArray::count() - ByteArray::size() ) ) {
        n = ByteArray::count() - ByteArray::size() ;
    }
    int new_head = _head - n;
    if ( new_head > ByteArray::size() ) {
        new_head -= ByteArray::size();
    }
    if ( new_head < 0 ) {
        new_head += ByteArray::size();
    }
    _head = new_head;
    update_count( ByteArray::count() - n );
    return *this;
}


/**
 * @brief   prints the buffer ar chars
 *
 * @param   -
 *
 * @return  -
 */
void
CircularBuffer::print( void ) const {
    for ( uint16_t i = 0; i < ByteArray::count(); ++i ) {
        printf( "%c", at( i ) );
    }
}

        /**
         * @brief   prints the buffer as chars in 2D
         *
         * @param   -
         *
         * @return  -
         */
//        void        print2D( int width, int height ) const;

        /**
         * @brief   prints the buffer as numbers in 2D
         *
         * @param   -
         *
         * @return  -
         */
//        void        print2Dd( int width, int height ) const;
