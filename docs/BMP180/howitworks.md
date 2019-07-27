---
layout: default
title: How it works
parent: BMP180
nav_order: 3
---

From Datasheet:
{% include image.html url="/assets/bmp180_algorithm.jpg" description="Sensor Algorithm" %}
The steps in this figure are the algorithm for getting Pressure and Temperature from sensor. First you need to read some data from sensor then do some calculations to these data to get Pressure and temperature. 
{% include image.html url="/assets/bmp180_algorithm_steps.jpg" description="Sensor Algorithm in details" %}



|           | BMP180 register Address |
| Parameter | MSB         | LSB       |
|:----------|:------------|:----------|
| AC1       | 0xAA        | 0xAB      |
| AC2       | 0xAC        | 0xAD      |
| AC3       | 0xAE        | 0xAF      |
| AC4       | 0xB0        | 0xB1      |
| AC5       | 0xB2        | 0xB3      |
| AC6       | 0xB4        | 0xB5      |
| B1        | 0xB6        | 0xB7      |
| B2        | 0xB8        | 0xB9      |
| MB        | 0xBA        | 0xBB      |
| MC        | 0xBC        | 0xBD      |
| MD        | 0xBE        | 0xBF      |

- Read some parameters (AC1 ,AC2 ,...) each parmeter consist of 16 bits, parameters are stored in EEPROM register, Each parameter is stored in 2 registers (each register 8 bits).
- Send value(0x2E) to **Control Register**(0xF4) to measure temperature.
- Read UT (from 0xF6(MSB), & 0xF7(LSB))
- Send value(the value depends on the mode selected) to **Control Register**(0xF4) to measure pressure.
- Do some calculations to get temperature.
- Do some calcualtions to get pressure.

<br>

Be Careful
{: .label .label-red}
* You should use appropriate data type for each variable you use (you can find example with the data types in datasheet).

<br>

Be Careful
{: .label .label-red}
* You should wait conversion time until data be ready.

| Measurement   | Control register value | conversion time [ms] |
|:--------------|:-----------------------|:---------------------|
|Tempearature   | 0x2E                   | 4.5                  |
|Pressure(oss=0)| 0x34                   | 4.5                  |
|Pressure(oss=1)| 0x74                   | 7.5                  |
|Pressure(oss=2)| 0xB4                   | 13.5                 |
|Pressure(oss=3)| 0xF4                   | 25.5                 |


