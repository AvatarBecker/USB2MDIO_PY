
Connect to serial invoking the script like so (baudrate = 9600):
    python3 usb2mdio.py <com_port>

After connected:
Configure PHY access:
    PHY address chosen with:
    ```config phy <phy_address>```
    Extended register mode chosen with:
    ```config ext <yes/no, y/n, Y/N, YES/NO>```

Write register with:
    ```<reg> <value>```
Formats: 23 (decimal) or 0x17 (hexadecimal) or b00010111 (binary)

Read register with:
    ```<reg>```

Show board verbose:
    ```info```

Dump registers with (WIP):
    ```dump <start_reg> <end_reg>```

Execute a script in TIs format with:
    ```script_ti <path>```

    Syntax for TI script:
    ```
    begin

    0000      // comment, read BMCR (Basic Mode Control Register)
    0001      // read BMSR (Basic Mode Status Register)
    0002      // read PHYIDR1 (should read 0x2000)
    0003      // read PHYIDR2 (should read 0xA270)
    0602 0003 // write 0x0003 to reg 0x0602

    end
    ```

Execute a file in usb2mdio_py format with (lets us batch writes to many PHYs):
    ```script <path>```

    Syntax for usb2mdio_py script:
    ```
    01   // this is a comment, choose to PHY 01
    /my_path/ti_script_1.txt
    /my_path/ti_script_2.txt
    
    02   // choose to PHY 01
    /my_path/ti_script_3.txt
    ```

TI UART Protocol:

In pure ASCII digits:
    Send:
    ```
        <PP><AAAA>[VVVV]<X><'/'>
        P: PHY Address digit
        A: Register Address digit
        V: Register Value digit
        X: Extended register:
            '*': yes
            '=': no
        '/': Delimiter char - End of request packet marker
    ```
    Receive:
    ```
        <VVVV><0x0a>
        V: Register Value digit
        0x0a: Delimiter char - End of reply packet
    ```


Ideas/TODO:
Use files for verbose dump of registers: represent as class/structure like Basic_Control_Reg.Master_!Slave
Maybe we could use the format/code from Unix drivers...?
Maybe the same as for C?
0. Accept commands and parse them (COM connect)
1. COM connect and RW COM port
2. Get USB2MDIO sequences for write/read