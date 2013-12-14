/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#define _HAL_INTF_C_
#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>

#include <hal_intf.h>

#include <usb_hal.h>

void rtw_hal_chip_configure(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.intf_chip_configure)
		padapter->HalFunc.intf_chip_configure(padapter);
}

void rtw_hal_read_chip_info(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.read_adapter_info)
		padapter->HalFunc.read_adapter_info(padapter);
}

void rtw_hal_read_chip_version(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.read_chip_version)
		padapter->HalFunc.read_chip_version(padapter);
}

void rtw_hal_def_value_init(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.init_default_value)
		padapter->HalFunc.init_default_value(padapter);
}
void	rtw_hal_free_data(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.free_hal_data)
		padapter->HalFunc.free_hal_data(padapter);
}
void	rtw_hal_dm_init(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.dm_init)
		padapter->HalFunc.dm_init(padapter);
}
void rtw_hal_dm_deinit(struct rtw_adapter *padapter)
{
	// cancel dm  timer
	if(padapter->HalFunc.dm_deinit)
		padapter->HalFunc.dm_deinit(padapter);
}
void	rtw_hal_sw_led_init(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.InitSwLeds)
		padapter->HalFunc.InitSwLeds(padapter);
}

void rtw_hal_sw_led_deinit(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.DeInitSwLeds)
		padapter->HalFunc.DeInitSwLeds(padapter);
}

u32 rtw_hal_power_on(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.hal_power_on)
		return padapter->HalFunc.hal_power_on(padapter);
	return _FAIL;
}


uint	 rtw_hal_init(struct rtw_adapter *padapter)
{
	uint	status = _SUCCESS;

	padapter->hw_init_completed=_FALSE;

	status = padapter->HalFunc.hal_init(padapter);

	if(status == _SUCCESS){
		padapter->hw_init_completed = true;

		if (padapter->registrypriv.notch_filter == 1)
			rtw_hal_notch_filter(padapter, 1);

		rtw_hal_reset_security_engine(padapter);
	}
	else{
		padapter->hw_init_completed = _FALSE;
		DBG_8723A("rtw_hal_init: hal__init fail\n");
	}

	RT_TRACE(_module_hal_init_c_,_drv_err_,("-rtl871x_hal_init:status=0x%x\n",status));

	return status;
}

uint rtw_hal_deinit(struct rtw_adapter *padapter)
{
	uint	status = _SUCCESS;

_func_enter_;

	status = padapter->HalFunc.hal_deinit(padapter);

	if(status == _SUCCESS){
		padapter->hw_init_completed = _FALSE;
	}
	else
	{
		DBG_8723A("\n rtw_hal_deinit: hal_init fail\n");
	}

_func_exit_;

	return status;
}

void rtw_hal_set_hwreg(struct rtw_adapter *padapter, u8 variable, u8 *val)
{
	if (padapter->HalFunc.SetHwRegHandler)
		padapter->HalFunc.SetHwRegHandler(padapter, variable, val);
}

void rtw_hal_get_hwreg(struct rtw_adapter *padapter, u8 variable, u8 *val)
{
	if (padapter->HalFunc.GetHwRegHandler)
		padapter->HalFunc.GetHwRegHandler(padapter, variable, val);
}

u8 rtw_hal_set_def_var(struct rtw_adapter *padapter, HAL_DEF_VARIABLE eVariable, void * pValue)
{
	if(padapter->HalFunc.SetHalDefVarHandler)
		return padapter->HalFunc.SetHalDefVarHandler(padapter,eVariable,pValue);
	return _FAIL;
}
u8 rtw_hal_get_def_var(struct rtw_adapter *padapter, HAL_DEF_VARIABLE eVariable, void * pValue)
{
	if(padapter->HalFunc.GetHalDefVarHandler)
		return padapter->HalFunc.GetHalDefVarHandler(padapter,eVariable,pValue);
	return _FAIL;
}

void rtw_hal_set_odm_var(struct rtw_adapter *padapter, HAL_ODM_VARIABLE eVariable, void * pValue1,bool bSet)
{
	if(padapter->HalFunc.SetHalODMVarHandler)
		padapter->HalFunc.SetHalODMVarHandler(padapter,eVariable,pValue1,bSet);
}
void	rtw_hal_get_odm_var(struct rtw_adapter *padapter, HAL_ODM_VARIABLE eVariable, void * pValue1,bool bSet)
{
	if(padapter->HalFunc.GetHalODMVarHandler)
		padapter->HalFunc.GetHalODMVarHandler(padapter,eVariable,pValue1,bSet);
}

void rtw_hal_enable_interrupt(struct rtw_adapter *padapter)
{
	if (padapter->HalFunc.enable_interrupt)
		padapter->HalFunc.enable_interrupt(padapter);
	else
		DBG_8723A("%s: HalFunc.enable_interrupt is NULL!\n", __FUNCTION__);

}
void rtw_hal_disable_interrupt(struct rtw_adapter *padapter)
{
	if (padapter->HalFunc.disable_interrupt)
		padapter->HalFunc.disable_interrupt(padapter);
	else
		DBG_8723A("%s: HalFunc.disable_interrupt is NULL!\n", __FUNCTION__);

}


u32	rtw_hal_inirp_init(struct rtw_adapter *padapter)
{
	u32 rst = _FAIL;
	if(padapter->HalFunc.inirp_init)
		rst = padapter->HalFunc.inirp_init(padapter);
	else
		DBG_8723A(" %s HalFunc.inirp_init is NULL!!!\n",__FUNCTION__);
	return rst;
}

u32	rtw_hal_inirp_deinit(struct rtw_adapter *padapter)
{

	if(padapter->HalFunc.inirp_deinit)
		return padapter->HalFunc.inirp_deinit(padapter);

	return _FAIL;

}

u8	rtw_hal_intf_ps_func(struct rtw_adapter *padapter,HAL_INTF_PS_FUNC efunc_id, u8* val)
{
	if(padapter->HalFunc.interface_ps_func)
		return padapter->HalFunc.interface_ps_func(padapter,efunc_id,val);
	return _FAIL;
}

s32	rtw_hal_xmitframe_enqueue(struct rtw_adapter *padapter, struct xmit_frame *pxmitframe)
{
	if(padapter->HalFunc.hal_xmitframe_enqueue)
		return padapter->HalFunc.hal_xmitframe_enqueue(padapter, pxmitframe);

	return _FALSE;
}

s32	rtw_hal_xmit(struct rtw_adapter *padapter, struct xmit_frame *pxmitframe)
{
	if(padapter->HalFunc.hal_xmit)
		return padapter->HalFunc.hal_xmit(padapter, pxmitframe);

	return _FALSE;
}

s32	rtw_hal_mgnt_xmit(struct rtw_adapter *padapter, struct xmit_frame *pmgntframe)
{
	s32 ret = _FAIL;
	if(padapter->HalFunc.mgnt_xmit)
		ret = padapter->HalFunc.mgnt_xmit(padapter, pmgntframe);
	return ret;
}

s32	rtw_hal_init_xmit_priv(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.init_xmit_priv != NULL)
		return padapter->HalFunc.init_xmit_priv(padapter);
	return _FAIL;
}
void	rtw_hal_free_xmit_priv(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.free_xmit_priv != NULL)
		padapter->HalFunc.free_xmit_priv(padapter);
}

s32	rtw_hal_init_recv_priv(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.init_recv_priv)
		return padapter->HalFunc.init_recv_priv(padapter);

	return _FAIL;
}
void	rtw_hal_free_recv_priv(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.free_recv_priv)
		padapter->HalFunc.free_recv_priv(padapter);
}

void rtw_hal_update_ra_mask(struct sta_info *psta, u8 rssi_level)
{
	struct rtw_adapter *padapter;
	struct mlme_priv *pmlmepriv;

	if(!psta)
		return;

	padapter = psta->padapter;

	pmlmepriv = &(padapter->mlmepriv);

	if(check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
	{
		add_RATid(padapter, psta, rssi_level);
	}
	else
	{
		if(padapter->HalFunc.UpdateRAMaskHandler)
			padapter->HalFunc.UpdateRAMaskHandler(padapter, psta->mac_id, rssi_level);
	}
}

void	rtw_hal_add_ra_tid(struct rtw_adapter *padapter, u32 bitmap, u8 arg, u8 rssi_level)
{
	if(padapter->HalFunc.Add_RateATid)
		padapter->HalFunc.Add_RateATid(padapter, bitmap, arg, rssi_level);
}

/*	Start specifical interface thread		*/
void	rtw_hal_start_thread(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.run_thread)
		padapter->HalFunc.run_thread(padapter);
}
/*	Start specifical interface thread		*/
void	rtw_hal_stop_thread(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.cancel_thread)
		padapter->HalFunc.cancel_thread(padapter);
}

u32	rtw_hal_read_bbreg(struct rtw_adapter *padapter, u32 RegAddr, u32 BitMask)
{
	u32 data = 0;
	if(padapter->HalFunc.read_bbreg)
		 data = padapter->HalFunc.read_bbreg(padapter, RegAddr, BitMask);
	return data;
}
void	rtw_hal_write_bbreg(struct rtw_adapter *padapter, u32 RegAddr, u32 BitMask, u32 Data)
{
	if(padapter->HalFunc.write_bbreg)
		padapter->HalFunc.write_bbreg(padapter, RegAddr, BitMask, Data);
}

u32	rtw_hal_read_rfreg(struct rtw_adapter *padapter, u32 eRFPath, u32 RegAddr, u32 BitMask)
{
	u32 data = 0;
	if( padapter->HalFunc.read_rfreg)
		data = padapter->HalFunc.read_rfreg(padapter, eRFPath, RegAddr, BitMask);
	return data;
}
void	rtw_hal_write_rfreg(struct rtw_adapter *padapter, u32 eRFPath, u32 RegAddr, u32 BitMask, u32 Data)
{
	if(padapter->HalFunc.write_rfreg)
		padapter->HalFunc.write_rfreg(padapter, eRFPath, RegAddr, BitMask, Data);
}

s32	rtw_hal_interrupt_handler(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.interrupt_handler)
		return padapter->HalFunc.interrupt_handler(padapter);
	return _FAIL;
}

void	rtw_hal_set_bwmode(struct rtw_adapter *padapter, HT_CHANNEL_WIDTH Bandwidth, u8 Offset)
{
	if(padapter->HalFunc.set_bwmode_handler)
		padapter->HalFunc.set_bwmode_handler(padapter, Bandwidth, Offset);
}

void	rtw_hal_set_chan(struct rtw_adapter *padapter, u8 channel)
{
	if(padapter->HalFunc.set_channel_handler)
		padapter->HalFunc.set_channel_handler(padapter, channel);
}

void	rtw_hal_dm_watchdog(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.hal_dm_watchdog)
		padapter->HalFunc.hal_dm_watchdog(padapter);
}

void rtw_hal_bcn_related_reg_setting(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.SetBeaconRelatedRegistersHandler)
		padapter->HalFunc.SetBeaconRelatedRegistersHandler(padapter);
}


#ifdef CONFIG_ANTENNA_DIVERSITY
u8	rtw_hal_antdiv_before_linked(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.AntDivBeforeLinkHandler)
		return padapter->HalFunc.AntDivBeforeLinkHandler(padapter);
	return _FALSE;
}
void	rtw_hal_antdiv_rssi_compared(struct rtw_adapter *padapter, WLAN_BSSID_EX *dst, WLAN_BSSID_EX *src)
{
	if(padapter->HalFunc.AntDivCompareHandler)
		padapter->HalFunc.AntDivCompareHandler(padapter, dst, src);
}
#endif

#ifdef CONFIG_HOSTAPD_MLME
s32	rtw_hal_hostap_mgnt_xmit_entry(struct rtw_adapter *padapter, _pkt *pkt)
{
	if(padapter->HalFunc.hostap_mgnt_xmit_entry)
		return padapter->HalFunc.hostap_mgnt_xmit_entry(padapter, pkt);
	return _FAIL;
}
#endif //CONFIG_HOSTAPD_MLME

#ifdef DBG_CONFIG_ERROR_DETECT
void	rtw_hal_sreset_init(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.sreset_init_value)
		padapter->HalFunc.sreset_init_value(padapter);
}
void rtw_hal_sreset_reset(struct rtw_adapter *padapter)
{
	padapter = GET_PRIMARY_ADAPTER(padapter);

	if(padapter->HalFunc.silentreset)
		padapter->HalFunc.silentreset(padapter);
}

void rtw_hal_sreset_reset_value(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.sreset_reset_value)
		padapter->HalFunc.sreset_reset_value(padapter);
}

void rtw_hal_sreset_xmit_status_check(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.sreset_xmit_status_check)
		padapter->HalFunc.sreset_xmit_status_check(padapter);
}
void rtw_hal_sreset_linked_status_check(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.sreset_linked_status_check)
		padapter->HalFunc.sreset_linked_status_check(padapter);
}
u8   rtw_hal_sreset_get_wifi_status(struct rtw_adapter *padapter)
{
	u8 status = 0;
	if(padapter->HalFunc.sreset_get_wifi_status)
		status = padapter->HalFunc.sreset_get_wifi_status(padapter);
	return status;
}

bool rtw_hal_sreset_inprogress(struct rtw_adapter *padapter)
{
	bool inprogress = _FALSE;

	padapter = GET_PRIMARY_ADAPTER(padapter);

	if(padapter->HalFunc.sreset_inprogress)
		inprogress = padapter->HalFunc.sreset_inprogress(padapter);
	return inprogress;
}
#endif	//DBG_CONFIG_ERROR_DETECT

#ifdef CONFIG_IOL
int rtw_hal_iol_cmd(ADAPTER *adapter, struct xmit_frame *xmit_frame, u32 max_wating_ms, u32 bndy_cnt)
{
	if(adapter->HalFunc.IOL_exec_cmds_sync)
		return adapter->HalFunc.IOL_exec_cmds_sync(adapter, xmit_frame, max_wating_ms,bndy_cnt);
	return _FAIL;
}
#endif

#ifdef CONFIG_XMIT_THREAD_MODE
s32 rtw_hal_xmit_thread_handler(struct rtw_adapter *padapter)
{
	if(padapter->HalFunc.xmit_thread_handler)
		return padapter->HalFunc.xmit_thread_handler(padapter);
	return _FAIL;
}
#endif

void rtw_hal_notch_filter(struct rtw_adapter *adapter, bool enable)
{
	if(adapter->HalFunc.hal_notch_filter)
		adapter->HalFunc.hal_notch_filter(adapter,enable);
}

void rtw_hal_reset_security_engine(struct rtw_adapter * adapter)
{
	if(adapter->HalFunc.hal_reset_security_engine)
		adapter->HalFunc.hal_reset_security_engine(adapter);
}

s32 rtw_hal_c2h_handler(struct rtw_adapter *adapter, struct c2h_evt_hdr *c2h_evt)
{
	s32 ret = _FAIL;
	if (adapter->HalFunc.c2h_handler)
		ret = adapter->HalFunc.c2h_handler(adapter, c2h_evt);
	return ret;
}

c2h_id_filter rtw_hal_c2h_id_filter_ccx(struct rtw_adapter *adapter)
{
	return adapter->HalFunc.c2h_id_filter_ccx;
}
