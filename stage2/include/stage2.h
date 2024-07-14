#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <cpuid.h>

#define __cdecl     __attribute__((__cdecl__))
#define __packed    __attribute__((__packed__))

#include "disk.h"
#include "tty.h"
#include "memory.h"
