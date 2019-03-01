/*PINES */
int pwma1 = 10;
int pwmb1 = 11;
int ain21 = A3;
int ain11 = A2;
int bin11 = A0;
int bin21 = 13;
int stby1 = A1;
int pwma2 = 3;
int pwmb2 = 6;
int ain22 = 2;
int ain12 = 4;
int bin12 = 9;
int bin22 = 7;
int stby2 = 8;
int sol = 12;

/*VARIABLES*/
String ord;
int pwm_a1 = 0;
int pwm_b1 = 0;
int pwm_a2 = 0;
int pwm_b2 = 0;
int dire_a11 = LOW;
int dire_b11 = LOW;
int dire_a21 = LOW;
int dire_b21 = LOW;
int dire_a12 = LOW;
int dire_b12 = LOW;
int dire_a22 = LOW;
int dire_b22 = LOW;

int position_ly=0;
int position_ry=0;
int fire = -1;
int fire_force = 210;
float trans = 0.398;
void setup() {
  pinMode ( pwma2, OUTPUT);
  pinMode ( pwmb2, OUTPUT);
  pinMode ( ain22, OUTPUT);
  pinMode ( ain12, OUTPUT);
  pinMode ( bin12, OUTPUT);
  pinMode ( bin22, OUTPUT);
  pinMode (stby1, OUTPUT);
  pinMode (stby2, OUTPUT);
  pinMode (pwma1, OUTPUT);
  pinMode(pwmb1, OUTPUT);
  pinMode(ain11, OUTPUT);
  pinMode(ain21, OUTPUT);
  pinMode(bin21, OUTPUT);
  pinMode(bin11, OUTPUT);

  pinMode(0, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.setTimeout(6);

}
void loop() {


  /* borrara esto serial print */
  if (Serial.available()) {
    ord = Serial.readStringUntil('\n');
    Serial.println("********************");
    Serial.println("STRING");
    Serial.println(ord);
    Serial.println("********************");
    /* hasta aqui */

    /* SLICING */
    int position_ly_ind = ord.indexOf(";", 0);
    int position_rx_ind = ord.indexOf(";", position_ly_ind + 1);


    int position_ly = ((ord.substring(0, position_ly_ind)).toInt()) * trans;  /*control motor1 */
    int position_ry = ((ord.substring(position_ly_ind + 1, position_rx_ind)).toInt()) * trans; /* control motor 2*/
    int fire = (ord.substring(position_rx_ind + 1)).toInt(); /* estado del disparador */

    /*tambien borrar esto*/
    Serial.println("--------------------------");
    Serial.println("position ly");
    Serial.println(position_ly);

    Serial.println("position ry");
    Serial.println(position_ry);
    Serial.println("fire");
    Serial.println(fire);
    Serial.println("--------------------------");

    Serial.println(position_ly);
    /* hasta aqui*/

  }


    /* CONTROL */
    /* stanby*/
    if (position_ly == 0 and position_ry == 0) {
      digitalWrite(stby1, LOW);
    }
    else {
      digitalWrite(stby1, HIGH);
    }
    if (fire == -1) {
      digitalWrite(stby2, LOW);
      fire_force = 0;

    }


    else {
      digitalWrite(stby2, HIGH);
      fire_force = 210;
    }


    /*direccion y potencia */
    if (position_ly >= 0) {
      pwma1 = position_ly;
      dire_a11 = HIGH;
      dire_a21 = LOW;
    }
    else {
      pwma1 = -position_ly;
      dire_a11 = LOW;
      dire_a21 = HIGH;
    }
    if (position_ry >= 0){
    pwmb1 = position_ry;
    dire_b11 = HIGH;
    dire_b21 = LOW;
  }
  else {
    pwmb1 = -position_ry;
    dire_b11 = LOW;
    dire_b21 = HIGH;
  }
  /* Disparo */

  if (fire == 1) {
      dire_a12 = HIGH;
      dire_a22 = LOW;
      dire_b12 = HIGH;
      dire_b22 = LOW;
    }
    else if (fire == 0) {
      dire_a12 = LOW;
      dire_a22 = HIGH;
      dire_b12 = LOW;
      dire_b22 = HIGH;
    }

    /* motor 1 puente h 1*/
    analogWrite ( pwma1, pwm_a1);
    digitalWrite(ain11, dire_a11);
    digitalWrite(ain21, dire_a21);
    /* motor 2 puente h 1*/

    analogWrite(pwmb1, pwm_b1);
    digitalWrite(bin11, dire_b11);
    digitalWrite(bin21, dire_b21);

    /* motor 1 puente H 2 */
    analogWrite(pwma2, fire_force);
    digitalWrite(ain12, dire_a12);
    digitalWrite(ain22, dire_a22);
    /* motor 2 puente H 2*/
    analogWrite(pwmb2, fire_force);
    digitalWrite(bin12, dire_b12);
    digitalWrite(bin22, dire_b22);
if (fire==1){
  digitalWrite(sol,HIGH);
}
else{
  digitalWrite(sol,LOW);
}
  
}
