# EuchreCompanion
Senior Project utilizing libnfc to make a card table game

Cable I/O
3.3V = 4
SCK = 22
MISO = 18
MOSI = 21
SCL = 17
GND = 1

gcc -o quick_start_example1 quick_start_example1.c -lnfc

set date
./configure --with-drivers=pn532_spi
make
make install


http://www.mathworks.com/help/supportpkg/beagleboneio/ug/use-the-beaglebone-black-spi-interface-to-connect-to-a-device.html
