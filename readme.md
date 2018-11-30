# 操作指南：
将树莓派上的spi使能
raspi-config ==> Interface Options ==> SPI ==> select ==> yes

## 安装bcm2835库：
官网：http://www.airspayce.com/mikem/bcm2835/(可按照下面指令安装，一般情况下不需要去官网下载)


### 按照下面的指令安装：
注意：1.xx对应具体版本号，比如下载的是1.57，就替换成1.57

wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.57.tar.gz 
tar zxvf bcm2835-1.xx.tar.gz
cd bcm2835-1.xx
./configure
make
sudo make check
sudo make install


## 使用：
2.13：
进入 2_13_bcm,键入命令：

    make clean && make
    sudo ./epd

2.7
进入2_7_bcm，键入命令：

    make clean && make
    sudo ./epd


## 注意
2.13和2.7可能存在冲突，测试完一个换成另一个时最好重启树莓派。

