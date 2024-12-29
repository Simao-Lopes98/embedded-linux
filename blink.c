// blink.c

#include <gpiod.h>
#include <error.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GPIO_CHIP "/dev/gpiochip0"
#define GPIO_CONSUMER "blink_routine"

void gpio_cleanup(void);

struct gpiod_chip *chip;
struct gpiod_line_request_config config;
struct gpiod_line_bulk lines;

int main(int argc, char *argv[]) 
{
    unsigned int offsets[1];
    int values[1];
    int err;
    int counter = 10;

    chip = gpiod_chip_open (GPIO_CHIP);
    
    if (chip == NULL)
    {
        perror ("gpiod_chip_open");
        gpio_cleanup();
        return EXIT_FAILURE;
    }

    // Set pin 3 (GPIO 2) to HIGH
    offsets[0] = 3;
    values[0] = 0;

    err = gpiod_chip_get_lines (chip, offsets, 1, &lines);

    if (err != 0)
    {
        perror ("gpiod_chip_get_lines");
        gpio_cleanup();
        return EXIT_FAILURE;
    }

    //config config
    memset(&config, 0, sizeof(config));
    config.consumer = GPIO_CONSUMER;
    config.request_type = GPIOD_LINE_REQUEST_DIRECTION_OUTPUT;

    //get the bulk lines setting default value to 0. Takes ownership of liones
    err = gpiod_line_request_bulk (&lines, &config, values);
    if (err != 0)
    {
        perror ("gpiod_line_request_bulk");
        gpio_cleanup();
        return EXIT_FAILURE;
    }

    values[0] = 1;
    while (counter != 0)
    {
        //output value 
        err = gpiod_line_set_value_bulk (&lines, values);
        if (err != 0)
        {
            perror ("gpiod_line_set_value_bulk");
            gpio_cleanup();
            return EXIT_FAILURE; 
        }

        sleep(1); // Wait 1 sec
        counter--;
        values[0] = !values[0];
    }

    gpio_cleanup();

    return EXIT_SUCCESS;
}


void gpio_cleanup(void)
{
    gpiod_line_release_bulk (&lines);
    gpiod_chip_close (chip);
}