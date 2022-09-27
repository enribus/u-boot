// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Guillaume Girou <git@modoki.ovh>
 */

#include <common.h>
#include <init.h>
#include <miiphy.h>
#include <net.h>
#include <asm/global_data.h>
#include <asm/mach-types.h>
#include <asm/arch/cpu.h>
#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include "ix4-200d.h"

DECLARE_GLOBAL_DATA_PTR;

int board_early_init_f(void)
{
	/*
	 * default gpio configuration
	 * There are maximum 64 gpios controlled through 2 sets of registers
	 * the  below configuration configures mainly initial LED status
	 */
	mvebu_config_gpio(IX4_200D_OE_VAL_LOW,
			  IX4_200D_OE_VAL_HIGH,
			  IX4_200D_OE_LOW, IX4_200D_OE_HIGH);

	/* Multi-Purpose Pins Functionality configuration */
	static const u32 kwmpp_config[] = {
		// IX4_200D_MPP0_7                      0x01111111
		MPP0_NF_IO2,
		MPP1_NF_IO3,
		MPP2_NF_IO4,
		MPP3_NF_IO5,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP6_SYSRST_OUTn,
		MPP7_GPO,
		// IX4_200D_MPP8_15                     0x00003311
		MPP8_TW_SDA,
		MPP9_TW_SCK,
		MPP10_UART0_TXD,
		MPP11_UART0_RXD,
		// MPP12_SD_CLK, // SPI_MOSI --> 74HC164D
		// MPP13_SD_CMD, // SPI_SCK --> 74HC164D
		// MPP14_SD_D0, // SPI_CS  --> 74HC164D
		MPP12_GPO,
		MPP13_GPIO,
		MPP14_GPIO,
		MPP15_GPIO, // LCM_BUS_RS
		// IX4_200D_MPP16_23                    0x33331140
		MPP16_GPIO, // select-button
		MPP17_SATA0_PRESENTn,
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		MPP20_GE1_0,
		MPP21_GE1_1,
		MPP22_GE1_2,
		MPP23_GE1_3,
		// IX4_200D_MPP24_31                    0x33003333
		MPP24_GE1_4,
		MPP25_GE1_5,
		MPP26_GE1_6,
		MPP27_GE1_7,
		MPP28_GPIO,
		MPP29_GPIO, // reset-button
		MPP30_GE1_10,
		MPP31_GE1_11,
		// IX4_200D_MPP32_39                    0x00000033
		MPP32_GE1_12,
		MPP33_GE1_13,
		MPP34_GPIO, // LCM_BUS_A0
		MPP35_GPIO, // LCM_BUS_CS
		MPP36_GPIO, // LCM_DATA_D0
		MPP37_GPIO, // LCM_DATA_D1
		MPP38_GPIO, // LCM_DATA_D2
		MPP39_GPIO, // LCM_DATA_D3
		// IX4_200D_MPP40_47                    0x00000000
		MPP40_GPIO, // LCM_DATA_D4
		MPP41_GPIO, // LCM_DATA_D5
		MPP42_GPIO, // LCM_DATA_D6
		MPP43_GPIO, // LCM_DATA_D7
		MPP44_GPIO, // LCM_BUS_RW
		MPP45_GPIO, // LCM_BUS_E
		MPP46_GPIO,
		MPP47_GPIO, // scroll-button
		// IX4_200D_MPP48_55                    0x00000000
		MPP48_GPIO,
		MPP49_GPIO, // power-button
		0
	};
	kirkwood_mpp_conf(kwmpp_config, NULL);
	return 0;
}

int board_init(void)
{
	/*
	 * arch number of board
	 */
	//gd->bd->bi_arch_number = MACH_TYPE_IX4_200D;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = mvebu_sdram_bar(0) + 0x100;

	return 0;
}

#ifdef CONFIG_RESET_PHY_R
/* Configure and enable MV88E1116 PHY */
void mv_phy_88e1116_init(char *name)
{
	u16 reg;
	int phyaddr;

	if (miiphy_set_current_dev(name))
		return;

	/* command to read PHY dev address */
	if (miiphy_read(name, 0xEE, 0xEE, (u16 *) &phyaddr)) {
		printf("Err..%s could not read PHY dev address\n",
			__FUNCTION__);
		return;
	}

	/*
	 * Enable RGMII delay on Tx and Rx for CPU port
	 * Ref: sec 4.7.2 of chip datasheet
	 */
	miiphy_write(name, phyaddr, MV88E1116_PGADR_REG, 2);
	miiphy_read(name, phyaddr, MV88E1116_MAC_CTRL_REG, &reg);
	reg |= (MV88E1116_RGMII_RXTM_CTRL | MV88E1116_RGMII_TXTM_CTRL);
	miiphy_write(name, phyaddr, MV88E1116_MAC_CTRL_REG, reg);
	miiphy_write(name, phyaddr, MV88E1116_PGADR_REG, 0);

	/* reset the phy */
	miiphy_reset(name, phyaddr);

	printf("88E1116 Initialized on %s\n", name);
}

void reset_phy(void)
{
	/* configure and initialize both PHY's */
	mv_phy_88e1116_init("ethernet-controller@72000");
	mv_phy_88e1116_init("ethernet-controller@76000");
}
#endif /* CONFIG_RESET_PHY_R */
