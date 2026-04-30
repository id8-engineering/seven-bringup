// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <errno.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/can.h>
#include <zephyr/logging/log.h>
#include "mikroBUS_CAN.h"

LOG_MODULE_REGISTER(mikroBUS_CAN, LOG_LEVEL_INF);

#if defined(CONFIG_SEVEN_TEST_CAN_MIKROBUS)

static const struct device *can_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_canbus));

CAN_MSGQ_DEFINE(can_rx_msgq, 10);

void test_mikroBUS_CAN(void)
{
	const struct can_filter filter = {
		.flags = 0,
		.id = 0,
		.mask = 0,
	};
	struct can_frame frame;
	int64_t end_time;
	int filter_id;
	int ret;

	LOG_INF("Starting mikroBUS CAN test");
	LOG_INF("Listening for CAN frames for 10 seconds");
	LOG_INF("...");

	if (!device_is_ready(can_dev)) {
		LOG_ERR("CAN device %s is not ready", can_dev->name);
		return;
	}

	ret = can_set_bitrate(can_dev, 250000);
	if (ret < 0) {
		LOG_ERR("Failed to set CAN bitrate: %d", ret);
		return;
	}

	ret = can_start(can_dev);
	if (ret < 0) {
		LOG_ERR("Failed to start CAN controller: %d", ret);
		return;
	}

	filter_id = can_add_rx_filter_msgq(can_dev, &can_rx_msgq, &filter);
	if (filter_id < 0) {
		LOG_ERR("Failed to add CAN RX filter: %d", filter_id);
		return;
	}

	end_time = k_uptime_get() + 10000;

	while (k_uptime_get() < end_time) {
		int64_t remaining = end_time - k_uptime_get();

		ret = k_msgq_get(&can_rx_msgq, &frame, K_MSEC(remaining));
		if (ret == -EAGAIN) {
			break;
		}
		if (ret < 0) {
			LOG_ERR("Failed to read CAN frame: %d", ret);
			break;
		}

		LOG_INF("CAN id=0x%x dlc=%u data=%02x %02x %02x %02x %02x %02x %02x %02x", frame.id,
			frame.dlc, frame.data[0], frame.data[1], frame.data[2], frame.data[3],
			frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
	}

	can_remove_rx_filter(can_dev, filter_id);
	LOG_INF("mikroBUS CAN test done");
}

#endif
