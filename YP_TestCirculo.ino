#include <stdint.h>
#include <stdio.h>  //c printf
//#include <iostream>
//#include <cstdio>

#include "printf.inc"   //enable printf


volatile uint32_t mySysTick = 0;
volatile uint32_t lastIOtick;


#include "CircularBuffer.h"
#include "Processors.h"

CircularBuffer* pCBuff2 = nullptr;  //serial2 activity

//#include "CRC16.h"
//#include "SlipDecoder.h"
//#include "SlipEncoder.h"


/*********************************************************************/
/*                               Pins                                */
/*********************************************************************/
#include "LED.h"

/*********************************************************************/
/*                              Serials                              */
/*********************************************************************/
//data from PC, called by default when
//defined(USBCON) && defined(USBD_USE_CDC)
//and ndef DISABLE_GENERIC_SERIALUSB
void serialEventUSB( void ) {
    LEDtoggle();
    uint8_t buff;
#if 1
    printf("sEvU: ");
    while ( 0 < SerialUSB.available() ) {
        buff = SerialUSB.read();
        printf("%c", buff );
    }
    //printf("\r\n");
#endif
//    while ( 0 < SerialUSB.available() ) {
//        buff = SerialUSB.read();
    buff = Serial1.write( &buff, 1 );
//    buff = SerialUSB.write( &buff, 1 );
    printf(" %d, %d\r\n", buff, Serial1.availableForWrite() );
//    }
//    Serial1.flush();
}


//data from modem
void serialEvent1() {
    LEDtoggle();
    //printf("sEv1\r\n");
}

//data to modem
void serialEvent2() {
    LEDtoggle();
    //printf("sEv2\r\n");
    lastIOtick = HAL_GetTick();
    if ( pCBuff2 ) {
        while ( 0 < Serial2.available() ) {
            LEDtoggle();
            pCBuff2->append( (uint8_t)Serial2.read() );
        }
    }
}

/*********************************************************************/
/*                               Setup                               */
/*********************************************************************/
void setupPins( void ) {
  LEDinit();
}

void setupSerials( void ) {
  //Serial.end();
  SerialUSB.begin( 115200 );
  //Initialize serial and wait for port to open:
  while ( !SerialUSB ) {
    ;   //wait for serial port to connect. Needed for native USB port only
  }
  LEDoff();
  printf( "1RX PA10 DigitalPin/PinName: %d/%d\r\n", PA10, digitalPinToPinName( PA10 ) );
  printf( "1TX PA9  DigitalPin/PinName: %d/%d\r\n", PA9, digitalPinToPinName( PA9 ) );
  printf( "2RX PA_3_ALT1 DigitalPin/PinName: %d/%d\r\n", PA_3_ALT1, digitalPinToPinName( PA_3_ALT1 ) );
  printf( "2TX PA_2_ALT1 DigitalPin/PinName: %d/%d\r\n", PA_2_ALT1, digitalPinToPinName( PA_2_ALT1 ) );

  Serial1.end();
  Serial2.end();
  Serial4.end();
  //Serial5.end();

  Serial1.setRx( PA10 );
  Serial1.setTx( PA9 );
  Serial1.begin( 115200 );
  while ( !Serial1 ) {
    printf("1");
  }
  printf( "Sirreal1 ready!\r\n" );

  //Serial2.setRx( PA3 );
  //Serial2.setTx( PA2 );
  Serial2.setRx( PA_3_ALT1 );
  Serial2.setTx( PA_2_ALT1 );
  Serial2.begin( 115200 );
  while ( !Serial2 ) {
    printf("2");
  }
  printf( "Sirreal2 ready!\r\n" );

  Serial1.print( "Sirreal1\r\n" );
  Serial2.print( "Sirreal2\r\n" );

  printf( "1RX PA10 PinName: %d\r\n", Serial1.getRx() );
  printf( "1TX PA9  PinName: %d\r\n", PA9, Serial1.getTx() );
  printf( "2RX PA_3_ALT1 PinName: %d\r\n", PA_3_ALT1, digitalPinToPinName( PA_3_ALT1 ) );
  printf( "2TX PA_2_ALT1 PinName: %d\r\n", PA_2_ALT1, digitalPinToPinName( PA_2_ALT1 ) );

}

void setupTimers( void ) {

#if 0 == _SYSTIME_
  //initCurrentTime(); temp!!!
#endif
#if defined( TIM1 )
  TIM_TypeDef *Instance = TIM1;
#else
  TIM_TypeDef *Instance = TIM2;
#endif

  //Instantiate HardwareTimer object.
  //Thanks to 'new' instanciation, HardwareTimer is not destructed when setup() function is finished.
/* temp!!!
  pMyTim = new HardwareTimer( Instance );
  pMyTim->setMode( 2, TIMER_OUTPUT_COMPARE );
  pMyTim->setOverflow( 10, HERTZ_FORMAT );  //10 Hz
  pMyTim->attachInterrupt( _100msCallback );
  pMyTim->resume();
*/
}


//dynamically allocated objects
Processors* pProcessors     = nullptr;


void setupObjects() {

    //serial2 buffer
    pCBuff2 = new CircularBuffer( 300 );
    
    //Initialize Processors object specifying the default buffer size
    pProcessors = new Processors( pCBuff2 );

    //Add a parser and a processor to the Processors list
    pProcessors->AddProcessor( parser, 20 );
    pProcessors->AddProcessor( process, 1 );

    //init GoL
    //GoLinit( pProcessors->getFrontEnd(), pProcessors->getBackEnd() );

    //pProcessors->getFrontEnd()->print2D( width, height );

}


void setup( void ) {

  setupPins();
  setupSerials();

  printf("\r\nYP_TestCirculo\r\n");

  Serial1.write("Serial1\r\n");
  Serial2.write("Serial2\r\n");

  //setupTimers();
  setupObjects();
  //setup mySysTick
  mySysTick = HAL_GetTick();

}

void clean() {
    //Delete dynamically allocated objects
    if ( pCBuff2     ) delete pCBuff2;
    if ( pProcessors ) delete pProcessors;
}


/*********************************************************************/
/*                               Main                                */
/*********************************************************************/
uint32_t lastONtick = 0;

void loop() {

//Serial.flush()

    mySysTick = HAL_GetTick();

    if ( pCBuff2->count() ) {
        printf("%d byte[s] incoming.\r\n", pCBuff2->count() );
        switch ( pProcessors->processAll() ) {
            case StatusCode::PENDING:
                printf("Pending %d bytes in pipe: %d.\r\n",
                    pProcessors->getFrontEnd()->count(),
                    pProcessors->getFaultyPipe() );
                break;
            case StatusCode::ERROR:
                printf("Processing failed in pipe: %d.\r\n", pProcessors->getFaultyPipe() );
                break;
            default:
                ;
        }
    }

}
