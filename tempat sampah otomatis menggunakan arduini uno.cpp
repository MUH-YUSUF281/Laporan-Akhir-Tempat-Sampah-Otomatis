#include <Servo.h>

// Define pin untuk komponen
const int trigPin = 9;  // Trigger pin sensor ultrasonik ke pin 9 Arduino
const int echoPin = 10; // Echo pin sensor ultrasonik ke pin 10 Arduino
const int servoPin = 11; // Sinyal pin servo ke pin 11 Arduino

// Inisialisasi objek Servo
Servo myServo;

// Variabel untuk menyimpan jarak
long duration;
int distance;

void setup() {
  Serial.begin(9600); // Inisialisasi komunikasi serial
  pinMode(trigPin, OUTPUT); // Set trigPin sebagai output
  pinMode(echoPin, INPUT);  // Set echoPin sebagai input
  myServo.attach(servoPin); // Set servo ke pin yang ditentukan
  myServo.write(0); // Set posisi awal servo (tertutup)
}

void loop() {
  // Mengukur jarak
  distance = calculateDistance();

  // Cek apakah ada objek terdeteksi dalam jarak tertentu (misal 30 cm)
  if (distance < 30) {
    Serial.println("Objek terdeteksi!");
    myServo.write(90); // Buka tutup tempat sampah (sesuaikan sudut sesuai kebutuhan)
    delay(1000); // Tunggu sebentar agar tutup terbuka sepenuhnya 
    
    // Looping sampai objek tidak terdeteksi lagi
    while (calculateDistance() < 30) {
      delay(100); // Delay sebentar untuk menghindari pembacaan sensor yang terlalu cepat
    }
    
    Serial.println("Objek hilang!");
    myServo.write(0); // Tutup kembali tempat sampah
  }

  delay(100); // Delay sebentar sebelum pengukuran jarak selanjutnya
}

// Fungsi untuk menghitung jarak dengan sensor ultrasonik
int calculateDistance() {
  // Membersihkan trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Mengirim pulsa ultrasonik
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Menghitung durasi pulsa echo
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak dalam centimeter
  distance = duration * 0.034 / 2;

  Serial.print("Jarak: ");
  Serial.println(distance);

  return distance;
}