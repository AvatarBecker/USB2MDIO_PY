#!/usr/bin/env python3

# TODO
# Check why read broke
# upload it to git

# Get arguments from outside:
#    connect [port] <speed=9600>
#
#    After connected:
#        write <reg> <value>     #formats: 23 or 0x17 or b00010111
#        write -h <reg> <value>  #format: reg name/name.field; value in above form
#        read [-h] <reg>
#        dump [-h]
#        [-ti] file    # file containing a list of the commands above, same syntax; if -ti, use texas format

# Ideas/TODO:
# Use files for verbose dump of registers: represent as class/structure like Basic_Control_Reg.Master_!Slave
#     Maybe we could use the format/code from Unix drivers...?
#     Maybe the same as for C?
# 0. Accept commands and parse them (COM connect)
# 1. COM connect and RW COM port
# 2. Get USB2MDIO sequences for write/read

import sys
import serial


help_str = """
Connect to serial invoking the script like so:
python3 usb2mdio.py [port] <speed=9600>

After connected:
Set PHY address with:
phy <phy_address>

Write register with (WIP):
<reg> <value>
Formats: 23 (decimal) or 0x17 (hexadecimal) or b00010111 (binary)

Read register with (WIP):
<reg>

Dump registers with (WIP):
dump <start_reg> <end_reg>

Execute a file in TIs format with (WIP):
file <address>
"""

# ---------- Function definitions ----------

def GetFirstString(str_list):
    if(str_list):
        return str_list[0]
    else:
        return ''

def PrintRaw(str):
    for char in str:
        print(hex(ord(char)), end=' ')
    print()

def ReadBackReg(addr):
    pkt_reply = com_port.read(5)  # 4 value chars + 0x0a as delimiter character
    #PrintRaw(pkt_reply.decode('utf-8'))
    if(pkt_reply[4] == 0x0a):
        data_str = pkt_reply[0:4].decode('utf-8')
        if(data_str):
            print("Reg 0x", f'{addr:04x}', ": 0x", data_str, sep='')
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
    pkt_request = f'{phy_addr:02x}{addr:04x}{value:04x}'+ext+'/'
    #print(pkt_request+': ', end='')
    #PrintRaw(pkt_request)
    pkt_request = pkt_request.encode('utf-8')

    # write it
    com_port.write(pkt_request)

    # read back value and print it
    ReadBackReg(addr)

def ReadReg(com_port, phy_addr, addr, ext):
    
    # flush input (board keeps seding verbose)
    #com_port.reset_input_buffer() # too slow

    # assemble COM message
    pkt_request = f'{phy_addr:02x}{addr:04x}'+ext+'/'
    #print(pkt_request+': ', end='')
    #PrintRaw(pkt_request)
    pkt_request = pkt_request.encode('utf-8')

    # write it
    com_port.write(pkt_request)

    ReadBackReg(addr)

def ReadCleanLine(file):
    line = file.readline()
    line = GetFirstString(line.split('//',1))
    cmd = line.split()
    repr(cmd)

    return cmd

def ExecScriptTi(file):   # file: file handler of the opened file

    bad_fmt_str = 'Bad file format. '

    cmd=ReadCleanLine(file)
    curr_line = 1

    while(GetFirstString(cmd) != 'begin'):

        if(not line):
            print(bad_fmt_str+"No 'begin' keyword...")
            return
        #print(line)

        cmd=ReadCleanLine(file)
        curr_line += 1

    cmd=ReadCleanLine(file)
    curr_line += 1

    while(GetFirstString(cmd) != 'end'):

        # Get ADDR
        try:
            addr = int(GetFirstString(cmd), 16)
        except ValueError:
            # empty line
            continue

        len_cmd = len(cmd)

        # Get VALUE (if any)
        if(len_cmd == 2):
            try:
                value = int(usr_data[1], 16)
                WriteReg(com_port, phy_addr, addr, value, ext)
            except ValueError:
                print("Invalid write value at line "+curr_line)
                continue
        elif(len_cmd == 1):
            ReadReg(com_port, phy_addr, addr, ext)
        else:
            print('Wrong number of args at line '+curr_line)

        cmd=ReadCleanLine(file)
        curr_line += 1

    return

# ---------- Check arguments ----------
if(len(sys.argv)==1):
    print(help_str)
    quit()
elif(sys.argv[1] == "--help" or sys.argv[1] == "-h"):
    print(help_str)
    quit()
elif(len(sys.argv)==2):
    # ---------- Open COM Port ----------
    com_port = serial.Serial(sys.argv[1], 9600, timeout=1)

    # ---------- Read board verbose ----------
    board_verbose = bytearray(b'')
    while(1):
        temp_data = com_port.read(350)
        board_verbose.extend(temp_data)
        if(not temp_data):
            break

    # TODO: make it a config class, with description, name, and value. Easens pretty print and feedback on change.
    phy_addr = 0x01
    ext = '*'  # extended registers. Yes: '*', No: '='
    ext_dict = {
        '*': 'yes',
        '=': 'no'
    }

    # ---------- Parse user inputs ----------
    while(1):
        usr_data_raw = input("> ")

        usr_data = usr_data_raw.split()
        len_usr_data = len(usr_data)

        if(len_usr_data==0):
            continue

        elif(usr_data[0] == "script"):
            try:
                path = usr_data[1]
                print("read file (WIP):" + path )
            except IndexError:
                print("Invalid file or file path...")
                continue
        elif(usr_data[0] == "script_ti"):
            path = usr_data[1]
            print("read file (WIP):" + path )

            file = open(path, 'r')
            ExecScriptTi(file)
            file.close()

            # try:
            #     path = usr_data[1]
            #     print("read file " + path + "(WIP)")

            #     file = open(path, 'r')
            #     ExecScriptTi(file)
            #     file.close()
            # except IndexError:
            #     print("Invalid file or file path...")
            #     continue
        elif(usr_data[0] == "info"):
            if(board_verbose):
                print(board_verbose.decode('utf-8'))
            else:
                print("Board didn't send any info (verbose)...")
        elif(usr_data[0] == "config"):
            if(len_usr_data == 3):
                if(usr_data[1] == "phy"):
                    try:
                        phy_addr = int(usr_data[2], 16)
                        print("MDIO PHY addr = 0x"+f'{phy_addr:02x}')
                    except ValueError:
                        print("Invalid PHY address...")
                        continue
                elif(usr_data[1] == "ext"):
                    try:
                        if(usr_data[2] in ('yes', 'y', 'YES', 'Y')):
                            ext = '*'
                        elif(usr_data[2] in ('no', 'n', 'NO', 'n')):
                            ext = '='
                        print("Extended register mode: "+ext_dict[ext])
                    except ValueError:
                        print("Invalid Ext mode...")
                        continue
            else:
                print("MDIO PHY addr = 0x"+f'{phy_addr:02x}')
                print("Extended register mode: "+ext_dict[ext])

        elif(usr_data[0] in ("exit", "exit()", "quit", "quit()")):
            com_port.close()
            quit()
        elif(usr_data[0] in ("help", "--help", "h", "-h", "?")):
            print(help_str)

        # ---------- W/R Registers ----------
        else:   # no text, then numbers
            # Get ADDR
            try:
                addr = int(usr_data[0], 16)
            except ValueError:
                print("Invalid command...")
                continue

            # Get VALUE (if any)
            if(len_usr_data == 2):
                try:
                    value = int(usr_data[1], 16)
                    WriteReg(com_port, phy_addr, addr, value, ext)
                except ValueError:
                    print("Invalid value...")
                    continue
            elif(len_usr_data == 1):
                ReadReg(com_port, phy_addr, addr, ext)
            else:
                print('Wrong number of args...')