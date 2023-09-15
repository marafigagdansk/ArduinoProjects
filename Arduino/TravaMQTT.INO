#include <SPI.h>
#include <Ethernet.h>

#include <PubSubClient.h>

byte mac[]    = { 0xDE, 0xED, 0xFD, 0xFE, 0xFE, 0xED };  
IPAddress server(52,13,116,147); 
int ID_RANDOM = random(0,9999);
EthernetClient ethClient;
PubSubClient client(ethClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
 
  if ((char)payload[0] == '1') {

    frente();
    delay(1000);
    parar();
    
  
    
  } else if  ((char)payload[0] == '0') {

    tras();
    delay(1000);
    parar();

  } 
}



void tras(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);

  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);

}

void frente(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);

  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);

}

void parar(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}

void setup()
{
  Serial.begin(57600);

  pinMode(3,OUTPUT);
  pinMode(2,OUTPUT); 

  pinMode(8, OUTPUT);

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  client.setServer(server, 1883);
  client.setCallback(callback);

  Ethernet.begin(mac);
  delay(5000); 

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
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }

  }
  client.loop();
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
}
