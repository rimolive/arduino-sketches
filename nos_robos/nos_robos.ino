 /*************************************************************
Garoando em linha para o BSides
por Ricardo Martinelli a.k.a. rimolive
*************************************************************/

void setup() {
  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  
  Serial.begin(9600);
}

void loop(){
  analogWrite(3, 200);
  analogWrite(11, 200);

  // Informaçoes dos sensores.
  //Serial.write("OTL=");
  Serial.write(digitalRead(2) == HIGH ? "HIGH" : "LOW");
  Serial.write(", OTC=");
  Serial.write(digitalRead(3) == HIGH ? "HIGH" : "LOW");
  Serial.write(", OTR=");
  Serial.write(digitalRead(4) == HIGH ? "HIGH" : "LOW");
  Serial.write("\n");
  
  // Logica bem simplista dos sensores
  if(digitalRead(5) == LOW && digitalRead(7) == LOW) {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
  } else if(digitalRead(5) == LOW) {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  } else if(digitalRead(7) == LOW) {
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
  }
    
}

