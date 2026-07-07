#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 11, 4, 5, 6, 7);
String inputText = "";

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Enter Text:");
  Serial.println("Type text & press Enter:");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();

    // Accept A-Z and a-z
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      inputText += c;
      lcd.setCursor(0, 1);
      lcd.print(inputText);
    }

    if (c == '\n') {
      String encrypted = "";
      for (int i = 0; i < inputText.length(); i++) {
        char ch = inputText[i];
        if (ch >= 'A' && ch <= 'Z') {
          encrypted += char((ch - 'A' + 3) % 26 + 'A'); // uppercase
        } else {
          encrypted += char((ch - 'a' + 3) % 26 + 'a'); // lowercase
        }
      }

      // Show Encrypted
      lcd.clear();
      lcd.print("Enc:" + encrypted);
      Serial.println("Encrypted: " + encrypted);
      delay(3000);

      // Decrypt
      String decrypted = "";
      for (int i = 0; i < encrypted.length(); i++) {
        char ch = encrypted[i];
        if (ch >= 'A' && ch <= 'Z') {
          decrypted += char((ch - 'A' + 23) % 26 + 'A'); // uppercase
        } else {
          decrypted += char((ch - 'a' + 23) % 26 + 'a'); // lowercase
        }
      }

      // Show Decrypted
      lcd.clear();
      lcd.print("Dec:" + decrypted);
      Serial.println("Decrypted: " + decrypted);
      delay(3000);

      // Reset
      inputText = "";
      lcd.clear();
      lcd.print("Enter Text:");
    }
  }
}
