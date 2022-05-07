/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     misonyo   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <sht3x.h>
/* defined the LED0 pin: PD14 */
#define LED0_PIN    GET_PIN(D, 14)

int main(void)
{
    static sht3x_device_t dev = RT_NULL;
    rt_uint8_t sht_addr = SHT3X_ADDR_PD;
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);


    while (1)
    {
        if (!dev)
        {
            dev = sht3x_init("i2c1", sht_addr);
        }
        if (dev)
        {

            if (sht3x_read_status(dev) == RT_EOK)
            {

                if (sht3x_read_singleshot(dev) == RT_EOK)
                {
                    rt_kprintf("sht3x humidity   : %d.%d \n", (int) dev->humidity, (int) (dev->humidity * 10) % 10);
                    rt_kprintf("sht3x temperature: %d.%d \n", (int) dev->temperature,  (int)(dev->temperature * 10) % 10);
                    rt_pin_write(LED0_PIN, PIN_HIGH);
                    rt_thread_mdelay(500);
                    rt_pin_write(LED0_PIN, PIN_LOW);
                    rt_thread_mdelay(500);
                }
                else
                {
                    rt_pin_write(LED0_PIN, PIN_HIGH);
                    rt_thread_mdelay(1500);
                    rt_pin_write(LED0_PIN, PIN_LOW);
                    rt_thread_mdelay(1500);
                }
            }
            else
            {
                rt_pin_write(LED0_PIN, PIN_HIGH);
                rt_thread_mdelay(1500);
                rt_pin_write(LED0_PIN, PIN_LOW);
                rt_thread_mdelay(1500);
            }
        }
    }


return RT_EOK;
}
