void setup() {
  // Inicia Serial para mostrar resultados na IDE Arduino
  Serial.begin(9600);
  delay (20000); // 20 segundos para o sensor estabilizar
}
 
void loop() {
  if (digitalRead(2)) { // Checa pino 2 para detectar movimento
    Serial.println("MOVEMENT"); // Movemento detectado
  } else {
    Serial.println("No Movement");// Movemento não detectado
  }
  // Lê em uma frequência de 2Hz, este valor pode ser alterado
  delay(500);
}
