#ifndef DIO_H
#define DIO_H

#include "inc/tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "types.h"

void DIO_Init(void);
void DIO_WritePin(vuint32 port, uint8 pin_num, uint8 value);
void DIO_WritePort(vuint32 port, uint32 data);
uint8 DIO_ReadPin(vuint32 port, uint8 pin_num);
uint32 DIO_ReadPort(void);
void DIO_toggleBit(vuint32 port, uint8 pin_num);


#endif /* DIO_H */