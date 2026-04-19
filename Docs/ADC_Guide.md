# GUIDE USE ADC

 To activate the ADC the bit PRADC (Power Reduction ADC) from register PRR, must be disabled by writing logical 0. And bit ADEN(ADC Enable) from register ADCSRA ste to 1.

__Note: In slepp modes ADEN must be clared.__

[Block Schematic ADC](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf#page=206)
## Some Features ADC ATmega328P
* 10 bit resolution
* 8 chanels usung multiplexer
* Reference voltages 

    | Reference         | Reg Selection |
    | -------------     |:-------------:|
    | 1.1 Volts         | ADMUX     |
    | AV<sub>cc</sub>   | ADMUX     |
    | AREF              | ADMUX     |

* ADC data registers [ADCH](#adc-data-register) and [ADCL](#adc-data-register) right adjusted, left adjusted by setting the ADLAR bit in [ADMUX](#adc-multiplexer-selection-register). 

## Starting a Conversion

### Single Converison 
|  Bits | Register | Status |
| ------|:--------:|:------:|
| PRADC | [PRR](/Docs/Power_and_sleep_modes.md#power-reduction-register)| 0      |
| ADSC  | [ADCSRA](#adc-control-and-status-register-a) | 1      |

__Note: ADSC bit is cleared by hardware when the conversio is complete.__

### Trigger Conversion
|  Bits | Register | Status |
| ------|:--------:|:------:|
| PRADC | [PRR](/Docs/Power_and_sleep_modes.md#power-reduction-register)| 0      |
| ADATE | [ADCSRA](#adc-control-and-status-register-a) | 1      |
| ADTS*  | [ADCSRB](#adc-control-and-status-register-b) | 1      |

When a positive edge occurs on the selected trigger signal, the ADC prescaler is reset and 
a conversion is started. This provides a method of starting conversions at fixed intervals. 
If the trigger signal still is set when the conversion completes, a new conversion will not 
be started. If another positive edge occurs on the trigger signal during conversion, the 
edge will be ignored.

__*Note: ADTS2:0 select the trigger sourse from the [list](#adts_table).__

### Free Running mode

Using the ADC interrup flag as trigger sourse makes the ADC start a new conversion as soon 
as the ongoing conversion has finished.

If auto triggering is enabled, single conversions can be started by writing ADSC in ADCSRA 
to one. ADSC can also be used to determine if a conversion is in progress. The ADSC bit 
will be read as one during a conversion, independently of how the conversion was started.
## Prescaling and Conversion Timing

* Clock Frequency 50Khz- 200Khz, more than 200kz if a lower resolution of 10 bits.

* ADC module prescaler is set by bits ADPS2:0 in register [ADCSRA](#adc-control-and-status-register-a); the ADEN bit acts as a prescaler clock enable.

* When a conversion is complete, the result is written in ADC data registers and ADIF is set. In single conversion mode, ADSC is cleared simultaneosly and config again ADSC init a new convetion.

* In auto triggering mode, the prescaler is reset any time that trigger events occurs. This assures a fixed delay (2 clock cycles) from the trigger event to the start converison. and tree aditional cycles fot synchronization.

* In free running mode, a new conversion will be started immediately after the conversion completes, while ADSC remains high.

## Changing channel and reference selection

The bits MUXn and REFS1:0 in the [ADMUX](#adc-multiplexer-selection-register) register are update before a new even converision inits. ADIF is an flag thet conversion is complete.

Warning! in trigger mode any change to ADMUX must be in any of this conditions:
* When ADATE and ADEN (in [ADCSRA](#adc-control-and-status-register-a)) is cleared.
* Diring converion, minimun one ADC clock cycle after the trigger event.
* After a converesion, before the interrupt Flag used as trigger sourse is cleared. 

### ADC Inputs Channels 

* Single converion mode, select the channel before starting the firts converion.

* Free runinig mode, same that single mode but for nexts converion events the effect the change the channel will not be reflet in the next event, but subsequent conversions will reflect the new channel selection.

### ADC Voltage Reference 

VREF can be selected as either AVCC, internal 1.1V reference, or external AREF pin. If AREF pin is connect to external fixed voltage sourse the user can't use the AVCC or 1.1V references. If no external voltage is applied to the AREF pin, the user may switch between AVCC and 1.1V as reference.

## Register Description 

### ADC Multiplexer Selection Register

|       |       |       | ADMUX |       |       |       |       |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|   7   |   6   |   5   |   4   |   4   |   2   |   1   |   0   |
| REFS1 | REFS0 | ADLAR |   -   |  MUX3 |  MUX2 |  MUX1 |  MUX0 |

* __REFS1:0__ Reference selectiojn bits:


    |REFS1:0| Voltage Reference selection|
    |-------|:---------------------------|
    |  00   |AREF external reference     |
    |  01   |AV<sub>CC</sub> with ecternal capacitor to AREF pin |
    |  10   | Reserved                   |
    |  11   | Internal 1.1V with ecternal capacitor to AREF pin|

* __ADLAR__ ADC left adjust result

* __MUX3:0__ Analog Channel Selection Bits

    | MUX3:0| Single Ended Input|
    |-------|:------------------|
    | 0000  |       ADC0        |
    | 0001  |       ADC1        |
    | 0010  |       ADC2        |
    | 0011  |       ADC3        |
    | 0100  |       ADC4        |
    | 0101  |       ADC5        |
    | 0110  |       ADC6        |
    | 0111  |       ADC7        |
    | 1000  |       TEMP        |
    | 1110  |1.1V(V<sub>BG</sub>)|
    | 1111  |       0V (GND)    |

### ADC Control and Status Register A

|       |       |       | ADCSRA|       |       |       |       |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|   7   |   6   |   5   |   4   |   4   |   2   |   1   |   0   |
| ADEN  | ADSC  | ADATE |  ADIF |  ADIE | ADPS2 | ADPS1 | ADPS0 |

* _ADEN_ ADC eneable set this bit in 1.

* __ADSC__ ADC start converion set 1 to single and free converion mode, When the conversion is complete, it returns to zero.

* __ADATE__ ADC auto trigger mode set in 1. The trigger source is selected by setting the ADC trigger select bits, ADTS in ADCSRB. Active in positive edge.

* __ADIF__ ADC interrupt flag the bit is swe when teh conversion is complete and the data register are updated.

* __ADIE__ ADC interrup eneable converion complete.

* __ADPS2:0__ ADC prescaler select bits 

    |ADPS2:0| Division Factor   |
    |-------|:------------------|
    | 000   |       2           |
    | 001   |       2           |
    | 010   |       4           |
    | 011   |       8           |
    | 100   |       16          |
    | 101   |       32          |
    | 110   |       64          |
    | 111   |       128         |

### ADC Control and Status Register B 
|       |       |       | ADCSRB|       |       |       |       |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|   7   |   6   |   5   |   4   |   4   |   2   |   1   |   0   |
|   -   | ACME  |   -   |   -   |   -   | ADTS2 | ADTS1 | ADTS0 |

* __ACME__ see register in analog comparator mode

<a id="adts_table"></a>
* __ADTS2:0__ ADC auto trigger sourse
    |ADTS2:0| Trigger Sourse    |
    |-------|:------------------|
    | 000   | Free running mode |
    | 001   | Analog Comparator |
    | 010   | External interrupt request 0   |
    | 011   | Timer/Counter0 compare match A |
    | 100   | Timer/Counter0 Overflow        |
    | 101   | Timer/Counter1 compare match B |
    | 110   | Timer/Counter1 Overflow        |
    | 111   | Timer/Counter1 capture event   |

### ADC Data Register

#### ADLAR = 0
|       |       |       | ADCH|   -    |  ADCL  |       |       |    |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:---|
|  15   |  14   |   13  |   12  |   11  |   10  |   9   |   8   |    |
| -     | -     |   -   |    -  |    -  | -     | ADC9  | ADC8  |ADCH|
| ADC7  | ADC6  | ADC5  | ADC4  | ADC3  | ADC2  | ADC1  | ADC0  |ADCL|
|   7   |   6   |   5   |   4   |   4   |   2   |   1   |   0   |    |

#### ADLAR = 1
|       |       |       | ADCH|   -    |  ADCL  |       |       |    |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:---|
|  15   |  14   |   13  |   12  |   11  |   10  |   9   |   8   |    |
| ADC9  |  ADC8 | ADC7  | ADC6  | ADC5  | ADC4  | ADC3  | ADC2  |ADCH|
| ADC1  | ADC0  | -     |   -   |   -   |   -   |   -   |   -   |ADCL|
|   7   |   6   |   5   |   4   |   4   |   2   |   1   |   0   |    |

### Digital input disable register 

|       |       |       | DIDR0 |       |       |       |       |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|   7   |   6   |   5   |   4   |   4   |   2   |   1   |   0   |
|   -   |   -   | ADC5D | ADC4D | ADC3D | ADC2D | ADC1D | ADC0D |

__ADC5:0D__ digital input buffer on the corresponding ADC pin is disabled.




