#!/usr/bin/env python3

import sys
import csv
from pathlib import Path

help_str = """
Usage: python3 regs_csv2c.py [file.csv]

Take a .csv of the registers of a PHY in the following format:
# address; acronym; name; mask; shift; width; permission
0;BCR;Basic control register;;;;
;;RESET;0x8000;15;1;
2;PHYIDR1;PHY identifier register 1;;;;
;;PHY_ID;0xFFFF;0;16;
...

Ouputs a file.c with the definition of an array of registers using:

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

Obs.: NULL-terminated register array, with "fields" being a NULL-terminated array of fields.

"""



len_argv = len(sys.argv)
if(len_argv==1):
    print(help_str)
    quit()
elif(sys.argv[1] == "--help" or sys.argv[1] == "-h"):
    print(help_str)
    quit()
elif(len_argv>=2):
    # ---------- Open File ----------
    with open(sys.argv[1]) as file_csv:
        file_c_name = sys.argv[1]

        file_c_name = file_c_name[:file_c_name.rfind('.')]+'.c'

        print(file_c_name)

        file_c = open(file_c_name, 'w')

        reader_csv = csv.reader(file_csv, delimiter=';', quotechar='"')
        
        is_in_reg = 0
        is_in_fields = 0

        str = '#ifdef USE_VERBOSE\n\ntReg phy_regs[/*address*/] =\n{\n'
        file_c.write(str)

        for row in reader_csv:
            addr = row[0]

            if(addr):
                if(addr[0]=='#'):
                    continue
                elif(is_in_reg):
                    # ---- finish reg ----
                    str = '            {}\n        }\n    },\n'
                    file_c.write(str)
                
                # ---- start reg ----
                acr = row[1]
                name = row[2]

                str = f'    \u007b\n        .addr = {addr}, .acr = "{acr}", .name = "{name}",\n        .fields =\n        \u007b\n'
                file_c.write(str)

                is_in_reg = 1
            elif(row[2]):
                name = row[2]
                mask = row[3]
                shift = row[4]
                width = row[5]

                str = f'            \u007b.name="{name}", .mask={mask}, .shift={shift}, .width={width}\u007d,\n'
                file_c.write(str)

        str = '            {}\n        }\n    },\n    {}\n};\n\n#endif'
        file_c.write(str)

        file_csv.close()
        file_c.close()