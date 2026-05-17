#define BLYNK_TEMPLATE_ID "TMPL38N5ixTRf"
#define BLYNK_TEMPLATE_NAME "Irrigation System"
#define BLYNK_AUTH_TOKEN "OD0VM21FsFgJgFepkV4HpQRr_omrob4Q"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Blah blah";
char pass[] = "tinni2812";

#define SOIL_SENSOR_PIN 34
#define RELAY_PIN 25

BlynkTimer timer;

int moistureLevel = 0;
int percentage = 0;

bool manualControl = false;
bool pumpState = false;   // for hysteresis

// 🔘 Manual control from Blynk (V0 button)
BLYNK_WRITE(V0) {
  int value = param.asInt();

  if (value == 1) {
    manualControl = true;
    pumpState = true;
    digitalWrite(RELAY_PIN, HIGH);   // ON pump
  } else {
    manualControl = false;
    pumpState = false;
    digitalWrite(RELAY_PIN, LOW);    // OFF pump
  }
}

// 🌱 Auto irrigation logic
void checkSoil() {

  if (manualControl) return;

  moistureLevel = analogRead(SOIL_SENSOR_PIN);

  // 🔧 CALIBRATION (YOU MAY ADJUST THESE AFTER TESTING)
  int wetValue = 1500;
  int dryValue = 3500;

percentage = map(moistureLevel, dryValue, wetValue, 0, 100);
percentage = constrain(percentage, 0, 100);

  // Debug
  Serial.print("Raw ADC: "); 
  Serial.print(moistureLevel);
  Serial.print(" | Moisture %: ");
  Serial.println(percentage);

  Blynk.virtualWrite(V1, percentage);

  // 💧 HYSTERESIS CONTROL (prevents flickering)
  if (percentage < 40) {
    pumpState = true;     // soil dry → ON pump
  } 
  else if (percentage > 60) {
    pumpState = false;    // soil wet → OFF pump
  }

  digitalWrite(RELAY_PIN, pumpState ? LOW : HIGH);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting System...");

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // pump OFF initially

  WiFi.begin(ssid, pass);

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("Blynk Connected");

  timer.setInterval(3000L, checkSoil);
}

void loop() {
  Blynk.run();
  timer.run();
}
