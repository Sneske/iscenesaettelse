// C++ code
//
#define soilWet 350 //definerer grænsen til hvornår jorden er våd
#define soilDry 650 //definerer grænsen til hvornår jorden er tør

#define rgb_red 9 //Den port de forskellige farver til rgb bruger
#define rgb_green 11
#define rgb_blue 10

#define sensorPower 7 //porten vi bruger til at give hydrometeret strøm
#define sensorPin A1 //Det analoge input hvor vi modtager information fra hydrometeret
#define motorPower 2 //Porten vi bruger til at give motoren/vandpumpen strøm

void setup(){
  pinMode(sensorPower, OUTPUT); //Sætter sensorPower pinnen til at være output, så den kan give strøm
  digitalWrite(sensorPower, LOW); //Slukker for strømmen til sensoren, så den ikke bare kører på fuld skrald lige så snart vi tænder den
  
  pinMode(motorPower, OUTPUT); //Sætter motorPower pinnen til at være output så arduinoen kan give den strøm
  digitalWrite(motorPower, LOW); //Igen slukker for motoren/vandpumpen så den ikke bare kører lige så snart vi tænder det

  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  
  Serial.begin(9600); //Siger til arduinoen at den skal "snakke" med serial monitoren 9600 gange i sekundet
}

void loop() //vores main loop, som er selve programmet
{
  int moisture = readSensor(); //Laver en integer variabel kaldt "moisture" som læser sensoren/hydrometeret
  Serial.print("Analog output: ");
  Serial.println(moisture); //De her 2 linjer printer moisture værdien til kommandopromptet
  
  if (moisture < soilWet) {
    Serial.println("Soil is too wet");
    digitalWrite(motorPower, HIGH);
    Serial.println("Motor stopped");
  }
  //Noget logik der siger at hvis jorden er for våd, så skal den slukke for motoren (hvis den altså er tændt)

  else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Soil moisture is perfect");
    digitalWrite(motorPower, HIGH);
    Serial.println("Motor stopped");
  }
  //Noget mere logik der siger at hvis jorden er midt imellem at være for tør og for våd, så er jorden perfekt, og motoren/vandpumpen stoppes

  else {
    Serial.println("Soil is too dry");
    digitalWrite(motorPower, LOW);
    Serial.println("Motor started");
    delay(2000);
    digitalWrite(motorPower, HIGH);
    Serial.println("Motor Stopped");
  }
  //Logik der gør at hvis jorden er for tør, så tændes motoren i 2000 ms, altså 2 sekunder, så den ikke bare bliver ved med at sprøjte vand
  
  analogWrite(rgb_red, 255);
  analogWrite(rgb_blue, 255);
  delay(2000); //Et lille delay der gør at den kun løber det her loop igennem en gang i sekundet
  Serial.println(); //Bare et lille mellemrum
  
}

int readSensor() { //Funktionen der læser sensorens værdi
  digitalWrite(sensorPower, HIGH); //starter med at tænde sensoren
  delay(10); //Lidt tid til at få respons fra sensoren
  int value = analogRead(sensorPin); //Laver variablen "value" som gemmer værdien fra sensoren
  Serial.println(value); //Printer "value" til kommandpromptet så vi kan se værdien
  digitalWrite(sensorPower, LOW); //slukker igen for sensoren
  return value; //Sender den aflæste værdi tilbage til der hvor funktionen er blevet kørt fra
}