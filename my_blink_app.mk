MY_BLINK_APP_VERSION = 1.0
MY_BLINK_APP_SITE = $(TOPDIR)/../my_blink_app
MY_BLINK_APP_SITE_METHOD = local
MY_BLINK_APP_DEPENDENCIES = gpiod

define MY_BLINK_APP_BUILD_CMDs
	$(MAKE) -C $(@D)
endef

define MY_BLINK_APP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/blink $(TARGET_DIR)/usr/bin/blink
endef

$(eval $(generic-package))