void tras(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);

  analogWrite(9, LOW);
  analogWrite(10, HIGH);
  analogWrite(11, LOW);

}

void frente(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);

  analogWrite(9, LOW);
  analogWrite(10, LOW);
  analogWrite(11, HIGH);

}

void parar(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);

  analogWrite(9, HIGH);
  analogWrite(10, LOW);
  analogWrite(11, LOW);
}

void setup() {
pinMode(3,OUTPUT);
pinMode(2,OUTPUT); 

pinMode(8, OUTPUT);

pinMode(9,OUTPUT);
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
}

void loop() {
  
 frente();
 delay(3000);
 parar();
 delay(5000);
 tras();
 delay(3000);

}
