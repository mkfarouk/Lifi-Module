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

#include "fume.h"

#include "bluetooth.h"


#define RED_LED_GPIO_BASE GPIO_PORTF_BASE
#define RED_LED_PIN GPIO_PIN_1
#define BLUE_LED_PIN GPIO_PIN_2
#define GREEN_LED_PIN GPIO_PIN_3
//#define BLUE_LED_PIN GPIO_PIN_2

void fume_sensor_init(void) {
  

  
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB) ) ;


    
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0);

   // GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    //GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTB_BASE, FumeSensorIntHandler);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_0);


}


void fume_sensor_deinit(void) {

    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOB);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) ;
}


uint8_t read_fume_sensor(void) {
  if (GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) == 0){
    return 0 ;
  }
    return 1;
}

void init_led(void) {

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
     while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) ) ;


    GPIOPinTypeGPIOOutput(RED_LED_GPIO_BASE, RED_LED_PIN);
    GPIOPinTypeGPIOOutput(RED_LED_GPIO_BASE, BLUE_LED_PIN);
    GPIOPinTypeGPIOOutput(RED_LED_GPIO_BASE, GREEN_LED_PIN);
    //GPIOPinTypeGPIOOutput(RED_LED_GPIO_BASE, BLUE_LED_PIN);
}



void FumeSensorIntHandler(void) {
  
  
    if (read_fume_sensor() == 0) {
  
      if ( GPIOPinRead(RED_LED_GPIO_BASE, GREEN_LED_PIN) == GREEN_LED_PIN){
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
            SysCtlDelay(SysCtlClockGet() / 3);
      }
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, GREEN_LED_PIN);
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, BLUE_LED_PIN);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, RED_LED_PIN);
      
      sendBluetoothData("Fire is Detected\n");
     
      SysCtlDelay(SysCtlClockGet());
            
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0);
      
      SysCtlDelay(SysCtlClockGet() / 2);
 
     // sendBluetoothData("Smoke Detected a7aaaaa\n");
       
     
      
    }/* else {
        // If fume sensor output is not 0, turn off the red LED
        GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
         sendBluetoothData("amaaan \n");
    }*/

 
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_0);
}

