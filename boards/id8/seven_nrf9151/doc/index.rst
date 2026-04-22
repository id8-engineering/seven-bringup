.. zephyr:board:: seven

Overview
********

Seven is a custom nRF9151-based board from ID8 Engineering. The
``seven/nrf9151`` board target supports the Nordic Semiconductor nRF9151 ARM
Cortex-M33 CPU with Armv8-M Security Extension.

Hardware
********

Seven is based on the Nordic nRF9151 and provides:

* LTE-M / NB-IoT modem support
* GNSS support
* 6 V to 40 V input supply
* One Nano-SIM card holder
* LTE and GNSS SMA connectors
* One WS2812-compatible system LED on ``P0.18``
* One passive buzzer on ``P0.19``
* One debug UART on ``P0.27`` (TX) and ``P0.26`` (RX)
* Two mikroBUS headers

Supported Features
==================

.. zephyr:board-supported-hw::

mikroBUS Notes
==============

Seven provides default serial routing for the mikroBUS sockets:

* mikroBUS 1 uses ``uart2`` / ``i2c2`` / ``spi2``
* mikroBUS 2 uses ``uart3`` / ``i2c3`` / ``spi3``

Application overlays are expected to enable the function they need on the
target socket.

On nRF9151, the serial blocks are multiplexed:

* ``uart1`` / ``i2c1`` / ``spi1``
* ``uart2`` / ``i2c2`` / ``spi2``
* ``uart3`` / ``i2c3`` / ``spi3``

Only one function from each group can be enabled at a time, so each mikroBUS
socket may use UART or I2C or SPI, but not multiple of those functions
simultaneously.

The on-board RGB LED uses ``spi1`` with MOSI on ``P0.18`` by default, so
serial block 1 is not available for mikroBUS™ overlays unless that LED route
is overridden.

For ``seven/nrf9151/ns``, ``uart1`` is disabled by default to match the
upstream ``nrf9151dk`` non-secure board behavior where TF-M uses it by
default.

Examples:

* To place an I2C Click board on mikroBUS 1, enable ``&i2c2`` and add the
  device below it in an app overlay.
* To place an SPI Click board on mikroBUS 2, enable ``&spi3`` and add the
  device below it in an app overlay.

Connections and IOs
===================

On-board peripherals
--------------------

* System LED data = ``P0.18`` via ``spi1`` MOSI
* Buzzer PWM = ``P0.19``
* Debug UART TX = ``P0.27``
* Debug UART RX = ``P0.26``

mikroBUS 1
----------

* AN = ``P0.14``
* RST = ``P0.02``
* CS = ``P0.00``
* SCK = ``P0.06``
* MISO = ``P0.05``
* MOSI = ``P0.04``
* PWM = ``P0.03``
* INT = ``P0.01``
* RX = ``P0.11``
* TX = ``P0.10``
* SCL = ``P0.08``
* SDA = ``P0.09``

mikroBUS 2
----------

* AN = ``P0.20``
* RST = ``P0.16``
* CS = ``P0.07``
* SCK = ``P0.29``
* MISO = ``P0.28``
* MOSI = ``P0.21``
* PWM = ``P0.17``
* INT = ``P0.15``
* RX = ``P0.13``
* TX = ``P0.12``
* SCL = ``P0.23``
* SDA = ``P0.22``

Programming and Debugging
*************************

Seven provides a TC2030 SWD/JTAG connector for programming and a UART VCOM
interface for debug output.

.. zephyr:board-supported-runners::

Building
********

Build a secure application with:

.. code-block:: console

   west build -b seven/nrf9151 app

Build a non-secure application with:

.. code-block:: console

   west build -b seven/nrf9151/ns app

References
**********

.. target-notes::
