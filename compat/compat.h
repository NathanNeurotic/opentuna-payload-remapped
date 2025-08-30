#ifndef __COMPAT_H__
#define __COMPAT_H__

// This file provides compatibility shims for functions that are no longer
// available in the modern ps2sdk.

// These functions were used to disable ps2sdk patches to save memory.
// We provide empty stubs for them to allow the code to compile.
// It is assumed that the modern ps2sdk does not need these patches to be
// disabled in this way, or that they are disabled by default.
void DISABLE_PATCHED_FUNCTIONS(void);
void DISABLE_EXTRA_TIMERS_FUNCTIONS(void);

#endif // __COMPAT_H__
