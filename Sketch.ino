int buzzer = 2 ;// настройка управления цифровыми выводами динамика и датчика
int echoPin = 4;
int trigPin = 3;

void setup ()
{
  pinMode (buzzer, OUTPUT) ;// установка режима цифрового ввода-вывода
  pinMode(trigPin, OUTPUT); // на вывод данных
  pinMode(echoPin, INPUT);  // на ввод данных
   Serial.begin (9600); 
}
void loop ()
{
  int duration;
  int cm; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(15); //импульс длительностью 15 мкс чтобы запустить ультразвуковой датчик в работу
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); // считываем время
  cm = duration / 58,2;     // пересчитываем время в расстояние
  Serial.print(cm); 
  Serial.println(" cm"); 
  
    delay(300);

  if (cm >= 10 && cm <=200)
  {
    int wait = map(cm, 10, 200, 0, 255);
    digitalWrite (buzzer, HIGH) ; // включение пищалки
    delay (wait) ;    // длительность звукового сигнала 1мс
     digitalWrite (buzzer, LOW) ;// выключение пищалки
  }else {
} digitalWrite (buzzer, LOW);
}