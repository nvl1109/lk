/*
 * Copyright (c) 2008 Travis Geiselbrecht
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <app.h>
#include <debug.h>
#include <stdio.h>
#include <dev/gpio.h>
#include <platform/gpio.h>
#include <kernel/timer.h>
#include <compiler.h>


#define BLUE_LED_GPIO	GPIO(3,15)
static char flag = 0;

static enum handler_return blink_timer(timer_t *timer, lk_time_t now, void *arg) {
	gpio_set(BLUE_LED_GPIO, (flag) ? 1 : 0);
	flag = ~flag;

	return INT_RESCHEDULE;
}

static timer_t led_timer = TIMER_INITIAL_VALUE(led_timer);

static void ledblink_init(const struct app_descriptor *app)
{
	/* Configure LED */
	gpio_config(BLUE_LED_GPIO, GPIO_OUTPUT);

	timer_set_periodic(&led_timer, 500, blink_timer, NULL);
}

APP_START(ledblink)
.init = ledblink_init,
  APP_END