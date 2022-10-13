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

Pretty print ON/OFF with:\
`config pretty <yes/no, y/n, Y/N, YES/NO>`

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

#### (Pretty print) import a register structure to work with:
`regs <path>`

Reads in a register structure from a .csv file and uses it to print the reg values in human readable form.

The required .csv format is the following (also check the comments in csv2regs.py).
```
# address; acronym; name; mask; shift; width;
0;BCR;Basic control register;;;;
;;RESET;0x8000;15;1;
;;LOOPBACK;0x4000;14;1;
...
2;PHYIDR1;PHY identifier register 1;;;;
;;PHY_ID;0xFFFF;0;16;
...
```

This feature uses the tool csv2regs.py, which reads in the .csv and outputs a Python list of tReg objects (used internally by usb2mdio.py).

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

#### regs_csv2c:
This tool takes the same register structure as used for the pretty pring and creates a C-struct initialization for a .c source file.
The struct definition that must go in a .h header file should be the following (also check the comments in regs_csv2c.py):

```
// file.h
#define USE_VERBOSE

typedef struct
{
    char     *name;
    uint16_t  mask;
    uint8_t   shift;
    uint8_t   width;
}tRegField;

typedef struct
{
    uint16_t  addr;
    char      *acr;
    char      *name;
    tRegField fields[17];
}tReg;

extern tReg phy_regs[/*address*/];
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
