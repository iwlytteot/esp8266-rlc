# RGB LED control
Simple and intuitive RGB LED device, controlled via smartphone app using WiFi.

## Requirements
- ESP8266 microchip with available PWM pins
- smartphone
- RGB LED strip
- 3x resistor    
- 3x NPN transistor 

## Setting up circuit
<p align="left">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/vbbrgbled.PNG" width="430" alt="accessibility text">
</p>

- 24V input to LED strip 
- 5V Arduino board voltage

## Android app
<p align="left">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/20200824_234753.jpg" width="210">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/Screenshot_20200824-235340.jpg" width="200">
</p>
- steady mode for constant RGB value
- blink mode to apply transition from one RGB value to the other RGB value

## Technical background
- this project is for ESP8266 mainly. For other boards, remove multiplier by 4 of RGB value. (This is due to the fact that ESP8266 uses 10-bit pin for PWM insted of 8-bit in other boards)
- choose <b>correct</b> transistor to withstand power load from your LED strip
- resistor value <b>depends</b> on transistor and your board




