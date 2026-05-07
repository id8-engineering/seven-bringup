#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

LOG_MODULE_REGISTER(gpio, LOG_LEVEL_INF);

static const struct gpio_dt_spec mikrobus1[] = {
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 14,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* AN */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 2,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* RST */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 0,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* CS */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 6,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* SCK */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 5,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* MISO */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 4,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* MOSI */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 3,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* PWM */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 1,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* INT */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 11,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* RX */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 10,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* TX */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 8,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* SCL */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 9,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* SDA */
};

static const struct gpio_dt_spec mikrobus2[] = {
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 20,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* AN */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 16,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* RST */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 7,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* CS */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 29,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* SCK */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 28,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* MISO */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 21,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* MOSI */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 17,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* PWM */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 15,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* INT */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 13,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* RX */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 12,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* TX */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 23,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* SCL */
	{.port = DEVICE_DT_GET(DT_NODELABEL(gpio0)),
	 .pin = 22,
	 .dt_flags = GPIO_ACTIVE_HIGH}, /* SDA */
};

static void configure_gpio(void)
{
	for (size_t i = 0; i < ARRAY_SIZE(mikrobus1); i++) {
		gpio_pin_configure_dt(&mikrobus1[i], GPIO_OUTPUT_INACTIVE);
	}

	for (size_t i = 0; i < ARRAY_SIZE(mikrobus2); i++) {
		gpio_pin_configure_dt(&mikrobus2[i], GPIO_OUTPUT_INACTIVE);
	}
}

void test_gpio(void)
{
	LOG_INF("Running GPIO test");
	configure_gpio();

	while (1) {
		for (size_t i = 0; i < ARRAY_SIZE(mikrobus1); i++) {
			gpio_pin_set_dt(&mikrobus1[i], 1);
			gpio_pin_set_dt(&mikrobus2[i], 1);

			k_sleep(K_MSEC(500));

			gpio_pin_set_dt(&mikrobus1[i], 0);
			gpio_pin_set_dt(&mikrobus2[i], 0);
		}
	}
}
