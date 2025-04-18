# 🐟 Sistem Otomatisasi Peternakan Ikan

Proyek ini merupakan prototype alat otomatisasi untuk peternakan ikan yang dirancang oleh Kelompok 2. Alat ini dapat mengatur pemberian pakan ikan secara otomatis dan memantau ketinggian air dengan indikator visual berupa LED dan tampilan pada LCD.

## ⚙️ Spesifikasi Komponen

- **Arduino Uno R3** – Mikrokontroler utama
- **Mini Servo** – Menggerakkan pemberi pakan otomatis
- **Ultrasonic Sensor HC-SR04** – Mengukur ketinggian air
- **LCD I2C 16x2** – Menampilkan data ketinggian air
- **LED Merah, Kuning, Hijau** – Indikator visual kondisi air
- **Kabel Jumper, Breadboard, Resistor, Power Supply** – Komponen pendukung

## 🔁 Cara Kerja

### 1. Pengukuran Ketinggian Air
- Sensor ultrasonik menghitung jarak permukaan air ke sensor.
- Nilai dikonversi ke dalam satuan cm dan ditampilkan pada LCD.

### 2. Indikator LED
- **< 5 cm** → LED Merah: Air terlalu rendah
- **5 – 8 cm** → LED Kuning: Air sedang
- **>= 9 cm** → LED Hijau: Air cukup tinggi

### 3. Pemberian Pakan Otomatis
- Servo membuka pintu pakan setiap 10 detik (untuk simulasi).
- Pintu terbuka selama 2 detik, lalu menutup kembali.

## 🧠 Flowchart dan Alur Program

Program utama menggunakan library berikut:

```cpp
#include <Servo.h>
#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
