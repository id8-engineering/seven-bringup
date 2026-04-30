// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/logging/log.h>
#include "led_rbg.h"
#include <stdint.h>

LOG_MODULE_REGISTER(led_rbg, LOG_LEVEL_INF);

static const struct device *led_strip = DEVICE_DT_GET(DT_CHOSEN(zephyr_led_strip));

void test_led(void)
{
	LOG_INF("Running RGB LED test");
	LOG_INF("...");

	struct led_rgb pixel = {
		.r = 0x00,
		.g = 0x00,
		.b = 0x00,
	};

	if (!device_is_ready(led_strip)) {
		return;
	}

	for (int i = 0; i <= 255; i++) {
		pixel.r = i;
		pixel.g = 0;
		pixel.b = 0;
		int ret = led_strip_update_rgb(led_strip, &pixel, 1);
		k_sleep(K_MSEC(10));
		if (ret < 0) {
			LOG_ERR("RGB=(%d,%d,%d) ret=%d", pixel.r, pixel.g, pixel.b, ret);
		}
	}

	for (int i = 0; i <= 255; i++) {
		pixel.r = 0;
		pixel.g = i;
		pixel.b = 0;
		int ret = led_strip_update_rgb(led_strip, &pixel, 1);
		k_sleep(K_MSEC(10));
		if (ret < 0) {
			LOG_ERR("RGB=(%d,%d,%d) ret=%d", pixel.r, pixel.g, pixel.b, ret);
		}
	}

	for (int i = 0; i <= 255; i++) {
		pixel.r = 0;
		pixel.g = 0;
		pixel.b = i;
		int ret = led_strip_update_rgb(led_strip, &pixel, 1);
		k_sleep(K_MSEC(10));
		if (ret < 0) {
			LOG_ERR("RGB=(%d,%d,%d) ret=%d", pixel.r, pixel.g, pixel.b, ret);
		}
	}
}
