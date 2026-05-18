// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "mikroBUS_pwm.h"

LOG_MODULE_REGISTER(mikroBUS_pwm, LOG_LEVEL_INF);

#if defined(CONFIG_SEVEN_TEST_PWM_MIKROBUS)

static const struct pwm_dt_spec mikrobus_pwm_led = PWM_DT_SPEC_GET(DT_NODELABEL(mikrobus_pwm));

void test_mikroBUS_pwm(void)
{
	if (!pwm_is_ready_dt(&mikrobus_pwm_led)) {
		LOG_ERR("mikroBUS PWM device is not ready");
		return;
	}

	LOG_INF("Running mikroBUS PWM LED test");

	for (uint8_t i = 0; i < 3; i++) {
		for (uint16_t value = 0; value <= 255; value++) {
			uint32_t pulse = (mikrobus_pwm_led.period * value) / 255U;
			int ret = pwm_set_pulse_dt(&mikrobus_pwm_led, pulse);

			if (ret < 0) {
				LOG_ERR("Failed to set PWM value to %u", value);
				return;
			}

			k_sleep(K_MSEC(20));
		}
	}

	(void)pwm_set_pulse_dt(&mikrobus_pwm_led, 0);
}

#endif
