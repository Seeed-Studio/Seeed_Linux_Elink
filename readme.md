# Elink driver for raspberry pi 
*** 
## Usage

### Enable SPI on raspbery pi.
* sudo raspi-config
* select Interface Options
* select SPI
* enable
* exit & save

### install bcm2835 library
Because this library is based on bcm2835 library,we have to install it.you can follow the instructions below:
* wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.57.tar.gz 
* tar zxvf bcm2835-1.57.tar.gz 
* cd bcm2835-1.57
* ./configure
* make
* sudo make check
* sudo make install

If you fail to install the library with the  instructions above.you also can get follow the  official website:http://www.airspayce.com/mikem/bcm2835/.

### Plug the elink shield on raspberry PI.
### sudo reboot

## Test the library：
2.13：
enter 2_13_bcm directory,type:

    make
    sudo ./epd

2.7:
enter 2_7_bcm，type：

    make
    sudo ./epd


***
This software is written by downey  for seeed studio<br>
Email:dao.huang@seeed.cc
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>

