MODULE := engines/immortal

MODULE_OBJS :=  \
	console.o   \
	detection.o \
	immortal.o

MODULE_DIRS += \
	engines/immortal

# This module can be built as a plugin
ifeq ($(ENABLE_IMMORTAL), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
