## USB2MDIO_PY

A python alternative to TI's USB2MDIO tool.

TI has this USB2MDIO (or USB-2-MDIO) interface for configuring PHYs via USB on their evaluation boards (using an on-board MSP430 that controls the SMI (MDIO) interface and receives the commands from the PC via USB).
However, the tool is only made available for Windows, and it doesn't offer a good UX.
Therefore I decided (needed) to write a small tool to substitute it and used the opportunity to expand it.

An expanded script syntax was created to permit changing the PHY and batching multiple scripts.
A script can be passed directly to the command via bash, or via the commands CLI.

## Usage

`python3 usb2mdio.py <com_port> [script_file]`

'script_file' can be in TI's format or USB2MDIO_PY's extended format.
Check out the syntax below.

If no script is passed, a CLI opens, where the following commands are possible:

### CLI commands
#### Configure PHY access:

Show current config: \
`config`

PHY address chosen with:\
`config phy <phy_address>`

Extended register mode chosen with:\
`config ext <yes/no, y/n, Y/N, YES/NO>`

#### Write register:
`<reg> <value>   #Only HEX values without '0x' for now, e.g. ff`

#### Read register with:
`<reg>           #Only HEX values without '0x' for now, e.g. ff`

#### Show board verbose:
`info`

#### Help:
`<help, --help, h, -h, ?>`

#### Quit:
`<exit, exit(), quit, quit(), q>`

#### Dump registers with (WIP):
`dump <start_reg> <end_reg>`

#### Execute a script with:
`script <path>`

This accepts either TI's format of usb2mdio_py's extended format. They look like the following:

##### TI script format:
```c
begin

0000      // comment, read reg 0x0000 (HEX value! TI specs mandatory 4 digits, but this tools accepts any number of digits)
0001      // read BMSR (Basic Mode Status Register)
0002      // read PHYIDR1 (should read 0x2000)
0003      // read PHYIDR2 (should read 0xA270)
0602 0003 // write 0x0003 to reg 0x0603

end
```

##### USB2MDIO_PY script format:
```c
// TI's format is a subset of this one, and is also supported.
// Only the extensions to the format are exemplified below

begin

config ext yes
config phy 01  // switch to PHY 01 (DECIMAL value)
2              // read reg 2 (HEX value)
3              // read reg 3
1f             // read reg 31 (0x1f)
9 0            // write 0 to reg 9

script ./test_scripts/dp83867_init_config.txt    // read script. Home directory is where the python script is running...

config phy 10  // switch to PHY 10 (DECIMAL value)
2       // PHYIDR 1
3       // PHYIDR 2

script ./test_scripts/tc812_init_config.txt

end
```

#### TI UART Protocol:
In pure ASCII digits:\
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

<!---
Ideas/TODO:
Use files for verbose dump of registers: represent as class/structure like Basic_Control_Reg.Master_!Slave
Maybe we could use the format/code from Unix drivers...?
Maybe the same as for C?
0. Accept commands and parse them (COM connect)
1. COM connect and RW COM port
2. Get USB2MDIO sequences for write/read
-->
