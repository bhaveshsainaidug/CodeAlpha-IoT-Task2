#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ── LCD Setup ─────────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ── Pin Definitions ───────────────────────────────
const int POT_PIN    = A0;
const int LED_GREEN  = 8;
const int LED_RED    = 9;
const int LED_BLUE   = 10;
const int LED_YELLOW = 11;
const int BUZZER     = 12;

// ── BPM Thresholds ────────────────────────────────
const int IRREG_LOW   = 40;
const int NORMAL_LOW  = 60;
const int NORMAL_HIGH = 100;

// ── Timing ────────────────────────────────────────
unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 1000;

// ── Variables ─────────────────────────────────────
int bpm = 0;
int raw = 0;
String condition = "";

// ── Clear all LEDs ────────────────────────────────
void clearLEDs() {
  digitalWrite(LED_GREEN,  LOW);
  digitalWrite(LED_RED,    LOW);
  digitalWrite(LED_BLUE,   LOW);
  digitalWrite(LED_YELLOW, LOW);
}

// ── Classify BPM ──────────────────────────────────
String classify(int b) {
  if      (b >= NORMAL_LOW && b <= NORMAL_HIGH) return "NORMAL";
  else if (b > NORMAL_HIGH)                     return "TACHYCARDIA";
  else if (b >= IRREG_LOW  && b < NORMAL_LOW)   return "BRADYCARDIA";
  else                                           return "IRREGULAR";
}

// ── LCD Update ────────────────────────────────────
void updateLCD(int b, String cond) {
  lcd.setCursor(0, 0);
  lcd.print("BPM: ");
  lcd.print(b);
  lcd.print("     ");

  lcd.setCursor(0, 1);
  if      (cond == "TACHYCARDIA") lcd.print("TACHYCARDIA     ");
  else if (cond == "BRADYCARDIA") lcd.print("BRADYCARDIA     ");
  else if (cond == "IRREGULAR")   lcd.print("IRREGULAR       ");
  else                            lcd.print("NORMAL          ");
}

// ── Play tone based on condition ──────────────────
void playTone(String cond) {
  noTone(BUZZER);
  if      (cond == "NORMAL")      tone(BUZZER, 1000, 200);
  else if (cond == "TACHYCARDIA") tone(BUZZER, 1500, 100);
  else if (cond == "BRADYCARDIA") tone(BUZZER,  500, 600);
  else                            tone(BUZZER,  800, 300);
}

void setup() {
  Serial.begin(9600);

  Wire.begin();
  delay(100);
  lcd.init();
  delay(100);
  lcd.init();
  lcd.backlight();
  delay(200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arrhythmia");
  lcd.setCursor(0, 1);
  lcd.print("Detector v1.0");
  delay(2000);
  lcd.clear();

  pinMode(LED_GREEN,  OUTPUT);
  pinMode(LED_RED,    OUTPUT);
  pinMode(LED_BLUE,   OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(BUZZER,     OUTPUT);

  clearLEDs();
  noTone(BUZZER);

  Serial.println("=== Arrhythmia Detector Started ===");
}

void loop() {
  unsigned long now = millis();

  if (now - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = now;

    // 1. Read + map
    raw = analogRead(POT_PIN);
    bpm = map(raw, 0, 1023, 20, 180);
    bpm = constrain(bpm, 20, 180);

    // 2. Classify
    condition = classify(bpm);

    // 3. Reset
    clearLEDs();
    noTone(BUZZER);

    // 4. Set LED
    if      (condition == "NORMAL")      digitalWrite(LED_GREEN,  HIGH);
    else if (condition == "TACHYCARDIA") digitalWrite(LED_RED,    HIGH);
    else if (condition == "BRADYCARDIA") digitalWrite(LED_BLUE,   HIGH);
    else                                 digitalWrite(LED_YELLOW, HIGH);

    // 5. Play tone — no blocking delays
    playTone(condition);

    // 6. LCD
    updateLCD(bpm, condition);

    // 7. Serial
    Serial.print("RAW: ");
    Serial.print(raw);
    Serial.print("  |  BPM: ");
    Serial.print(bpm);
    Serial.print("  |  ");
    Serial.println(condition);
  }
}
