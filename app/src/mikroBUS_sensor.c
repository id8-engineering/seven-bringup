// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <inttypes.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(mikroBUS_sensor, LOG_LEVEL_INF);

static const struct device *dev = DEVICE_DT_GET_ONE(st_hts221);

static int read_sensor_parameters(const struct device *dev, struct sensor_value *temp,
				  struct sensor_value *hum);

void test_mikroBUS_sensor(void)
{
	LOG_INF("Starting MikroBUS I2C test");
	LOG_INF("...");

	struct sensor_value temp;
	struct sensor_value hum;

	if (!device_is_ready(dev)) {
		LOG_ERR("sensor: device not ready");
		return;
	}

	int ret = read_sensor_parameters(dev, &temp, &hum);
	if (ret < 0) {
		LOG_ERR("Failed to read mikroBUS sensor: %d", ret);
		return;
	}

	int64_t temp_milli = sensor_value_to_milli(&temp);
	int64_t hum_milli = sensor_value_to_milli(&hum);

	LOG_INF("Temperature: %" PRId64 " mC", temp_milli);
	LOG_INF("Relative Humidity: %" PRId64 " m%%", hum_milli);
}

static int read_sensor_parameters(const struct device *dev, struct sensor_value *temp,
				  struct sensor_value *hum)
{
	int ret;

	if (dev == NULL) {
		LOG_ERR("Device pointer is NULL");
		return -EINVAL;
	}

	if (temp == NULL) {
		LOG_ERR("Temp pointer is NULL");
		return -EINVAL;
	}

	if (hum == NULL) {
		LOG_ERR("Humidity pointer is NULL");
		return -EINVAL;
	}

	ret = sensor_sample_fetch(dev);
	if (ret < 0) {
		LOG_ERR("Sensor sample update error: %d", ret);
		return ret;
	}

	ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, temp);
	if (ret < 0) {
		LOG_ERR("Cannot read HTS221 temperature channel: %d", ret);
		return ret;
	}

	ret = sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, hum);
	if (ret < 0) {
		LOG_ERR("Cannot read HTS221 humidity channel: %d", ret);
		return ret;
	}

	return 0;
}
