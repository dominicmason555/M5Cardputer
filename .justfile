set shell := ["bash", "-uc"]

alias b := build
alias f := flash
alias bf := build_flash

default_port := "/dev/ttyACM0"

# Lists the targets
default:
    just --list

# Builds the image using podman
build:
    podman run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp docker.io/espressif/idf:v4.4.6 idf.py build

# Flashes the image using esptool
flash port=default_port:
    esptool.py --port {{port}} -b 460800 --before default_reset --after hard_reset --chip esp32s3  write_flash --flash_mode dio --flash_size detect --flash_freq 80m 0x0 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0x10000 build/cardputer.bin

# Build and then flash
build_flash: build flash
