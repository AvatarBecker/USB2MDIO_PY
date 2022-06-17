#!/usr/bin/env python3

# MIT License

# Copyright (c) 2022 Wesley Becker

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


import sys
import serial
import re
import time

# mine:
import csv2regs as cr


help_str = """
Usage: python3 usb2mdio.py <com_port> [script_file]

A python alternative to TI's USB2MDIO tool.

'script_file' can be in TI's format of USB2MDIO_PY's extended format.
Check out the syntax here: https://github.com/AvatarBecker/USB2MDIO_PY

If no script is passed, a CLI opens, where the following commands are possible:

Configure PHY access:
    Show current config:
        config
    PHY address chosen with:
        config phy <phy_address>
    Extended register mode chosen with:
        config ext <yes/no, y/n, Y/N, YES/NO, true/false, True/False, 1/0>
    Pretty print:
        config pretty <yes/no, y/n, Y/N, YES/NO, true/false, True/False, 1/0>

Write register:
    <reg> <value>   #Only HEX values without '0x' for now, e.g. ff

Read register with:
    <reg>           #Only HEX values without '0x' for now, e.g. ff

Show board verbose:
    info

Dump registers with:
    dump [<start_reg> <end_reg>]

Execute a script (either in TI's of usb2mdio_py's own format) with:
    script <path>

Read register structure from a .csv and assign it to the current PHY address:
    regs <path>

    The format must be like the following:

    # this is a comment
    # address; acronym; name; mask; shift; width; permission
    0x0;BMCR;Basic Mode Control Register;;;;
    ;;MII_reset ;0x8000;15;1;
    ;;xMII Loopback ;0x4000;14;1;
    0x1;BMSR;Basic Mode Status Register;;;;
    ;;100Base-T4 ;0x8000;15;1;
    ;;100Base-X Full Duplex ;0x4000;14;1;

Help:
    <help, --help, h, -h, ?>

Quit:
    <exit, exit(), quit, quit(), q>

For more documentation check https://github.com/AvatarBecker/USB2MDIO_PY
"""

# ---------- Function definitions ----------

# TODO: make it a config class, with description, name, and value. Easens pretty print and feedback on change.
pretty_print = False
phy_addr = 10   # this is a decimal value
regs_dict = {}  # index reg struct with phy_addr

ext = '*'  # extended registers. Yes: '*', No: '='
ext_dict = {
    '*': 'yes',
    '=': 'no'
}

# ---------- Function definitions ----------

def GetFirstString(str_list):
    if(str_list):
        return str_list[0]
    else:
        return ''

# Helper function for debug
def PrintRaw(str):
    for char in str:
        print(hex(ord(char)), end=' ')
    print()

def ReadBackReg(addr):
    pkt_reply = com_port.read(6)
    #PrintRaw(pkt_reply.decode('utf-8'))

    pkt_reply = [i for i in pkt_reply if i != 0xd]   # for whatever reason, MSP sends a carriage return within reply for addr 0x1
    pkt_reply = bytes(pkt_reply)

    if(pkt_reply[4] == 0x0a):
        
        data_str = pkt_reply[0:4].decode('utf-8')
        
        if(data_str):
            
            if(pretty_print):
                
                if(phy_addr in regs_dict.keys()):
                    value = int(data_str, 16)
                    cr.PrintRegPretty(regs_dict[phy_addr], addr, value)
                else:
                    str_temp = f"Pretty print is on and no register structure was given for PHY Address {phy_addr}...\n\rYou can disable pretty print with:\n\rconfig pretty no"
                    print(str_temp)
            else:
                print('0x', data_str, sep='')
                #PrintRaw(data_str)
                #data = int(pkt_reply[0:4], 16)
        else:
            print("No reply...")
    else:
        print("Invalid reply...")

def WriteReg(com_port, phy_addr, addr, value, ext):
    # flush input (board keeps seding verbose)
    #com_port.reset_input_buffer() # too slow

    # assemble COM message
    pkt_request = f'{phy_addr:02d}{addr:04x}{value:04x}'+ext+'/'
    #print(pkt_request+': ', end='')
    #PrintRaw(pkt_request)
    pkt_request = pkt_request.encode('utf-8')

    # write it
    com_port.write(pkt_request)

    # read back value and print it
    print("wr reg 0x", f'{addr:04x}', ": ",  sep='', end='')
    ReadBackReg(addr)

def ReadReg(com_port, phy_addr, addr, ext):
    
    # flush input (board keeps seding verbose)
    #com_port.reset_input_buffer() # too slow

    # assemble COM message
    pkt_request = f'{phy_addr:02d}{addr:04x}'+ext+'/'
    #print(pkt_request+': ', end='')
    #PrintRaw(pkt_request)
    pkt_request = pkt_request.encode('utf-8')

    # write it
    com_port.write(pkt_request)

    if(not pretty_print):
        print("rd reg 0x", f'{addr:04x}', ": ", sep='', end='')
    ReadBackReg(addr)

# Unused. I'll leave it here just for future reference of a neat solution
def ReadCleanLine(file):
    line = file.readline()
    line = GetFirstString(line.split('//',1))
    cmd = line.split()
    repr(cmd)

    return cmd

def RwRegs(cmd, len_cmd):

    # Get ADDR
    try:
        # print(cmd[0])
        # print(type(cmd[0]))
        addr = int(cmd[0], 16)
    except:
        print("Invalid command...")
        return

    # Get VALUE (if any)
    if(len_cmd == 2):
        try:
            value = int(cmd[1], 16)
            WriteReg(com_port, phy_addr, addr, value, ext)
        except ValueError:
            print("Invalid value...")
            return
    elif(len_cmd == 1):
        ReadReg(com_port, phy_addr, addr, ext)
    else:
        print('Wrong number of args...')

def DumpRegs(cmd, len_cmd):

    # Get ADDRs
    if(len_cmd == 1):
        addr_start = 0x00
        addr_end = 0x1f
    elif(len_cmd >= 2):
        try:
            addr_start = int(cmd[1], 16)
        except:
            print("Bad argument...")
            return
    
        try:
            addr_end = int(cmd[2], 16)
        except:
            print("Bad argument...")
            return

    for my_addr in range(addr_start, addr_end+1):
        ReadReg(com_port, phy_addr, my_addr, ext)


def Config(usr_data, len_usr_data):

    global pretty_print
    global phy_addr
    global ext
    global ext_dict

    if(len_usr_data == 3):
        if(usr_data[1] == "phy"):
            try:
                phy_addr = int(usr_data[2], 10)
                print("PHY addr = "+f'{phy_addr:02d}')
            except ValueError:
                print("Invalid PHY address...")
                return
        elif(usr_data[1] == "ext"):
            try:
                if(usr_data[2] in ('yes', 'y', 'YES', 'Y', 'true', 'True', '1')):
                    ext = '*'
                elif(usr_data[2] in ('no', 'n', 'NO', 'n', 'false', 'False', '0')):
                    ext = '='
                print("Extended register mode: "+ext_dict[ext])
            except ValueError:
                print("Invalid Ext mode...")
                return
        elif(usr_data[1] == "pretty"):
            try:
                if(usr_data[2] in ('yes', 'y', 'YES', 'Y', 'true', 'True', '1')):
                    pretty_print = True
                elif(usr_data[2] in ('no', 'n', 'NO', 'n', 'false', 'False', '0')):
                    pretty_print = False
                print("Pretty print: "+f'{pretty_print}')
            except ValueError:
                print("Unknown option...")
                return

    else:
        print("PHY addr = "+f'{phy_addr:02d}')
        print("Extended register mode: "+ext_dict[ext])
        print("Pretty print: "+f'{pretty_print}')

def CmdDecision(cmd):
    len_cmd = len(cmd)

    if(cmd[0] == "script"):
        try:
            path = cmd[1]
            print("Reading file:" + path )

            file = open(path, 'r')
            ExecScript(file)
            file.close()
        except FileNotFoundError:
            print("Invalid file or file path...")
            return
    elif(cmd[0] == "regs"):
        try:
            path = cmd[1]
            print("Reading file:" + path )

            regs = cr.csv2regs(path)

            regs_dict[phy_addr] = regs
        except IndexError:
            if(phy_addr in regs_dict.keys()):
                cr.PrintRegs(regs_dict[phy_addr])
            else:
                str_temp = f"No register structure was given for PHY Address {phy_addr}..."
                print(str_temp)
        except FileNotFoundError:
            print("Invalid file or file path...")
            return
    elif(cmd[0] == "info"):
        if(board_verbose):
            print(board_verbose.decode('utf-8'))
        else:
            print("Board didn't send any info (verbose)...")
    elif(cmd[0] == "config"):
        Config(cmd, len_cmd)
    elif(cmd[0] == "dump"):
        DumpRegs(cmd, len_cmd)
    elif(cmd[0] in ("exit", "exit()", "quit", "quit()", "q")):
        com_port.close()
        quit()
    elif(cmd[0] in ("help", "--help", "h", "-h", "?")):
        print(help_str)

    # ---------- R/W Registers ----------
    else:
        RwRegs(cmd, len_cmd)

def ExecScript(file):   # file: file handler of the opened file

    bad_fmt_str = 'Bad file format. '

    conts = file.read()
    conts = re.split('\n|\r|\n\r|\r\n', conts)

    cmds = []

    for i in range(0,len(conts)):
        temp = conts[i].split('//',1)[0]
        if(temp != ''):
            cmds.append(temp)


    if('begin' in cmds[:1] and 'end' in cmds[-1:]):
        # All good, treat commands
        
        # strip 'begin' and 'end'
        del cmds[:1]
        del cmds[-1:]

        for cmd in cmds:
            cmd = cmd.split()

            CmdDecision(cmd)

    else:
        # Wrong format, abort
        print(bad_fmt_str)
        return

# ---------- Check arguments ----------
len_argv = len(sys.argv)
if(len_argv==1):
    print(help_str)
    quit()
elif(sys.argv[1] == "--help" or sys.argv[1] == "-h"):
    print(help_str)
    quit()
elif(len_argv>=2):
    # ---------- Open COM Port ----------
    com_port = serial.Serial(sys.argv[1], 9600, timeout=.1)

    # ---------- Read board verbose ----------
    board_verbose = bytearray(b'')
    while(1):
        temp_data = com_port.read(350)
        board_verbose.extend(temp_data)
        if(not temp_data):
            break

    if(len_argv==3):
        try:
            path = sys.argv[2]
            print("Reading file:" + path )

            file = open(path, 'r')
            ExecScript(file)
            file.close()
        except FileNotFoundError:
            print("Invalid file or file path...")
    elif(len_argv==2):
        # ---------- Parse user inputs ----------
        while(1):
            usr_data_raw = input("> ")

            usr_data = usr_data_raw.split()
            len_usr_data = len(usr_data)

            if(len_usr_data==0):
                continue
            else:
                CmdDecision(usr_data)
    else:
        print("Too many arguments... try 'help'")
