#ifdef USE_VERBOSE

tReg phy_regs[/*address*/] =
{
    {
        .addr = 0x0, .acr = "BMCR", .name = "Basic Mode Control Register",
        .fields =
        {
            {.name="MII_reset ", .mask=0x8000, .shift=15, .width=1},
            {.name="xMII Loopback ", .mask=0x4000, .shift=14, .width=1},
            {.name="Manual_speed_MII ", .mask=0x2000, .shift=13, .width=1},
            {.name="Auto-Negotiation Enable ", .mask=0x1000, .shift=12, .width=1},
            {.name="Power Down ", .mask=0x0800, .shift=11, .width=1},
            {.name="Isolate ", .mask=0x0400, .shift=10, .width=1},
            {.name="RESERVED ", .mask=0x0200, .shift=9, .width=1},
            {.name="Duplex Mode ", .mask=0x0100, .shift=8, .width=1},
            {.name="RESERVED ", .mask=0x0080, .shift=7, .width=1},
            {.name="RESERVED ", .mask=0x007F, .shift=0, .width=7},
            {}
        }
    },
    {
        .addr = 0x1, .acr = "BMSR", .name = "Basic Mode Status Register",
        .fields =
        {
            {.name="100Base-T4 ", .mask=0x8000, .shift=15, .width=1},
            {.name="100Base-X Full Duplex ", .mask=0x4000, .shift=14, .width=1},
            {.name="100Base-X Half Duplex ", .mask=0x2000, .shift=13, .width=1},
            {.name="10 Mbps Full Duplex ", .mask=0x1000, .shift=12, .width=1},
            {.name="10 Mbps Half Duplex ", .mask=0x0800, .shift=11, .width=1},
            {.name="RESERVED ", .mask=0x0780, .shift=7, .width=4},
            {.name="MF Preamble Suppression ", .mask=0x0040, .shift=6, .width=1},
            {.name="Auto-Negotiation ", .mask=0x0020, .shift=5, .width=1},
            {.name="Remote fault ", .mask=0x0010, .shift=4, .width=1},
            {.name="Auto-Negotiation Ability ", .mask=0x0008, .shift=3, .width=1},
            {.name="Link status ", .mask=0x0004, .shift=2, .width=1},
            {.name="jabber detect ", .mask=0x0002, .shift=1, .width=1},
            {.name="Extended Capability ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x2, .acr = "PHYIDR1", .name = "PHY Identifier Register #1",
        .fields =
        {
            {.name="Organizationally Unique Identifier Bits 21:6", .mask=0xFFFF, .shift=0, .width=16},
            {}
        }
    },
    {
        .addr = 0x3, .acr = "PHYIDR2", .name = "PHY Identifier Register #2",
        .fields =
        {
            {.name="Organizationally Unique Identifier Bits 5:0 ", .mask=0xFC00, .shift=10, .width=6},
            {.name="Model Number ", .mask=0x03F0, .shift=4, .width=6},
            {.name="Revision Number ", .mask=0x000F, .shift=0, .width=4},
            {}
        }
    },
    {
        .addr = 0xD, .acr = "REGCR", .name = "Register Control Register",
        .fields =
        {
            {.name="Extended Register Command", .mask=0xC000, .shift=14, .width=2},
            {.name="RESERVED ", .mask=0x3FE0, .shift=5, .width=9},
            {.name="DEVAD ", .mask=0x001F, .shift=0, .width=5},
            {}
        }
    },
    {
        .addr = 0xE, .acr = "ADDAR", .name = "Address or Data Register",
        .fields =
        {
            {.name="Address/Data", .mask=0xFFFF, .shift=0, .width=16},
            {}
        }
    },
    {
        .addr = 0x10, .acr = "PHYSTS", .name = "PHY Status Register",
        .fields =
        {
            {.name="RESERVED ", .mask=0x8000, .shift=15, .width=1},
            {.name="RESERVED ", .mask=0x4000, .shift=14, .width=1},
            {.name="receive_error_latch ", .mask=0x2000, .shift=13, .width=1},
            {.name="RESERVED ", .mask=0x1000, .shift=12, .width=1},
            {.name="RESERVED ", .mask=0x0800, .shift=11, .width=1},
            {.name="signal_detect ", .mask=0x0400, .shift=10, .width=1},
            {.name="descrambler_lock ", .mask=0x0200, .shift=9, .width=1},
            {.name="RESERVED ", .mask=0x0100, .shift=8, .width=1},
            {.name="mii_interrupt ", .mask=0x0080, .shift=7, .width=1},
            {.name="RESERVED ", .mask=0x0040, .shift=6, .width=1},
            {.name="jabber_dtct ", .mask=0x0020, .shift=5, .width=1},
            {.name="RESERVED ", .mask=0x0010, .shift=4, .width=1},
            {.name="loopback_status ", .mask=0x0008, .shift=3, .width=1},
            {.name="duplex_status ", .mask=0x0004, .shift=2, .width=1},
            {.name="RESERVED ", .mask=0x0002, .shift=1, .width=1},
            {.name="link_status ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x11, .acr = "PHYSCR", .name = "",
        .fields =
        {
            {.name="dis_clk_125 ", .mask=0x8000, .shift=15, .width=1},
            {.name="pwr_save_mode_en ", .mask=0x4000, .shift=14, .width=1},
            {.name="pwr_save_mode ", .mask=0x3000, .shift=12, .width=2},
            {.name="sgmii_soft_reset ", .mask=0x0800, .shift=11, .width=1},
            {.name="use_PHYAD0_as_Isolate ", .mask=0x0400, .shift=10, .width=1},
            {.name="tx_fifo_depth ", .mask=0x0300, .shift=8, .width=2},
            {.name="RESERVED ", .mask=0x0080, .shift=7, .width=1},
            {.name="RESERVED ", .mask=0x0070, .shift=4, .width=3},
            {.name="int_pol ", .mask=0x0008, .shift=3, .width=1},
            {.name="force_interrupt ", .mask=0x0004, .shift=2, .width=1},
            {.name="INTEN ", .mask=0x0002, .shift=1, .width=1},
            {.name="INT_OE ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x12, .acr = "MISR1", .name = "",
        .fields =
        {
            {.name="link_qual_int ", .mask=0x8000, .shift=15, .width=1},
            {.name="energy_det_int ", .mask=0x4000, .shift=14, .width=1},
            {.name="link_int ", .mask=0x2000, .shift=13, .width=1},
            {.name="wol_int ", .mask=0x1000, .shift=12, .width=1},
            {.name="esd_int ", .mask=0x0800, .shift=11, .width=1},
            {.name="ms_train_done_int ", .mask=0x0400, .shift=10, .width=1},
            {.name="fhf_int ", .mask=0x0200, .shift=9, .width=1},
            {.name="rhf_int ", .mask=0x0100, .shift=8, .width=1},
            {.name="link_qual_int_en ", .mask=0x0080, .shift=7, .width=1},
            {.name="energy_det_int_en ", .mask=0x0040, .shift=6, .width=1},
            {.name="link_int_en ", .mask=0x0020, .shift=5, .width=1},
            {.name="wol_int_en ", .mask=0x0010, .shift=4, .width=1},
            {.name="esd_int_en ", .mask=0x0008, .shift=3, .width=1},
            {.name="ms_train_done_int_en ", .mask=0x0004, .shift=2, .width=1},
            {.name="fhf_int_en ", .mask=0x0002, .shift=1, .width=1},
            {.name="rhf_int_en ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x13, .acr = "MISR2", .name = "",
        .fields =
        {
            {.name="under_volt_int ", .mask=0x8000, .shift=15, .width=1},
            {.name="over_volt_int ", .mask=0x4000, .shift=14, .width=1},
            {.name="RESERVED ", .mask=0x2000, .shift=13, .width=1},
            {.name="RESERVED ", .mask=0x1000, .shift=12, .width=1},
            {.name="RESERVED ", .mask=0x0800, .shift=11, .width=1},
            {.name="sleep_int ", .mask=0x0400, .shift=10, .width=1},
            {.name="pol_int ", .mask=0x0200, .shift=9, .width=1},
            {.name="jabber_int ", .mask=0x0100, .shift=8, .width=1},
            {.name="under_volt_int_en ", .mask=0x0080, .shift=7, .width=1},
            {.name="over_volt_int_en ", .mask=0x0040, .shift=6, .width=1},
            {.name="page_rcvd_int_en ", .mask=0x0020, .shift=5, .width=1},
            {.name="Fifo_int_en ", .mask=0x0010, .shift=4, .width=1},
            {.name="RESERVED ", .mask=0x0008, .shift=3, .width=1},
            {.name="sleep_int_en ", .mask=0x0004, .shift=2, .width=1},
            {.name="pol_int_en ", .mask=0x0002, .shift=1, .width=1},
            {.name="jabber_int_en ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x15, .acr = "RECR", .name = "Receiver Error Counter Register",
        .fields =
        {
            {.name="rx_err_cnt", .mask=0xFFFF, .shift=0, .width=16},
            {}
        }
    },
    {
        .addr = 0x16, .acr = "BISCR", .name = "BIST Control Register",
        .fields =
        {
            {.name="RESERVED ", .mask=0xF800, .shift=11, .width=5},
            {.name="prbs_sync_loss ", .mask=0x0400, .shift=10, .width=1},
            {.name="RESERVED ", .mask=0x0200, .shift=9, .width=1},
            {.name="core_pwr_mode ", .mask=0x0100, .shift=8, .width=1},
            {.name="RESERVED ", .mask=0x0080, .shift=7, .width=1},
            {.name="tx_mii_lpbk ", .mask=0x0040, .shift=6, .width=1},
            {.name="loopback_mode ", .mask=0x003C, .shift=2, .width=4},
            {.name="pcs_lpbck ", .mask=0x0002, .shift=1, .width=1},
            {.name="RESERVED ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x18, .acr = "MISR3", .name = "",
        .fields =
        {
            {.name="wup_psv_int", .mask=0x8000, .shift=15, .width=1},
            {.name="no_link_int", .mask=0x4000, .shift=14, .width=1},
            {.name="sleep_fail_int ", .mask=0x2000, .shift=13, .width=1},
            {.name="POR_done_int ", .mask=0x1000, .shift=12, .width=1},
            {.name="no_frame_int ", .mask=0x0800, .shift=11, .width=1},
            {.name="wake_req_int ", .mask=0x0400, .shift=10, .width=1},
            {.name="WUP_int ", .mask=0x0200, .shift=9, .width=1},
            {.name="LPS_int ", .mask=0x0100, .shift=8, .width=1},
            {.name="RESERVED ", .mask=0x00C0, .shift=6, .width=2},
            {.name="sleep_fail_int_en ", .mask=0x0020, .shift=5, .width=1},
            {.name="POR_done_int_en ", .mask=0x0010, .shift=4, .width=1},
            {.name="no_frame_int_en ", .mask=0x0008, .shift=3, .width=1},
            {.name="wake_req_int_en ", .mask=0x0004, .shift=2, .width=1},
            {.name="WUP_int_en ", .mask=0x0002, .shift=1, .width=1},
            {.name="LPS_int_en ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 0x19, .acr = "REG_19", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1E, .acr = "CDCR", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1F, .acr = "PHYRCR", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x18B, .acr = "LPS_CFG2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x18C, .acr = "LPS_CFG3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x18E, .acr = "LPS_STATUS", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x198, .acr = "SQI", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x300, .acr = "TDR_TX_CFG", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x301, .acr = "TAP_PROCESS_CFG", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x302, .acr = "TDR_CFG1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x303, .acr = "TDR_CFG2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x304, .acr = "TDR_CFG3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x305, .acr = "TDR_CFG4", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x306, .acr = "TDR_CFG5", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x309, .acr = "TDR_STATUS0", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x30A, .acr = "TDR_STATUS1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x30B, .acr = "TDR_STATUS2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x30C, .acr = "TDR_STATUS3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x30D, .acr = "TDR_STATUS4", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x30E, .acr = "TDR_STATUS5", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x310, .acr = "TDR_TC1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x450, .acr = "LEDS_CFG_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x451, .acr = "LEDS_CFG_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x452, .acr = "IO_MUX_CFG_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x453, .acr = "IO_MUX_CFG_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x45D, .acr = "CHIP_SOR_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x45E, .acr = "CHIP_SOR_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x45F, .acr = "LED1_CLKOUT_ANA_CTRL", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x466, .acr = "REV_ID", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x497, .acr = "TEST_MODE_CTRL", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x560, .acr = "TC1_CFG_RW", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x561, .acr = "TC1_LINK_FAIL_LOSS", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x562, .acr = "TC1_LINK_TRAINING_TIME", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x600, .acr = "RGMII_CTRL", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x601, .acr = "RGMII_FIFO_STATUS", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x602, .acr = "RGMII_CLK_SHIFT_CTRL", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x608, .acr = "SGMII_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x60A, .acr = "SGMII_STATUS", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x60C, .acr = "SGMII_CTRL_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x60D, .acr = "SGMII_FIFO_STATUS", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x618, .acr = "PRBS_STATUS_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x619, .acr = "PRBS_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x61A, .acr = "PRBS_CTRL_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x61B, .acr = "PRBS_CTRL_3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x61C, .acr = "PRBS_STATUS_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x61D, .acr = "PRBS_STATUS_3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x61E, .acr = "PRBS_STATUS_4", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x620, .acr = "PRBS_STATUS_5", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x622, .acr = "PRBS_STATUS_6", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x623, .acr = "PRBS_STATUS_7", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x624, .acr = "PRBS_CTRL_4", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x625, .acr = "PATTERN_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x626, .acr = "PATTERN_CTRL_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x627, .acr = "PATTERN_CTRL_3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x628, .acr = "PMATCH_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x629, .acr = "PMATCH_CTRL_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x62A, .acr = "PMATCH_CTRL_3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x638, .acr = "PKT_CRC_STAT", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x639, .acr = "TX_PKT_CNT_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x63A, .acr = "TX_PKT_CNT_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x63B, .acr = "TX_PKT_CNT_3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x63C, .acr = "RX_PKT_CNT_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x63D, .acr = "RX_PKT_CNT_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x63E, .acr = "RX_PKT_CNT_3", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x648, .acr = "RMII_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x649, .acr = "RMII_STATUS_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x64A, .acr = "RMII_OVERRIDE_CTRL", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1000, .acr = "MMD1_PMA_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1001, .acr = "MMD1_PMA_STATUS_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1007, .acr = "MMD1_PMA_STATUS_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x100B, .acr = "MMD1_PMA_EXT_ABILITY_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1012, .acr = "MMD1_PMA_EXT_ABILITY_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1834, .acr = "MMD1_PMA_CTRL_2", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x1836, .acr = "MMD1_PMA_TEST_MODE_CTRL", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x3000, .acr = "MMD3_PCS_CTRL_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {
        .addr = 0x3001, .acr = "MMD3_PCS_Status_1", .name = "",
        .fields =
        {
            {}
        }
    },
    {}
};

#endif