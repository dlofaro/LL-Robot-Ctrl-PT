import os
import ach
import ll_robot_ctrl_pt_h as pt
from ctypes import *


f = 0


# make ach 
os.popen('ach -1 -C '+pt.ACH_CHAN+' -m 10 -n 3000')

# feedforward channel 
r = ach.Channel(pt.ACH_CHAN)

while True:
  ret = os.popen('netcat -lv 8085').read()
  #print "dan ",ret
  spl = ret.split(' ', 3)
  #print spl

  if spl[0] == 'GET':
    fi = spl[1]
    f = fi[1:]
    data = f.split(',', 3)
    print f
    print data[0]+' '+data[1]+' '+data[2]


