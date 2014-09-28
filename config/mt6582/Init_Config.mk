#Android forbiden developer use product level variables(PRODUCT_XXX, TARGET_XXX, BOARD_XXX) in Android.mk
#Because AndroidBoard.mk include by build/target/board/Android.mk
#split from AndroidBoard.mk for PRODUCT level variables definition.
#use MTK_ROOT_CONFIG_OUT instead of MTK_ROOT_CONFIG_OUT

TARGET_PROVIDES_INIT_RC := true

PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/mtk-kpd.kl:system/usr/keylayout/mtk-kpd.kl \
                      $(MTK_ROOT_CONFIG_OUT)/init.rc:root/init.rc \
                      $(MTK_ROOT_CONFIG_OUT)/init.usb.rc:root/init.usb.rc \
                      $(MTK_ROOT_CONFIG_OUT)/init.xlog.rc:root/init.xlog.rc \
                      $(MTK_ROOT_CONFIG_OUT)/player.cfg:system/etc/player.cfg \
                      $(MTK_ROOT_CONFIG_OUT)/media_codecs.xml:system/etc/media_codecs.xml \
                      $(MTK_ROOT_CONFIG_OUT)/mtk_omx_core.cfg:system/etc/mtk_omx_core.cfg \
                      $(MTK_ROOT_CONFIG_OUT)/audio_policy.conf:system/etc/audio_policy.conf \
                      $(MTK_ROOT_CONFIG_OUT)/init.modem.rc:root/init.modem.rc \
                      $(MTK_ROOT_CONFIG_OUT)/meta_init.rc:root/meta_init.rc \
                      $(MTK_ROOT_CONFIG_OUT)/meta_init.modem.rc:root/meta_init.modem.rc \
                      $(MTK_ROOT_CONFIG_OUT)/factory_init.rc:root/factory_init.rc \
                      $(MTK_ROOT_CONFIG_OUT)/init.protect.rc:root/init.protect.rc \
                      $(MTK_ROOT_CONFIG_OUT)/ACCDET.kl:system/usr/keylayout/ACCDET.kl \
                      $(MTK_ROOT_CONFIG_OUT)/fstab:root/fstab \
                      $(MTK_ROOT_CONFIG_OUT)/fstab:root/fstab.nand \
                      $(MTK_ROOT_CONFIG_OUT)/fstab:root/fstab.fat.nand \
		      $(MTK_ROOT_CONFIG_OUT)/enableswap.sh:root/enableswap.sh \
                      $(MTK_ROOT_CONFIG_OUT)/recovery.fstab:system/etc/recovery.fstab

ifeq ($(MTK_KERNEL_POWER_OFF_CHARGING),yes)
PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/init.charging.rc:root/init.charging.rc 
endif

ifeq ($(MTK_FAT_ON_NAND),yes)
PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/init.fon.rc:root/init.fon.rc
endif
_init_project_rc := $(MTK_ROOT_CONFIG_OUT)/init.project.rc
ifneq ($(wildcard $(_init_project_rc)),)
PRODUCT_COPY_FILES += $(_init_project_rc):root/init.project.rc
endif

_meta_init_project_rc := $(MTK_ROOT_CONFIG_OUT)/meta_init.project.rc
ifneq ($(wildcard $(_meta_init_project_rc)),)
PRODUCT_COPY_FILES += $(_meta_init_project_rc):root/meta_init.project.rc
endif

_factory_init_project_rc := $(MTK_ROOT_CONFIG_OUT)/factory_init.project.rc
ifneq ($(wildcard $(_factory_init_project_rc)),)
PRODUCT_COPY_FILES += $(_factory_init_project_rc):root/factory_init.project.rc
endif

PRODUCT_COPY_FILES += $(strip \
                        $(foreach file,$(wildcard $(MTK_ROOT_CONFIG_OUT)/*.xml), \
                          $(addprefix $(MTK_ROOT_CONFIG_OUT)/$(notdir $(file)):system/etc/permissions/,$(notdir $(file))) \
                         ) \
                       )

ifeq ($(strip $(HAVE_SRSAUDIOEFFECT_FEATURE)),yes)
  PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/srs_processing.cfg:system/data/srs_processing.cfg
endif
ifeq ($(MTK_SHARED_SDCARD),yes)
ifeq ($(MTK_2SDCARD_SWAP),yes)
  PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/init.ssd_nomuser.rc:root/init.ssd_nomuser.rc
else
  PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/init.ssd.rc:root/init.ssd.rc
endif
else
  PRODUCT_COPY_FILES += $(MTK_ROOT_CONFIG_OUT)/init.no_ssd.rc:root/init.no_ssd.rc
endif
##### INSTALL ht120.mtc ##########

_ht120_mtc := $(MTK_ROOT_CONFIG_OUT)/configs/ht120.mtc
ifneq ($(wildcard $(_ht120_mtc)),)
PRODUCT_COPY_FILES += $(_ht120_mtc):system/etc/.tp/.ht120.mtc
endif

##################################

##### INSTALL thermal.conf ##########

_thermal_conf := $(MTK_ROOT_CONFIG_OUT)/configs/thermal.conf
ifneq ($(wildcard $(_thermal_conf)),)
PRODUCT_COPY_FILES += $(_thermal_conf):system/etc/.tp/thermal.conf
endif

##################################

##### INSTALL thermal.off.conf ##########

_thermal_off_conf := $(MTK_ROOT_CONFIG_OUT)/configs/thermal.off.conf
ifneq ($(wildcard $(_thermal_off_conf)),)
PRODUCT_COPY_FILES += $(_thermal_off_conf):system/etc/.tp/thermal.off.conf
endif

##################################

##### INSTALL throttle.sh ##########

_throttle_sh := $(MTK_ROOT_CONFIG_OUT)/configs/throttle.sh
ifneq ($(wildcard $(_throttle_sh)),)
PRODUCT_COPY_FILES += $(_throttle_sh):system/etc/throttle.sh
endif

##### INSTALL rio_5_compass ##########
_rio_5_compass_cfg := $(MTK_ROOT_CONFIG_OUT)/configs/accel_nvm
ifneq ($(wildcard $(_rio_5_compass_cfg)),)
PRODUCT_COPY_FILES += $(_rio_5_compass_cfg):system/etc/accel_nvm
endif

##### rio5 AAL ###################
ifeq ($(MTK_AAL_SUPPORT),yes)
PRODUCT_COPY_FILES += \
    $(MTK_PATH_PLATFORM)/hardware/aal/inc/cust_labc_map.txt:system/etc/cust_labc_map.txt \
    $(MTK_PATH_PLATFORM)/hardware/aal/inc/mtk_aal_config.txt:system/etc/mtk_aal_config.txt
endif
##################################

##### INSTALL jrdcom ##########
PRODUCT_COPY_FILES += \
	$(TOP)/vendor/jrdcom/etc/rspermtcl.xml:etc/permissions/rspermtcl.xml

PRODUCT_COPY_FILES += \
                  $(TOP)/vendor/jrdcom/libs/libSwypeCore.3.26.92.39261.so:system/lib/libSwypeCore.3.26.92.39261.so \
                  $(TOP)/vendor/jrdcom/libs/libpsrntcl.so:system/lib/libpsrntcl.so \
                  $(TOP)/vendor/jrdcom/libs/libjzlibtcl.so:system/lib/libjzlibtcl.so \
                  $(TOP)/vendor/jrdcom/libs/libsuapp_d_native.so:system/lib/libsuapp_d_native.so \
                  $(TOP)/vendor/jrdcom/libs/libstlport_shared.so:system/lib/libstlport_shared.so

## Added for CR371771 by xiangrui.huang-001 begin
ifeq ($(JRD_CU_SUPPORT),no)
   PRODUCT_COPY_FILES += \
	$(TOP)/vendor/jrdcom/audio/alarms/Band.mp3:system/media/audio/alarms/Band.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Buzzer.mp3:system/media/audio/alarms/Buzzer.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/By.mp3:system/media/audio/alarms/By.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Flute.mp3:system/media/audio/alarms/Flute.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Guitar.mp3:system/media/audio/alarms/Guitar.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Revival.mp3:system/media/audio/alarms/Revival.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Sight.mp3:system/media/audio/alarms/Sight.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Sober.mp3:system/media/audio/alarms/Sober.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Tinkle.mp3:system/media/audio/alarms/Tinkle.mp3 \
	$(TOP)/vendor/jrdcom/audio/alarms/Treat.mp3:system/media/audio/alarms/Treat.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Bell.mp3:system/media/audio/notifications/Bell.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Ceramic.mp3:system/media/audio/notifications/Ceramic.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Digitek.mp3:system/media/audio/notifications/Digitek.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Doorbell.mp3:system/media/audio/notifications/Doorbell.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Drop.mp3:system/media/audio/notifications/Drop.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Mallets.mp3:system/media/audio/notifications/Mallets.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Message7.mp3:system/media/audio/notifications/Message7.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Message10.mp3:system/media/audio/notifications/Message10.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Paillette.mp3:system/media/audio/notifications/Paillette.mp3 \
	$(TOP)/vendor/jrdcom/audio/notifications/Sign_default.mp3:system/media/audio/notifications/Sign_default.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Buoy.mp3:system/media/audio/ringtones/Buoy.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Crunchy_Step.mp3:system/media/audio/ringtones/Crunchy_Step.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Domino.mp3:system/media/audio/ringtones/Domino.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Luminosity.mp3:system/media/audio/ringtones/Luminosity.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Metallic.mp3:system/media/audio/ringtones/Metallic.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/MidTown.mp3:system/media/audio/ringtones/MidTown.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Modern_Funk.mp3:system/media/audio/ringtones/Modern_Funk.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/NeverSimple.mp3:system/media/audio/ringtones/NeverSimple.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/NotN2It.mp3:system/media/audio/ringtones/NotN2It.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Poltergeist.mp3:system/media/audio/ringtones/Poltergeist.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Punky.mp3:system/media/audio/ringtones/Punky.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Reactive.mp3:system/media/audio/ringtones/Reactive.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Rockin_Roll.mp3:system/media/audio/ringtones/Rockin_Roll.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/SlappedUp.mp3:system/media/audio/ringtones/SlappedUp.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/SwingYourBody.mp3:system/media/audio/ringtones/SwingYourBody.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/TonePoems.mp3:system/media/audio/ringtones/TonePoems.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/Trot.mp3:system/media/audio/ringtones/Trot.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/WalkingCat.mp3:system/media/audio/ringtones/WalkingCat.mp3 \
	$(TOP)/vendor/jrdcom/audio/ringtones/X-Ray.mp3:system/media/audio/ringtones/X-Ray.mp3
endif

_rio_5_compass_cfg := $(MTK_ROOT_CONFIG_OUT)/configs/accel_nvm
ifeq ("rio_5","$(TARGET_PRODUCT)")
ifneq ($(wildcard $(_rio_5_compass_cfg)),)
PRODUCT_COPY_FILES += $(_rio_5_compass_cfg):system/etc/accel_nvm
endif
endif

