// SPDX-License-Identifier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#include "../wifi.h"
#include "../pci.h"
#include "../base.h"
#include "../core.h"
#include "reg.h"
#include "def.h"
#include "fw.h"
#include "../rtl8723com/fw_common.h"

static bool _rtl8723e_check_fw_read_last_h2c(struct ieee80211_hw *hw,
					     u8 boxnum)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 val_hmetfr, val_mcutst_1;
	bool result = false;

	val_hmetfr = rtl_read_byte(rtlpriv, REG_HMETFR);
	val_mcutst_1 = rtl_read_byte(rtlpriv, (REG_MCUTST_1 + boxnum));

	if (((val_hmetfr >> boxnum) & BIT(0)) == 0 && val_mcutst_1 == 0)
		result = true;
	return result;
}

static void _rtl8723e_fill_h2c_command(struct ieee80211_hw *hw, u8 element_id,
				       u32 cmd_len, u8 *cmdbuffer)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 boxnum;
	u16 box_reg = 0, box_extreg = 0;
	u8 u1b_tmp;
	bool isfw_read = false;
	u8 buf_index = 0;
	bool bwrite_sucess = false;
	u8 wait_h2c_limmit = 100;
	u8 wait_writeh2c_limmit = 100;
	u8 boxcontent[4], boxextcontent[2];
	u32 h2c_waitcounter = 0;
	unsigned long flag;
	u8 idx;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "come in\n");

	while (true) {
		spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
		if (rtlhal->h2c_setinprogress) {
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"H2C set in progress! Wait to set..element_id(%d).\n",
				element_id);

			while (rtlhal->h2c_setinprogress) {
				spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock,
						       flag);
				h2c_waitcounter++;
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Wait 100 us (%d times)...\n",
					h2c_waitcounter);
				udelay(100);

				if (h2c_waitcounter > 1000)
					return;
				spin_lock_irqsave(&rtlpriv->locks.h2c_lock,
						  flag);
			}
			spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);
		} else {
			rtlhal->h2c_setinprogress = true;
			spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);
			break;
		}
	}

	while (!bwrite_sucess) {
		wait_writeh2c_limmit--;
		if (wait_writeh2c_limmit == 0) {
			pr_err("Write H2C fail because no trigger for FW INT!\n");
			break;
		}

		boxnum = rtlhal->last_hmeboxnum;
		switch (boxnum) {
		case 0:
			box_reg = REG_HMEBOX_0;
			box_extreg = REG_HMEBOX_EXT_0;
			break;
		case 1:
			box_reg = REG_HMEBOX_1;
			box_extreg = REG_HMEBOX_EXT_1;
			break;
		case 2:
			box_reg = REG_HMEBOX_2;
			box_extreg = REG_HMEBOX_EXT_2;
			break;
		case 3:
			box_reg = REG_HMEBOX_3;
			box_extreg = REG_HMEBOX_EXT_3;
			break;
		default:
			pr_err("switch case %#x not processed\n",
			       boxnum);
			break;
		}

		isfw_read = _rtl8723e_check_fw_read_last_h2c(hw, boxnum);
		while (!isfw_read) {

			wait_h2c_limmit--;
			if (wait_h2c_limmit == 0) {
				rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
					"Waiting too long for FW read clear HMEBox(%d)!\n",
					boxnum);
				break;
			}

			udelay(10);

			isfw_read = _rtl8723e_check_fw_read_last_h2c(hw,
								boxnum);
			u1b_tmp = rtl_read_byte(rtlpriv, 0x1BF);
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Waiting for FW read clear HMEBox(%d)!!! 0x1BF = %2x\n",
				boxnum, u1b_tmp);
		}

		if (!isfw_read) {
			rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
				"Write H2C register BOX[%d] fail!!!!! Fw do not read.\n",
				boxnum);
			break;
		}

		memset(boxcontent, 0, sizeof(boxcontent));
		memset(boxextcontent, 0, sizeof(boxextcontent));
		boxcontent[0] = element_id;
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"Write element_id box_reg(%4x) = %2x\n",
			box_reg, element_id);

		switch (cmd_len) {
		case 1:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 1);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 2:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 2);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 3:
			boxcontent[0] &= ~(BIT(7));
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index, 3);

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 4:
			boxcontent[0] |= (BIT(7));
			memcpy((u8 *)(boxextcontent),
			       cmdbuffer + buf_index, 2);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index + 2, 2);

			for (idx = 0; idx < 2; idx++) {
				rtl_write_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			}

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		case 5:
			boxcontent[0] |= (BIT(7));
			memcpy((u8 *)(boxextcontent),
			       cmdbuffer + buf_index, 2);
			memcpy((u8 *)(boxcontent) + 1,
			       cmdbuffer + buf_index + 2, 3);

			for (idx = 0; idx < 2; idx++) {
				rtl_write_byte(rtlpriv, box_extreg + idx,
					       boxextcontent[idx]);
			}

			for (idx = 0; idx < 4; idx++) {
				rtl_write_byte(rtlpriv, box_reg + idx,
					       boxcontent[idx]);
			}
			break;
		default:
			pr_err("switch case %#x not processed\n",
			       cmd_len);
			break;
		}

		bwrite_sucess = true;

		rtlhal->last_hmeboxnum = boxnum + 1;
		if (rtlhal->last_hmeboxnum == 4)
			rtlhal->last_hmeboxnum = 0;

		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD,
			"pHalData->last_hmeboxnum  = %d\n",
			rtlhal->last_hmeboxnum);
	}

	spin_lock_irqsave(&rtlpriv->locks.h2c_lock, flag);
	rtlhal->h2c_setinprogress = false;
	spin_unlock_irqrestore(&rtlpriv->locks.h2c_lock, flag);

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "go out\n");
}

void rtl8723e_fill_h2c_cmd(struct ieee80211_hw *hw,
			   u8 element_id, u32 cmd_len, u8 *cmdbuffer)
{
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 tmp_cmdbuf[2];

	if (!rtlhal->fw_ready) {
		WARN_ONCE(true,
			  "rtl8723ae: error H2C cmd because of Fw download fail!!!\n");
		return;
	}
	memset(tmp_cmdbuf, 0, 8);
	memcpy(tmp_cmdbuf, cmdbuffer, cmd_len);
	_rtl8723e_fill_h2c_command(hw, element_id, cmd_len,
				   (u8 *)&tmp_cmdbuf);
}

void rtl8723e_set_fw_pwrmode_cmd(struct ieee80211_hw *hw, u8 mode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1_h2c_set_pwrmode[3] = { 0 };
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "FW LPS mode = %d\n", mode);

	SET_H2CCMD_PWRMODE_PARM_MODE(u1_h2c_set_pwrmode, mode);
	SET_H2CCMD_PWRMODE_PARM_SMART_PS(u1_h2c_set_pwrmode,
		(rtlpriv->mac80211.p2p) ? ppsc->smart_ps : 1);
	SET_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME(u1_h2c_set_pwrmode,
					      ppsc->reg_max_lps_awakeintvl);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl8723e_set_fw_rsvdpagepkt(): u1_h2c_set_pwrmode\n",
		      u1_h2c_set_pwrmode, 3);
	rtl8723e_fill_h2c_cmd(hw, H2C_SETPWRMODE, 3, u1_h2c_set_pwrmode);
}

#define BEACON_PG		0 /* ->1 */
#define PSPOLL_PG		2
#define NULL_PG			3
#define PROBERSP_PG		4 /* ->5 */

#define TOTAL_RESERVED_PKT_LEN	768

static u8 reserved_page_packet[TOTAL_RESERVED_PKT_LEN] = {
	/* page 0 beacon */
	0x80, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x50, 0x08,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x64, 0x00, 0x00, 0x04, 0x00, 0x0C, 0x6C, 0x69,
	0x6E, 0x6B, 0x73, 0x79, 0x73, 0x5F, 0x77, 0x6C,
	0x61, 0x6E, 0x01, 0x04, 0x82, 0x84, 0x8B, 0x96,
	0x03, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x2A,
	0x01, 0x00, 0x32, 0x08, 0x24, 0x30, 0x48, 0x6C,
	0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C, 0x18,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3D, 0x00, 0xDD, 0x06, 0x00, 0xE0, 0x4C, 0x02,
	0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 1 beacon */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x10, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 2  ps-poll */
	0xA4, 0x10, 0x01, 0xC0, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 3  null */
	0x48, 0x01, 0x00, 0x00, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x72, 0x00, 0x20, 0x8C, 0x00, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
	0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 4  probe_resp */
	0x50, 0x00, 0x00, 0x00, 0x00, 0x40, 0x10, 0x10,
	0x00, 0x03, 0x00, 0xE0, 0x4C, 0x76, 0x00, 0x42,
	0x00, 0x40, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00,
	0x9E, 0x46, 0x15, 0x32, 0x27, 0xF2, 0x2D, 0x00,
	0x64, 0x00, 0x00, 0x04, 0x00, 0x0C, 0x6C, 0x69,
	0x6E, 0x6B, 0x73, 0x79, 0x73, 0x5F, 0x77, 0x6C,
	0x61, 0x6E, 0x01, 0x04, 0x82, 0x84, 0x8B, 0x96,
	0x03, 0x01, 0x01, 0x06, 0x02, 0x00, 0x00, 0x2A,
	0x01, 0x00, 0x32, 0x08, 0x24, 0x30, 0x48, 0x6C,
	0x0C, 0x12, 0x18, 0x60, 0x2D, 0x1A, 0x6C, 0x18,
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x3D, 0x00, 0xDD, 0x06, 0x00, 0xE0, 0x4C, 0x02,
	0x01, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	/* page 5  probe_resp */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void rtl8723e_set_fw_rsvdpagepkt(struct ieee80211_hw *hw, bool b_dl_finished)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct sk_buff *skb = NULL;
	u32 totalpacketlen;
	bool rtstatus;
	u8 u1rsvdpageloc[3] = { 0 };
	bool b_dlok = false;
	u8 *beacon;
	u8 *p_pspoll;
	u8 *nullfunc;
	u8 *p_probersp;

	/*---------------------------------------------------------
	 *			(1) beacon
	 *---------------------------------------------------------
	 */
	beacon = &reserved_page_packet[BEACON_PG * 128];
	SET_80211_HDR_ADDRESS2(beacon, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(beacon, mac->bssid);

	/*-------------------------------------------------------
	 *			(2) ps-poll
	 *--------------------------------------------------------
	 */
	p_pspoll = &reserved_page_packet[PSPOLL_PG * 128];
	SET_80211_PS_POLL_AID(p_pspoll, (mac->assoc_id | 0xc000));
	SET_80211_PS_POLL_BSSID(p_pspoll, mac->bssid);
	SET_80211_PS_POLL_TA(p_pspoll, mac->mac_addr);

	SET_H2CCMD_RSVDPAGE_LOC_PSPOLL(u1rsvdpageloc, PSPOLL_PG);

	/*--------------------------------------------------------
	 *			(3) null data
	 *---------------------------------------------------------
	 */
	nullfunc = &reserved_page_packet[NULL_PG * 128];
	SET_80211_HDR_ADDRESS1(nullfunc, mac->bssid);
	SET_80211_HDR_ADDRESS2(nullfunc, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(nullfunc, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_NULL_DATA(u1rsvdpageloc, NULL_PG);

	/*---------------------------------------------------------
	 *			(4) probe response
	 *----------------------------------------------------------
	 */
	p_probersp = &reserved_page_packet[PROBERSP_PG * 128];
	SET_80211_HDR_ADDRESS1(p_probersp, mac->bssid);
	SET_80211_HDR_ADDRESS2(p_probersp, mac->mac_addr);
	SET_80211_HDR_ADDRESS3(p_probersp, mac->bssid);

	SET_H2CCMD_RSVDPAGE_LOC_PROBE_RSP(u1rsvdpageloc, PROBERSP_PG);

	totalpacketlen = TOTAL_RESERVED_PKT_LEN;

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_LOUD,
		      "rtl8723e_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      &reserved_page_packet[0], totalpacketlen);
	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl8723e_set_fw_rsvdpagepkt(): HW_VAR_SET_TX_CMD: ALL\n",
		      u1rsvdpageloc, 3);

	skb = dev_alloc_skb(totalpacketlen);
	if (!skb)
		return;
	skb_put_data(skb, &reserved_page_packet, totalpacketlen);

	rtstatus = rtl_cmd_send_packet(hw, skb);

	if (rtstatus)
		b_dlok = true;

	if (b_dlok) {
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Set RSVD page location to Fw.\n");
		RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
			      "H2C_RSVDPAGE:\n",
			      u1rsvdpageloc, 3);
		rtl8723e_fill_h2c_cmd(hw, H2C_RSVDPAGE,
				      sizeof(u1rsvdpageloc), u1rsvdpageloc);
	} else
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set RSVD page location to Fw FAIL!!!!!!.\n");
}

void rtl8723e_set_fw_joinbss_report_cmd(struct ieee80211_hw *hw, u8 mstatus)
{
	u8 u1_joinbssrpt_parm[1] = { 0 };

	SET_H2CCMD_JOINBSSRPT_PARM_OPMODE(u1_joinbssrpt_parm, mstatus);

	rtl8723e_fill_h2c_cmd(hw, H2C_JOINBSSRPT, 1, u1_joinbssrpt_parm);
}

static void rtl8723e_set_p2p_ctw_period_cmd(struct ieee80211_hw *hw,
					    u8 ctwindow)
{
	u8 u1_ctwindow_period[1] = { ctwindow};

	rtl8723e_fill_h2c_cmd(hw, H2C_P2P_PS_CTW_CMD, 1, u1_ctwindow_period);

}

void rtl8723e_set_p2p_ps_offload_cmd(struct ieee80211_hw *hw, u8 p2p_ps_state)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_ps_ctl *rtlps = rtl_psc(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_p2p_ps_info *p2pinfo = &(rtlps->p2p_ps_info);
	struct p2p_ps_offload_t *p2p_ps_offload = &rtlhal->p2p_ps_offload;
	u8	i;
	u16	ctwindow;
	u32	start_time, tsf_low;

	switch (p2p_ps_state) {
	case P2P_PS_DISABLE:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_DISABLE\n");
		memset(p2p_ps_offload, 0, sizeof(*p2p_ps_offload));
		break;
	case P2P_PS_ENABLE:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_ENABLE\n");
		/* update CTWindow value. */
		if (p2pinfo->ctwindow > 0) {
			p2p_ps_offload->ctwindow_en = 1;
			ctwindow = p2pinfo->ctwindow;
			rtl8723e_set_p2p_ctw_period_cmd(hw, ctwindow);
		}

		/* hw only support 2 set of NoA */
		for (i = 0 ; i < p2pinfo->noa_num ; i++) {
			/* To control the register setting for which NOA*/
			rtl_write_byte(rtlpriv, 0x5cf, (i << 4));
			if (i == 0)
				p2p_ps_offload->noa0_en = 1;
			else
				p2p_ps_offload->noa1_en = 1;

			/* config P2P NoA Descriptor Register */
			rtl_write_dword(rtlpriv, 0x5E0,
					p2pinfo->noa_duration[i]);
			rtl_write_dword(rtlpriv, 0x5E4,
					p2pinfo->noa_interval[i]);

			/*Get Current TSF value */
			tsf_low = rtl_read_dword(rtlpriv, REG_TSFTR);

			start_time = p2pinfo->noa_start_time[i];
			if (p2pinfo->noa_count_type[i] != 1) {
				while (start_time <=
					(tsf_low+(50*1024))) {
					start_time +=
						p2pinfo->noa_interval[i];
					if (p2pinfo->noa_count_type[i] != 255)
						p2pinfo->noa_count_type[i]--;
				}
			}
			rtl_write_dword(rtlpriv, 0x5E8, start_time);
			rtl_write_dword(rtlpriv, 0x5EC,
				p2pinfo->noa_count_type[i]);

		}

		if ((p2pinfo->opp_ps == 1) || (p2pinfo->noa_num > 0)) {
			/* rst p2p circuit */
			rtl_write_byte(rtlpriv, REG_DUAL_TSF_RST, BIT(4));

			p2p_ps_offload->offload_en = 1;

			if (P2P_ROLE_GO == rtlpriv->mac80211.p2p) {
				p2p_ps_offload->role = 1;
				p2p_ps_offload->allstasleep = 0;
			} else {
				p2p_ps_offload->role = 0;
			}

			p2p_ps_offload->discovery = 0;
		}
		break;
	case P2P_PS_SCAN:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_SCAN\n");
		p2p_ps_offload->discovery = 1;
		break;
	case P2P_PS_SCAN_DONE:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "P2P_PS_SCAN_DONE\n");
		p2p_ps_offload->discovery = 0;
		p2pinfo->p2p_ps_state = P2P_PS_ENABLE;
		break;
	default:
		break;
	}

	rtl8723e_fill_h2c_cmd(hw, H2C_P2P_PS_OFFLOAD, 1, (u8 *)p2p_ps_offload);

}
