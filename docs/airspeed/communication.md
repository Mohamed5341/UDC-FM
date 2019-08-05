---
layout: default
title: Communication
parent: Airspeed
nav_order: 4
---

Airspeed sensor outputs analog signal correspond to pressure difference. You can read this signal using **ADC**(Analog to Digital covertor) module in Tiva C. This module takes analog signal as input and outputs digital number correspond to this value.
Tiva C has 2 ADC modules(AD0, AD1). it has 12 bits resolution (this means that lowest value you can measure is 3.3V / (2^12) = 1.22mV). it has 12 channels(it can read from 12 pins). 
* You can provide clock to module using **RCGCADC** register
{% include image.html url="/assets/rcgcadc_reg.JPG" description="RCGCADC register" %}
<dl>
	<dt>R0</dt>
	<dd>If it is 1 clock is enabled to module 0<br>If it is 0 clock is disabled to module 0</dd>
	<dt>R1</dt>
	<dd>If it is 1 clock is enabled to module 1<br>If it is 0 clock is disabled to module 1</dd>
</dl>
* You can use **ADCACTSS** register to enable sample sequencers
{% include image.html url="/assets/adcactss_reg.JPG" description="ADCACTSS register" %}
Tiva C has 4 sample sequencers. They are used to get number of samples each one take different number of samples. You must disable ADC module while configuring sample sequencer to avoid errors.

| Sequencer | Number of Samples  | Depth of FIFO |
|:----------|:-------------------|:--------------|
| SS0       | 8                  | 8             |
| SS1       | 4                  | 4             |
| SS2       | 4                  | 4             |
| SS3       | 1                  | 1             |

You can enable any one by setting ASENx (x is the number of sequencer)bit.
* You can select the way to trigger (start reading data and put it in data register) using **ADCEMUX** register
{% include image.html url="/assets/adcemux_reg.JPG" description="ADCEMUX register" %}
write the value of the trigger in the corresponding bits (if you use sample sequencer 3 write in EM3). Trigger value  of processor (software ask the ADC to read) is 0x00 and other values in datasheet.
* To start conversion from sample sequencers using processor you can use **ADCPSSI** register
{% include image.html url="/assets/adcpssi_reg.JPG" description="ADCPSSI register" %}
You write in the bit correspond to selceted sample sequencer and conversion is started.
* You can select channel(pin) for input from **ADCSSMUXx** register (where x correspond to sample sequencer number)
{% include image.html url="/assets/adcssmux0_reg.JPG" description="ADCSSMUX0 register" %}
{% include image.html url="/assets/adcssmux12_reg.JPG" description="ADCSSMUX1 & ADCSSMUX2 registers" %}
{% include image.html url="/assets/adcssmux3_reg.JPG" description="ADCSSMUX3 register" %}
You write pin number in the corresponding sample number bit (if you use pin AIN0 you need to write its value 0 in the MUX of samples so when start reading values Tiva C know that at sample x it reads from which pin you write in MUXx)
* You can check conversion end from **ADCRIS** register 
{% include image.html url="/assets/adcris_reg.JPG" description="ADCRIS register" %}
if bit INRx is set this means sample sequencer x finished conversion
* Output data is at **ADCSSFIFOx** register (x corresponds to sequencer number)
{% include image.html url="/assets/adcssfifox_reg.JPG" description="ADCSSFIFOx register" %}
* After you read data you need to clear flag using **ADCISC** register
{% include image.html url="/assets/adcisc_reg.JPG" description="ADCISC register" %}
clear INx bit.
* You can specify some settings from **ADCSSCTLx** register
{% include image.html url="/assets/adcssctl0_reg.JPG" description="ADCSSCTL register" %}
{% include image.html url="/assets/adcssctl12_reg.JPG" description="ADCSSCTL1 & ADCSSCTL2 registers" %}
{% include image.html url="/assets/adcssctl3_reg.JPG" description="ADCSSCTL3 register" %}
each 4 bits corresponds to sample number (D0,END0,IE0,TS0 configures first sample).
* You can enable intterupt using **ADCIM** register
{% include image.html url="/assets/adcim_reg.JPG" description="ADCIM register" %}
if MASKx is 1 this means that sample sequencer number x is going to make intterupt to controller and if it is 0 the sample sequencer is not going to send interrupt and it just going to change the flag.





