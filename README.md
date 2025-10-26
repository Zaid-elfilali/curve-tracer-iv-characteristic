# Curve Tracer - IV Characteristic Tracer for Component Testing

## 📋 Project Overview
This project involves the design and implementation of an IV (Current-Voltage) characteristic tracer for electronic components, with applications in fault detection and circuit analysis. The system can trace and display the electrical characteristics of components in real-time on a TFT display.

## 🎯 Key Features
- **Dual Channel Testing**: Ability to test and compare two components simultaneously
- **Real-time Graphing**: Visual display of IV characteristics on 1.8" TFT screen
- **Multiple Component Support**: Tests resistors, capacitors, diodes, and other electronic components
- **Automatic Switching**: Relay-based channel switching between CH1 and CH2
- **Signal Generation**: AD9833-based programmable waveform generator

## 🛠 Hardware Components
- **Microcontroller**: Arduino Nano
- **Display**: 1.8" TFT LCD (128x160 pixels)
- **Waveform Generator**: AD9833 DDS Module
- **Relay**: For channel switching
- **Op-Amps**: For signal conditioning and measurement
- **Power Supply**: 9V batteries for portability

## 🔧 Installation & Setup

### Hardware Connections

#### TFT Display Wiring:
| TFT Pin | Arduino Pin | Description |
|---------|-------------|-------------|
| GND     | GND         | Ground      |
| VDD     | 5V          | Power       |
| SCL     | D13         | Serial Clock|
| SDA     | D11         | Serial Data |
| RST     | D8          | Reset       |
| DC      | D9          | Data/Command|
| CS      | D10         | Chip Select |
| BLK     | 3.3V        | Backlight   |

#### AD9833 Generator Wiring:
| AD9833 Pin | Arduino Pin | Description |
|------------|-------------|-------------|
| VCC        | 3.3V/5V     | Power       |
| GND        | GND         | Ground      |
| DAT        | D6          | Serial Data |
| CLK        | D7          | Serial Clock|
| FNC        | D5          | Frequency   |

#### Relay Wiring:
| Relay Pin | Arduino Pin | Description |
|-----------|-------------|-------------|
| VCC       | 5V          | Power       |
| GND       | GND         | Ground      |
| S         | D4          | Control     |

### Software Setup
1. Install Arduino IDE
2. Install required libraries:
   - TFT Library for ST7735
   - AD9833 Library
   - SPI Library
3. Upload the `arduino_code.ino` to your Arduino Nano

## 🚀 Usage Instructions

### Basic Operation:
1. **Power On**: Connect 9V batteries to power the system
2. **Component Connection**:
   - CH1: Connect component to CH1 and GND terminals
   - CH2: Connect second component to CH2 and GND terminals
3. **Mode Selection**:
   - Use the mode button to switch between CH1 only or CH1+CH2 display
4. **View Results**: IV characteristics will be displayed in real-time on the TFT screen

### Testing Different Components:
- **Resistors**: Straight line through origin
- **Capacitors**: Elliptical characteristic curve
- **Diodes**: Characteristic forward voltage curve
- **Open Circuit**: Horizontal line
- **Short Circuit**: Vertical line

## 📊 Technical Specifications
- **Voltage Range**: 0-24V (selectable)
- **Frequency Range**: 25Hz-1kHz (selectable)
- **Display Resolution**: 128x160 pixels
- **Sampling Rate**: 126 points per period
- **Power Supply**: 2x 9V batteries

## 🔍 Applications
- **Fault Detection**: Identify defective components
- **Component Characterization**: Analyze IV characteristics
- **Educational Tool**: Learn about electronic component behavior
- **Quality Control**: Compare components for matching characteristics

## 🐛 Troubleshooting

### Common Issues:
1. **No Display**:
   - Check TFT connections
   - Verify power supply
   - Ensure proper library installation

2. **Incorrect Waveforms**:
   - Verify AD9833 connections
   - Check signal conditioning circuit
   - Calibrate offset voltages

3. **Channel Switching Problems**:
   - Test relay functionality
   - Verify mode button operation
   - Check relay control pin

## 📈 Future Improvements
- [ ] Automatic amplitude and frequency adjustment
- [ ] Curve storage and recall functionality
- [ ] Touch screen interface
- [ ] USB data export
- [ ] Automated fault detection algorithms

## 👥 Contributors
- **IHFRANE Ali**
- **EL FILALI Zaid**
## 👨‍🏫 Academic References

### Pr. Mohammed BENLAMLIH
**Project Supervisor** - Faculty of Sciences and Techniques, Tangier
- 📧 Email: mbenlamlih@uae.ac.ma
- 🔗 LinkedIn: https://www.linkedin.com/in/mohammed-benlamlih-dr-ing-49b04a1a7/

## 📚 References
- Project Report: `rapport-PFE.pdf`
- AD9833 Datasheet
- ST7735 TFT Display Documentation
- Arduino Official Documentation

## 📄 License
This project is developed as part of a university final year project at Abdelmalek Essaâdi University.
