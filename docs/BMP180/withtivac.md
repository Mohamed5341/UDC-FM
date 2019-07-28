---
layout: default
title: Algorithm with Tiva C
nav_order: 5
parent: BMP180
---

Be Careful
{: .label .label-red}
Before you configure I2C module you need to configure system clock speed, this work is used for 16MHz clock speed.

First, lets start with connections
{% include image.html url="/assets/bmp180connections.png" description="BMP180 connections with TivaC" %}

Second, lets configure I2C1 module:
* Enable clock to module using **RCGCI2C** register. write the value 0x00000002 
{% include image.html url="/assets/rcgci2c_reg_en1.jpg" description="RCGCI2C register" %}
* Enable clock to I2C pins (in our case PA6,PA7), but we enable clock to port not pins so we enable clock to port A using **RCGCGPIO** register. write value 0x00000001
{% include image.html url="/assets/rcgcgpio_reg_en0.jpg" description="RCGCGPIO register" %}
* Select pins for alternate function using **GPIOAFSEL** register, write the value 0x000000C0
{% include image.html url="/assets/gpioafsel_reg_en67.jpg" description="RCGCAFSEL register" %}
* Choose the other function type using **GPIOPCTL** register, write value 0x33000000
{% include image.html url="/assets/gpiopctl_reg_eni2c.jpg" description="GPIOPCTL register" %}

Be Careful
{: .label .label-red}
Make sure you first clear bits 31:24 then write the value.
* Enable digital function to pins using **RCGCDEN** register, write the value 0x000000C0
{% include image.html url="/assets/gpioden_reg_en67.jpg" description="RCGCDEN register" %}
* Enable open-drain to data pin (in our case PA7) using **GPIOODR** register, write the value 0x00000080
{% include image.html url="/assets/gpioodr_reg_en7.jpg" description="GPIOODR register" %}
* Configure TivaC as Master using **I2CMCR** register, write value 0x00000010
{% include image.html url="/assets/i2cmcr_reg_mfe.jpg" description="I2CMCR register" %}
* Set clock speed using **I2CMTPR** register, write value 0x00000007 this value is calculated from relation:
<span>$$TPR=\frac{clockfreq}{20 * I2Cclock}-1=\frac{16MHz}{20 * 100Kbps}-1=\frac{16000000}{20 * 100000}-1=7$$</span>
{% include image.html url="/assets/i2cmtpr_reg_7.jpg" description="I2CMTPR register" %}
this was the initialization of I2C module now lets begin with sensor:
* We need to read some data (AC1,AC2,...) from some registers in BMP180 each one is 16 bits (you can get it reading from 2 registers)

Be Careful
{: .label .label-red}
Although all data you read are in consecutive memory locations, if you try to brust read (read all 22 bytes) this would not work. you can brust read 2 bytes at once then you end communications and then start reading next 2 bytes until you finish.
<br>
lets start with AC1 and the rest are in the same way
* Write slave address and process you want (read or write) in **I2CMSA** register, write the value 0xEE (0x77 is BMP address and 0 in last bit is for write)
{% include image.html url="/assets/i2cmsa_reg_writebmp.jpg" description="I2CMSA register" %}
* Wait for Bus if it is busy (another I2C device use the bus) by reading **I2CMCS** register, wait until busbsy bit be 0
{% include image.html url="/assets/i2cmcs_reg_ro_busbsy.jpg" description="I2CMCS register" %}
* Write the location of AC1 MSB register using **I2CMDR** register, write 0x000000AA
{% include image.html url="/assets/i2cmdr_reg_bmpac1.jpg" description="I2CMDR register" %}
* Start and Run (send start bit and send the data to the address) using **I2CMCS** register, Write the value 0x00000003
{% include image.html url="/assets/i2cmcs_reg_wo_sr.jpg" description="I2CMCS register" %}
* Wait for transmission ends if it is busy (data isn't sent yet) by reading **I2CMCS** register, wait until busy bit be 0
{% include image.html url="/assets/i2cmcs_reg_ro_busy.jpg" description="I2CMCS register" %}
* Check if error happens by using **I2CMCS** register, read value of error bit if it is 0 no error
{% include image.html url="/assets/i2cmcs_reg_ro_error.jpg" description="I2CMCS register" %}
* If error happens you need to check if you lost arbitration if it happens you need to send stop bit to check lost of arbitration use **I2CMCS** register, read value of ARBLST if it is 1 you need to send stop bit using **I2CMCS** register, write the value 0x00000004
{% include image.html url="/assets/i2cmcs_reg_ro_arblst.jpg" description="I2CMCS register" %}
{% include image.html url="/assets/i2cmcs_reg_wo_s.jpg" description="I2CMCS register" %}
* Write slave address for read to start read data which BMP180 will send using **I2CMSA** register, write the value 0xEF (0x77 is BMP address and 1 in last bit is for read)
{% include image.html url="/assets/i2cmsa_reg_bmpread.jpg" description="I2CMSA register" %}
* Send restart bit and run and acknowledge if data is sent from BMP180 using **I2CMCS** register, write the value 0x0000000B
{% include image.html url="/assets/i2cmcs_reg_wo_sra.jpg" description="I2CMCS register" %}
* Check if busy and check for error as previous.
* Read data which comes from BMP180 (AC1 MSB) from **I2CMDR** register
* Run the next read process and aknowledge if data is recieved using **I2CMCS** register, Write the value 0x00000009
{% include image.html url="/assets/i2cmcs_reg_wo_sa.jpg" description="I2CMCS register" %}
* Check if busy and check for error as previous.
* Read data which comes from BMP180 (AC1 LSB) from **I2CMDR** register
* Stop transmission process using **I2CMCS** register, Write the value 0x00000004
{% include image.html url="/assets/i2cmcs_reg_wo_s.jpg" description="I2CMCS register" %}

* You can read rest of variables (AC2,AC3,...) in the same way

* We need to write value 0x2E in **control** register (0xF4) so the sensor measure UT and put it in data register (0xF6,0xF7)
* Write slave address and process you want (read or write) in **I2CMSA** register, write the value 0xEE (0x77 is BMP address and 0 in last bit is for write)
{% include image.html url="/assets/i2cmsa_reg_writebmp.jpg" description="I2CMSA register" %}
* Wait for Bus if it is busy (another I2C device use the bus) by reading **I2CMCS** register, wait until busbsy bit be 0
{% include image.html url="/assets/i2cmcs_reg_ro_busbsy.jpg" description="I2CMCS register" %}
* Write the location of **control** register in **I2CMDR** register, write 0xF4
{% include image.html url="/assets/i2cmdr_reg_bmpctrl.jpg" description="I2CMDR register" %}
* Start and Run (send start bit and send the data to the address) using **I2CMCS** register, Write the value 0x00000003
{% include image.html url="/assets/i2cmcs_reg_wo_sr.jpg" description="I2CMCS register" %}
* Wait for transmission and check for errors as previous
* Write value (0x2E) in **I2CMDR** register 
* Run transmission process and stop bit using **I2CMCS** register, write value 0x00000005
{% include image.html url="/assets/i2cmcs_reg_wo_rs.jpg" description="I2CMCS register" %}
* Wait for transmission and check for errors as previous
* Delay conversion time 5ms
* Read content of registers 0xF6(MSB),0xF7(LSB) and this is UT value.
* We need to write value for **control** register (0xF4) so sensor read UP and put data in registers (0xF6,0xF7,0xF8) and this process as previous.
* Do the calculations as datasheet mention and be careful with these calculations you may write wrong equation.

Be Careful
{: .label .label-red}
Temperature value is in 0.1 C (This means you need to divide temperature value by 10 to get temperature in celsius) 

* To calculate altitude you need to substitute with pressure value in this equation:
<span>$$altitude=44330 * (1 - ({\frac{P}{P_0}})^{\frac{1}{5.255}})$$</span>
<br>
Where:
<dl>
	<dt>P</dt>
	<dd>is measured pressure</dd>
	<dt>P<sub>0</sub></dt>
	<dd>is pressure at which you measure data from (if you measure altitude from sea level this is pressure at sea level)</dd>
</dl>

Be Careful
{: .label .label-red}
P<sub>0</sub> at sea level is not constant (not 101325 pa)


<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
