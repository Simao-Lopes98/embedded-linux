#include <stdio.h>
#include <wiringPi.h>



#define LED_PIN 0 // GPIO 27 on RasPi


int main() {
    if(wiringPiSetup() == -1)
    {
        printf ("Failed to init wiringPi\n");
        return 1;
    }

    pinMode (LED_PIN, OUTPUT);

    printf ("Starting to blink\n");


    while (1)
    {
        digitalWrite(LED_PIN, HIGH);
        printf("LED is ON\n");
        delay(500);
        digitalWrite(LED_PIN, LOW);
        printf("LED is off\n");
        delay(500);
    }
    

    return 0;
}