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

    
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);  //  trigger

    
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);   // echo receiver 


    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0 );
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    
    uint32_t clockFrequency = SysCtlClockGet();
    uint32_t delaySeconds = 40;
    uint32_t loadValue = clockFrequency * delaySeconds;


    TimerLoadSet(TIMER0_BASE, TIMER_A, loadValue);


    TimerEnable(TIMER0_BASE, TIMER_A);
    
}

void ultrasonic_sensor_deinit(void) {

    SysCtlPeripheralDisable(SYSCTL_PERIPH_GPIOD);
    while (SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) ;
}


void softwareDelay(uint32_t delay) {
    while (delay--) {
        
    }
}
void ultrasonic_trigger_pulse(void) {
    
  
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 , 1);
    
   
     softwareDelay(100);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
}

uint32_t ultrasonic_measure_pulse_echo(void) {
    ultrasonic_trigger_pulse();
 
    while (!GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)) {}

    
    uint32_t start_time = TimerValueGet(TIMER0_BASE, TIMER_A);

  
    while (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1)) {}

    
    uint32_t end_time = TimerValueGet(TIMER0_BASE, TIMER_A);

    
    uint32_t pulse_echo_time = abs(end_time - start_time);

    return pulse_echo_time;
}

float ultrasonic_calculate_distance(uint32_t pulse_echo_time) {
  

  
    return (pulse_echo_time * 34300.0) / (2.0 * SysCtlClockGet());
}




