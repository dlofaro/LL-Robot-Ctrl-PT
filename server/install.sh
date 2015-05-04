sudo ls >> /dev/null
echo 'deb http://code.golems.org/debian squeeze golems.org' | sudo tee --append /etc/apt/sources.list
sudo apt-get update
sudo apt-get install openbsd-inetd
sudo apt-get install build-essential
sudo apt-get install python-dev
sudo apt-get install linux-headers-$(uname -r)
sudo apt-get install autoconf automake libtool autoconf-archive
sudo apt-get install libreadline-dev
sudo apt-get install gcc
sudo apt-get install g++
sudo apt-get install libpopt-dev
#sudo apt-get install libboost-all-dev
#sudo apt-get install libc6-dev
sudo apt-get install libach*
#git clone https://github.com/thedancomplex/ach
#git clone https://github.com/golems/ach
#cd ach
#mkdir build
#cd build
#cmake ../
#autoreconf -i
#./configure 
#make
#sudo make install



echo '8076  stream  tcp  nowait  nobody  /usr/local/bin/achd /usr/local/bin/achd serve' | sudo tee --append /etc/inetd.conf
sudo service openbsd-inetd restart

sudo apt-get install python-pip
sudo pip install http://code.golems.org/src/ach/py_ach-latest.tar.gz

