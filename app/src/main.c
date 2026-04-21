// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include "led_rbg.h"
#include "zephyr/sys/clock.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	LOG_INF("Hello world, starting functional tests on Seven!");

	LOG_INF("Starting RGB LED test");
	k_sleep(K_SECONDS(3));
	led_test();
	LOG_INF("RGB LED test is done");
	return 0;
}
