#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte mac[] = { 0xDE, 0xDF, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(52, 13, 116, 147);
int ID_RANDOM = random(0, 9999);
EthernetClient ethClient;
PubSubClient client(ethClient);

bool isFrenteRunning = false;
bool isTrasRunning = false;

void callback(char* topic, byte* payload, unsigned int length) {

  if ((char)payload[0] == '1') {

    isFrenteRunning = true;
    isTrasRunning = false;
    frente();
    delay(1000);
    parar();
    isFrenteRunning = false;

  } else if ((char)payload[0] == '0') {

    isFrenteRunning = false;
    isTrasRunning = true;
    tras();
    delay(1000); 
    parar();
    isTrasRunning = false;

  }
}

void sensor() {
  int pinoSensor = 9;
  int valorSensor = digitalRead(pinoSensor);

  if (valorSensor == HIGH) {
    Serial.println("Trava aberta");
  } else {
    Serial.println("Trava fechada");

  }
}


void tras(){

  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);

}

void frente(){

  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);

}

void setup()
{

  Serial.begin(57600);
  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT); 

  pinMode(9,OUTPUT);

  client.setServer(server, 1883);
  client.setCallback(callback);
  Ethernet.begin(mac);
  delay(5000); 
  Serial.println(Ethernet.localIP());
  Serial.println();

}

void loop(){
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    byte willQoS = 0;
    const char* willTopic = "arduino/status";
    const char* willMessage = "OFF_LINE";
    boolean willRetain = true;

    if (client.connect(ID_RANDOM, willTopic, willQoS, willRetain, willMessage)) {
      Serial.println("connected");
      char* message = "ON_LINE";
      int length = strlen(message);
      boolean retained = true; 
      client.publish("catequese/status", (byte*)message, length, retained);
      client.subscribe("catequese/funcionamento");

    } else {
      Serial.print("falha, rc= ");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 seg");
      delay(5000);

    }

  }
  client.loop();
    digitalWrite(4,HIGH);
    sensor();
}
