#!/bin/sh
echo 268435456 > /sys/block/zram0/disksize
/system/xbin/mkswap /dev/block/mmcblk1p2
/system/xbin/swapon /dev/block/mmcblk1p2
