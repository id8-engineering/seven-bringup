cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nrfcredstore_app)

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated)

generate_inc_file_for_target(app ${CMAKE_CURRENT_SOURCE_DIR}/certs/root_ca.pem ${gen_dir}/root_ca.pem.inc)
generate_inc_file_for_target(app ${CMAKE_CURRENT_SOURCE_DIR}/certs/client_cert.pem ${gen_dir}/client_cert.pem.inc)
generate_inc_file_for_target(app ${CMAKE_CURRENT_SOURCE_DIR}/certs/private_key.pem ${gen_dir}/private_key.pem.inc)

target_sources(app PRIVATE src/main.c)
