#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Servo.h> 
Servo myservo; 


// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "Mohamed";
const char* password = "11223344";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "broker.mqttdashboard.com";

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient mohamed;
PubSubClient client(mohamed);





const int lm35_pin = A0;  /* LM35 O/P pin */
const int p1_empty = 5;
const int p1_ocuppied = 4;
const int p2_empty = 14;
const int p2_ocuppied = 12;
const int led_g= 13;
int degree=0;


//Connect your NodeMCU to your router
void setup_wifi() {
  delay(10);
  Serial.begin(115200);
  Serial.println();
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - NodeMCU IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your NodeMCU is subscribed to

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageInfo;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageInfo += (char)message[i];
  }
  Serial.println();
 
  // If a message is received on the topic room/lamp, you check if the message is either on or off. Turns the lamp GPIO according to the message
  if(topic=="garage/p1"){
      Serial.print("Changing garage parking p1 Light to");
      if(messageInfo == "p1"){
        digitalWrite(p1_ocuppied , HIGH);
         digitalWrite(p1_empty ,LOW);
        Serial.print("ocuppied");
      }
      else {
          digitalWrite(p1_ocuppied , LOW);
         digitalWrite(p1_empty ,HIGH); 
         Serial.print("empty");      
      }
  }

  if(topic=="garage/p2"){
      Serial.print("Changing garage  parking p2 Light to ");
      if(messageInfo == "p2"){
        digitalWrite(p2_ocuppied , HIGH);
         digitalWrite(p2_empty ,LOW);
   
      }
      else {
    digitalWrite(p2_ocuppied , LOW);
         digitalWrite(p2_empty ,HIGH);
      }
  }

 if(topic=="garage/light"){
      Serial.print("Changing garage Light to ");
      if(messageInfo == "on"){
        digitalWrite(led_g, HIGH);
        Serial.print("On");
      }
      else if(messageInfo == "off"){
        digitalWrite(led_g, LOW);
        Serial.print("Off");
      }
  } 
   if(topic=="garage/open"){
      Serial.print("openning garage door ");
      if(messageInfo == "open"){
            Serial.print("openning garage door ");
        for(degree=90; degree>0; degree-=1){ 
        myservo.write(degree);   
       delay(3);  
        }    
      }
      else if(messageInfo == "close"){
            Serial.print("closeing garage door ");
        for(degree=0; degree<90; degree+=1){ 
        myservo.write(degree);   
        delay(3);     
        }    
      }
  } 
  Serial.println();
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    
    if (client.connect("mohamed")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("garage/light");
      client.subscribe("garage/p1");
      client.subscribe("garage/p2");
      client.subscribe("garage/p3");
      client.subscribe("garage/p4");
      client.subscribe("garage/open");

      
    } else {
      Serial.print("failed, rc=");
//      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  pinMode(p1_empty , OUTPUT);
  pinMode( p1_ocuppied , OUTPUT);
  pinMode(p2_empty , OUTPUT);
  pinMode( p2_ocuppied , OUTPUT);
  pinMode(led_g , OUTPUT);
  digitalWrite(p1_empty ,HIGH); 
  digitalWrite(p2_empty ,HIGH); 
//pinMode(trigpin, OUTPUT); // declare ultrasonic sensor Echo pin as input
//pinMode(echopin, INPUT);  // declare ultrasonic sensor Trigger pin as Output 

delay(500); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 myservo.attach(15); // declare Servo Motor as output
myservo.write(degree);  
}

// For this project, you don't need to change anything in the loop function. Basically it ensures that the NodeMCU is connected to MQTT broker
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("mohamed");
static char  temp_adc_val;
static char temp_val;
  temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10);
char tempString[8];
dtostrf(temp_val, 1, 2, tempString);

client.publish("garage/temp", tempString);
delay(200);

  }
