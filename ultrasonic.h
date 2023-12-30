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


//float check_intrusion(float door_distance);


void ultrasonic_sensor_init(void);


void ultrasonic_trigger_pulse(void);


uint32_t ultrasonic_measure_pulse_echo(void);


float ultrasonic_calculate_distance(uint32_t pulse_echo_time);

void softwareDelay(uint32_t delay);

void ultrasonic_sensor_deinit(void);

//float performDistanceMeasurement(void);


