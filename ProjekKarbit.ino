#include <Servo.h> // Library untuk mengontrol servo
#include <NewPing.h> // Library untuk sensor ultrasonik
#include <Wire.h> // Library untuk komunikasi I2C
#include <LiquidCrystal_I2C.h> // Library untuk LCD I2C

// Pin untuk sensor ultrasonik
const int trigPin = 7; // Pin trig untuk mengirimkan sinyal ultrasonik
const int echoPin = 5; // Pin echo untuk menerima pantulan sinyal ultrasonik
const int maxdistance = 13; // Jarak maksimum sensor (cm)

// Pin untuk servo dan LED
const int servoPin = 9; // Pin untuk servo
const int ledPin_red = 2; // Pin LED merah
const int ledPin_yellow = 3; // Pin LED kuning
const int ledPin_green = 4; // Pin LED hijau

// Variabel untuk pengaturan interval servo
unsigned long waktu_servosebelumnya = 0; // Menyimpan waktu terakhir servo bergerak
unsigned long interval_waktuservo = 10000; // Interval waktu (10 detik)

// Inisialisasi objek servo, ultrasonik, dan LCD
Servo myservo; // Objek untuk mengontrol servo
NewPing sonar(trigPin, echoPin, maxdistance); // Objek untuk sensor ultrasonik
LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD dengan alamat I2C 0x27 dan ukuran 16x2

void setup() {
  myservo.attach(servoPin); // Hubungkan servo dengan pin
  myservo.write(0); // Set posisi awal servo pada 0 derajat (tertutup)
  Serial.begin(9600); // Inisialisasi komunikasi serial untuk debugging

  // Inisialisasi pin LED sebagai output
  pinMode(ledPin_red, OUTPUT);
  pinMode(ledPin_yellow, OUTPUT);
  pinMode(ledPin_green, OUTPUT);

  // Inisialisasi LCD
  lcd.begin(16, 2); // Set ukuran LCD (16 kolom, 2 baris)
  lcd.backlight(); // Aktifkan lampu latar LCD
  lcd.clear(); // Bersihkan layar LCD
}

void loop() {
  unsigned long waktusekarang = millis(); // Ambil waktu saat ini

  // Logika pemberian pakan menggunakan servo
  if (waktusekarang - waktu_servosebelumnya >= interval_waktuservo) {
    myservo.write(90); // Buka servo (90 derajat)
    delay(1000); // Tunggu selama 2 detik (pemberian pakan)
    myservo.write(0); // Kembali ke posisi awal (tertutup)
    waktu_servosebelumnya = waktusekarang; // Update waktu terakhir servo bergerak
  }

  // Mengukur jarak menggunakan sensor ultrasonik
  int distance = sonar.ping_cm(); // Hitung jarak dalam cm
  int ketinggian = maxdistance - distance; // Konversi ke ketinggian air

  // Tampilkan ketinggian air di Serial Monitor
  Serial.print("Ketinggian Air: ");
  Serial.print(ketinggian);
  Serial.println(" cm");

  // Tampilkan ketinggian air di LCD
  lcd.setCursor(0, 0); // Atur kursor ke baris pertama
  lcd.print("Tinggi Air: "); // Tampilkan teks
  lcd.print(ketinggian); // Tampilkan ketinggian
  lcd.print("cm  "); // Tambahkan spasi untuk menghapus karakter lama

  // Logika kontrol LED berdasarkan ketinggian air
  if (ketinggian < 5) { // Jika ketinggian kurang dari 5 cm
    digitalWrite(ledPin_red, HIGH); // Nyalakan LED merah
    digitalWrite(ledPin_yellow, LOW); // Matikan LED kuning
    digitalWrite(ledPin_green, LOW); // Matikan LED hijau
    lcd.setCursor(0, 1); // Atur kursor ke baris kedua
    lcd.print("Air Rendah      "); // Tampilkan pesan
  } else if (ketinggian >= 5 && ketinggian < 9) { // Jika ketinggian antara 5 - 8 cm
    digitalWrite(ledPin_red, LOW); // Matikan LED merah
    digitalWrite(ledPin_yellow, HIGH); // Nyalakan LED kuning
    digitalWrite(ledPin_green, LOW); // Matikan LED hijau
    lcd.setCursor(0, 1); // Atur kursor ke baris kedua
    lcd.print("Air Sedang      "); // Tampilkan pesan
  } else { // Jika ketinggian 9 cm atau lebih
    digitalWrite(ledPin_red, LOW); // Matikan LED merah
    digitalWrite(ledPin_yellow, LOW); // Matikan LED kuning
    digitalWrite(ledPin_green, HIGH); // Nyalakan LED hijau
    lcd.setCursor(0, 1); // Atur kursor ke baris kedua
    lcd.print("Air Tinggi      "); // Tampilkan pesan
  }

  delay(500); // Tunggu sebelum melakukan pengukuran berikutnya
}