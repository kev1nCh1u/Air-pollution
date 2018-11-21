# 程式操作紀錄

## 2018/11/21更新
以前在做小鍵盤是用AVR studio7開發的，其實完全就只是改寫程式碼而已，一堆細節我還是不太懂

總之今天我先把它裝回來

一開始先建新專案
![](https://i.imgur.com/wSK4996.png)
~~依照我的直覺~~應該是選c executable選項

![](https://i.imgur.com/MzQAs0E.png)
選擇我們要用的晶片

￼￼![](https://i.imgur.com/w4u2TmL.png)
大概寫了一下程式，就只是普通的亮滅程式而已

再來就讓他跑編譯產生hex檔
燒錄器的部分，我直接用arduino來代替，並且透過avrdude來燒錄，一些小步驟我就懶得講了，去cmd下以下指令就能燒進去了。
```
avrdude -q -c avrisp -P com3 -b 19200 -p atmega328p -U flash:w:(檔案位置):i
```
