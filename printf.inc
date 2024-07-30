#define REDEFINE_WRITE 1
#if 0 == REDEFINE_WRITE
/* Private function prototypes -----------------------------------------------*/
extern "C" PUTCHAR_PROTOTYPE {
  HAL_UART_Transmit( SerialUSB.getHandle(), (uint8_t*)&ch, 1, HAL_MAX_DELAY );
  return ch;
}
#else   //0 == REDEFINE_WRITE
//Override the _write function to use SerialUSB
extern "C" int _write( int file, char* ptr, int len ) {
    //Write the character array to SerialUSB
    return (int)SerialUSB.write( (uint8_t*)ptr, len );
}
#endif  //0 == REDEFINE_WRITE
