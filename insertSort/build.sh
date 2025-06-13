#!/bin/sh

set -xe

mkdir -p build

cc -Wall -Wextra -o build/insertion main.c
