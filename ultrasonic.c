#include <stdbool.h>
#include <stdlib.h>
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

#include "ultrasonic.h"

 void ultrasonic_sensor_init(void) {
   
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);  
    
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) {}

    
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);  // pulse maker / trigger

    
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);   // echo receiver 

    // Enable the timer used for measuring pulse echo time
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0 );
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    
    uint32_t clockFrequency = SysCtlClockGet();
    uint32_t delaySeconds = 40;
    uint32_t loadValue = clockFrequency * delaySeconds;

    // Set the load value
    TimerLoadSet(TIMER0_BASE, TIMER_A, loadValue);

    // Enable Timer 0
    TimerEnable(TIMER0_BASE, TIMER_A);
    
}

void ultrasonic_sensor_deinit(void) {
    // Disable the Timer
    /*TimerDisable(TIMER0_BASE, TIMER_A);
    
    // Disable the GPIO pins used for the ultrasonic sensor
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0);   // Echo receiver
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);   // Pulse maker / Trigger
    
    // Disable the Timer peripheral
    SysCtlPeripheralDisable(SYSCTL_PERIPH_TIMER0);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)) ;*/
    
    // Disable the GPIO port connected to the ultrasonic sensor
    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOD);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) ;
}


void softwareDelay(uint32_t delay) {
    while (delay--) {
        
    }
}
void ultrasonic_trigger_pulse(void) {
    
  
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 , 1);
    
    //SysCtlDelay(8);  // Adjust delay as needed for your sensor
    //SysCtlDelay(3 * SysCtlClockGet());
     softwareDelay(100);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
}

uint32_t ultrasonic_measure_pulse_echo(void) {
    ultrasonic_trigger_pulse();
    // Wait for the rising edge on the Ultrasonic Echo pin
    while (!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)) {}

    // Record the start time
    uint32_t start_time = TimerValueGet(TIMER0_BASE, TIMER_A);

    // Wait for the falling edge on the Ultrasonic Echo pin
    while (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)) {}

    // Record the end time
    uint32_t end_time = TimerValueGet(TIMER0_BASE, TIMER_A);

    // Calculate the pulse echo time (in microseconds)
    uint32_t pulse_echo_time = abs(end_time - start_time);

    return pulse_echo_time;
}

float ultrasonic_calculate_distance(uint32_t pulse_echo_time) {
  
    // Speed of sound in air at 20 degrees Celsius is approximately 343 meters per second
    // Divide by 2 for one-way travel, and multiply by 100 to get centimeters
  
    return (pulse_echo_time * 34300.0) / (2.0 * SysCtlClockGet());
}





/*
float performDistanceMeasurement(void) {
    // Step 1: Apply a 10 microseconds pulse to the Trigger pin
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
    softwareDelay(100);  // 10 microseconds delay
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);

    // Step 2: Wait for the echo pin to go high
    while (!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)) {}

    // Step 3: Record the start time
    uint32_t start_time = TimerValueGet(TIMER0_BASE, TIMER_A);

    // Step 4: Wait for the echo pin to go low
    while (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)) {}

    // Step 5: Record the end time
    uint32_t end_time = TimerValueGet(TIMER0_BASE, TIMER_A);

    // Step 6: Calculate the pulse echo time (in microseconds)
    uint32_t pulse_echo_time = start_time - end_time;

    // Step 7: Calculate the distance
    float distance = (pulse_echo_time * 34300.0) / (2.0 * SysCtlClockGet());

   
}
*/