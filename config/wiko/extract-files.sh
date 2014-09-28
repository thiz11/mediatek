#!/bin/sh

VENDOR=mediatek
DEVICE=wiko
PROG=$(dirname `realpath $0`)
BASE=$ANDROID_TOP/vendor/$VENDOR/$DEVICE/proprietary

echo "Pulling $DEVICE files..."
for FILE in `cat $PROG/proprietary-files.txt | grep -v ^# | grep -v ^$`; do
DIR=`dirname $FILE`
#    if [ ! -d $BASE/$DIR ]; then
mkdir -p $BASE/$DIR
#    fi

# DUMP=/repos/MTK6592/dump201403
# cp $DUMP/$FILE $BASE/$FILE
adb pull /system/$FILE $BASE/$FILE

done

# some extra stuff
# cp $DUMP/lib/hw/audio_policy.default.so $BASE/lib/hw/audio_policy.mt6592.so
# cp $DUMP/lib/libaudio.primary.default.so $BASE/lib/hw/audio.primary.mt6592.so
mkdir -p $BASE/lib/hw
adb pull /system/lib/hw/audio_policy.default.so $BASE/lib/hw/audio_policy.mt6592.so
adb pull /system/lib/libaudio.primary.default.so $BASE/lib/hw/audio.primary.mt6592.so

#./setup-makefiles.sh
