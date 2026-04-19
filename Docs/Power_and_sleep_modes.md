# Power Management and Sleep Modes 

## Register Description 

### Power Reduction Register

|       |       |       |  PPR  |       |       |        |       |
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:------:|:-----:|
|   7   |   6   |   5   |   4   |   4   |   2   |   1    |   0   |
| PRTWI | PRTIM2| PRTIM0|   -   | PRTIM1| PRSPI |PRUSART0| PRADC |

* __PRADC__ Power reduction ADC a logic 1 to this bit shuts down the ADC and the analog comparator. The ADC must be disabled before shut down.