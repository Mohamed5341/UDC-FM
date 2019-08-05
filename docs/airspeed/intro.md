---
layout: default
title: Introduction
parent: Airspeed
nav_order: 1
---

Airspeed sensor (MPXV7002dp, dp stands for Differential pressure) is used to measure airspeed (speed of Airplane). Tiva C will be used to read data from it

{% include image.html url="/assets/mpvx7002dp.jpg" description="Airspeed sensor" %}
{% include image.html url="/assets/tivac.jpg" description="Tiva C Launchpad" %}

This sensor measure **dynamic pressure** (difference between total pressure and static pressure) and from this you can get your speed.
