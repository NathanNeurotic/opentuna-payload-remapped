#ifndef COMPAT_COMPAT_H
#define COMPAT_COMPAT_H

/* Suppress pedantic warnings from ps2sdk headers that use large enums. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#include <kernel.h>
#pragma GCC diagnostic pop

#endif /* COMPAT_COMPAT_H */
