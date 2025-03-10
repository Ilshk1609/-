// Определяем пины для ультразвукового датчика
const int trigPin = 9;
const int echoPin = 10;

// Определяем пин для вибромотора
const int motorPin = 3;

// Переменные для хранения расстояния и времени
long duration;
int distance;

void setup() {
  // Инициализация пинов
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin, OUTPUT);
  
  // Инициализация Serial для отладки
  Serial.begin(9600);
}

void loop() {
  // Очищаем trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Устанавливаем trigPin в HIGH на 10 микросекунд
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Считываем echoPin, возвращаем время в микросекундах
  duration = pulseIn(echoPin, HIGH);
  
  // Рассчитываем расстояние в сантиметрах
  distance = duration  / 58,2;
  
  // Выводим расстояние в Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Управляем вибромотором в зависимости от расстояния
  if (distance >= 10 && distance <= 175) {
    // Преобразуем расстояние в интенсивность вибрации (обратная зависимость)
    int intensity = map(distance, 10, 175, 255, 0);
    analogWrite(motorPin, intensity);
  } else {
    // Если расстояние вне диапазона, выключаем мотор
    analogWrite(motorPin, 0);
  }
  
  // Задержка для стабилизации измерений
  delay(100);
}
