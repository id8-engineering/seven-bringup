// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "buzzer.h"
#include "gnss.h"
#include "led_rbg.h"
#include "lte.h"
#include "mikroBUS_sensor.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
	LOG_INF("Hello world, starting functional tests on Seven!");

	LOG_INF("Starting RGB LED test");
	k_sleep(K_SECONDS(1));
	test_led();
	LOG_INF("RGB LED test done");

	LOG_INF("Starting Buzzer test");
	k_sleep(K_SECONDS(1));
	test_buzzer();
	LOG_INF("Buzzer test done");

	LOG_INF("Starting mikroBUS sensor test");
	test_mikroBUS_sensor();
	LOG_INF("mikroBUS sensor test done");

	LOG_INF("Starting GNSS test");
	test_gnss();
	LOG_INF("GNSS test done");
	test_lte();
	return 0;
}
