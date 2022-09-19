/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 */

#ifndef __IX4_200D_H
#define __IX4_200D_H

#define IX4_200D_OE_LOW		0xefff0f7f
#define IX4_200D_OE_HIGH		0xfffec003
#define IX4_200D_OE_VAL_LOW		0x1000d080
#define IX4_200D_OE_VAL_HIGH		0x0001000c

/* PHY related */
#define MV88E1116_LED_FCTRL_REG		10
#define MV88E1116_CPRSP_CR3_REG		21
#define MV88E1116_MAC_CTRL_REG		21
#define MV88E1116_PGADR_REG		22
#define MV88E1116_RGMII_TXTM_CTRL	(1 << 4)
#define MV88E1116_RGMII_RXTM_CTRL	(1 << 5)

#endif /* __IX4_200D_H */
