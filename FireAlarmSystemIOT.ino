 #include <DHT.h>  
 #include <ESP8266WiFi.h>  
 #include <WiFiClient.h>  
 #include <ThingSpeak.h>  
 #define DHTPIN D6 
 #define DHTTYPE DHT11  
 DHT dht(DHTPIN, DHTTYPE);
 int smoke;
 const int flame = D0; 
 const int buzz = D2;  
 const char* ssid = "GNXS-46665";  
 const char* password = "123456780";  
 WiFiClient client;  
 unsigned long myChannelNumber = 1255530;  
 const char * myWriteAPIKey = "ZQVO62SRG1M24S";  
 uint8_t temperature; 
 void setup()  
 {  
  pinMode(flame,INPUT);
  pinMode(buzz,OUTPUT);
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
 }  
 void loop()   
 {  
   smoke=analogRead(A0);
   Serial.print("smoke value is:");
   Serial.print(smoke);
   ThingSpeak.writeField(myChannelNumber, 1, smoke, myWriteAPIKey); 
   int flme = digitalRead(flame);
   Serial.print("Flame value is:");
   Serial.print(flme);
   ThingSpeak.writeField(myChannelNumber, 2, flme, myWriteAPIKey); 
  temperature = dht.readTemperature();   
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
  Serial.println("C");      
  ThingSpeak.writeField(myChannelNumber, 3, temperature, myWriteAPIKey); 
  if((smoke>300 && flme==0) || (smoke>300 && temperature>35.00) || (flme==0 && temperature>35.00) || (smoke>300 && temperature>35.00 && flme==0))
  {
    ThingSpeak.writeField(myChannelNumber, 4,1, myWriteAPIKey);
    digitalWrite(buzz,HIGH); 
  }
  else
  {
    ThingSpeak.writeField(myChannelNumber, 4,0, myWriteAPIKey);
    digitalWrite(buzz,LOW);  
  }
  delay(13000);  
 }
