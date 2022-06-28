/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2009-2014
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Guillaume Girou <git@modoki.ovh>
 */

#ifndef _CONFIG_IX4_200D_H
#define _CONFIG_IX4_200D_H

#include "mv-common.h"

/*
 *  Environment variables configurations
 */
/*
 * max 4k env size is enough, but in case of nand
 * it has to be rounded to sector size
 */
/*
 * Environment is right behind U-Boot in flash. Make sure U-Boot
 * doesn't grow into the environment area.
 */
#define CONFIG_BOARD_SIZE_LIMIT		CONFIG_ENV_OFFSET

/*
 * Default environment variables
 */

#define CONFIG_EXTRA_ENV_SETTINGS	"x_bootargs=console"	\
	"=ttyS0,115200 mtdparts=${mtdparts}\0"	\
	"x_bootcmd_kernel=ext4load usb 0:1 ${loadaddr} /boot/uImage\0" \
	"x_bootcmd_usb=usb start; ext4load usb 0:1 ${loadaddr} uEnv.txt; env import -t ${loadaddr} ${filesize}\0" \
	"x_bootargs_root=root=/dev/disk/by-path/platform-f1050000.ehci-usb-0:1.2:1.0-scsi-0:0:0:0-part1 rw rootfstype=ext2\0" \
	"mtdparts="CONFIG_MTDPARTS_DEFAULT"\0"

/*
 * Ethernet Driver configuration
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_MVGBE_PORTS	{1, 1}	/* enable both ports */
#define CONFIG_PHY_BASE_ADR	0
#endif /* CONFIG_CMD_NET */

/*
 * SATA driver configuration
 */
#ifdef CONFIG_SATA
#define CONFIG_LBA48
#endif /* CONFIG_SATA */

#endif /* _CONFIG_IX4_200D_H */
