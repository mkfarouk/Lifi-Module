#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "magnetic.h"
#include "bluetooth.h"

// Define the GPIO pin connected to the Blue LED

#define BLUE_LED_GPIO_BASE GPIO_PORTF_BASE
#define BLUE_LED_PIN GPIO_PIN_2
#define RED_LED_PIN GPIO_PIN_1
#define GREEN_LED_PIN GPIO_PIN_3

void magnetic_sensor_init(void) {
  
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC ));

   
    
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);
    
    
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_RISING_EDGE);
    GPIOIntRegister(GPIO_PORTC_BASE, MagneticSensorIntHandler);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4);
    
    //IntMasterEnable();

}

void magnetic_sensor_deinit(void) {
   /* // Disable the GPIO interrupt for the Magnetic Sensor pin
    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_4);
    
    // Unregister the GPIO interrupt handler
    GPIOIntUnregister(GPIO_PORTC_BASE);

    // Clear the interrupt flag
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4);

    // Configure the Magnetic Sensor pin as a regular input (not an interrupt)
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);*/

    // Disable the GPIO port connected to the Magnetic Sensor
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOC);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) ;
}


uint8_t read_magnetic_sensor(void) {
  if (GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4) == 0){
    return 0 ;
  }
    return 1;
}
/*
void init_blue_led(void) {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
     while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) ) ;

    // Configure the Red LED pin as an output
    GPIOPinTypeGPIOOutput(BLUE_LED_GPIO_BASE, BLUE_LED_PIN);
    //GPIOPinTypeGPIOOutput(BLUE_LED_GPIO_BASE, RED_LED_PIN);
   
}*/

void MagneticSensorIntHandler(void) {
    
    if (read_magnetic_sensor() == 0) {
       
        GPIOPinWrite(BLUE_LED_GPIO_BASE, BLUE_LED_PIN, 0);
        sendBluetoothData("Door is closed\n");
       
        // sendBluetoothData("Door is opened aloo \n");
        
        
       // GPIOPinWrite(BLUE_LED_GPIO_BASE, BLUE_LED_PIN, BLUE_LED_PIN );
      
        
    } 
    else {
      GPIOPinWrite(BLUE_LED_GPIO_BASE, RED_LED_PIN, 0);
      GPIOPinWrite(BLUE_LED_GPIO_BASE, GREEN_LED_PIN, 0);
      GPIOPinWrite(BLUE_LED_GPIO_BASE, BLUE_LED_PIN, BLUE_LED_PIN);
      sendBluetoothData("Door is opened aloo \n");
        SysCtlDelay(2 * SysCtlClockGet());
        
        
      GPIOPinWrite(BLUE_LED_GPIO_BASE, BLUE_LED_PIN, 0);
      SysCtlDelay(SysCtlClockGet() / 2);
      
      //sendBluetoothData("Door is not opened \n");
      //  GPIOPinWrite(BLUE_LED_GPIO_BASE, BLUE_LED_PIN, 0);
        //GPIOPinWrite(BLUE_LED_GPIO_BASE, RED_LED_PIN, RED_LED_PIN);
    }

    // Clear the interrupt flag
      
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4);
} 