EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:BuddiesJewel-cache
LIBS:BuddiesJewel-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "BuddiesJewel"
Date "14 nov 2013"
Rev "1"
Comp "FabLab"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF430CL330H U5
U 1 1 5263BC72
P 7850 1800
F 0 "U5" H 7650 1750 60  0000 C CNN
F 1 "RF430CL330H" H 7950 950 60  0000 C CNN
F 2 "~" H 7950 950 60  0000 C CNN
F 3 "" H 7950 950 60  0000 C CNN
	1    7850 1800
	1    0    0    -1  
$EndComp
$Comp
L ALIM P1
U 1 1 5263BDB9
P 1150 2400
F 0 "P1" H 1150 2350 60  0000 C CNN
F 1 "ALIM" H 1250 1900 60  0000 C CNN
F 2 "" H 1250 1900 60  0000 C CNN
F 3 "" H 1250 1900 60  0000 C CNN
	1    1150 2400
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR2
U 1 1 5263BF00
P 1800 2550
F 0 "#PWR2" H 1800 2510 30  0001 C CNN
F 1 "+3.3V" H 1800 2660 30  0000 C CNN
F 2 "" H 1800 2550 60  0000 C CNN
F 3 "" H 1800 2550 60  0000 C CNN
	1    1800 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5263BF0F
P 1800 2800
F 0 "#PWR3" H 1800 2800 30  0001 C CNN
F 1 "GND" H 1800 2730 30  0001 C CNN
F 2 "" H 1800 2800 60  0000 C CNN
F 3 "" H 1800 2800 60  0000 C CNN
	1    1800 2800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR12
U 1 1 5263BF4A
P 7150 1450
F 0 "#PWR12" H 7150 1410 30  0001 C CNN
F 1 "+3.3V" H 7150 1560 30  0000 C CNN
F 2 "" H 7150 1450 60  0000 C CNN
F 3 "" H 7150 1450 60  0000 C CNN
	1    7150 1450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 5263BF59
P 8900 1700
F 0 "#PWR14" H 8900 1700 30  0001 C CNN
F 1 "GND" H 8900 1630 30  0001 C CNN
F 2 "" H 8900 1700 60  0000 C CNN
F 3 "" H 8900 1700 60  0000 C CNN
	1    8900 1700
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5263BFC3
P 7900 1500
F 0 "C1" H 7900 1600 40  0000 L CNN
F 1 "C" H 7906 1415 40  0000 L CNN
F 2 "~" H 7938 1350 30  0000 C CNN
F 3 "~" H 7900 1500 60  0000 C CNN
	1    7900 1500
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 5263C02F
P 7900 1700
F 0 "C2" H 7900 1800 40  0000 L CNN
F 1 "C" H 7906 1615 40  0000 L CNN
F 2 "~" H 7938 1550 30  0000 C CNN
F 3 "~" H 7900 1700 60  0000 C CNN
	1    7900 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR16
U 1 1 5263C0F9
P 10450 2600
F 0 "#PWR16" H 10450 2600 30  0001 C CNN
F 1 "GND" H 10450 2530 30  0001 C CNN
F 2 "" H 10450 2600 60  0000 C CNN
F 3 "" H 10450 2600 60  0000 C CNN
	1    10450 2600
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5263C108
P 10100 2350
F 0 "R7" V 10180 2350 40  0000 C CNN
F 1 "R" V 10107 2351 40  0000 C CNN
F 2 "~" V 10030 2350 30  0000 C CNN
F 3 "~" H 10100 2350 30  0000 C CNN
	1    10100 2350
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 5263C117
P 10100 2500
F 0 "R8" V 10180 2500 40  0000 C CNN
F 1 "R" V 10107 2501 40  0000 C CNN
F 2 "~" V 10030 2500 30  0000 C CNN
F 3 "~" H 10100 2500 30  0000 C CNN
	1    10100 2500
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5263C1CF
P 6450 2050
F 0 "R3" V 6530 2050 40  0000 C CNN
F 1 "R" V 6457 2051 40  0000 C CNN
F 2 "~" V 6380 2050 30  0000 C CNN
F 3 "~" H 6450 2050 30  0000 C CNN
	1    6450 2050
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR8
U 1 1 5263C1E3
P 6100 1950
F 0 "#PWR8" H 6100 1910 30  0001 C CNN
F 1 "+3.3V" H 6100 2060 30  0000 C CNN
F 2 "" H 6100 1950 60  0000 C CNN
F 3 "" H 6100 1950 60  0000 C CNN
	1    6100 1950
	1    0    0    -1  
$EndComp
Text Label 8750 2150 0    60   ~ 0
SDA/MOSI
Text Label 8750 2250 0    60   ~ 0
SCL/SCK
Text Label 8750 2550 0    60   ~ 0
IT/RST
Text Label 2100 3850 0    60   ~ 0
SDA/MOSI
Text Label 1200 4050 0    60   ~ 0
SCL/SCK
Text Label 3000 4350 0    60   ~ 0
IT/RST
Text Label 3000 3950 0    60   ~ 0
PWM0/MISO
Text Label 3000 4150 0    60   ~ 0
PWM1
Text Label 3000 4250 0    60   ~ 0
PWM2
$Comp
L GND #PWR9
U 1 1 5263C5EB
P 6100 2800
F 0 "#PWR9" H 6100 2800 30  0001 C CNN
F 1 "GND" H 6100 2730 30  0001 C CNN
F 2 "" H 6100 2800 60  0000 C CNN
F 3 "" H 6100 2800 60  0000 C CNN
	1    6100 2800
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5263C631
P 6450 2350
F 0 "R4" V 6530 2350 40  0000 C CNN
F 1 "R" V 6457 2351 40  0000 C CNN
F 2 "~" V 6380 2350 30  0000 C CNN
F 3 "~" H 6450 2350 30  0000 C CNN
	1    6450 2350
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 5263C640
P 6450 2500
F 0 "R5" V 6530 2500 40  0000 C CNN
F 1 "R" V 6457 2501 40  0000 C CNN
F 2 "~" V 6380 2500 30  0000 C CNN
F 3 "~" H 6450 2500 30  0000 C CNN
	1    6450 2500
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5263C64F
P 6450 2650
F 0 "R6" V 6530 2650 40  0000 C CNN
F 1 "R" V 6457 2651 40  0000 C CNN
F 2 "~" V 6380 2650 30  0000 C CNN
F 3 "~" H 6450 2650 30  0000 C CNN
	1    6450 2650
	0    1    1    0   
$EndComp
Text Label 6750 4250 0    60   ~ 0
IT/RST
Text Label 6750 4150 0    60   ~ 0
SCL/SCK
Text Label 6750 4050 0    60   ~ 0
PWM0/MISO
Text Label 9100 4150 0    60   ~ 0
SDA/MOSI
Text Label 6000 5350 0    60   ~ 0
PWM0/MISO
Text Label 5900 6500 0    60   ~ 0
PWM1
Text Label 6500 6050 0    60   ~ 0
PWM2
$Comp
L PT U2
U 1 1 5283E30A
P 2050 2200
F 0 "U2" H 1940 2380 60  0000 C CNN
F 1 "PT" H 2120 2100 60  0000 C CNN
F 2 "~" H 1750 2450 60  0000 C CNN
F 3 "~" H 1750 2450 60  0000 C CNN
	1    2050 2200
	1    0    0    -1  
$EndComp
$Comp
L PT U3
U 1 1 5283E319
P 2400 2200
F 0 "U3" H 2290 2380 60  0000 C CNN
F 1 "PT" H 2470 2100 60  0000 C CNN
F 2 "~" H 2100 2450 60  0000 C CNN
F 3 "~" H 2100 2450 60  0000 C CNN
	1    2400 2200
	1    0    0    -1  
$EndComp
$Comp
L RGB_LED D2
U 1 1 5283E81A
P 7250 5750
F 0 "D2" H 7150 5750 60  0000 C CNN
F 1 "RGB_LED" H 7450 5300 60  0000 C CNN
F 2 "~" H 7150 5750 60  0000 C CNN
F 3 "~" H 7150 5750 60  0000 C CNN
	1    7250 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 5283E829
P 8050 6100
F 0 "#PWR13" H 8050 6100 30  0001 C CNN
F 1 "GND" H 8050 6030 30  0001 C CNN
F 2 "" H 8050 6100 60  0000 C CNN
F 3 "" H 8050 6100 60  0000 C CNN
	1    8050 6100
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP1
U 1 1 5283EA50
P 5750 5850
F 0 "JP1" H 5750 6000 60  0000 C CNN
F 1 "JUMPER" H 5750 5770 40  0000 C CNN
F 2 "~" H 5750 5850 60  0000 C CNN
F 3 "~" H 5750 5850 60  0000 C CNN
	1    5750 5850
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP2
U 1 1 5283EA5F
P 5750 6250
F 0 "JP2" H 5750 6400 60  0000 C CNN
F 1 "JUMPER" H 5750 6170 40  0000 C CNN
F 2 "~" H 5750 6250 60  0000 C CNN
F 3 "~" H 5750 6250 60  0000 C CNN
	1    5750 6250
	1    0    0    -1  
$EndComp
$Comp
L WS2812 D1
U 1 1 5283EC88
P 4150 5600
F 0 "D1" H 4050 5550 60  0000 C CNN
F 1 "WS2812" H 4250 5100 60  0000 C CNN
F 2 "~" H 4250 5100 60  0000 C CNN
F 3 "~" H 4250 5100 60  0000 C CNN
	1    4150 5600
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR7
U 1 1 5283ED24
P 4900 5600
F 0 "#PWR7" H 4900 5560 30  0001 C CNN
F 1 "+3,3V" H 4900 5710 30  0000 C CNN
F 2 "" H 4900 5600 60  0000 C CNN
F 3 "" H 4900 5600 60  0000 C CNN
	1    4900 5600
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR6
U 1 1 5283ED33
P 3500 6150
F 0 "#PWR6" H 3500 6110 30  0001 C CNN
F 1 "+3,3V" H 3500 6260 30  0000 C CNN
F 2 "" H 3500 6150 60  0000 C CNN
F 3 "" H 3500 6150 60  0000 C CNN
	1    3500 6150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 5283ED42
P 3250 5950
F 0 "#PWR5" H 3250 5950 30  0001 C CNN
F 1 "GND" H 3250 5880 30  0001 C CNN
F 2 "" H 3250 5950 60  0000 C CNN
F 3 "" H 3250 5950 60  0000 C CNN
	1    3250 5950
	1    0    0    -1  
$EndComp
$Comp
L ATTINY25-P IC1
U 1 1 5283EF71
P 4850 4100
F 0 "IC1" H 3800 4500 60  0000 C CNN
F 1 "ATTINY25-P" H 5700 3700 60  0000 C CNN
F 2 "DIP8" H 3800 3700 60  0001 C CNN
F 3 "" H 4850 4100 60  0000 C CNN
	1    4850 4100
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR1
U 1 1 5283F1F1
P 1700 3350
F 0 "#PWR1" H 1700 3310 30  0001 C CNN
F 1 "+3,3V" H 1700 3460 30  0000 C CNN
F 2 "" H 1700 3350 60  0000 C CNN
F 3 "" H 1700 3350 60  0000 C CNN
	1    1700 3350
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR4
U 1 1 5283F200
P 2550 3150
F 0 "#PWR4" H 2550 3110 30  0001 C CNN
F 1 "+3,3V" H 2550 3260 30  0000 C CNN
F 2 "" H 2550 3150 60  0000 C CNN
F 3 "" H 2550 3150 60  0000 C CNN
	1    2550 3150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5283F20F
P 1700 3750
F 0 "R1" V 1780 3750 40  0000 C CNN
F 1 "R" V 1707 3751 40  0000 C CNN
F 2 "~" V 1630 3750 30  0000 C CNN
F 3 "~" H 1700 3750 30  0000 C CNN
	1    1700 3750
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5283F21E
P 2550 3550
F 0 "R2" V 2630 3550 40  0000 C CNN
F 1 "R" V 2557 3551 40  0000 C CNN
F 2 "~" V 2480 3550 30  0000 C CNN
F 3 "~" H 2550 3550 30  0000 C CNN
	1    2550 3550
	1    0    0    -1  
$EndComp
$Comp
L PT U1
U 1 1 5283F22D
P 1950 3650
F 0 "U1" H 1840 3830 60  0000 C CNN
F 1 "PT" H 2020 3550 60  0000 C CNN
F 2 "~" H 1650 3900 60  0000 C CNN
F 3 "~" H 1650 3900 60  0000 C CNN
	1    1950 3650
	1    0    0    -1  
$EndComp
$Comp
L PT U4
U 1 1 5283F23C
P 2900 3400
F 0 "U4" H 2790 3580 60  0000 C CNN
F 1 "PT" H 2970 3300 60  0000 C CNN
F 2 "~" H 2600 3650 60  0000 C CNN
F 3 "~" H 2600 3650 60  0000 C CNN
	1    2900 3400
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR10
U 1 1 5283F8FA
P 6450 3650
F 0 "#PWR10" H 6450 3610 30  0001 C CNN
F 1 "+3,3V" H 6450 3760 30  0000 C CNN
F 2 "" H 6450 3650 60  0000 C CNN
F 3 "" H 6450 3650 60  0000 C CNN
	1    6450 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 5283F909
P 6450 4500
F 0 "#PWR11" H 6450 4500 30  0001 C CNN
F 1 "GND" H 6450 4430 30  0001 C CNN
F 2 "" H 6450 4500 60  0000 C CNN
F 3 "" H 6450 4500 60  0000 C CNN
	1    6450 4500
	1    0    0    -1  
$EndComp
$Comp
L AVR-ISP6 CON1
U 1 1 5283FB65
P 7900 3900
F 0 "CON1" H 7900 3900 60  0000 C CNN
F 1 "AVR-ISP6" H 8000 3400 60  0000 C CNN
F 2 "" H 7900 3900 60  0000 C CNN
F 3 "" H 7900 3900 60  0000 C CNN
	1    7900 3900
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5283FF56
P 9550 2050
F 0 "C3" H 9550 2150 40  0000 L CNN
F 1 "C" H 9556 1965 40  0000 L CNN
F 2 "~" H 9588 1900 30  0000 C CNN
F 3 "~" H 9550 2050 60  0000 C CNN
	1    9550 2050
	0    1    1    0   
$EndComp
$Comp
L GND #PWR15
U 1 1 5283FF65
P 9950 2150
F 0 "#PWR15" H 9950 2150 30  0001 C CNN
F 1 "GND" H 9950 2080 30  0001 C CNN
F 2 "" H 9950 2150 60  0000 C CNN
F 3 "" H 9950 2150 60  0000 C CNN
	1    9950 2150
	1    0    0    -1  
$EndComp
$Comp
L ANTENNE CON2
U 1 1 52851A3E
P 4200 1950
F 0 "CON2" H 4150 2050 60  0000 C CNN
F 1 "ANTENNE" H 4150 1650 60  0000 C CNN
F 2 "" H 4150 2050 60  0000 C CNN
F 3 "" H 4150 2050 60  0000 C CNN
	1    4200 1950
	1    0    0    -1  
$EndComp
Connection ~ 1800 2600
Wire Wire Line
	1800 2600 1800 2550
Wire Wire Line
	1800 2750 1800 2800
Wire Wire Line
	7150 1950 7300 1950
Wire Wire Line
	7150 1450 7150 1950
Wire Wire Line
	8550 1450 8550 1950
Wire Wire Line
	8550 1450 8900 1450
Wire Wire Line
	8900 1450 8900 1700
Wire Wire Line
	8100 1500 8550 1500
Connection ~ 8550 1500
Wire Wire Line
	7700 1500 7150 1500
Connection ~ 7150 1500
Wire Wire Line
	7700 1700 7150 1700
Connection ~ 7150 1700
Wire Wire Line
	8100 1700 8550 1700
Connection ~ 8550 1700
Wire Wire Line
	10350 2500 10450 2500
Wire Wire Line
	10450 2350 10450 2600
Wire Wire Line
	10450 2350 10350 2350
Connection ~ 10450 2500
Wire Wire Line
	9850 2350 8550 2350
Wire Wire Line
	9850 2500 9700 2500
Wire Wire Line
	9700 2500 9700 2450
Wire Wire Line
	9700 2450 8550 2450
Wire Wire Line
	6100 1950 6100 2050
Wire Wire Line
	6100 2050 6200 2050
Wire Wire Line
	8550 2150 8750 2150
Wire Wire Line
	8550 2250 8750 2250
Wire Wire Line
	8550 2550 8750 2550
Wire Wire Line
	6700 2050 6950 2050
Wire Wire Line
	6950 2050 6950 2250
Wire Wire Line
	6950 2250 7300 2250
Wire Wire Line
	6100 2350 6100 2800
Wire Wire Line
	6100 2350 6200 2350
Wire Wire Line
	6100 2500 6200 2500
Connection ~ 6100 2500
Wire Wire Line
	6200 2650 6100 2650
Connection ~ 6100 2650
Wire Wire Line
	6700 2650 7150 2650
Wire Wire Line
	7150 2650 7150 2550
Wire Wire Line
	7150 2550 7300 2550
Wire Wire Line
	7300 2450 7000 2450
Wire Wire Line
	7000 2450 7000 2500
Wire Wire Line
	7000 2500 6700 2500
Wire Wire Line
	6700 2350 7300 2350
Connection ~ 1800 2750
Wire Wire Line
	9372 2052 9372 2054
Wire Wire Line
	1650 2600 2050 2600
Wire Wire Line
	1650 2750 2400 2750
Wire Wire Line
	2050 2600 2050 2550
Wire Wire Line
	2400 2750 2400 2550
Wire Wire Line
	7900 5950 8050 5950
Wire Wire Line
	8050 5950 8050 6100
Wire Wire Line
	6050 5850 6800 5850
Wire Wire Line
	6500 5850 6500 5350
Wire Wire Line
	6500 5350 6000 5350
Wire Wire Line
	6800 6050 6500 6050
Wire Wire Line
	6800 5950 6200 5950
Wire Wire Line
	6200 5950 6200 6500
Wire Wire Line
	6200 6250 6050 6250
Connection ~ 6500 5850
Wire Wire Line
	6200 6500 5900 6500
Connection ~ 6200 6250
Wire Wire Line
	5450 5850 4700 5850
Wire Wire Line
	4700 5750 4900 5750
Wire Wire Line
	4900 5750 4900 5600
Wire Wire Line
	3700 5950 3700 6250
Wire Wire Line
	3700 6250 3500 6250
Wire Wire Line
	3500 6250 3500 6150
Wire Wire Line
	3700 5850 3250 5850
Wire Wire Line
	3250 5850 3250 5950
Wire Wire Line
	4700 5950 4800 5950
Wire Wire Line
	4800 5950 4800 6250
Wire Wire Line
	4800 6250 5450 6250
Wire Wire Line
	3500 4350 3000 4350
Wire Wire Line
	3500 4250 3000 4250
Wire Wire Line
	3500 4150 3000 4150
Wire Wire Line
	3500 3950 3000 3950
Wire Wire Line
	3500 4050 1200 4050
Wire Wire Line
	2550 3800 2550 3850
Connection ~ 2550 3850
Wire Wire Line
	2900 3750 2900 3850
Connection ~ 2900 3850
Wire Wire Line
	2550 3150 2550 3300
Wire Wire Line
	1700 3350 1700 3500
Wire Wire Line
	1700 4000 1700 4050
Connection ~ 1700 4050
Wire Wire Line
	1950 4000 1950 4050
Connection ~ 1950 4050
Wire Wire Line
	2100 3850 3500 3850
Wire Wire Line
	6200 3850 8700 3850
Wire Wire Line
	6450 3850 6450 3650
Wire Wire Line
	6200 4350 6700 4350
Wire Wire Line
	6450 4350 6450 4500
Wire Wire Line
	8500 4250 8700 4250
Wire Wire Line
	8700 4250 8700 4550
Wire Wire Line
	8700 4550 6700 4550
Wire Wire Line
	6700 4550 6700 4350
Connection ~ 6450 4350
Wire Wire Line
	8700 3850 8700 4050
Wire Wire Line
	8700 4050 8500 4050
Connection ~ 6450 3850
Wire Wire Line
	8500 4150 9100 4150
Wire Wire Line
	7450 4250 6750 4250
Wire Wire Line
	7450 4150 6750 4150
Wire Wire Line
	7450 4050 6750 4050
Wire Wire Line
	9950 2150 9950 2050
Wire Wire Line
	9950 2050 9750 2050
Wire Wire Line
	9350 2050 8550 2050
Wire Wire Line
	7300 2050 7050 2050
Wire Wire Line
	7300 2150 7050 2150
Text Label 7050 2050 0    60   ~ 0
ANT1
Text Label 7050 2150 0    60   ~ 0
ANT2
Wire Wire Line
	4700 2000 4800 2000
Wire Wire Line
	4800 2000 4800 1850
Wire Wire Line
	4800 1850 5350 1850
$Comp
L C C4
U 1 1 52851CF9
P 5100 2100
F 0 "C4" H 5100 2200 40  0000 L CNN
F 1 "C" H 5106 2015 40  0000 L CNN
F 2 "~" H 5138 1950 30  0000 C CNN
F 3 "~" H 5100 2100 60  0000 C CNN
	1    5100 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 1900 5100 1850
Connection ~ 5100 1850
Wire Wire Line
	4700 2100 4800 2100
Wire Wire Line
	4800 2100 4800 2300
Wire Wire Line
	4800 2300 5350 2300
Connection ~ 5100 2300
Wire Wire Line
	3600 2100 3550 2100
Wire Wire Line
	3550 2100 3550 2350
Wire Wire Line
	3550 2350 3200 2350
Wire Wire Line
	3200 2350 3200 1700
Wire Wire Line
	3200 1700 3550 1700
Wire Wire Line
	3550 1700 3550 2000
Wire Wire Line
	3550 2000 3600 2000
Text Label 5350 1850 0    60   ~ 0
ANT1
Text Label 5350 2300 0    60   ~ 0
ANT2
$EndSCHEMATC
