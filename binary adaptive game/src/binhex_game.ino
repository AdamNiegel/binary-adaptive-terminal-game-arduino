
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// BUTTONS
const int bit0Btn = 6;
const int bit1Btn = 7;
const int enterBtn = 8;
const int nextBtn = 9;

// GAME STATE
String currentBin = "";
String targetBin = "";
String targetHex = "";

// STATS
int score = 0;
int streak = 0;
int wrongStreak = 0;
int difficulty = 1;

// CONTROL
bool gameActive = true;

// STATES
bool last0 = HIGH;
bool last1 = HIGH;
bool lastEnter = HIGH;
bool lastNext = HIGH;

// ---------------- HEX CONVERTER ----------------
String binToHex(String bin) {
  String hex = "";

  while (bin.length() % 4 != 0) {
    bin = "0" + bin;
  }

  for (int i = 0; i < bin.length(); i += 4) {
    String chunk = bin.substring(i, i + 4);
    int val = 0;

    for (int j = 0; j < 4; j++) {
      if (chunk[j] == '1') val += (1 << (3 - j));
    }

    if (val < 10) hex += String(val);
    else hex += char('A' + (val - 10));
  }

  return hex;
}

// ---------------- DIFFICULTY UPDATE ----------------
void updateDifficulty(bool correct) {

  if (correct) {
    streak++;
    wrongStreak = 0;

    if (streak >= 3 && difficulty < 4) {
      difficulty++;
      streak = 0;
    }

  } else {
    wrongStreak++;
    streak = 0;

    if (wrongStreak >= 2 && difficulty > 1) {
      difficulty--;
      wrongStreak = 0;
    }
  }
}

// ---------------- NEW CHALLENGE ----------------
void newChallenge() {

  int minVal, maxVal;

  if (difficulty == 1) { minVal = 0; maxVal = 63; }
  else if (difficulty == 2) { minVal = 64; maxVal = 127; }
  else if (difficulty == 3) { minVal = 128; maxVal = 191; }
  else { minVal = 192; maxVal = 255; }

  int value = random(minVal, maxVal + 1);

  targetHex = String(value, HEX);
  targetHex.toUpperCase();

  targetBin = "";

  for (int i = 7; i >= 0; i--) {
    targetBin += bitRead(value, i);
  }

  currentBin = "";

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(difficulty);
  lcd.print(" HEX:");
  lcd.print(targetHex);
}

// ---------------- CHECK ANSWER ----------------
void checkAnswer() {

  bool correct = (currentBin == targetBin);

  updateDifficulty(correct);

  if (correct) {
    score++;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CORRECT!");
    lcd.setCursor(0, 1);
    lcd.print("Score:");
    lcd.print(score);

    delay(1200);
    newChallenge();

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WRONG!");
    lcd.setCursor(0, 1);
    lcd.print("Lvl:");
    lcd.print(difficulty);

    delay(1200);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("HEX:");
    lcd.print(targetHex);
  }
}

// ---------------- INPUT DISPLAY ----------------
void showInput() {
  lcd.setCursor(0, 1);
  lcd.print("BIN:");
  lcd.print(currentBin);
  lcd.print("   ");
}

// ---------------- EXIT GAME ----------------
void exitGame() {
  gameActive = false;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM OFF");
  lcd.setCursor(0, 1);
  lcd.print("Reset to start");
}

// ---------------- SETUP ----------------
void setup() {
  pinMode(bit0Btn, INPUT_PULLUP);
  pinMode(bit1Btn, INPUT_PULLUP);
  pinMode(enterBtn, INPUT_PULLUP);
  pinMode(nextBtn, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(0));

  lcd.setCursor(0, 0);
  lcd.print("Adaptive Game");
  delay(1500);

  newChallenge();
}

// ---------------- LOOP ----------------
void loop() {

  if (!gameActive) return;

  // ================= EXIT CONDITION =================
  if (digitalRead(bit0Btn) == LOW &&
      digitalRead(bit1Btn) == LOW &&
      digitalRead(enterBtn) == LOW &&
      digitalRead(nextBtn) == LOW) {

    exitGame();

    while (true) {
      // freeze system until reset
    }
  }

  // ================= BIT 0 =================
  if (digitalRead(bit0Btn) == LOW && last0 == HIGH) {
    currentBin += "0";
    showInput();
  }
  last0 = digitalRead(bit0Btn);

  // ================= BIT 1 =================
  if (digitalRead(bit1Btn) == LOW && last1 == HIGH) {
    currentBin += "1";
    showInput();
  }
  last1 = digitalRead(bit1Btn);

  // ================= ENTER =================
  if (digitalRead(enterBtn) == LOW && lastEnter == HIGH) {
    checkAnswer();
  }
  lastEnter = digitalRead(enterBtn);

  // ================= NEXT =================
  if (digitalRead(nextBtn) == LOW && lastNext == HIGH) {
    newChallenge();
  }
  lastNext = digitalRead(nextBtn);
}