import os
import ach
import time
import ll_robot_ctrl_pt_h as pt
from ctypes import *


f = 0


# make ach 
#os.popen('ach -1 -C '+pt.ACH_CHAN+' -m 10 -n 3000')

# feedforward channel 
r = ach.Channel(pt.ACH_CHAN)
ref = pt.LL_CTRL_PT()

ref.pan = 0.0
ref.tilt = 0.0
ref.time = time.time()




while True:
  ret = os.popen('netcat -lv 8085').read()
  #print "dan ",ret
  spl = ret.split(' ', 3)
  #print spl

  if spl[0] == 'GET':
    fi = spl[1]
    f = fi[1:]
    data = f.split(',', 3)
#    print f
#    print data[0]+' '+data[1]+' '+data[2]
    ref.pan = float(data[1])/1.0
    ref.tilt = float(data[2])/1.0
    ref.time = time.time() 
    r.put(ref)
    print str(ref.time) + ' ' + str(ref.pan) + ' ' + str(ref.tilt)

