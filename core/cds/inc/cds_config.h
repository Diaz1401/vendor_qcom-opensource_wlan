/*
 * Copyright (c) 2016-2018 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * DOC: cds_config.h
 *
 * Defines the configuration Information for various modules. Default values
 * are read from the INI file and saved into cds_config_info which are passed
 * to various modules for the initialization.
 */

#if !defined(__CDS_CONFIG_H)
#define __CDS_CONFIG_H

#include "osdep.h"
#include "cdp_txrx_mob_def.h"
#include "wlan_pmo_common_public_struct.h"

/**
 * enum cfg_sub_20_channel_width: ini values for su 20 mhz channel width
 * @WLAN_SUB_20_CH_WIDTH_5: Use 5 mhz channel width
 * @WLAN_SUB_20_CH_WIDTH_10: Use 10 mhz channel width
 */
enum cfg_sub_20_channel_width {
	WLAN_SUB_20_CH_WIDTH_NONE = 0,
	WLAN_SUB_20_CH_WIDTH_5 = 1,
	WLAN_SUB_20_CH_WIDTH_10 = 2,
};

/**
 * enum active_apf_mode - the modes active APF can operate in
 * @ACTIVE_APF_DISABLED: APF is disabled in active mode
 * @ACTIVE_APF_ENABLED: APF is enabled for all packets
 * @ACTIVE_APF_ADAPTIVE: APF is enabled for packets up to some threshold
 * @ACTIVE_APF_MODE_COUNT: The number of active APF modes
 */
enum active_apf_mode {
	ACTIVE_APF_DISABLED = 0,
	ACTIVE_APF_ENABLED,
	ACTIVE_APF_ADAPTIVE,
	ACTIVE_APF_MODE_COUNT
};

/**
 * struct cds_config_info - Place Holder for cds configuration
 * @max_station: Max station supported
 * @max_bssid: Max Bssid Supported
 * @sta_maxlimod_dtim: station max listen interval
 * @driver_type: Enumeration of Driver Type whether FTM or Mission mode
 * currently rest of bits are not used
 * Indicates whether support is enabled or not
 * @ap_disable_intrabss_fwd: pass intra-bss-fwd info to txrx module
 * @ap_maxoffload_peers: max offload peer
 * @ap_maxoffload_reorderbuffs: max offload reorder buffs
 * @ra_ratelimit_interval: RA rate limit value
 * @is_ra_ratelimit_enabled: Indicate RA rate limit enabled or not
 * @reorder_offload: is RX re-ordering offloaded to the fw
 * @dfs_pri_multiplier: dfs radar pri multiplier
 * @uc_offload_enabled: IPA Micro controller data path offload enable flag
 * @enable_rxthread: Rx processing in thread from TXRX
 * @max_scan: Maximum number of parallel scans
 * @tx_flow_stop_queue_th: Threshold to stop queue in percentage
 * @tx_flow_start_queue_offset: Start queue offset in percentage
 * @num_dp_rx_threads: number of dp rx threads to be configured
 * @enable_dp_rx_threads: enable dp rx threads
 * @is_lpass_enabled: Indicate whether LPASS is enabled or not
 * @tx_chain_mask_cck: Tx chain mask enabled or not
 * @self_gen_frm_pwr: Self gen from power
 * @sub_20_channel_width: Sub 20 MHz ch width, ini intersected with fw cap
 * @is_fw_timeout: Indicate whether crash host when fw timesout or not
 * @active_uc_apf_mode: Setting that determines how APF is applied in active
 *	mode for uc packets
 * @active_mc_bc_apf_mode: Setting that determines how APF is applied in
 *	active mode for MC/BC packets
 * @ito_repeat_count: Indicates ito repeated count
 * @force_target_assert_enabled: Indicate whether target assert enabled or not
 * @bandcapability: Configured band by user
 * @rps_enabled: RPS enabled in SAP mode
 * Structure for holding cds ini parameters.
 * @num_vdevs: Configured max number of VDEVs can be supported in the stack.
 */

struct cds_config_info {
	uint16_t max_station;
	uint16_t max_bssid;
	uint8_t sta_maxlimod_dtim;
	enum qdf_driver_type driver_type;
	uint8_t ap_maxoffload_peers;
	uint8_t ap_maxoffload_reorderbuffs;
#ifdef FEATURE_WLAN_RA_FILTERING
	uint16_t ra_ratelimit_interval;
	bool is_ra_ratelimit_enabled;
#endif
	uint8_t reorder_offload;
	uint8_t uc_offload_enabled;
	bool enable_rxthread;
	uint8_t max_scan;
#ifdef QCA_LL_TX_FLOW_CONTROL_V2
	uint32_t tx_flow_stop_queue_th;
	uint32_t tx_flow_start_queue_offset;
#endif
	uint8_t num_dp_rx_threads;
	uint8_t enable_dp_rx_threads;
#ifdef WLAN_FEATURE_LPSS
	bool is_lpass_enabled;
#endif
	uint16_t self_gen_frm_pwr;
	enum cfg_sub_20_channel_width sub_20_channel_width;
	uint8_t max_msdus_per_rxinorderind;
	bool self_recovery_enabled;
	bool fw_timeout_crash;
	struct ol_tx_sched_wrr_ac_specs_t ac_specs[TX_WMM_AC_NUM];
	enum active_apf_mode active_uc_apf_mode;
	enum active_apf_mode active_mc_bc_apf_mode;
	uint8_t ito_repeat_count;
	bool force_target_assert_enabled;
	uint8_t bandcapability;
	bool rps_enabled;
	uint32_t num_vdevs;
};

#ifdef WLAN_FEATURE_FILS_SK
#define MAX_PMK_LEN 48
#define MAX_PMKID_LEN 16
#define FILS_MAX_KEYNAME_NAI_LENGTH 253
#define FILS_MAX_REALM_LEN 255
#define FILS_MAX_RRK_LENGTH 64
#define FILS_MAX_RIK_LENGTH FILS_MAX_RRK_LENGTH

struct cds_fils_connection_info {
	bool is_fils_connection;
	uint8_t keyname_nai[FILS_MAX_KEYNAME_NAI_LENGTH];
	uint32_t key_nai_length;
	uint16_t sequence_number;
	uint8_t r_rk[FILS_MAX_RRK_LENGTH];
	uint32_t r_rk_length;
	uint8_t realm[FILS_MAX_REALM_LEN];
	uint32_t realm_len;
	uint8_t akm_type;
	uint8_t auth_type;
	uint8_t pmk[MAX_PMK_LEN];
	uint8_t pmk_len;
	uint8_t pmkid[MAX_PMKID_LEN];
};
#endif
#endif /* !defined( __CDS_CONFIG_H ) */
