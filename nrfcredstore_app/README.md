# nrfcredstore_app

Small helper app to provision AWS credentials into the nRF91 modem credential store over RTT.

We use this because `nrfcredstore` normally needs access to a VCOM/AT serial interface, and on this board setup we do not have usable VCOM access for that path.

It writes these files from `certs/` into modem security tag `CONFIG_NRFCREDSTORE_APP_SEC_TAG`:

- `root_ca.pem`
- `client_cert.pem`
- `private_key.pem`

## Build

From the `seven-bringup` repo root:

```bash
west build --sysbuild -p always -b seven/nrf9151/ns nrfcredstore_app -- \
  -DBOARD_ROOT=$PWD \
  -DDTS_ROOT=$PWD
```

## Flash

```bash
west flash
```

## Check RTT

```bash
west rtt
```

Expected output:

```text
Root CA written
Client cert written
Private key written
Done provisioning tag 123
```
