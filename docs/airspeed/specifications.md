---
layout: default
title: Specifications
parent: Airspeed
nav_order: 2
---


|                | Min  | Max  | Unit |
|:---------------|:---- |:-----|:-----|
| Supply Voltage | 4.75 | 5.25 | V    |
| Pressure Range | -2   | 2    | kpa  |
| Output         | 0.5  | 4.5  | V    |

Be Careful
{: .label .label-red}
Sensor works with 5 Volt but Tiva C maximum voltage is 3.3V so you can't get this voltage from Tiva C you need another power source.

Be Careful
{: .label .label-red}
Sensor output max output is 4.5V but Tiva C max input for ADC is 3.3V so you can read output less than 3.3V or you can use external circuit (Voltage Divider)to modify output so the maximum output is 3.3V
{% include image.html url="/assets/airspeed_output_scale.jpg" description="Airspeed Output range" %}

But there maybe offset in sensor output.

|                   | Min  | Max  | Unit |
|:------------------|:-----|:-----|:-----|
| Pressure offset   | 0.25 | 0.75 | V    |
| Full scale output | 4.25 | 4.75 | V    |
| Full scale span   | 3.5  | 4.5  | V    |

{% include image.html url="/assets/airspeed_output_scale_offset.jpg" description="Airspeed Output offset" %}

<dl>
	<dt>Pressure offset</dt>
	<dd>The minimum value of output may be changed.</dd>
	<dt>Full scale output</dt>
	<dd>The maximum value of output may be changed.</dd>
	<dt>Full scale span</dt>
	<dd>The range of the output may be changed</dd>
</dl>
All these changes values in the above table.

Sensor has error 2.5% to 6.25% from its range(this means that at normal sensor give error 2.5% of its full scale span and this value can increase up to 6.25%), This error in the value you read not in offset.
