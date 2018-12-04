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

然後PIN是來讀腳位資料用的

## 12/4更新
看了一些網路上的教學，先把程式碼抄下來用，設定甚麼的可能要慢慢摸索datasheet了。
### PWM
參考網址：https://www.youtube.com/watch?v=ZhIRRyhfhLM&t=766s
```c=
/*
 * PWM.c
 *
 * Created: 3/20/2013 9:29:11 PM
 *  Author: SAM
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double dutyCycle = 0;

int main(void)
{	
    DDRD = (1 << PORTD6);
    
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
    
    OCR0A = (dutyCycle/100.0)*255.0;
    
    sei();
    
    TCCR0B = (1 << CS00) | (1 << CS02);
    
    while(1)
    {
        //TODO:: Please write your application code
    	_delay_ms(100);
    	
    	dutyCycle += 10;
    	
    	if(dutyCycle > 100)
    	{
    		dutyCycle = 0;
    	}						
    }
}

ISR(TIMER0_OVF_vect)
{
    OCR0A = (dutyCycle/100.0)*255;
}
```
上面牽扯到了一堆設定，而且還用到了計數中斷。
如果從while迴圈來看，每隔0.1秒dutyCycle就會加10，大於100就跳回0。
下方函式應該是計數中斷觸發的時候，就會把dutyCycle的資料傳給OCR0A，這好像是跟PORTD6是連動的，所以最後在PD6腳就會輸出一個週期為1秒的三角波。

### Analog Input
參考網址：https://www.youtube.com/watch?v=51QJ_WHN7u0&t=64s
```c=
/*
 * ADCexample.c
 *
 * Created: 4/13/2013 5:22:48 PM
 *  Author: SAM
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

double dutyCycle = 0;

int main(void)
{
    DDRD = (1 << PORTD6);
    
    TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
    
    setupADC();
    
    sei();
    
    TCCR0B = (1 << CS00) | (1 << CS02);
    
    while(1)
    {
    	//TODO:: Please write your application code
    }
}

void setupADC()
{
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    DIDR0 = (1 << ADC5D);
	
    startConversion();
}

void startConversion()
{
    ADCSRA |= (1 << ADSC);
}

ISR(TIMER0_OVF_vect)
{
    OCR0A = dutyCycle;
}

ISR(ADC_vect)
{
    dutyCycle = ADC;
    startConversion();
}
```
同樣也有用到計數中斷，計數的設定跟上面的PWM差不多，只是analog方面我幾乎就看不懂了，好像也有用到中斷。
我的猜測是這樣，在main()有一行叫setupADC()，很直觀應該就是設定ADC了。
設定完就是startConrversion()，好像是啟動analog中斷吧?
最下面的ISR(ADC_vect)大概是analog中斷發生時的處理吧，把資料讀過去後一樣要startConrversion()。
