---
layout: default
title: Specifications
parent: BMP180
nav_order: 2
---


|                             | Min | Max  | Unit          |
|:----------------------------|:----|:-----|:--------------|
| Supply Voltage              | 1.8 | 3.6  | V             |
| Pressure Range              | 300 | 1100 | hpa           |
| Temperature (Operating)     | -40 | 85   | <sup>o</sup>C |
| Temperature (Full accuracy) | 0   | 65   | <sup>o</sup>C |


<dl>
	<dt>hpa</dt>
	<dd>hectopascals = 100 pa</dd>
</dl>

This sensor can operate in number of modes. Modes are used for pressure measuring only(not temperature).

| Mode                 | oss | num. of samples | conversion time [ms] | Average current[uA] | noise [hpa] | noise [m] |
|:---------------------|:----|:----------------|:---------------------|:--------------------|:------------|:----------|
| Ultra low Power      | 0   | 1               | 4.5                  | 3                   | 0.06        | 0.5       |
| standard             | 1   | 2               | 7.5                  | 5                   | 0.05        | 0.4       |
| high resolution      | 2   | 4               | 13.5                 | 7                   | 0.04        | 0.3       |
| Ultra high resolution| 3   | 8               | 25.5                 | 12                  | 0.03        | 0.25      |

You can select the mode by using oss (oversampling setting) variable, for example if you want to select **standard** mode this mean oss = 1, number of samples sensor take to get the output data is 2 (sensor read 2 data and get the average), sensor conversion time is the time sensor needs to get the data (you need to wait after the sensor start measuring 7.5 millisecond), Noise in sensor 0.05 hpa (0.4m).
