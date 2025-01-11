/* 
 *  Name: ScorePod
 *  Desc: Small device intended to track and display the set, score and winner of a volleyball game.
 *  Auth: Smith Hayward
 *  Vers: 1.0
 *  Date: 1/10/2025
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define custom I2C pins
#define I2C_SDA 23  // Custom SDA pin
#define I2C_SCL 22 // Custom SCL pin

// Button pins
#define HOME_PIN 14
#define AWAY_PIN 12
#define SET_PIN 13

// LED PINS
#define RED_LED 33
#define GREEN_LED 32
#define BLUE_LED 25

// APP CONSTANTS
#define SPLASH_DURATION 5000
#define LAST_SET 3
#define WIN_SCORE 25
#define WIN_SCORE_LAST_SET 15
#define WIN_BY 2
//#define TEAM_NAME "OMNI"

#define APP_NAME "ScorePod"
#define APP_VERSION "v1.0"



// Create an instance of the display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// '0', 16x24px
const unsigned char epd_bitmap_0 [] PROGMEM = {
  0x3f, 0xf8, 0x9f, 0xf2, 0xcf, 0xe6, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xc0, 0x06, 0x80, 0x02, 0x00, 0x00, 0x80, 0x02, 0xc0, 0x06, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xcf, 0xe6, 0x9f, 0xf2, 0x3f, 0xf8, 0x00, 0x00
};
// '1', 16x24px
const unsigned char epd_bitmap_1 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x02, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
};
// '2', 16x24px
const unsigned char epd_bitmap_2 [] PROGMEM = {
  0x3f, 0xf8, 0x1f, 0xf2, 0x0f, 0xe6, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x06, 0x1f, 0xf2, 0x3f, 0xf8, 0x9f, 0xf0, 0xc0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 
  0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0xcf, 0xe0, 0x9f, 0xf0, 0x3f, 0xf8, 0x00, 0x00
};
// '3', 16x24px
const unsigned char epd_bitmap_3 [] PROGMEM = {
  0x3f, 0xf8, 0x1f, 0xf2, 0x0f, 0xe6, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x06, 0x1f, 0xf2, 0x3f, 0xf8, 0x1f, 0xf2, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x0f, 0xe6, 0x1f, 0xf2, 0x3f, 0xf8, 0x00, 0x00
};
// '4', 16x24px
const unsigned char epd_bitmap_4 [] PROGMEM = {
  0x00, 0x00, 0x80, 0x02, 0xc0, 0x06, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xc0, 0x06, 0x9f, 0xf2, 0x3f, 0xf8, 0x1f, 0xf2, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
};
// '5', 16x24px
const unsigned char epd_bitmap_5 [] PROGMEM = {
  0x3f, 0xf8, 0x9f, 0xf0, 0xcf, 0xe0, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 
  0xe0, 0x00, 0xc0, 0x00, 0x9f, 0xf0, 0x3f, 0xf8, 0x1f, 0xf2, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x0f, 0xe6, 0x1f, 0xf2, 0x3f, 0xf8, 0x00, 0x00
};
// '6', 16x24px
const unsigned char epd_bitmap_6 [] PROGMEM = {
  0x3f, 0xf8, 0x9f, 0xf0, 0xcf, 0xe0, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 0xe0, 0x00, 
  0xe0, 0x00, 0xc0, 0x00, 0x9f, 0xf0, 0x3f, 0xf8, 0x9f, 0xf2, 0xc0, 0x06, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xcf, 0xe6, 0x9f, 0xf2, 0x3f, 0xf8, 0x00, 0x00
};
// '7', 16x24px
const unsigned char epd_bitmap_7 [] PROGMEM = {
  0x3f, 0xf8, 0x1f, 0xf2, 0x0f, 0xe6, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
};
// '8', 16x24px
const unsigned char epd_bitmap_8 [] PROGMEM = {
  0x3f, 0xf8, 0x9f, 0xf2, 0xcf, 0xe6, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xc0, 0x06, 0x9f, 0xf2, 0x3f, 0xf8, 0x9f, 0xf2, 0xc0, 0x06, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xcf, 0xe6, 0x9f, 0xf2, 0x3f, 0xf8, 0x00, 0x00
};
// '9', 16x24px
const unsigned char epd_bitmap_9 [] PROGMEM = {
  0x3f, 0xf8, 0x9f, 0xf2, 0xcf, 0xe6, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 0xe0, 0x0e, 
  0xe0, 0x0e, 0xc0, 0x06, 0x9f, 0xf2, 0x3f, 0xf8, 0x1f, 0xf2, 0x00, 0x06, 0x00, 0x0e, 0x00, 0x0e, 
  0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x0f, 0xe6, 0x1f, 0xf2, 0x3f, 0xf8, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 640)
const int epd_bitmap_allArray_LEN = 10;
const unsigned char* epd_bitmap_allArray[10] = {
  epd_bitmap_0,
  epd_bitmap_1,
  epd_bitmap_2,
  epd_bitmap_3,
  epd_bitmap_4,
  epd_bitmap_5,
  epd_bitmap_6,
  epd_bitmap_7,
  epd_bitmap_8,
  epd_bitmap_9
};

int homeScore = 0;
int awayScore = 0;
int homeSets = 0;
int awaySets = 0;
int currentSet = 1;
bool scoreChanged = false;

// Variables to track button presses
// int homeCount = 0;
// int awayCount = 0;
int awayState = 0;
int homeState = 0;
int setState = 0;
String userMsg = "";
String appState = "";


// Variables for timing
unsigned long lastHomePressTime = 0;
unsigned long lastAwayPressTime = 0;
unsigned long homePressTime = 0;
unsigned long awayPressTime = 0;
unsigned long setPressTime = 0;
unsigned long homePressDur = 0;
unsigned long awayPressDur = 0;
unsigned long setPressDur = 0;


// const unsigned long debounceDelay = 1000; // 1 second delay
// const unsigned long doubleClickDelay = 300; // 300ms delay

void setup() {

appState = "STARTING";

    // Initialize serial communication for debugging
    Serial.begin(115200);
    Serial.println("App State: " + appState);

// Configure button pins as input with pull-up resistors
  pinMode(HOME_PIN, INPUT_PULLUP);
  pinMode(AWAY_PIN, INPUT_PULLUP);
  pinMode(SET_PIN, INPUT_PULLUP);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

// CHECK THAT ALL BUTTONS ARE RELEASED
// TODO?


    // Start I2C on custom pins
    Wire.begin(I2C_SDA, I2C_SCL);

    // Initialize the SSD1306 display
    if (!display.begin(SSD1306_PAGEADDR, 0x3C)) { // Default I2C address is 0x3C
        Serial.println("SSD1306 initialization failed!");
        while (true); // Halt the program
    }

    // SPLASH SCREEN
    drawSplashScreen();


    display.clearDisplay();

    drawLabels();
    
    drawScore(homeScore, awayScore);
    drawSetNum();
    display.display();

    appState = "SCORING";

}

void loop() {                                                               // MAIN PROGRAM LOOP



// Home Button
    if (digitalRead(HOME_PIN) == LOW) { // Button is pressed (LOW because of INPUT_PULLUP)
        
        if (homeState == 0) {   // if the button is pressed but was previously NOT pressed change state & set timing of press
          homeState = 1;
          Serial.println("Home Pressed.");
          homePressTime = millis();
          homePressDur = 0;
        }  else {                        // if the button was already pressed, then recalc how long it's been down

          homePressDur = millis() - homePressTime;
          Serial.print("Home Press Duration: ");
          Serial.println(homePressDur);
            
          // INSERT FUNCTIONALITY BASED ON A LONG HOLD UNTIL A THRESHOLD

          if (homePressDur > 1400 && appState == "SCORING") {
            homeState = 0;
            homePressDur = 0;
            resetScore();
           
          }
        }
    }

    if (digitalRead(HOME_PIN) == HIGH) {
        if (homeState == 1) {   // if the button is released but was previously pressed change state but don't reset duration
          homeState = 0;

          // DO THE THINGS DEPENDING ON DURATION THEN RESET DURATION

          if (homePressDur > 30 && homePressDur < 500 && appState == "SCORING") {  // SINGLE SHORT PRESS 
            homeScore++;
            scoreChanged = true;
          }
          else if ( homePressDur > 500 && appState == "SCORING" ) {  // Medium Press
            homeScore--;
            scoreChanged = true;
          }

          homePressDur = 0;
        }
        else {                        // if the button was already up, then do nothing

        }
    }


// AWAY Button
    if (digitalRead(AWAY_PIN) == LOW) { // Button is pressed (LOW because of INPUT_PULLUP)
        
        if (awayState == 0) {   // if the button is pressed but was previously NOT pressed change state & set timing of press
          awayState = 1;
          Serial.println("away Pressed.");
          awayPressTime = millis();
          awayPressDur = 0;
        }  else {                        // if the button was already pressed, then recalc how long it's been down

          awayPressDur = millis() - awayPressTime;
          Serial.print("away Press Duration: ");
          Serial.println(awayPressDur);

            // INSERT FUNCTIONALITY BASED ON A LONG HOLD UNTIL A THRESHOLD
            // NONE PLANNED AT THIS TIME
          }
    }
    

    if (digitalRead(AWAY_PIN) == HIGH) {
        if (awayState == 1) {   // if the button is released but was previously pressed change state but don't reset duration
          awayState = 0;

          // DO THE THINGS DEPENDING ON DURATION THEN RESET DURATION

          if (awayPressDur > 30 && awayPressDur < 500 && appState == "SCORING") {  // SINGLE SHORT PRESS 
            awayScore++;
            scoreChanged = true;
          }
          else if ( awayPressDur > 500 && appState == "SCORING" ) {  // Medium Press
            awayScore--;
            scoreChanged = true;
          }

          homePressDur = 0;

        } 
        else {                        // if the button was already up, then do nothing

        }
    }

// SET BUTTON

    if (digitalRead(SET_PIN) == LOW) { // Button is pressed (LOW because of INPUT_PULLUP)
        
        if (setState == 0) {   // if the button is pressed but was previously NOT pressed change state & set timing of press
          setState = 1;
          Serial.println("Set Pressed.");
          setPressTime = millis();
          setPressDur = 0;
        }  else {                        // if the button was already pressed, then recalc how long it's been down

          setPressDur = millis() - setPressTime;
          Serial.print("Set Press Duration: ");
          Serial.println(setPressDur);
            // INSERT FUNCTIONALITY BASED ON A LONG HOLD UNTIL A THRESHOLD
            // NONE PLANNED AT THIS TIME
        }
    }

    if (digitalRead(SET_PIN) == HIGH) {
        if (setState == 1) {   // if the button is released but was previously pressed change state but don't reset duration
          setState = 0;

          // DO THE THINGS DEPENDING ON DURATION THEN RESET DURATION

          if (setPressDur > 250 && setPressDur < 1500 && appState == "SCORING") {  // SINGLE MEDIUM PRESS 
            currentSet++;
            scoreChanged = true;
          }
          else if ( setPressDur > 1500 && setPressDur < 3000 && appState == "SCORING" ) {  // LONG Press
            currentSet = 1;
            scoreChanged = true;
            // resetScore();
          }
          else if (setPressDur > 30 && setPressDur < 200 && appState == "WINNER") {
            // GAME IS OVER AND PRESSING SET, INCREASES SET AND RESETS THE SCORE PUTTING THE SCORE INTO MEMORY
            scoreChanged = true;
            currentSet++;
            resetScore();
            appState = "SCORING";
          }

          homePressDur = 0;
        }
        else {                        // if the button was already up, then do nothing

        }
    }

    if (scoreChanged) { 

      scoreChanged = false;

      clampScore();

      int winner = getSetWinner();

      // DETERMINE SET & GAME WINNER
      // GAME WIN REQUIRES (MAX_SETS / 2) + 1


      renderScreen();

    }

delay(10);

  }


void drawSplashScreen(void){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(21, 13);
  display.println("SmithDoesStuff");
  display.setTextSize(2);
  display.setCursor(16, 29);
  display.println(APP_NAME);
  display.setTextSize(1);
  display.setCursor(46, 48);
  display.println(APP_VERSION);
  display.display();
  delay(SPLASH_DURATION);
}
    
void renderScreen(void){

  display.clearDisplay();
  drawLabels();
  drawSetNum();
  drawScore(homeScore, awayScore);
  drawSetCount();
  drawUserMsg();
  display.display();

}


void drawSetCount(void){


}

void clampScore(void){
  if (homeScore < 0 || homeScore > 99) {
        homeScore = 0;
      }

      if (awayScore < 0 || awayScore > 99) {
        awayScore = 0;
      }
}
void drawLabels(void){
  display.setTextSize(1);
  display.setCursor(8, 4);
  display.println("OMNI    SET    OPPO");
}

void drawUserMsg(void) {
  if (userMsg != "") {
      display.setTextSize(1);
      display.setCursor(8, 56);
      display.println(userMsg);

  }

}

void drawSetNum(void){
  display.setTextSize(1);
  display.setCursor(62,18);
  display.print(currentSet);

}

#define x_home_dec 6
#define x_home_one 24
#define x_away_dec 88
#define x_away_one 106
#define y_all 16

void drawScore(int home, int away) {
  
  int home_dec = home / 10;
  int home_one = home % 10;
  int away_dec = away / 10;
  int away_one = away % 10;

  if (home_dec > 0) { display.drawBitmap( x_home_dec, y_all, epd_bitmap_allArray[home_dec], 16, 24, 1); }
  display.drawBitmap( x_home_one, y_all, epd_bitmap_allArray[home_one], 16, 24, 1);
  if (away_dec > 0) { display.drawBitmap( x_away_dec, y_all, epd_bitmap_allArray[away_dec], 16, 24, 1); }
  display.drawBitmap( x_away_one, y_all, epd_bitmap_allArray[away_one], 16, 24, 1);

}

int getSetWinner(void){

  int winner = 0;

  if (currentSet < LAST_SET) {
  
    if (homeScore - awayScore >= WIN_BY && homeScore >= WIN_SCORE) {
        winner = 1;
    } 
    if (awayScore - homeScore >= WIN_BY && awayScore >= WIN_SCORE) {
          winner = 2;
    }

  } else if (currentSet == LAST_SET) {
      
      if (homeScore - awayScore >= WIN_BY && homeScore >= WIN_SCORE_LAST_SET) {
          winner = 1;
      } 
      if (awayScore - homeScore >= WIN_BY && awayScore >= WIN_SCORE_LAST_SET) {
            winner = 2;
      }
}
  return winner;
}

void resetScore(void){
  homeScore=0;
  awayScore=0;
  scoreChanged=1;
  userMsg="";
}
