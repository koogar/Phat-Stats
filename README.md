![](https://github.com/koogar/Phat-Stats/blob/main/images/PhatStats%20RTX3080_i9-13900k.jpg)

Phat-Stats is an open-source Arduino project that transforms a TFT display into a real-time PC hardware performance monitor. Developed by Rupert Hirst and Colin Conway, it serves as a larger, color-enhanced counterpart to the Gnat-Stats OLED monitor, offering a visually rich interface for tracking system metrics.([GitHub][1], [GitHub][2])

---

### 🔧 Features

* **Real-Time Monitoring**: Displays key PC performance metrics such as CPU usage, temperatures, and more.
* **TFT Display Support**: Designed for ILI9341 TFT screens, providing a vibrant and detailed visual output.
* **Arduino Compatibility**: Supports various Arduino-compatible boards, including ESP32 and Seeeduino XIAO.
* **Windows Integration**: Utilizes the HardwareSerialMonitor Windows client to fetch and transmit system data via USB serial communication.([GitHub][1], [GitHub][3], [GitHub][4])

---

### 🛠️ Getting Started

1. **Hardware Setup**:

   * Connect an ILI9341 TFT display to your chosen Arduino-compatible board.
   * For detailed setup guides and tutorials, refer to the [Phat-Stats ILI9341 TFT Display Hook-Up Guide](https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html).
    
2. **Software Installation**:

   * Flash the appropriate Phat-Stats firmware onto your microcontroller.
   * Install the [HardwareSerialMonitor](https://github.com/koogar/HardwareSerialMonitor) on your Windows PC to relay performance data.
3. **Configuration**:

   * Adjust settings within the Phat-Stats firmware and HardwareSerialMonitor to match your hardware setup and monitoring preferences.

---

### 📦 Repository Contents

* **Firmware Variants**:

  * `PhatStats_ESP32_LOLIN`: For ESP32-based boards.
  * `PhatStats_XIAO_QT-PY_WIO`: Tailored for Seeeduino XIAO and similar boards.

* **Documentation**:

  * `README.md`: Project overview and setup instructions.
  * `LICENSE.txt`: GPL v2 license details.([GitHub][1], [GitHub][3], [GitHub][2])

---

### 📄 License

Phat-Stats is released under the GNU General Public License v2.0. You are free to use, modify, and distribute this software in accordance with the license terms.

---

### 🔗 Additional Resources

* **Project Blog**: [Runaway Brainz](http://runawaybrainz.blogspot.com/)
* **Developer Site**: [Tallman Labs](http://tallmanlabs.com)
* **Related Projects**:

  * [Gnat-Stats](https://github.com/koogar/Gnat-Stats): A compact OLED-based performance monitor.
  * [Tacho-Stats](https://github.com/koogar/Tacho-Stats): Designed for Seeed Studio Round Displays.([GitHub][5], [GitHub][2], [GitHub][3])

---

For detailed setup guides and tutorials, refer to the [Phat-Stats ILI9341 TFT Display Hook-Up Guide](https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html).

---

[1]: https://github.com/koogar/Phat-Stats?utm_source=chatgpt.com "GitHub - koogar/Phat-Stats: TFT Arduino PC Hardware Performance Serial ..."
[2]: https://github.com/koogar/Gnat-Stats?utm_source=chatgpt.com "GitHub - koogar/Gnat-Stats: GnatStats Tiny OLED Arduino PC Hardware ..."
[3]: https://github.com/koogar/Tacho-Stats?utm_source=chatgpt.com "GitHub - koogar/Tacho-Stats: PC Hardware Performance Monitor for the ..."
[4]: https://github.com/koogar/HardwareSerialMonitor?utm_source=chatgpt.com "GitHub - koogar/HardwareSerialMonitor: PC Performance Stats Serial ..."
[5]: https://github.com/koogar?utm_source=chatgpt.com "koogar (Tallman Labs) - GitHub"

 
  #GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client  
   Rupert Hirst & Colin Conway © 2016-2025

 http://tallmanlabs.com
 http://runawaybrainz.blogspot.com/  
 https://hackaday.io/project/19018-phat-stats-pc-performance-tft-display
  

# Phat-Stats TFT
 Arduino PC Hardware Performance Serial Display
Phat-Stats ILI9341 TFT

https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html

![](https://github.com/koogar/Phat-Stats/blob/main/images/PhatStats%20RTX3080_i9-13900k.jpg)

![](https://github.com/koogar/Phat-Stats/blob/main/images/20230526_144402%20(Small).jpg)

![](https://github.com/koogar/Phat-Stats/blob/main/images/20230526_142556%20(Small).jpg)

![](https://github.com/koogar/Phat-Stats/blob/main/images/7245421623855690457.JPG)

![](https://github.com/koogar/Phat-Stats/blob/main/images/5498131627768760558.jpg)

![](https://github.com/koogar/Phat-Stats/blob/main/images/6503981623856862767.png)

  Licence
  -------
  
  GPL v2
  
Gnat-Stats, Phat-Stats & Hardware Serial Monitor 
Copyright (C) 2016  Colin Conway, Rupert Hirst and contributors
 
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; If not, see <http://www.gnu.org/licenses/>.
