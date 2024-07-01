# Yi-Hua Solder station
soldering iron controller for my garage project, this controller controlled by ESP32 microcontroller and featuring 16x2 Alphanumeric LCD display, the soldering iron handle using Yi Hua 907 A with built in Thermocouple sensor.

<h1>Specification:</h1>:
-MCU : ESP32<br>
-Solder Handle : Yi Hua 907 A<br>
-Sensor : Thermocouple<br>
-Thermocouple amplifier: OP AMP with 100x Gain + buffer gain<br>
-Supply : DC 12V-24V<br>
-Control mode : * Bang-Bang Control<br>
                * PID Control (Adjustable)<br>

<h1>Note:</h1>:
This code work on ESP32 Microcontroller because the program runs on both CPUs;<br>
-CPU 0 runs the control system routine<br>
-CPU 1 runs the user interface (rotary encoder and LCD display)<br>