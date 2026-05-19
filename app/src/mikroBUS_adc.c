#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "mikroBUS_adc.h"

LOG_MODULE_REGISTER(mikroBUS_adc, LOG_LEVEL_INF);

#if defined(CONFIG_SEVEN_TEST_AN_MIKROBUS)

#define ADC_NODE DT_PATH(zephyr_user)

static const struct adc_dt_spec mikrobus_1_an = ADC_DT_SPEC_GET_BY_NAME(ADC_NODE, mikrobus_1_an);
static const struct adc_dt_spec mikrobus_2_an = ADC_DT_SPEC_GET_BY_NAME(ADC_NODE, mikrobus_2_an);

void test_mikroBUS_adc(void)
{
	int ret;
	int16_t raw;
	int16_t raw_2;
	int32_t mv;
	int32_t mv_2;
	struct adc_sequence sequence = {
		.buffer = &raw,
		.buffer_size = sizeof(raw),
	};
	struct adc_sequence sequence_2 = {
		.buffer = &raw_2,
		.buffer_size = sizeof(raw_2),
	};

	if (!adc_is_ready_dt(&mikrobus_1_an)) {
		LOG_ERR("ADC device is not ready");
		return;
	}

	if (!adc_is_ready_dt(&mikrobus_2_an)) {
		LOG_ERR("ADC device 2 is not ready");
		return;
	}

	ret = adc_channel_setup_dt(&mikrobus_1_an);
	if (ret < 0) {
		LOG_ERR("adc_channel_setup_dt failed: %d", ret);
		return;
	}

	ret = adc_channel_setup_dt(&mikrobus_2_an);
	if (ret < 0) {
		LOG_ERR("adc_channel_setup_dt 2 failed: %d", ret);
		return;
	}

	ret = adc_sequence_init_dt(&mikrobus_1_an, &sequence);
	if (ret < 0) {
		LOG_ERR("adc_sequence_init_dt failed: %d", ret);
		return;
	}

	ret = adc_sequence_init_dt(&mikrobus_2_an, &sequence_2);
	if (ret < 0) {
		LOG_ERR("adc_sequence_init_dt 2 failed: %d", ret);
		return;
	}

	LOG_INF("Running Click ADC test");

	while (1) {
		raw = 0;
		raw_2 = 0;

		ret = adc_read_dt(&mikrobus_1_an, &sequence);
		if (ret < 0) {
			LOG_ERR("adc_read_dt failed: %d", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		ret = adc_read_dt(&mikrobus_2_an, &sequence_2);
		if (ret < 0) {
			LOG_ERR("adc_read_dt 2 failed: %d", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		mv = raw;
		ret = adc_raw_to_millivolts_dt(&mikrobus_1_an, &mv);
		if (ret < 0) {
			LOG_ERR("adc_raw_to_millivolts_dt failed: %d", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		mv_2 = raw_2;
		ret = adc_raw_to_millivolts_dt(&mikrobus_2_an, &mv_2);
		if (ret < 0) {
			LOG_ERR("adc_raw_to_millivolts_dt 2 failed: %d", ret);
			k_sleep(K_SECONDS(1));
			continue;
		}

		LOG_INF("AN1 raw=%d mv=%d AN2 raw=%d mv=%d", raw, mv, raw_2, mv_2);

		k_sleep(K_SECONDS(1));
	}
}

#endif /* CONFIG_SEVEN_TEST_AN_MIKROBUS */
