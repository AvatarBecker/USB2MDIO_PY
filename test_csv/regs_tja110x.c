#ifdef USE_VERBOSE

tReg phy_regs[/*address*/] =
{
    {
        .addr = 0, .acr = "BCR", .name = "Basic control register",
        .fields =
        {
            {.name="RESET", .mask=0x8000, .shift=15, .width=1},
            {.name="LOOPBACK", .mask=0x4000, .shift=14, .width=1},
            {.name="SPEED_SELECT (LSB)", .mask=0x2000, .shift=13, .width=1},
            {.name="AUTONEG_EN", .mask=0x1000, .shift=12, .width=1},
            {.name="POWER_DOWN", .mask=0x0800, .shift=11, .width=1},
            {.name="ISOLATE", .mask=0x0400, .shift=10, .width=1},
            {.name="RE_AUTONEG", .mask=0x0200, .shift=9, .width=1},
            {.name="DUPLEX_MODE", .mask=0x0100, .shift=8, .width=1},
            {.name="COLLISION_TEST", .mask=0x0080, .shift=7, .width=1},
            {.name="SPEED_SELECT (MSB)", .mask=0x0040, .shift=6, .width=1},
            {.name="UNIDIRECT_EN", .mask=0x0020, .shift=5, .width=1},
            {.name="reserved", .mask=0x001F, .shift=0, .width=5},
            {}
        }
    },
    {
        .addr = 1, .acr = "BSR", .name = "Basic status register",
        .fields =
        {
            {.name="100BASE-T4  ", .mask=0x8000, .shift=15, .width=1},
            {.name="100BASE-X_FD  ", .mask=0x4000, .shift=14, .width=1},
            {.name="100BASE-X_HD  ", .mask=0x2000, .shift=13, .width=1},
            {.name="10Mbps_FD  ", .mask=0x1000, .shift=12, .width=1},
            {.name="10Mbps_HD  ", .mask=0x0800, .shift=11, .width=1},
            {.name="100BASE-T2_FD  ", .mask=0x0400, .shift=10, .width=1},
            {.name="100BASE-T2_HD  ", .mask=0x0200, .shift=9, .width=1},
            {.name="EXTENDED_STATUS  ", .mask=0x0100, .shift=8, .width=1},
            {.name="UNIDIRECT_ ABILITY  ", .mask=0x0080, .shift=7, .width=1},
            {.name="MF_PREAMBLE_SUPPRESSION ", .mask=0x0040, .shift=6, .width=1},
            {.name="AUTONEG_COMPLETE  ", .mask=0x0020, .shift=5, .width=1},
            {.name="REMOTE_FAULT ", .mask=0x0010, .shift=4, .width=1},
            {.name="AUTONEG_ABILITY ", .mask=0x0008, .shift=3, .width=1},
            {.name="LINK_STATUS  ", .mask=0x0004, .shift=2, .width=1},
            {.name="JABBER_DETECT  ", .mask=0x0002, .shift=1, .width=1},
            {.name="EXTENDED_CAPABILITY  ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 2, .acr = "PHYIDR1", .name = "PHY identifier register 1",
        .fields =
        {
            {.name="PHY_ID", .mask=0xFFFF, .shift=0, .width=16},
            {}
        }
    },
    {
        .addr = 3, .acr = "PHYIDR2", .name = "PHY identifier register 2",
        .fields =
        {
            {.name="PHY_ID ", .mask=0xFC00, .shift=10, .width=6},
            {.name="TYPE_NO ", .mask=0x03F0, .shift=4, .width=6},
            {.name="REVISION_NO ", .mask=0x000F, .shift=0, .width=4},
            {}
        }
    },
    {
        .addr = 15, .acr = "XTNR", .name = "Extended status register",
        .fields =
        {
            {.name="1000BASE-X_FD ", .mask=0x8000, .shift=15, .width=1},
            {.name="1000BASE-X_HD ", .mask=0x4000, .shift=14, .width=1},
            {.name="1000BASE-T_FD ", .mask=0x2000, .shift=13, .width=1},
            {.name="1000BASE-T_HD ", .mask=0x1000, .shift=12, .width=1},
            {.name="reserved ", .mask=0x0F00, .shift=8, .width=4},
            {.name="100BASE-T1 ", .mask=0x0080, .shift=7, .width=1},
            {.name="1000BASE-RTPGE ", .mask=0x0040, .shift=6, .width=1},
            {.name="reserved ", .mask=0x003F, .shift=0, .width=6},
            {}
        }
    },
    {
        .addr = 16, .acr = "PHYIDR3", .name = "PHY identifier register 3 ",
        .fields =
        {
            {.name="PHY_ID", .mask=0xFFFF, .shift=0, .width=16},
            {}
        }
    },
    {
        .addr = 17, .acr = "ECR", .name = "Extended control register ",
        .fields =
        {
            {.name="LINK_CONTROL ", .mask=0x8000, .shift=15, .width=1},
            {.name="POWER_MODE ", .mask=0x0800, .shift=11, .width=1},
            {.name="SLAVE_JITTER_TEST", .mask=0x0400, .shift=10, .width=1},
            {.name="TRAINING_RESTART ", .mask=0x0200, .shift=9, .width=1},
            {.name="TEST_MODE [4] ", .mask=0x01C0, .shift=6, .width=3},
            {.name="CABLE_TEST ", .mask=0x0020, .shift=5, .width=1},
            {.name="LOOPBACK_MODE", .mask=0x0018, .shift=3, .width=2},
            {.name="CONFIG_EN ", .mask=0x0004, .shift=2, .width=1},
            {.name="reserved ", .mask=0x0002, .shift=1, .width=1},
            {.name="WAKE_REQUEST ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 18, .acr = "CR1", .name = "Configuration register 1 ",
        .fields =
        {
            {.name="MASTER_SLAVE ", .mask=0x8000, .shift=15, .width=1},
            {.name="FWDPHYLOC ", .mask=0x4000, .shift=14, .width=1},
            {.name="reserved ", .mask=0x3000, .shift=12, .width=2},
            {.name="REMWUPHY ", .mask=0x0800, .shift=11, .width=1},
            {.name="LOCWUPHY ", .mask=0x0400, .shift=10, .width=1},
            {.name="MII_MODE ", .mask=0x0300, .shift=8, .width=2},
            {.name="MII_DRIVER ", .mask=0x0080, .shift=7, .width=1},
            {.name="SLEEP_CONFIRM ", .mask=0x0040, .shift=6, .width=1},
            {.name="LPS_WUR_DIS ", .mask=0x0020, .shift=5, .width=1},
            {.name="SLEEP_ACK ", .mask=0x0010, .shift=4, .width=1},
            {.name="reserved ", .mask=0x0008, .shift=3, .width=1},
            {.name="FWDPHYREM ", .mask=0x0004, .shift=2, .width=1},
            {.name="AUTO_PWD ", .mask=0x0002, .shift=1, .width=1},
            {.name="LPS_ACTIVE ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 19, .acr = "CR2", .name = "Configuration register 2 ",
        .fields =
        {
            {.name="PHYAD[4:0] ", .mask=0xF800, .shift=11, .width=5},
            {.name="SQI_AVERAGING ", .mask=0x0600, .shift=9, .width=2},
            {.name="SQI_WLIMIT ", .mask=0x01C0, .shift=6, .width=3},
            {.name="SQI_FAILLIMIT ", .mask=0x0038, .shift=3, .width=3},
            {.name="JUMBO_ENABLE ", .mask=0x0004, .shift=2, .width=1},
            {.name="SLEEP_REQUEST_TO ", .mask=0x0003, .shift=0, .width=2},
            {}
        }
    },
    {
        .addr = 20, .acr = "SECR", .name = "Symbol error counter register ",
        .fields =
        {
            {.name="SYM_ERR_CNT", .mask=0xFFFF, .shift=0, .width=16},
            {}
        }
    },
    {
        .addr = 21, .acr = "ISR", .name = "Interrupt source register ",
        .fields =
        {
            {.name="PWON ", .mask=0x8000, .shift=15, .width=1},
            {.name="WAKEUP ", .mask=0x4000, .shift=14, .width=1},
            {.name="WUR_RECEIVED ", .mask=0x2000, .shift=13, .width=1},
            {.name="LPS_RECEIVED ", .mask=0x1000, .shift=12, .width=1},
            {.name="PHY_INIT_FAIL ", .mask=0x0800, .shift=11, .width=1},
            {.name="LINK_STATUS_FAIL ", .mask=0x0400, .shift=10, .width=1},
            {.name="LINK_STATUS_UP ", .mask=0x0200, .shift=9, .width=1},
            {.name="SYM_ERR ", .mask=0x0100, .shift=8, .width=1},
            {.name="TRAINING_FAILED ", .mask=0x0080, .shift=7, .width=1},
            {.name="SQI_WARNING ", .mask=0x0040, .shift=6, .width=1},
            {.name="CONTROL_ERR ", .mask=0x0020, .shift=5, .width=1},
            {.name="reserved ", .mask=0x0010, .shift=4, .width=1},
            {.name="UV_ERR ", .mask=0x0008, .shift=3, .width=1},
            {.name="UV_RECOVERY ", .mask=0x0004, .shift=2, .width=1},
            {.name="TEMP_ERR ", .mask=0x0002, .shift=1, .width=1},
            {.name="SLEEP_ABORT ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 22, .acr = "IER", .name = "Interrupt enable register ",
        .fields =
        {
            {.name="PWON_EN ", .mask=0x8000, .shift=15, .width=1},
            {.name="WAKEUP_EN ", .mask=0x4000, .shift=14, .width=1},
            {.name="WUR_RECEIVED_EN ", .mask=0x2000, .shift=13, .width=1},
            {.name="LPS_RECEIVED_EN ", .mask=0x1000, .shift=12, .width=1},
            {.name="PHY_INIT_FAIL_EN ", .mask=0x0800, .shift=11, .width=1},
            {.name="LINK_STATUS_FAIL_EN ", .mask=0x0400, .shift=10, .width=1},
            {.name="LINK_STATUS_UP_EN ", .mask=0x0200, .shift=9, .width=1},
            {.name="SYM_ERR_EN ", .mask=0x0100, .shift=8, .width=1},
            {.name="TRAINING_FAILED_EN ", .mask=0x0080, .shift=7, .width=1},
            {.name="SQI_WARNING_EN ", .mask=0x0040, .shift=6, .width=1},
            {.name="CONTROL_ERR_EN ", .mask=0x0020, .shift=5, .width=1},
            {.name="reserved ", .mask=0x0010, .shift=4, .width=1},
            {.name="UV_ERR_EN ", .mask=0x0008, .shift=3, .width=1},
            {.name="UV_RECOVERY_EN ", .mask=0x0004, .shift=2, .width=1},
            {.name="TEMP_ERR_EN ", .mask=0x0002, .shift=1, .width=1},
            {.name="SLEEP_ABORT_EN ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {
        .addr = 23, .acr = "CSR", .name = "Communication status register ",
        .fields =
        {
            {.name="LINK_UP ", .mask=0x8000, .shift=15, .width=1},
            {.name="TX_MODE ", .mask=0x6000, .shift=13, .width=2},
            {.name="LOC_RCVR_STATUS ", .mask=0x1000, .shift=12, .width=1},
            {.name="REM_RCVR_STATUS ", .mask=0x0800, .shift=11, .width=1},
            {.name="SCR_LOCKED ", .mask=0x0400, .shift=10, .width=1},
            {.name="SSD_ERR ", .mask=0x0200, .shift=9, .width=1},
            {.name="ESD_ERR ", .mask=0x0100, .shift=8, .width=1},
            {.name="SQI ", .mask=0x00E0, .shift=5, .width=3},
            {.name="RECEIVE_ERR ", .mask=0x0010, .shift=4, .width=1},
            {.name="TRANSMIT_ERR ", .mask=0x0008, .shift=3, .width=1},
            {.name="PHY_STATE ", .mask=0x0007, .shift=0, .width=3},
            {}
        }
    },
    {
        .addr = 24, .acr = "GSR", .name = "General status register ",
        .fields =
        {
            {.name="INT_STATUS ", .mask=0x8000, .shift=15, .width=1},
            {.name="PLL_LOCKED ", .mask=0x4000, .shift=14, .width=1},
            {.name="LOCAL_WU ", .mask=0x2000, .shift=13, .width=1},
            {.name="REMOTE_WU ", .mask=0x1000, .shift=12, .width=1},
            {.name="DATA_DET_WU ", .mask=0x0800, .shift=11, .width=1},
            {.name="EN_STATUS ", .mask=0x0400, .shift=10, .width=1},
            {.name="RESET_STATUS ", .mask=0x0200, .shift=9, .width=1},
            {.name="reserved ", .mask=0x0100, .shift=8, .width=1},
            {.name="LINKFAIL_CNT ", .mask=0x00F8, .shift=3, .width=5},
            {.name="reserved ", .mask=0x0007, .shift=0, .width=3},
            {}
        }
    },
    {
        .addr = 25, .acr = "XTRSR", .name = "External status register ",
        .fields =
        {
            {.name="UV_VDDD_3V3 ", .mask=0x8000, .shift=15, .width=1},
            {.name="UV_VDDA_3V3 ", .mask=0x4000, .shift=14, .width=1},
            {.name="UV_VDDD_1V8 ", .mask=0x2000, .shift=13, .width=1},
            {.name="reserved ", .mask=0x1000, .shift=12, .width=1},
            {.name="UV_VDDIO ", .mask=0x0800, .shift=11, .width=1},
            {.name="TEMP_HIGH ", .mask=0x0400, .shift=10, .width=1},
            {.name="TEMP_WARN ", .mask=0x0200, .shift=9, .width=1},
            {.name="SHORT_DETECT ", .mask=0x0100, .shift=8, .width=1},
            {.name="OPEN_DETECT ", .mask=0x0080, .shift=7, .width=1},
            {.name="POLARITY_DETECT ", .mask=0x0040, .shift=6, .width=1},
            {.name="INTERLEAVE_DETECT ", .mask=0x0020, .shift=5, .width=1},
            {.name="reserved ", .mask=0x001F, .shift=0, .width=5},
            {}
        }
    },
    {
        .addr = 26, .acr = "LFCR", .name = "Link-fail counter register ",
        .fields =
        {
            {.name="LOC_RCVR_CNT", .mask=0xFF00, .shift=8, .width=8},
            {.name="REM_RCVR_CNT", .mask=0x00FF, .shift=0, .width=8},
            {}
        }
    },
    {
        .addr = 27, .acr = "CCR", .name = "Common configuration register ",
        .fields =
        {
            {.name="AUTO_OP ", .mask=0x8000, .shift=15, .width=1},
            {.name="reserved ", .mask=0x4000, .shift=14, .width=1},
            {.name="CLK_MODE ", .mask=0x3000, .shift=12, .width=2},
            {.name="LDO_MODE ", .mask=0x0800, .shift=11, .width=1},
            {.name="CLK_DRIVER ", .mask=0x0400, .shift=10, .width=1},
            {.name="CLK_HOLD ", .mask=0x0200, .shift=9, .width=1},
            {.name="LOC_WU_TIM ", .mask=0x0180, .shift=7, .width=2},
            {.name="CONFIG_WAKE ", .mask=0x0040, .shift=6, .width=1},
            {.name="CONFIG_INH ", .mask=0x0020, .shift=5, .width=1},
            {.name="reserved ", .mask=0x001F, .shift=0, .width=5},
            {}
        }
    },
    {
        .addr = 28, .acr = "CR3", .name = "Configuration register 3 ",
        .fields =
        {
            {.name="reserved ", .mask=0xFFFC, .shift=2, .width=14},
            {.name="FORCE_SLEEP ", .mask=0x0002, .shift=1, .width=1},
            {.name="reserved ", .mask=0x0001, .shift=0, .width=1},
            {}
        }
    },
    {}
};

#endif