import os

f = 0

while True:
  ret = os.popen('netcat -lv 8085').read()
  #print "dan ",ret
  spl = ret.split(' ', 3)
  #print spl

  if spl[0] == 'GET':
    fi = spl[1]
    f = fi[1:]
    print f


