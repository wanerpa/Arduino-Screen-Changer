#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUTTON_PIN 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int currentScreen = 0;
bool lastButtonState = HIGH;
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED display not found");
    while (true) {
      delay(1000);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  showScreen();
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (
    lastButtonState == HIGH &&
    buttonState == LOW &&
    millis() - lastPressTime > debounceDelay
  ) {
    currentScreen = (currentScreen + 1) % 3;
    lastPressTime = millis();
    showScreen();
  }

  lastButtonState = buttonState;
}

void showScreen() {
  display.clearDisplay();

  switch (currentScreen) {
    case 0:
      showHomeScreen();
      break;

    case 1:
      showStatusScreen();
      break;

    case 2:
      showSettingsScreen();
      break;
  }

  display.display();
}

void showHomeScreen() {
  display.setTextSize(2);
  display.setCursor(12, 8);
  display.println("WA NERPA");

  display.setTextSize(1);
  display.setCursor(18, 40);
  display.println("Screen Changer");
}

void showStatusScreen() {
  display.setTextSize(2);
  display.setCursor(22, 8);
  display.println("STATUS");

  display.setTextSize(1);
  display.setCursor(24, 40);
  display.println("System Online");
}

void showSettingsScreen() {
  display.setTextSize(2);
  display.setCursor(10, 8);
  display.println("SETTINGS");

  display.setTextSize(1);
  display.setCursor(12, 40);
  display.println("Press to restart");
