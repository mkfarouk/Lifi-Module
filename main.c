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


float door_distance = 50.0;



int main(void) {
  

   UART_init();
   DIO_Init();
   bool flag = true;
   
   fume_sensor_init();
   
   magnetic_sensor_init();
    
   ultrasonic_sensor_init();
      
   
    while (1) {
      
      if (DIO_ReadPin(&GPIO_PORTF_DATA_R, 0) == 0) {    // on 

            // UART_init(); // dont forget to de init in mute

            // init_led(); // dont forget to de init in mute

      fume_sensor_init();
   
      magnetic_sensor_init();
    
      ultrasonic_sensor_init();
      
      flag = true;
   
        }
        
        while(flag){
            if (DIO_ReadPin(&GPIO_PORTF_DATA_R, 4) == 0) {


                magnetic_sensor_deinit();
                ultrasonic_sensor_deinit();
                flag = false;
                break;


          }
          
        ultrasonic_trigger_pulse();

        
        uint32_t pulse_echo_time = ultrasonic_measure_pulse_echo();

       
        float distance = ultrasonic_calculate_distance(pulse_echo_time);
      
        int distance_int = (int)distance;
       
        //GPIOPinWrite(GREEN_LED_GPIO_BASE, GREEN_LED_PIN, 0);
        
        if ( distance < door_distance ) {
            
           //  softwareDelay(100);
          //GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, RED_LED_PIN);
       //  GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
          
          
       // sendBluetoothData("There is an intruder \n");
        
       // char distance_str[20];  // Adjust the size based on your requirements
        //snprintf(distance_str, sizeof(distance_str), "%d", distance_int);
        //sendBluetoothData(distance_str);
        
        char message[50];  // Adjust the size based on your requirements
        snprintf(message, sizeof(message), "Intrusion is Detected %d cm away\n", distance_int);
        sendBluetoothData(message);
        
        
        //sendBluetoothData(distance_str);
       //  sendBluetoothIntruderMessage(distance);
          
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, GREEN_LED_PIN);
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, BLUE_LED_PIN);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, RED_LED_PIN);
         //softwareDelay(1000);
         SysCtlDelay(SysCtlClockGet() * 3);
      GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
      GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0); 
            //GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0);
          }
          
          
        } 
        

    }


/*
    
    //GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0 );
   while (1) {
        
             
        
     // GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, RED_LED_PIN); 
      //GPIOPinWrite(RED_LED_GPIO_BASE, RED_LED_PIN, 0);
        
        
        //ULTRASONIC
 
              // Trigger a pulse
       ultrasonic_trigger_pulse();

        // Measure the pulse echo time
        uint32_t pulse_echo_time = ultrasonic_measure_pulse_echo();

        // Calculate the distance
        float distance = ultrasonic_calculate_distance(pulse_echo_time);
      
        int distance_int = (int)distance;
       
        //GPIOPinWrite(GREEN_LED_GPIO_BASE, GREEN_LED_PIN, 0);
        
        if ( distance < door_distance ) {
            

        
        char message[50];  // Adjust the size based on your requirements
        snprintf(message, sizeof(message), "There is an intruder %d cm away\n", distance_int);
        sendBluetoothData(message);
        
        
        //sendBluetoothData(distance_str);
       //  sendBluetoothIntruderMessage(distance);
          
         GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0);
         GPIOPinWrite(RED_LED_GPIO_BASE, BLUE_LED_PIN, 0);
         GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, GREEN_LED_PIN);
         //softwareDelay(1000);
         SysCtlDelay(SysCtlClockGet() * 3);
         GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0);  
            //GPIOPinWrite(RED_LED_GPIO_BASE, GREEN_LED_PIN, 0);
        }



    } */
}





