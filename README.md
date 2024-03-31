# ColorMeterDuv
Arduino RGB Color Sensor Project

This Arduino project utilizes the Adafruit TCS34725 RGB color sensor to capture color data and provide valuable insights about light sources. The project calculates color temperature, illuminance, and tint difference, displaying them on an LCD screen. With additional features like chromaticity coordinates and Duv deviation calculation, users can understand and compare light sources for accurate color reproduction and lighting effects.


Features:

- Color Temperature Calculation: Measure the color temperature of light sources.
- Illuminance Measurement: Determine the illuminance (brightness) of the environment.
- Tint Difference Analysis: Calculate tint differences to identify shifts in color.
- Chromaticity Coordinates: Obtain xy chromaticity coordinates for detailed color analysis.
- Duv Deviation Calculation: Determine deviations from the Planckian locus for accurate color representation.
- LCD Display: View color data and analysis results on a 16x2 LCD screen.
 
Requirements:

- Arduino board (e.g., Arduino Uno)
- Adafruit TCS34725 RGB color sensor16x2 LCD display
- Resistors, wires, button and other basic electronic components
- 
Installation:

1. Connect the Adafruit TCS34725 sensor and the LCD display to the Arduino board. (I2c protocol on the 4 and 5 pin)
2. Upload the provided Arduino sketch to the board using the Arduino IDE.
3. Ensure all connections are secure and powered on.
4. Press the button to capture color data and view the results on the LCD display.

Usage

1. Press the button on the Arduino board to capture color data.
2. View color temperature, illuminance, and tint difference on the LCD display.
3. Analyze the data to understand the characteristics of different light sources.
4. Customize the code to suit specific requirements or integrate additional features.

Contributing
Contributions to this project are welcome! 
It would be great to add a calibration option.
A menu!
And if it is possible to check the math it would be great.
Feel free to submit bug reports, feature requests, or pull requests to improve the functionality and usability of the project.
LicenseThis project is licensed under the MIT License.

AcknowledgmentsThanks to Adafruit for providing the TCS34725 RGB color sensor library.
Special thanks to the Arduino community for their support and contribution.

Math is based on conmusa.org
https://cormusa.org/wp-content/uploads/2018/04/CORM_2011_Calculation_of_CCT_and_Duv_and_Practical_Conversion_Formulae.pdf
