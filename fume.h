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


void fume_sensor_init(void);

uint8_t read_fume_sensor(void);

void init_led(void);

void FumeSensorIntHandler(void);

void fume_sensor_deinit(void);

