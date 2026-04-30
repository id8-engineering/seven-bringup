// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "buzzer.h"
#include "gnss.h"
#include "led_rbg.h"
#include "lte.h"
#include "mikroBUS_CAN.h"
#include "mikroBUS_sensor.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{

	if (IS_ENABLED(CONFIG_SEVEN_TEST_LED)) {
		test_led();
	}

	if (IS_ENABLED(CONFIG_SEVEN_TEST_BUZZER)) {
		test_buzzer();
	}

	if (IS_ENABLED(CONFIG_SEVEN_TEST_I2C_MIKROBUS)) {
		test_mikroBUS_I2C();
	}

	if (IS_ENABLED(CONFIG_SEVEN_TEST_CAN_MIKROBUS)) {
		test_mikroBUS_CAN();
	}

	if (IS_ENABLED(CONFIG_SEVEN_TEST_GNSS)) {
		test_gnss();
	}

	if (IS_ENABLED(CONFIG_SEVEN_TEST_LTE)) {
		test_lte();
	}

	return 0;
}
