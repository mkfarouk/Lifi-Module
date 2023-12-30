#ifndef BITWISE_OPERATION_H
#define BITWISE_OPERATION_H


#define Set_Bit(Register,Bit) Register |= (1<<Bit)

#define Clear_Bit(Register,Bit) Register &= (0<<Bit)

#define Get_Bit(Register,Bit) ((Register & (1<<Bit))>>Bit)

#define Toggle_Bit(Register,Bit) Register ^= (1<<Bit)


#endif /* BITWISE_OPERATION_H */