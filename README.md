# RGB LED control
Simple and intuitive RGB LED device, controlled via smartphone app using WiFi.

## Requirements
- Wemos D1 mini (pretty much anything with ESP8266 and available PWM pins will work)
- RGB LED strip
- 3x resistor    
- 3x NPN transistor 
- (optional) DC-DC step down supply LM2596, 24V to 5V

## Setting up circuit
<p align="left">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/circuit.png" width="430" alt="accessibility text">
</p>

- 24V input to LED strip & USB 5V to Wemos D1 mini
- (optional) as shown in schematic, using single 24V supply for both LED strip & Wemos D1 mini via DC-DC step down

## Android app
<p align="left">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/20200827_202146.jpg" width="210">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/Screenshot_20200827-202432.jpg" width="200">
  <img src="https://github.com/iwlytteot/esp8266-rlc/blob/master/img/20200827_202223.jpg" width="200">
</p>

#### Static mode
- keep the same color or just dim it
#### Dynamic mode
- apply transition from one RGB value to the other RGB value

## Technical background
- this project is for ESP8266 mainly. For other boards, remove multiplier by 4 of RGB value. (This is due to the fact that ESP8266 uses 10-bit pin for PWM insted of 8-bit in other boards)
- choose <b>correct</b> transistor to withstand power load from your LED strip
- resistor value <b>depends</b> on transistor and your board




