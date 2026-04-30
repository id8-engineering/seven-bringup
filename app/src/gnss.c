// Copyright (c) 2026 ID8 Engineering AB
// SPDX-License-Identifier: Apache-2.0

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <modem/lte_lc.h>
#include <modem/nrf_modem_lib.h>
#include <nrf_modem_gnss.h>

#include "gnss.h"

LOG_MODULE_REGISTER(GNSS, LOG_LEVEL_INF);

static struct k_sem fix_sem;
static struct nrf_modem_gnss_pvt_data_frame last_pvt;

static void gnss_event_handler(int event)
{
	int err;
	uint8_t tracked = 0;
	uint8_t in_fix = 0;

	switch (event) {
	case NRF_MODEM_GNSS_EVT_PVT:
		err = nrf_modem_gnss_read(&last_pvt, sizeof(last_pvt), NRF_MODEM_GNSS_DATA_PVT);
		if (err == 0) {
			for (int i = 0; i < NRF_MODEM_GNSS_MAX_SATELLITES; i++) {
				if (last_pvt.sv[i].sv > 0) {
					tracked++;
				}
				if (last_pvt.sv[i].flags & NRF_MODEM_GNSS_SV_FLAG_USED_IN_FIX) {
					in_fix++;
				}
			}

			LOG_INF("PVT: tracked=%u used=%u fix=%s", tracked, in_fix,
				(last_pvt.flags & NRF_MODEM_GNSS_PVT_FLAG_FIX_VALID) ? "yes"
										     : "no");

			if (last_pvt.flags & NRF_MODEM_GNSS_PVT_FLAG_FIX_VALID) {
				LOG_INF("GNSS fix: lat=%.06f lon=%.06f acc=%.01f m",
					last_pvt.latitude, last_pvt.longitude,
					(double)last_pvt.accuracy);
				k_sem_give(&fix_sem);
				LOG_INF("GNSS Test done");
			}
		}
		break;

	case NRF_MODEM_GNSS_EVT_FIX:
		LOG_INF("GNSS fix event");
		k_sem_give(&fix_sem);
		break;

	default:
		break;
	}
}

void test_gnss(void)
{
	int err;

	k_sem_init(&fix_sem, 0, 1);

	LOG_INF("Running GNSS test");
	LOG_INF("...");

	err = nrf_modem_lib_init();
	if (err < 0) {
		LOG_ERR("Modem init failed: %d", err);
		return;
	}

	err = lte_lc_func_mode_set(LTE_LC_FUNC_MODE_ACTIVATE_GNSS);
	if (err < 0) {
		LOG_ERR("Failed to activate GNSS: %d", err);
		return;
	}

	err = nrf_modem_gnss_event_handler_set(gnss_event_handler);
	if (err < 0) {
		LOG_ERR("Failed to set GNSS event handler: %d", err);
		return;
	}

	err = nrf_modem_gnss_nmea_mask_set(
		NRF_MODEM_GNSS_NMEA_RMC_MASK | NRF_MODEM_GNSS_NMEA_GGA_MASK |
		NRF_MODEM_GNSS_NMEA_GLL_MASK | NRF_MODEM_GNSS_NMEA_GSA_MASK |
		NRF_MODEM_GNSS_NMEA_GSV_MASK);
	if (err < 0) {
		LOG_ERR("Failed to set GNSS NMEA mask: %d", err);
		return;
	}

	err = nrf_modem_gnss_use_case_set(NRF_MODEM_GNSS_USE_CASE_MULTIPLE_HOT_START);
	if (err < 0) {
		LOG_ERR("Failed to set GNSS use case: %d", err);
		return;
	}

	err = nrf_modem_gnss_fix_retry_set(0);
	if (err < 0) {
		LOG_ERR("Failed to set GNSS fix retry: %d", err);
		return;
	}

	err = nrf_modem_gnss_fix_interval_set(1);
	if (err < 0) {
		LOG_ERR("Failed to set GNSS fix interval: %d", err);
		return;
	}

	err = nrf_modem_gnss_start();
	if (err < 0) {
		LOG_ERR("Failed to start GNSS: %d", err);
		return;
	}

	LOG_INF("GNSS started, waiting for fix");

	if (k_sem_take(&fix_sem, K_MINUTES(10)) != 0) {
		LOG_WRN("GNSS fix timeout");
	}

	(void)nrf_modem_gnss_stop();
}
