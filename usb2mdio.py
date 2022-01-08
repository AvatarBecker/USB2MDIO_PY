#!/usr/bin/env python3

# Get arguments from outside:
#    connect [port] <speed=9600>
#
#    After connected:
#        write <reg> <value>     #formats: 23 or 0x17 or b00010111
#        write -h <reg> <value>  #format: reg name/name.field; value in above form
#        read [-h] <reg>
#        dump [-h]
#        [-ti] file    # file containing a list of the commands above, same syntax; if -ti, use texas format
#        


# Ideas/TODO:
# Use files for verbose dump of registers: represent as class/structure like Basic_Control_Reg.Master_!Slave
#     Maybe we could use the format/code from Unix drivers...?
#     Maybe the same as for C?
# 0. Accept commands and parse them (COM connect)
# 1. COM connect and RW COM port
# 2. Get USB2MDIO sequences for write/read



# treat arguments

# with serial.Serial(get from args) as com_port:


def PrintHelp():
   print("help yourself! (TODO)")

def PrintError():
   print("Unrecognized command. Try typing 'help'")

def WriteReg():
   pass

def ReadReg():
   pass

while(1):
   usr_data_raw = input("> ")
   
   usr_data = usr_data_raw.split()
   len_usr_data = len(usr_data)

   if(len_usr_data==0):
      continue

   if(usr_data[0] in ("exit", "exit()", "quit", "quit()")):
      quit()
   elif(usr_data[0] in ("help", "--help", "h", "-h", "?")):
      PrintHelp()

   # is file?
   try:
      usr_script = open(usr_data[0])
      print("Opened the file no worries!")
      continue
   except FileNotFoundError:
      pass

   # is address?
   try:
      addr = int(usr_data[0], 16) #hex
   except ValueError:
      try:
         addr = int(usr_data[0], 10) #decimal
      except ValueError:
         try:
            addr = int(usr_data[0], 2) #bin
         except ValueError:
            try:
               addr = int(usr_data[0], 10) #octal
            except ValueError:
               pass
   finally:
      print(addr)
      continue

   PrintError()