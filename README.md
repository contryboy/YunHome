家庭云信息YunHome
=======

本项目使用开源硬件组建家庭云信息系统，该系统可以从Internet获取各类常用信息（如天气预报等），并且在一个TFT显示屏上显示。

目前该项目使用两个硬件:

1. 一块Arduino Yun开发板(http://arduino.cc/)， 你可以从Arduino 中国代理的天猫商店上购买到：http://xidikaiyuanshuma.tmall.com/
2. 一块矽递 2.8" TFT触摸屏扩展卡，也可以从该商店购买到：http://xidikaiyuanshuma.tmall.com

安装配置：
1. 将触摸屏扩展卡插入Arduino开发板，然后用Micro USB连接线连接电脑和Arduino。
2. 参照http://arduino.cc/en/Guide/ArduinoYun 的描述安装驱动程序和设置WiFi。
3. 下载并安装Ardunio IDE (http://arduino.cc/en/Main/Software), Arduino Yun要求1.5.5以上版本。
4. 运行IDE，Tools->Board->选择Ardiuno Yun；Port->选择Ardiuno Yun所在的端口。
5. Sketch->Import Library...，在弹出框选择本项目里面arduino-src/libraries/SeeedTFTv2目录；同样方式选择SeeedTouchScreen目录。

运行调试：
1. 运行样例程序: File->Examples->SeeedTFTv2->drawCircle，然后Verify, Upload，完毕后可以看到屏幕上出现不同颜色的圆形；同样方式可以测试其他样例程序。

