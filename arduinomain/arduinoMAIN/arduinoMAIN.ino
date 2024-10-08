#include <AccelStepper.h>
#include <Servo.h>
Servo servoRIGHT;
Servo servoLEFT;
Servo servoKOLENO;

int counter = 0;
int s, x, y, w, h, n; //расстояние в мм
/*
  Написать значение переменных:
s = 12;
x = 12;
y = 12;
w = 12;
h = 12;
n = 12;
*/
String incomingByte;
int counter = 0;
int order = 0;
String ans;

//пины для шаговых
const int stepPin1 = 2;  // пин шага для двигателя 1
const int dirPin1 = 3;  // пин направления для двигателя 1
const int stepPin2 = 4;  // пин шага для двигателя 2
const int dirPin2 = 5;  // пин направления для двигателя 2
const int stepPin3 = 6;  // пин шага для двигателя 3
const int dirPin3 = 7;  // пин направления для двигателя 3

// ОТРЕДАКТИРОВАТЬ шаг в один оборот для немы17
const int stepsPerRevolution = 200;

//  объект accelstepper для каждого двигателя
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);

void setup() {

  servoRIGHT.attach(3);
  servoLEFT.attach(9);
  servoKOLENO.attach(11);

  // ПОМЕНЯТЬ ПОД ПАРАМЕТРЫ /настройка скорости и ускорения шаговых двигателей
  stepper1.setMaxSpeed(200);
  stepper1.setAcceleration(100);
  stepper2.setMaxSpeed(200);
  stepper2.setAcceleration(100);
  stepper3.setMaxSpeed(200);
  stepper3.setAcceleration(100);

  Serial.begin(115200);
  
}

int way_to_degrees(int way) {
  /*Перевод из миллиметров в градусы*/

  double diff = way/127.;
  int degree = diff*360/5;
  return (degree);
}

void move_forward(int arg) {
  /*Движение прямо*/
  int full_way = way_to_degrees(arg);
  servoRIGHT.write(full_way);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(full_way);
}

void turn_right(){
  /*Поворот направо*/
  servoRIGHT.write(-18);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(18);

}

void turn_left(){
  /*Поворот налево*/
  servoRIGHT.write(18);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(-18);
}

void reverse(){
  /*Функция поворота*/
  servoRIGHT.write(36);//ВПИСАТЬ УГЛЫ
  servoLEFT.write(-36);
}

void QR_low_moving_to_pos() {
  /*Для задачи положения манипулятора для нижней полки*/
  // ОТРЕДАКТИРОВАТЬ  движение колен 
  stepper1.moveTo(); 
  stepper1.runToPosition();

  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo(); 
  stepper3.runToPosition();
}

void QR_answer() {
  Serial.println("QR");
  delay(50);
  ans = Serial.readString();
  return ans;
}

void QR_low_moving_back() {
  // Пауза 1 секунда
  delay(1000);

  // движение обратно
  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}

void QR_high_moving_to_pos() {
  /*Для задачи положения манипулятора для верхней полки*/
  // ОТРЕДАКТИРОВАТЬ  движение колен 
  stepper1.moveTo();
  stepper1.runToPosition();

  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo();
  stepper3.runToPosition();
}
  
/*Написать движение манипулятора*/
void QR_high_moving_back() {
  delay(1000);

  // движение обратно
  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}


/*
Объяснение ( ):
  Робот должен встать в ту точку, где должна происходить выгрузка в зависимости от номера заказа (Переменная order)
  Далее происходит выгрузка в эту точку в завимости от количества деталек в его багажнике(Переменная counter)
*/
//Написать движение робота + коленей для каждого из номера заказов
load_out(int order, int counter) {
  if (order == 1){
    //подкатывает к столу заказов 
    servoRIGHT.write(-18);//ВПИСАТЬ УГЛЫ
    servoLEFT.write(18);

    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo(); 
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//взял
    delay(1000);

    stepper1.moveTo(0); 
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0); 
    stepper3.runToPosition();
    delay(1000);

    stepper1.moveTo();//в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo();
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);

    servoKOLENO.write(180);//выгрузил
    delay(1000);


    stepper1.moveTo(0); 
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0); 
    stepper3.runToPosition();
    delay(1000);
  }
  if (order == 2){
       //подкатывает к столу заказов 
    servoRIGHT.write(-18);//ВПИСАТЬ УГЛЫ
    servoLEFT.write(18);

    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo(); 
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//взял
    delay(1000);

    stepper1.moveTo(0); 
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0); 
    stepper3.runToPosition();
    delay(1000);

    stepper1.moveTo();//в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo();
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);

    servoKOLENO.write(180);//выгрузил
    delay(1000);


    stepper1.moveTo(0); 
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0); 
    stepper3.runToPosition();
    delay(1000);
    
  }
  if (order == 3){
      //подкатывает к столу заказов 
    servoRIGHT.write(-18);//ВПИСАТЬ УГЛЫ
    servoLEFT.write(18);

    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo(); 
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//взял
    delay(1000);

    stepper1.moveTo(0); 
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0); 
    stepper3.runToPosition();
    delay(1000);

    stepper1.moveTo();//в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo();
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);

    servoKOLENO.write(180);//выгрузил
    delay(1000);


    stepper1.moveTo(0); 
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0); 
    stepper3.runToPosition();
    delay(1000);
  } 
}
*/


// Написать движение коленей для каждого из каунтеров Каунтеры - кол-во коробок
load_in(int counter){
  servoKOLENO.write(36);//ВПИСАТЬ
  if (counter == 1){
//загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);

    stepper1.moveTo(0); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0);
    stepper3.runToPosition();
    delay(1000)

  }
  if (counter == 2){
   //загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);

    stepper1.moveTo(0); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0);
    stepper3.runToPosition();
    delay(1000)

  }
  if (counter == 3){
    //загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);

    stepper1.moveTo(0); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0);
    stepper3.runToPosition();
    delay(1000)

  }
  if (counter == 4){
    //загрузка В багажник
    stepper1.moveTo(); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(); 
    stepper2.runToPosition();

    stepper3.moveTo();
    stepper3.runToPosition();
    delay(1000);
    servoKOLENO.write(180);//отпустил, вписать угл
    delay(1000);

    stepper1.moveTo(0); //в аргументы функции дописать положение
    stepper1.runToPosition();

    stepper2.moveTo(0); 
    stepper2.runToPosition();

    stepper3.moveTo(0);
    stepper3.runToPosition();
    delay(1000)
}

//Здесь нужно больше кода. Манипулятор должен не только закинуть на верхнее звено коробку, но и поднять ее, не уронив полку
void take_high() {
  //Для захвата коробки на верхней полке

  stepper1.moveTo(); //в аргументы функции дописать положение
  stepper1.runToPosition();

  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo(); 
  stepper3.runToPosition();

  servoKOLENO.write(180)//взял 
  delay(1000)
  
  
  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}


//Здесь нужно больше кода. Манипулятор должен не только закинуть на верхнее звено коробку, но и поднять ее, не уронив полку, а потом положить в багажник
void take_low() {
   //Для захвата коробки на нижней полке

  stepper1.moveTo(); //в аргументы функции дописать положение
  stepper1.runToPosition();

  stepper2.moveTo(); 
  stepper2.runToPosition();

  stepper3.moveTo(); 
  stepper3.runToPosition();

  servoKOLENO.write(180)//взял 
  delay(1000)


  stepper1.moveTo(0);
  stepper1.runToPosition();

  stepper2.moveTo(0);
  stepper2.runToPosition();

  stepper3.moveTo(0);
  stepper3.runToPosition();
}


void loop() {
  delay(100);
  if (Serial.available() > 0) {
    incomingByte = Serial.readString();
    if (incomingByte == "START") {
      order = order + 1;
      move_forward(y);
      QR_low_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_back();
      if (ans == "TAKE"){
        take_low();
        counter = counter + 1;
        load_in(counter)
      QR_high_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_high_moving_back();
      if (ans == "TAKE"){
        take_high();
        counter = counter + 1;
        load_in(counter)
      turn_right();
      move_forward(w/2+n);
      turn_left();
      move_forward(h);
      turn_left();
      move_forward(w/2+n);
      turn_right();
      QR_low_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_low_moving_back();
      if (ans == "TAKE"){
        take_low();
        counter = counter + 1;
        load_in(counter)
      }
      QR_high_moving_to_pos();
      delay(100);
      ans = QR_answer();
      delay(100);
      QR_high_moving_back();
      if (ans == "TAKE"){
        take_high();
        counter = counter + 1;
        load_in(counter)
      }
      turn_left();
      move_forward(w/2+x);
      turn_right();
      move_forward();
      load_out(order, counter);
      reverse();
      move_forward(s+h);
      turn_left();
      move_forward(w/2+x);
      turn_right();
      move_forward(y);
      reverse();
      Serial.println("END");
  }
}
