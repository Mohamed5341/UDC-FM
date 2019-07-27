---
layout: default
title: Communication Protocol
parent: BMP180
nav_order: 4
---

This sensor uses I2C protocol. lets see how it works:

{% include image.html url="/assets/i2c_connect.jpg" description="I2C Bus interface" %}

I2C (Inter-Integrated Circuit) is 2 wire interface protocol (means protocol use 2 wires to transfer data). All devices connected together with 2 wires, **SCL** (Serial clock is the wire for transmitting clock), **SDA** (Serial data is the wire for transmitting data). SDA must be open drain if one device pull it to zero volt it becomes zero volt (logic 0), and if no device pull it to zero volt it becomes high volt (logic 1).
Each device connected to the Bus is called **Node**. each node may be master or slave:
<dl>
	<dt>Master</dt>
	<dd>is the device which generate the clock.</dd>
	<dt>Slave</dt>
	<dd>is the device which receive the clock.</dd>
</dl>
Master or Slave both can send or receive data (not only master sends)

It is synchronized serial protocol this means that data is transmitted when clock is high and is changed when it is low.

{% include image.html url="/assets/datachange.jpg" description="I2C bits send and change" %}
Transmission process starts with **Start bit** and ends with **Stop bit**

{% include image.html url="/assets/startstopbits.jpg" description="I2C Start and Stop conditions" %}
<dl>
	<dt>Start bit</dt>
	<dd>When clock is high data line changes from High to Low.</dd>
	<dt>Stop bit</dt>
	<dd>When clock is high data line changes from Low to High.</dd>
</dl>
Data is sent between them and bus is busy (the master which generates clock is the only device can send data no other device can send).
{% include image.html url="/assets/i2c_bytesend.jpg" description="I2C byte send" %}
{% include image.html url="/assets/i2c_bytesreceive.jpg" description="I2C byte receive" %}

<dl>
	<dt>Start</dt>
	<dd>start bit.</dd>
	<dt>Slave address</dt>
	<dd>the address of the slave which master want to start communication with.</dd>
	<dt>Read/Write</dt>
	<dd>is the process which master wants to initate (read process 1, write process 0).</dd>
	<dt>ACK(Acknowledge)</dt>
	<dd>is bit is sent from the device recieve data this is check for that device received data (0) if the deveice which receive the data don't want to receive more data it sends negative ACK (1).</dd>
	<dt>Location address</dt>
	<dd>is the memory location you want send data to or receive data from.</dd>
	<dt>Restart</dt>
	<dd>if the master doesn't want to leave bus and want to start new transmission process it sends start bit again called Repeated start (it is the same as start bit).</dd>
	<dt>Stop</dt>
	<dd>stop bit.</dd>
</dl>


Now lets see how Tiva C work with I2C, Tiva C has 4 I2C modules, each module can be configured and run using some registers.

| I2C Module | SCL pin | SDA pin |
|:-----------|:--------|:--------|
| I2C0       | PB2     | PB3     |
| I2C1       | PA6     | PA7     |
| I2C2       | PE4     | PE5     |
| I2C3       | PD0     | PD1     |

<br>
* You can enable clock to I2C module using **RCGCI2C** register
{% include image.html url="/assets/rcgci2c_reg.jpg" description="RCGCI2C register" %}
each bit controls clock for I2C module

<dl>
	<dt>R3</dt>
	<dd>if it is 1 clock is enabled to I2C3 module<br>if it is 0 clock is disabled</dd>
	<dt>R2</dt>
	<dd>if it is 1 clock is enabled to I2C2 module<br>if it is 0 clock is disabled</dd>
	<dt>R1</dt>
	<dd>if it is 1 clock is enabled to I2C1 module<br>if it is 0 clock is disabled</dd>
	<dt>R0</dt>
	<dd>if it is 1 clock is enabled to I2C0 module<br>if it is 0 clock is disabled</dd>
</dl>

<br>
* you can configure clock speed using **I2CMTPR** register
{% include image.html url="/assets/i2cmtpr_reg.jpg" description="I2CMTPR register" %}

<dl>
	<dt>HS</dt>
	<dd>High speed enable is used to control clock speed if it is set high speed mode is enabled (3.33Mbps), else high speed mode disabled</dd>
	<dt>TPR</dt>
	<dd>Timer period is value you write in register (6:0 bits), this value can be get from this equation
		<span>$$TPR=\frac{clockfreq}{20*I2Cclock}-1$$</span>
		<dl>
			<dt>clockfreq</dt>
			<dd>is the system clock.</dd>
			<dt>I2Cclock</dt>
			<dd>is the clock speed of I2C bus.</dd>
		</dl>
	</dd>
</dl>

<br>
* You can select operating mode (master or slave) using **I2CMCR** register
{% include image.html url="/assets/i2cmcr_reg.jpg" description="I2CMCR register" %}

<dl>
	<dt>MFE</dt>
	<dd>Master function enable is bit control master function if it is set (1) master function is enabled and if it is clear (0) master function is disabled</dd>
	<dt>SFE</dt>
	<dd>Slave function enable if it is set (1) slave mode is enabled (Tiva C works as slave) and if it is clear (0) slave mode is disabled</dd>
</dl>


<br>
* You can write slave address you want to communicate with using **I2CMSA** register 
{% include image.html url="/assets/i2cmsa_reg.jpg" description="I2CMSA register" %}

<dl>
	<dt>SA</dt>
	<dd>Slave Address is the address of the slave you will communicate with</dd>
	<dt>R/S</dt>
	<dd>Receive/Send is a bit which specify the process if it is receive it becomes high (1) and if it is send it becomes low (0).</dd>
</dl>


<br>
* You can start end communication and also see communication status using **I2CMCS** register
this one is two registers one for read and the other for write
{% include image.html url="/assets/i2cmcs_reg_ro.jpg" description="I2CMCS register for read only" %}
<dl>
	<dt>BUSBSY</dt><dd>this bit is 1 if bus is busy and it is 0 if bus is free</dd>
	<dt>IDLE</dt><dd>I2C device is IDLE (maens it is ready for communication) if it is 1 and it is not IDLE if it is 0</dd>
	<dt>ARBLST</dt><dd>Arbitration lost if it is 1 arbitration lost(this means that error happened while communication process and this error is happened because another device start communication with the device and while communication the two devices send the same bits until one device sends 1 and the other sends 0 because SDA becomes high when no device pull the current and in this case one device pull current so the device which sends 1 stop communication and this is called arbitration lost)</dd>
	<dt>DATACK</dt><dd>Acknowledge if it is 0 the ACK bit is sent and if it is 1 NACK is sent</dd>
	<dt>ADRACK</dt><dd>Address Acknowledge is the ACK bit sent after sending slave address if it is 0 it is ACK and if it is 1 it is NACK</dd>
	<dt>ERROR</dt><dd>Error if it is 0 no error happened while communication process and if it is 1 error happened</dd>
	<dt>BUSY</dt><dd>if it is 1 the controller is busy and if it is 0 the controller is idle</dd>

</dl>
{% include image.html url="/assets/i2cmcs_reg_wo.jpg" description="I2CMCS register for write only" %}
<dl>
	<dt>HS</dt><dd>High Speed enable if this bit is set high speed mode enabled and if it is clear high speed mode is disabled</dd>
	<dt>ACK</dt><dd>Acknowledge if this bit is set (1) ACK bit will be sent and if it is clear (0) NACK will be sent</dd>
	<dt>STOP</dt><dd>if this bit is set (1) stop bit is generated</dd>
	<dt>START</dt><dd>if this bit is set (1) start bit is generated</dd>
	<dt>RUN</dt><dd>if this bit is set (1) master can send or receive data</dd>
</dl>

<br>
* You can read and write data you send and receive using **I2CMDR** register
{% include image.html url="/assets/i2cmdr_reg.jpg" description="I2CMDR registery" %}
you can write data in bits 7:0




<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
