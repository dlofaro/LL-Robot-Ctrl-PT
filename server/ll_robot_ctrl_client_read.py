import os
import ach
import time
import ll_robot_ctrl_pt_h as pt
from ctypes import *

# state
s = ach.Channel(pt.ACH_CHAN)

state = pt.LL_CTRL_PT()


while True:
  [statuss, framesizes] = s.get(state, wait=True, last=False)
  print str(state.time) + ' ' + str(state.pan) + ' ' + str(state.tilt)
  time.sleep(0.01)
