#ifndef TYPES_H
#define TYPES_H


//Types
typedef signed char		int8;
typedef unsigned char		uint8;
typedef signed short		int16;
typedef unsigned short		uint16;
typedef signed int		int32;
typedef unsigned int		uint32;
typedef signed long long	int64;
typedef unsigned long long	uint64;
typedef float			float32;
typedef double			float64;


//Volatiles
typedef volatile int8	    	vint8;
typedef volatile uint8		vuint8;
typedef volatile int16		vint16;
typedef volatile uint16		vuint16;
typedef volatile int32		vint32;
typedef volatile unsigned long*	vuint32;
typedef volatile int64		vint64;
typedef volatile uint64		vuint64;
typedef volatile float32	vfloat32;
typedef volatile float64	vfloat64;

//Pointers
typedef int8*		int8_ptr;
typedef uint8*		uint8_ptr;
typedef int16*		int16_ptr;
typedef uint16*		uint16_ptr;
typedef int32*		int32_ptr;
typedef uint32*		uint32_ptr;
typedef int64*		int64_ptr;
typedef uint64*		uint64_ptr;
typedef float32*	float32_ptr;
typedef float64*	float64_ptr;


#endif /* TYPES_H */