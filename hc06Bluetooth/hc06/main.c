/*
 * Muhammet Tayyip �ankaya
 * HC 06 Bluetooth
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"

void bluetoothSendMessage(char *array);

/* HC06 BLUETOOTH
 * TX-->PC6
 * RX-->PC7*/

int main(void)
{
    unsigned char data;
    int LED;

    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //HC06 BLUETOOTH Pinleri
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE,GPIO_PIN_6|GPIO_PIN_7);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    UARTConfigSetExpClk(UART3_BASE,SysCtlClockGet(),9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE));
    UARTEnable(UART3_BASE);



    while(1){
        while(!UARTCharsAvail(UART3_BASE));
        data=UARTCharGetNonBlocking(UART3_BASE);
        LED=0;
        if(data=='r'){
            LED = 2;
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
            bluetoothSendMessage("\nTiva send = RED\n");
            SysCtlDelay(10000000);}
        else if(data=='b'){
            LED = 4;
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
            bluetoothSendMessage("\nTiva send = BLUE\n");
            SysCtlDelay(10000000);}
        else if(data=='g'){
            LED = 8;
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
            bluetoothSendMessage("\nTiva send = GREEN\n");
            SysCtlDelay(10000000);}
        else if(data=='w'){
            LED = 14;
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
            bluetoothSendMessage("\nTiva send = WHITE\n");
            SysCtlDelay(10000000);}
        else{
            LED = 0;
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
            GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
            bluetoothSendMessage("\nTiva send = NO\n");
            SysCtlDelay(10000000);}
       }
    UARTDisable(UART1_BASE);
}


void bluetoothSendMessage(char *array){
    while(*array){
        UARTCharPut(UART3_BASE,*array);
        array++;}}

