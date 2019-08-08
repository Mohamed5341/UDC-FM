---
layout: default
title: Algorithm with Tiva C
parent: Airspeed
nav_order: 5
---

Be Careful
{: .label .label-red}
You need to initialize clock first before using ADC (if you don't initalize clock module wouldn't work)

Be Careful
{: .label .label-red}
Because sensor works with 5 volts and Tiva C works with 3.3 volts this may be problem (Tiva C provides 3.3 volt but sensor needs 4.75 minimum volt You can use external source of power for example use Arduino board, ADC module in Tiva C works with 3.3 vref and this can't be changed this means that max value you can measure is 3.3 volt so the range from 3.3 V to 5 V you can't measure. Datasheet mentioned that it's pins can used with 5 volt input but if you give ADC 5 volts it can't measure it, but  you can use voltage divider)

Voltage divider is a circuit used to minimize volt to lower level using resistors.
{% include image.html url="/assets/voltage_divider.png" description="Voltage Divider" %}
<dl>
	<dt>$$V_{in}$$</dt>
	<dd>it is the voltage you want to lower its level</dd>
	<dt>$$V_{out}$$</dt>
	<dd>it is the voltage you will measure (after minimzing input voltage)</dd>
</dl> 
You can use this equation to get the ratio between input voltage and output voltage:
<br>
<br>
<span>$$V_{out} = V_{in} * \frac{R_2}{R_1 + R_2}$$</span>
<br>
<br>
If you want to minimize the volt you can put the values of max volt for sensor and and max volt for input and get the ratio between R1 & R2 then you can use any resistors with this ratio 
<br>
<span>$$V_{in} = 5$$</span>
<br>
<span>$$V_{out} = 3.3$$</span>
<br>
<span>$$V_{out} = V_{in} * \frac{R_2}{R_1 + R_2}$$</span> ==> <span>$$3.3 = 5 * \frac{R_2}{R_1 + R_2}$$</span>
<br>
<span>$$\frac{3.3}{5} * (R_1 + R_2) = R_2$$</span>
<br>
<span>$$\frac{R_1}{R_2} = \frac{17}{33}$$</span>
<br>
so you can use for example R1 = 1700 ohm and R2 = 3300 ohm

Connections: Vin and GND are connected to external source and ANALOG pin is connected to PE3 (channel 0 of ADC) this connection in case of not using voltage divider if you use voltage divider connect analog to Vin of voltage divider and connect Vout to pin PE3 in Tiva C.

The code works in 3 steps (but don't forget to initaite clock):
* Initiate GPIO pin
* Initiate ADC module
* Read data

Initaite GPIO pin in our case we use PE3:
* Provide clock to port E using **RCGCGPIO** register , write value 0x00000010
{% include image.html url="/assets/rcgcgpio_reg_ene.JPG" description="RCGCGPIO Register" %}
* Enable clock to ADC module 0 using **RCGCADC** register , write 0x00000001
{% include image.html url="/assets/rcgcadc_reg_adc0.jpg" description="RCGCADC Register" %}
* Choose alternate function to pin 3 in port E using **GPIOAFSEL** register for port E , write 0x00000008 
{% include image.html url="/assets/gpioafsel_reg_pe3.JPG" description="GPIOAFSEL Register" %}
* Disable digital function to port E using **GPIODEN** register ,  clear bit 3 in register
{% include image.html url="/assets/gpioden_reg_dis3.JPG" description="GPIODEN Register" %}
* Enable analog mode to pin 3 in port E using **GPIOAMSEL** , write value 0x00000008
{% include image.html url="/assets/gpioamsel_reg_en3.JPG" description="GPIOAMSEL Register" %}
* Disable sample seqencer 3 using **ADCACTSS** register , clear bit 3
{% include image.html url="/assets/adcactss_reg_dis3.jpg" description="ADCACTSS Register" %}
* Choose processor trigger to read data using register **ADCEMUX** register , clear bits 12:15
{% include image.html url="/assets/adcemux_reg_dissq3.jpg" description="ADCEMUX Register" %}
* Choose which channel(pin) to read from using **ADCSSMUX3** register, write value 0x0000000
{% include image.html url="/assets/adcssmux3_reg_ain0.jpg" description="ADCSSMUX3 Register" %}
* Control some settings using register **ADCSSCTL3** register, write value 0x00000006
{% include image.html url="/assets/adcssctl3_reg_siend_int.jpg" description="ADCSSCTL3 Register" %}
<dl>
	<dt>bit 3 (TS0)</dt>
	<dd>this bit is 0 because we raed from pins not internal temperature sensor</dd>
	<dt>bit 2 (IE0)</dt>
	<dd>this bit is 1 because we need flag to change after conversion endded</dd>
	<dt>bit 1 (END0)</dt>
	<dd>this bit is 1 because we get one sample</dd>
	<dt>bit 0 (D0)</dt>
	<dd>this bit is 0 because we use single endded</dd>
</dl>
* Enable sample seqencer 3 using **ADCACTSS** register , write value 0x00000008
{% include image.html url="/assets/adcactss_reg_en3.jpg" description="ADCACTSS Register" %}
* Begin (trigger) measuring transmission using **ADCPSSI** register, write value 0x00000008
{% include image.html url="/assets/adcpssi_reg_trig3.jpg" description="ADCPSSI Register" %}
* Wait untill conversion is done using **ADCRIS** register, wait until value of bit3 becomes 1
{% include image.html url="/assets/adcris_reg_inr3.jpg" description="ADCRIS Register" %}
* Read data from register **ADCSSFIFO3** register (this value is 12 bits you should store it in 2 bytes variable)
{% include image.html url="/assets/adcssfifox_reg.JPG" description="ADCSSFIFO3 register" %}
* You should clear the flag using **ADCISC** register, clear bit 3
{% include image.html url="/assets/adcisc_reg_cl3.jpg" description="ADCISC register" %}

* You can calculate voltage from number you read
<br><br>
<span>$$volt = output * \frac{3.3}{4096}$$</span> 
<br>
But if you use voltage divider the equation will be different
<br><br>
<span>$$volt = (output * \frac{3.3}{4096}) * \frac{5}{3.3}$$</span>
<br><br>
Then you can get pressure difference from equation
<br><br>
<span>$$\Delta P = volt - 2.5$$</span>
<br><br>
Calculate speed from Bernouli's equation
<br><br>
<span>$$v = \sqrt{\frac{2 * \Delta P}{\rho}}$$</span>



<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>