#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <SimpleDHT.h>

// Replace with your network credentials

const char* ssid = "WIFI_NAME";
const char* password = "password";



// Uncomment the type of sensor in use:
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

int moistpin = 36;

int gaspin = 15;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDHTTemperature() {

  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return "--";
  }
  
 
  else {
    Serial.println((float)temperature);
    delay(2000);
    return String((float)temperature);
  }
}

String readDHTHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return "--";
  }
  
  else {
    Serial.println((float)humidity);
    delay(2000);
    return String((float)humidity);
  }
}

String readMoisture(){
  int v = analogRead(moistpin);
  v = map(v,550,10,0,100);
  //v = ( 100 - ( (v/1023.00) * 100 ) );
  Serial.print("Moisture : ");
  Serial.print(v);
  Serial.println("%");
  //delay(2000);
  if(v)return String(v);
  else return "--";
}

String readGassensor(){
  int gasvalue = analogRead(gaspin);
  Serial.print("Gas Sensor: "); Serial.println(gasvalue);
  return String(gasvalue);
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
    <link rel="stylesheet" href="style.css">
    <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Trirong">
    <style>
        * {
  box-sizing: border-box;
  font-family: "Trirong", serif;
  font-weight: bold;
}

.projectName {
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 3rem;
  color:green;
  +
}
.sensor,
.desc {
  padding-top: 50px;
}
.container {
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
}
.row {
  display: flex;
  flex-direction: row;
  align-items: center;
  border: 2px solid rgb(12, 9, 9);
  padding: 0px 10px;
  margin: 0.5em;
  width: 20%;
}
.name {
  text-align: center;
  padding-right: 1em;
}
.text {
  width: 50%;
  border-left: 2px solid rgb(12, 9, 9);
  padding-left: 0.5em;
}
.desc {
  display: flex;
  justify-content: center;
  align-items: center;
}
.description {
  border: 2px solid rgb(12, 9, 9);
  width: 20%;
  padding: 0.5em;
  display: flex;
  flex-direction: column;
}

h3 {
  margin-top: 0px !important;
}

@media (min-width: 320px) and (max-width: 767px) {
  .container {
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
  }
  .row {
    display: flex;
    flex-direction: row;

    border: 2px solid rgb(12, 9, 9);
    padding: 0px 10px;
    margin: 0.5em;
    width: 80%;
  }
  .name {
    text-align: center;
    padding-right: 1em;
  }
  .text {
    width: 50%;
    border-left: 2px solid rgb(12, 9, 9);
    padding-left: 0.5em;
  }
  .description {
    border: 2px solid rgb(12, 9, 9);
    width: 100%;
    padding: 0.5em;
    display: flex;
    flex-direction: column;
  }

  .desc {
    display: flex;
    justify-content: center;
    align-items: center;
  }
}

    </style>
    <title>Mini Project</title>
</head>

<body>
    <section class="head">
        <div class="projectName">
            PLANT MONITORING
        </div>
    </section>
    <section class="sensor">
        <div class="container">
        
            <div class="row">
                <div class="fas fa-thermometer-half" style="color:#059e8a;"></div>
                <div class="name" id='sensor1'>Temperaure</div>
                <div class="text" id="temperature" >%TEMPERATURE%</div>
                <sup class="units">&deg;C</sup>
            </div>
            <div class="row">
                <i class="fas fa-tint" style="color:#00add6;"></i> 
                <div class="name" id='sensor2'>Humidity</div>
                <div class="text" id="humidity">%HUMIDITY%</div>
                <sup class="units">&percnt;</sup>
            </div>
            <div class="row">
                <div class="name" id='sensor3'>Moisture</div>
                <div class="text" id="moisture">%MOISTURE%</div>
                <sup class="units">&percnt;</sup>
            </div>
            <div class="row">
                <div class="name" id='sensor3'>GAS Sensor</div>
                <div class="text" id="gassensor">%GAS_SENSOR%</div>
                
            </div>
        </div>
    </section>
    <section class="desc">
        <div class="description">
           <h3>Presented By:</h3>
           <li>Harsh Sharma</li>  
           <li>Amar Mohanta</li>  
           <li>Manish Kumar Singh</li>   
           <li>Anikesh Kumar</li>   
           <li>Vikash Mishra</li>   
        </div>
    </section>
    <script src="script.js"></script>
</body>

</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  else if(var == "MOISTURE"){
    return readMoisture();
  }
  else if(var == "GAS_SENSOR"){
    return readGassensor();
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);


  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
  server.on("/moisture", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readMoisture().c_str());
  });
  server.on("/gassensor", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readGassensor().c_str());
  });
  // Start server
  server.begin();
}
 
void loop(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
   server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
    //request->send_P(200, "text/plain", readDHTHumidity().c_str());
    //request->send_P(200, "text/plain", readMoisture().c_str());
  });
  delay(2000);
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });
  delay(2000);
  server.on("/moisture", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readMoisture().c_str());
  });
  delay(2000);
    server.on("/gassensor", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readGassensor().c_str());
  });
  delay(2000);
}
