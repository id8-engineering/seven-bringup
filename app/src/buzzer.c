// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(buzzer, LOG_LEVEL_INF);

static const struct pwm_dt_spec buzzer = PWM_DT_SPEC_GET(DT_NODELABEL(buzzer));

static int play_tone(uint32_t freq_hz, uint32_t duration_ms)
{
	if (!pwm_is_ready_dt(&buzzer)) {
		return -ENODEV;
	}

	uint32_t period_ns = 1000000000U / freq_hz;
	uint32_t pulse_ns = period_ns / 2;

	int ret = pwm_set_dt(&buzzer, period_ns, pulse_ns);
	if (ret < 0) {
		LOG_ERR("pwm_set_dt start failed: ret=%d", ret);
		return ret;
	}

	k_sleep(K_MSEC(duration_ms));

	ret = pwm_set_dt(&buzzer, period_ns, 0);
	if (ret < 0) {
		LOG_ERR("pwm_set_dt stop failed: ret=%d", ret);
		return ret;
	}

	return 0;
}

void test_buzzer()
{
	play_tone(659, 125); /* E5 */
	k_sleep(K_MSEC(125));
	play_tone(659, 125); /* E5 */
	k_sleep(K_MSEC(250));
	play_tone(659, 125); /* E5 */
	k_sleep(K_MSEC(250));
	play_tone(523, 125); /* C5 */
	k_sleep(K_MSEC(125));
	play_tone(659, 125); /* E5 */
	k_sleep(K_MSEC(250));
	play_tone(784, 125); /* G5 */
	k_sleep(K_MSEC(625));
	play_tone(392, 125); /* G4 */
	k_sleep(K_MSEC(625));

	play_tone(523, 125); /* C5 */
	k_sleep(K_MSEC(375));
	play_tone(392, 125); /* G4 */
	k_sleep(K_MSEC(375));
	play_tone(330, 125); /* E4 */
	k_sleep(K_MSEC(375));
	play_tone(440, 125); /* A4 */
	k_sleep(K_MSEC(250));
	play_tone(494, 125); /* B4 */
	k_sleep(K_MSEC(250));
	play_tone(466, 125); /* Bb4 */
	k_sleep(K_MSEC(125));
	play_tone(440, 125); /* A4 */
	k_sleep(K_MSEC(250));

	play_tone(392, 100); /* G4 */
	k_sleep(K_MSEC(100));
	play_tone(659, 100); /* E5 */
	k_sleep(K_MSEC(100));
	play_tone(784, 100); /* G5 */
	k_sleep(K_MSEC(100));
	play_tone(880, 125); /* A5 */
	k_sleep(K_MSEC(250));
	play_tone(698, 125); /* F5 */
	k_sleep(K_MSEC(125));
	play_tone(784, 125); /* G5 */
	k_sleep(K_MSEC(125));
	play_tone(659, 125); /* E5 */
	k_sleep(K_MSEC(125));
	play_tone(523, 125); /* C5 */
	k_sleep(K_MSEC(125));
	play_tone(587, 125); /* D5 */
	k_sleep(K_MSEC(125));
	play_tone(494, 125); /* B4 */
	k_sleep(K_MSEC(375));
}
