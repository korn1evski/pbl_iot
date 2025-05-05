## 🛠 Getting Started

### 1. Initialize the Database

Run this command to create the database with students and schedule tables:

```
python init_db.py
```

---

## 🔌 USB Serial Version

### 2. Set the Serial Port

Find your ESP32 serial port (on macOS):

```
ls /dev/tty.*
```

Update the port in `listener.py`:

```python
ser = serial.Serial('/dev/tty.usbserial-0001', 115200)
```

Replace `/dev/tty.usbserial-0001` with your actual port.

### 3. Upload the Code to ESP32

Use PlatformIO to upload the serial version code (e.g. `main.cpp`).

### 4. Start the Listener

Run the Python listener:

```
python listener.py
```

---

## 🌐 Wi-Fi Version

### 1. Set Wi-Fi Credentials

In `main_wifi.cpp`, update:

```cpp
const char* ssid = "YourWiFi";
const char* password = "YourPassword";
const char* serverIP = "YourComputerIP"; // e.g. 192.168.0.134
```

### 2. Set Flask Port

Make sure `wifi_listener.py` uses the same port as the ESP32 expects:

```python
app.run(host='0.0.0.0', port=5001)
```

### 3. Upload Wi-Fi Code

Upload `main_wifi.cpp` to your ESP32 using PlatformIO.

### 4. Run the Flask Server

Run the Wi-Fi listener:

```
python wifi_listener.py
```
