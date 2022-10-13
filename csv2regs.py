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
import csv
from pathlib import Path

__CSV2REGS_DEBUG__ = 0

help_str = """
Usage: python3 regs_csv2c.py [file.csv]

Take a .csv of the registers of a PHY in the following format:
# address; acronym; name; mask; shift; width;
0;BCR;Basic control register;;;;
;;RESET;0x8000;15;1;
;;LOOPBACK;0x4000;14;1;
...
2;PHYIDR1;PHY identifier register 1;;;;
;;PHY_ID;0xFFFF;0;16;
...

Ouputs the register structure in the Python list format:

# list of register objects (tReg)
regs =
[
    [
        addr = 0
        acr = "BCR"
        name = "Basic control register"
        fields =
        [
            (RESET,0x8000,5,1)         # a field is the tuple: (name, mask, shift, width)
            (LOOPBACK,0x4000,14,1)
            # ...
            None
        ]
    ],
    [
        addr = 1
        acr = "PHYIDR1"
        name = "Basic control register"
        fields =
        [
            (PHY_ID,0xFFFF,0,16)
            None
        ]
    ],
    None
]

Obs.: NULL-terminated register array, with member "fields" being a NULL-terminated array of fields.

"""

class tRegField:
    name  = None
    mask  = None
    shift = None
    width = None

    def __init__(self, name, mask, shift, width):
        self.name  = name
        self.mask  = mask
        self.shift = shift
        self.width = width

class tReg:
    addr = None      # adress, also used for NULL-termination
    acr  = None
    name = None
    fields = None    # set of tuples, each tuple a field of the register

    def __init__(self, addr, acr, name):
        self.addr = addr
        self.acr  = acr
        self.name = name


def MyInt(my_string):
    if my_string[:2] in {"0x", "0X"}:
        return int(my_string, 16)
    else:
        return int(my_string, 10)

def ExtractFieldValue(field, value):
    return (value & field.mask) >> field.shift

def RegStringify(reg:tReg):
    return f'{reg.acr} 0x{reg.addr:x} ({reg.name})'

def FieldStringify(field:tRegField):
    return f'\t{field.name}: mask={field.mask}, shift={field.shift}, width={field.width}'

def PrintRegs(regs):
    for reg in regs:
        if(reg):
            string_temp = RegStringify(reg)
            print(string_temp)

            for field in reg.fields:
                if(field):
                    string_temp = FieldStringify(field)
                    print(string_temp)
                else:
                    continue
        else:
            return

def PrintRegPretty(regs, reg_addr, value):
    for reg in regs:
        if(reg):
            if(reg.addr == reg_addr):
                string_temp = RegStringify(reg) + f' = 0x{value:x}'
                print(string_temp)

                for field in reg.fields:
                    if(field):
                        field_value = ExtractFieldValue(field, value)

                        string_temp = f'\t{field.name} (' + (f'{field.shift}' if field.width==1 else f'{field.shift+field.width-1}-{field.shift}') + f') = 0x{field_value:x}'
                        print(string_temp)

                    else:
                        return
        else:
            return
    else:
        return -1


def csv2regs(file_name):
    regs       = None
    field_temp = None
    reg_temp   = None

    with open(file_name) as file_csv:

        reader_csv = csv.reader(file_csv, delimiter=';', quotechar='"')
        
        is_in_reg = 0
        is_in_fields = 0

        for row in reader_csv:
            addr = row[0]

            if(addr):
                if(addr[0]=='#'):
                    continue
                elif(is_in_reg):
                    # ---- finish reg ----
                    field_temp = None

                    if(reg_temp.fields):
                        reg_temp.fields.append(field_temp)  # NULL-terminating fields
                    else:
                        reg_temp.fields = {field_temp}
                        
                    if(regs):
                        regs.append(reg_temp)
                    else:
                        regs = [reg_temp]
                
                # ---- start reg ----
                acr = row[1]
                name = row[2]
                addr_int = MyInt(addr)

                reg_temp = tReg(addr_int, acr, name)

                is_in_reg = 1
            elif(row[2]):
                # ---- add new field ----
                name = row[2]
                mask = MyInt(row[3])
                shift = MyInt(row[4])
                width = MyInt(row[5])

                field_temp = tRegField(name, mask, shift, width)

                if(reg_temp):
                    if(reg_temp.fields):
                        reg_temp.fields.append(field_temp)
                    else:
                        reg_temp.fields = [field_temp]
                else:
                    reg_temp.fields = [field_temp]

        # ---- finish return the structure ----
        regs.append(None)
        
        file_csv.close()

        return regs


# ---- if run from terminal ----
if __name__ == '__main__':
    len_argv = len(sys.argv)
    if(len_argv==1):
        print(help_str)
        quit()
    elif(sys.argv[1] == "--help" or sys.argv[1] == "-h"):
        print(help_str)
        quit()
    elif(len_argv>=2):
        # ---------- Open File ----------

        file_name = sys.argv[1]

        regs = csv2regs(file_name)
        PrintRegs(regs)

        if(__CSV2REGS_DEBUG__):
            PrintRegPretty(regs, 0, 1)
            PrintRegPretty(regs, 2, 0xdeadbeef)
            PrintRegPretty(regs, 18, 0xa5a5)
