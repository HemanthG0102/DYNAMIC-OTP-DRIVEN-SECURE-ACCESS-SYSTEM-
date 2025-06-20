# DYNAMIC-OTP-DRIVEN-SECURE-ACCESS-SYSTEM-
# Dynamic OTP-Driven Secure Access System

## 📌 Project Overview

This project implements a **Dynamic OTP-Driven Secure Access System** using the **LPC2148 ARM7 microcontroller**. It uses peripherals like **LCD**, **GSM (SIM900A)/(M660A)**, **Keypad**, **RTC**, **Motor (via L293D driver)**, and **I2C EEPROM (AT24C256)** to create a real-time, secure entry mechanism based on OTP verification. The system is suitable for high-security applications like **labs, server rooms, and home automation**.

---

## 🧩 Key Features

* **OTP Generation** using time-based logic (RTC)
* **SMS Delivery** of OTP using GSM module
* **Password-protected access change** via external interrupt
* **Real-time LCD display** of status and OTP countdown
* **EEPROM storage** for password
* **Motor-based door control**

---

## ⚙️ Hardware Requirements

| Component                   | Quantity | Purpose                        |
| --------------------------- | -------- | ------------------------------ |
| LPC2148 ARM7 MCU            | 1        | Central controller             |
| GSM Module (SIM900A)/(M660A)| 1        | Sending OTP via SMS            |
| 4x4 Keypad                  | 1        | OTP entry                      |
| LCD 16x2                    | 1        | Display messages & OTP         |
| L293D Motor Driver          | 1        | Drive DC motor for door lock   |
| DC Motor                    | 1        | Simulate door lock movement    |
| I2C EEPROM                  | 1        | Store default password         |
| RTC                         | 1        | Time-based OTP                 |
| Push Button (Interrupt)     | 1        | Trigger password change        |
| External Power Supply       | 5V & 9V  | Power MCU and motor separately |

---

## 💾 Software Requirements

* Proteus 8 or later (for simulation)
* Keil uVision (for code compilation)
* Flash Magic (for programming LPC2148)
* Embedded C with ARM7 Libraries

---

## 🔁 Functional Flow

1. **System Bootup**

   * Initializes all peripherals: LCD, RTC, UART, I2C EEPROM, Keypad.
   * Displays welcome message.

2. **OTP Generation**

   * On system start or request, generates 4-digit OTP based on RTC values.
   * Sends OTP to predefined number via GSM.

3. **User OTP Entry**

   * User enters OTP via keypad.
   * LCD shows time-limited entry window (e.g. 60 seconds).

4. **Verification**

   * If OTP matches, motor is triggered to unlock door (Motor\_Forward).
   * If incorrect, shows "Wrong OTP".

5. **Password Change**

   * When interrupt button is pressed, flag is set.
   * System asks for existing password (default: 000000).
   * If matched, allows password update and writes to EEPROM.

6. **Motor Control**

   * Door opens (Motor\_Forward for 3s), then closes (Motor\_Reverse for 3s).

---

## ⚠️ Common Debugging Tips

* **GSM Rubbish Output**: Ensure GSM baud rate matches UART, and use Virtual Terminal.
* **Motor not rotating**: Connect **EN pin to 5V**, not 9V. Confirm IN1/IN2 logic.
* **Proteus delay issues**: Delays may lag. On real hardware, timings are accurate.
* **Interrupt not triggering**: Confirm edge triggering config and correct pin (e.g. P0.16).

---

## 📞 SMS Format (GSM)

```
AT

AT+CMGF=1

AT+CMGS="Phone Number"

<OTP>
Message from Vector Security Agency
<Ctrl+Z>
```

---

## ✅ Final Notes

* Works with both real-time hardware and Proteus simulation.
* Modular design — easy to extend (e.g., add fingerprint, keypad lockout).
* Ensures security through **OTP** and **EEPROM password backup**.

---

## 📚 Credits

Developed by: **G.HEMANTH**
Platform: **LPC2148 ARM7 TDMI**, **Proteus**, **Keil C**

---

Feel free to modify this readme for academic reports or GitHub!

