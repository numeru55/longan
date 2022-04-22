# Pin

```
GND
GND --------- INA219
PB9
PB8
PB7 - SDA0 -- INA219
PB6 - SCL0 -- INA219

...

PB12
3V3  -------- INA219
5V
```

# Memo

conversion time: 586usec max nealy equal 1.7k sample / sec

## Bus Voltage Register (address = 02h)

```
 15   14  ...  3  2  1   0
BD12 BD11 ... BD0 - CNVR OVF
```

Conversion Voltage = BD[12:0] * 4mV

## Caribration Register (address = 05h)

Set to 40.96 / (Rshunt[ohms])

Example:

```
R[SHUNT]=0.1
40.96/0.1 = 409.6 -> set to 410
```

