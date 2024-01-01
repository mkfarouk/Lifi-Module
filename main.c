#include <stdbool.h>
#include <stdint.h>
#include "DIO.h"
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
#include "magnetic.h"
#include "ultrasonic.h"
#include "bluetooth.h"




#define GREEN_LED_PIN GPIO_PIN_3
#define RED_LED_GPIO_BASE GPIO_PORTF_BASE
#define RED_LED_PIN GPIO_PIN_1
#define BLUE_LED_PIN GPIO_PIN_2


float door_distance = 35.0;



int main(void) {
  

   UART_init();
   DIO_Init();
   bool flag = true;
   
   fume_sensor_init();
   
   magnetic_sensor_init();
    
   ultrasonic_sensor_init();
      
   
    while (1) {
      
      if (DIO_ReadPin(&GPIO_PORTF_DATA_R, 0) == 0) {    

            

      fume_sensor_init();
   
      magnetic_sensor_init();
    
      ultrasonic_sensor_init();
      
      flag = true;
   
        }
        
        while(flag){
            if (DIO_ReadPin(&GPIO_PORTF_DATA_R, 4) == 0) {


                magnetic_sensor_deinit();
                ultrasonic_sensor_deinit();
                fume_sensor_deinit();
                flag = false;
                break;


          }
          
        ultrasonic_trigger_pulse();

        
        uint32_t pulse_echo_time = ultrasonic_measure_pulse_echo();

       
        float distance = ultrasonic_calculate_distance(pulse_echo_time);
      
        int distance_int = (int)distance;
       
        
        
        if ( distance < door_distance ) {
            
           
        
        char message[50];  
        snprintf(message, sizeof(message), "Intrusion is Detected %d cm away\n", distance_int);
        sendBluetoothData(message);
        
        
          
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, GREEN_LED_PIN);
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, BLUE_LED_PIN);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, RED_LED_PIN);
         
         SysCtlDelay(SysCtlClockGet() * 3);
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0); 
            
          }
          
          
        } 
        

    }


}





