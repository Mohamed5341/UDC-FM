---
layout: default
title: How it works
parent: Airspeed
nav_order: 3
---

Airspeed sensor measure pressure difference(dynamic pressure) using **Pitot tube** to get stagnation pressure and static pressure and drive each one through a hose to the sensor. Sensor has 2 input channels you connect each channel to a hose and the sensor measure difference between them.
{% include image.html url="/assets/airspeed_pitot_tube.jpg" description="Pitot Tube" %} 
You connect sensor with pitot tube using hoses as in image.
{% include image.html url="/assets/airspeed_pitot_tube_connections.jpg" description="Pitot Tube connection with sensor" %} 

Airspeed sensor outputs analog signal(voltage depend on the value of pressure difference), from datasheet sensor **Sensitivity** = 1V/kPa (this means that relation between voltage and pressure difference is linear and its slope is 1)
{% include image.html url="/assets/airspeed_output_relation_vp.png" description="Relation between voltage and pressure difference" %} 

Be Careful
{: .label .label-red}
This relation is for typical (ideal case 5v input and no error)
<br>
But, datasheet said there is error so the output maybe vary from true value(there is error 2.5% at normal operation mode).
{% include image.html url="/assets/airspeed_output_relation_datasheet.JPG" description="Relation between voltage and pressure difference (From datasheet)" %} 
<span>$$V_{out}=V_{s} * (0.2 * \Delta P+0.5)$$</span>
<br>
<span>$$V_s=5V$$</span>
<br>
<span>$$\Delta P = (\frac{V_{out}}{V_s} - 0.5) * 5 = (\frac{V_{out}}{5} - 0.5) * 5$$</span>
<br>
<br>
After you get pressure difference can calculate airspeed from **Bernoulli's equation**:
<br>
<br>
<span>$$P_0=P+\frac{1}{2}\rho{v}^{2}$$</span>
<br>
<span>$$v=\sqrt{\frac{2(P_0-P))}{\rho}}$$</span>



<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
