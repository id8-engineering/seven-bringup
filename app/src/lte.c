// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include "zephyr/logging/log_core.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <modem/lte_lc.h>
#include <modem/nrf_modem_lib.h>

LOG_MODULE_REGISTER(LTE, LOG_LEVEL_INF);

void test_lte()
{
	int err;

	LOG_INF("Starting LTE");

	err = nrf_modem_lib_init();
	if (err < 0) {
		LOG_ERR("Modem init failed: %d", err);
		return err;
	}

	err = lte_lc_connect();
	if (err < 0) {
		LOG_ERR("LTE connect failed: %d", err);
		return err;
	}

	LOG_INF("LTE connected");
}
