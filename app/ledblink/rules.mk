LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_DEPS += \
	lib/bio \
	lib/bootargs \
	lib/bootimage \
	lib/cbuf \
	lib/ptable \
	lib/sysparam

MODULE_SRCS += \
	$(LOCAL_DIR)/ledblink.c

include make/module.mk
