#include <Wire.h>
#include <VL53L0X.h> // Библиотека для лазерного датчика VL53L0X

// Пины для ультразвукового датчика
const int trigPin = 2;
const int echoPin = 3;

// Пин для вибромотора
const int motorPin = 9;

// Объект для лазерного датчика
VL53L0X laserSensor;

void setup() {
  // Инициализация Serial для отладки
  Serial.begin(9600);

  // Настройка пинов для ультразвукового датчика
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Настройка пина для вибромотора
  pinMode(motorPin, OUTPUT);

  // Инициализация лазерного датчика
  Wire.begin();
  laserSensor.init();
  laserSensor.setTimeout(5000);
  laserSensor.startContinuous();
}

void loop() {
  // Измерение расстояния ультразвуковым датчиком
  long duration, distanceCm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration / 58.2; // Пересчет в сантиметры

  // Логика работы устройства
  if (distanceCm >= 100 && distanceCm <= 200) {
    // Работа ультразвукового датчика
    int motorIntensity = map(distanceCm, 200, 100, 0, 200); // Интенсивность вибрации
    analogWrite(motorPin, motorIntensity);
    Serial.print("Ультразвуковой датчик: ");
    Serial.print(distanceCm);
    Serial.println(" см");
  } else if (distanceCm >= 10 && distanceCm < 100) {
    // Отключение ультразвукового датчика и включение лазерного
     // Выключение вибромотора
    int laserDistance = laserSensor.readRangeContinuousMillimeters() /10
    ; // Пересчет в сантиметры
    if (laserSensor.timeoutOccurred()) {
      Serial.println("Ошибка лазерного датчика!");
    } else {
      int motorIntensity = map(laserDistance, 100, 10, 50, 255); // Интенсивность вибрации
      analogWrite(motorPin, motorIntensity);
      Serial.print("Лазерный датчик: ");
      Serial.print(laserDistance);
      Serial.println(" см");
    }
  } else {
    // Если расстояние больше 200 см, вибромотор выключен
    analogWrite(motorPin, 0);
  }

  delay(100); // Задержка для стабилизации измерений
}
 
