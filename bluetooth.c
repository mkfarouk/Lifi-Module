#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

#include "bluetooth.h"

#define UART_MODULE_BASE UART5_BASE
#define UART_GPIO_BASE GPIO_PORTE_BASE
#define UART_PIN_RX GPIO_PIN_4
#define UART_PIN_TX GPIO_PIN_5

#define BLUETOOTH_UART_BAUDRATE 9600

void UART_init(void) {
    
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

 
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(UART_GPIO_BASE, UART_PIN_RX | UART_PIN_TX);


    UARTConfigSetExpClk(UART_MODULE_BASE, SysCtlClockGet(), BLUETOOTH_UART_BAUDRATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

 
    UARTEnable(UART_MODULE_BASE);
}

void sendBluetoothData(const char *data) {
    while (*data != '\0') {
        UARTCharPut(UART_MODULE_BASE, *data);
        data++;
    }
}


void sendBluetoothIntruderMessage(float distance) {
    char buffer[50];  // Adjust the buffer size based on your requirements
    snprintf(buffer, sizeof(buffer), "There is an intruder: %.2f meters\n", distance);
    
    // Send the formatted string over Bluetooth
    sendBluetoothData(buffer);
}