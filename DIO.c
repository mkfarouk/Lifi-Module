#include "DIO.h"
#include <stdint.h>
//#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x40025038)) //sasa
//#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))

void DIO_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x1F;
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DEN_R |= 0x1F;
}


void DIO_WritePin(vuint32 port, uint8 pin_num, uint8 value) {
    if (value == 1) {
        Set_Bit(*port, pin_num);
    } else {
        Clear_Bit(*port, pin_num);
    }
}


void DIO_WritePort(vuint32 port, uint32 data) {
    *port = data;
}


uint8 DIO_ReadPin(vuint32 port, uint8 pin_num) {
  return Get_Bit(*port, pin_num);
}


uint32 DIO_ReadPort(void) {
  return GPIO_PORTF_DATA_R;
}

void DIO_toggleBit(vuint32 port, uint8 pin_num) {
  Toggle_Bit(*port, pin_num);
}