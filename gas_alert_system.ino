#define BLYNK_TEMPLATE_ID "Add temp form blynk iot "
#define BLYNK_TEMPLATE_NAME "Gas Alert System"
#define BLYNK_AUTH_TOKEN "add token form blynk iot"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// -------- BLYNK DETAILS --------
char ssid[] = "Wifi name";
char pass[] = "WIfi pass";

// -------- PIN DEFINITIONS --------
#define MQ2_PIN 34
#define DHT_PIN 4
#define BUZZER 18
#define LED_NORMAL 26
#define LED_ALERT 27

#define DHTTYPE DHT11

// -------- OBJECTS --------
DHT dht(DHT_PIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

// -------- VARIABLES --------
int gasThreshold = 2000;   // Adjust after testing
bool alertState = false;

void setup() {
  Serial.begin(9600);

  pinMode(MQ2_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED_NORMAL, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);

  digitalWrite(LED_NORMAL, HIGH);
  digitalWrite(LED_ALERT, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Gas Alert System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, checkSensors);
}

void checkSensors() {
  int gasValue = analogRead(MQ2_PIN);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("Gas: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    alertState = true;
  } else {
    alertState = false;
  }

  if (alertState) {
    // ----- ALERT MODE -----
    digitalWrite(LED_NORMAL, LOW);
    digitalWrite(BUZZER, HIGH);

    digitalWrite(LED_ALERT, !digitalRead(LED_ALERT)); // Blinking

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  GAS LEAK!");
    lcd.setCursor(0, 1);
    lcd.print("  DANGER ALERT");

    Blynk.virtualWrite(V2, 1);
    Blynk.logEvent("gas_alert", "⚠ Gas Leakage Detected!");

  } else {
    // ----- NORMAL MODE -----
    digitalWrite(LED_NORMAL, HIGH);
    digitalWrite(LED_ALERT, LOW);
    digitalWrite(BUZZER, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(humidity);
    lcd.print(" %");

    Blynk.virtualWrite(V2, 0);
  }

  // Send DHT data to Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V3, humidity);
}

void loop() {
  Blynk.run();
  timer.run();
}