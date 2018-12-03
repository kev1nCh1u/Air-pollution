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

## 11/24更新
之前的燒錄方式，我來講清楚點好了
以下步驟為第一次燒錄時區要做的設定
首先先知道自己arduino的資料夾，如果沒下載的就去下載吧。

再來去對'我的電腦'右鍵內容，左邊那四個選進階系統設定
![](https://i.imgur.com/PZQZ15N.png)

接著按環境變數
![](https://i.imgur.com/HWuxsJn.png)

下面的系統變數點選path後按編輯
![](https://i.imgur.com/jbFoTbi.png)

點選新增，把你剛剛記的arduino位置，裡面的hardware\tools\avr的bin、avr\bin、etc三個資料夾的位置全部編進來
![](https://i.imgur.com/aDghbQT.png)

開啟cmd，打上avrdude，如果出現此畫面就代表成功了
![](https://i.imgur.com/oQ4AJlE.png)

再來是燒錄，這邊我因為沒有燒錄器，所以用arduino來代替。
燒錄之前請先開arduino IDE，把example裡的ArduinoISP這個範例程式碼燒進你的arduino板子裡。

再來把你要燒的atmega328接好
![](https://i.imgur.com/aLJMStW.png)

一切就緒之後，輸入這個指令就完成了
```
avrdude -q -c avrisp -P com3 -b 19200 -p atmega328p -U flash:w:(檔案位置):i
```

## 12/3更新
### input的使用方法
參考網址：http://www.elecrom.com/avr-tutorial-2-avr-input-output/
先付上程式碼
```c=
/*
 * test2.c
 *
 * Created: 2018/11/30 上午 10:22:30
 * Author : bsiotmceh
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0x00;
    PORTC |= 0b00000011; 
	
    while (1) 
    {
        if((PINC & 0b00000001)==1)
            PORTB |= 0b00100000;
        else if((PINC & 0b00000001)==0)
            PORTB &= 0b11011111;
    }
}
```
一開始DDR就是設定輸入輸出，1為輸出0為輸入，可是我嘗試在B設定輸入，但是燒進去後都沒有成功，後來改成C輸入，燒進去就成功了，真神奇。