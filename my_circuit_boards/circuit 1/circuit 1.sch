EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R?
U 1 1 602B5099
P 6350 1750
F 0 "R?" H 6280 1704 50  0000 R CNN
F 1 "220" H 6280 1795 50  0000 R CNN
F 2 "" V 6280 1750 50  0001 C CNN
F 3 "~" H 6350 1750 50  0001 C CNN
	1    6350 1750
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D?
U 1 1 602B69C2
P 6350 2950
F 0 "D?" V 6389 2832 50  0000 R CNN
F 1 "LED" V 6298 2832 50  0000 R CNN
F 2 "" H 6350 2950 50  0001 C CNN
F 3 "~" H 6350 2950 50  0001 C CNN
	1    6350 2950
	0    -1   -1   0   
$EndComp
$Comp
L Device:Battery BT?
U 1 1 602BAAFF
P 4450 2250
F 0 "BT?" H 4558 2296 50  0000 L CNN
F 1 "Battery" H 4558 2205 50  0000 L CNN
F 2 "" V 4450 2310 50  0001 C CNN
F 3 "~" V 4450 2310 50  0001 C CNN
	1    4450 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2050 4450 1400
Wire Wire Line
	4450 1400 6350 1400
Wire Wire Line
	6350 1400 6350 1600
Wire Wire Line
	6350 1900 6350 2800
Wire Wire Line
	6350 3100 6350 3250
Wire Wire Line
	6350 3250 4450 3250
Wire Wire Line
	4450 3250 4450 2450
$EndSCHEMATC
