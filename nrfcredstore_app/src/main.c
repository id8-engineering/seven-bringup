#include <errno.h>

#include <modem/modem_key_mgmt.h>
#include <modem/nrf_modem_lib.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(nrfcredstore_app, LOG_LEVEL_INF);

#define SEC_TAG CONFIG_NRFCREDSTORE_APP_SEC_TAG

static const unsigned char root_ca_pem[] = {
#include <root_ca.pem.inc>
};

static const unsigned char client_cert_pem[] = {
#include <client_cert.pem.inc>
};

static const unsigned char private_key_pem[] = {
#include <private_key.pem.inc>
};

static int write_cred(enum modem_key_mgmt_cred_type type, const char *name,
		      const unsigned char *data, size_t len)
{
	int err = modem_key_mgmt_write(SEC_TAG, type, data, len);

	if (err == -EALREADY) {
		LOG_INF("%s already exists", name);
		return 0;
	}
	if (err) {
		LOG_ERR("%s write failed: %d", name, err);
		return err;
	}

	LOG_INF("%s written", name);
	return 0;
}

int main(void)
{
	int err;

	LOG_INF("Init modem");
	err = nrf_modem_lib_init();
	if (err) {
		LOG_ERR("nrf_modem_lib_init failed: %d", err);
		return 0;
	}

	err = write_cred(MODEM_KEY_MGMT_CRED_TYPE_CA_CHAIN, "Root CA", root_ca_pem,
			 sizeof(root_ca_pem));
	if (err) {
		return 0;
	}

	err = write_cred(MODEM_KEY_MGMT_CRED_TYPE_PUBLIC_CERT, "Client cert", client_cert_pem,
			 sizeof(client_cert_pem));
	if (err) {
		return 0;
	}

	err = write_cred(MODEM_KEY_MGMT_CRED_TYPE_PRIVATE_CERT, "Private key", private_key_pem,
			 sizeof(private_key_pem));
	if (err) {
		return 0;
	}

	LOG_INF("Done provisioning tag %d", SEC_TAG);
	return 0;
}
