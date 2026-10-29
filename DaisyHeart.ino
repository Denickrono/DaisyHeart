
// --- Pin Definitions ---
const int DATA_PIN  = 0; // PB0 -> DS
const int CLOCK_PIN = 1; // PB1 -> SHCP
const int LATCH_PIN = 2; // PB2 -> STCP

const int BTN_MODE  = 3; // PB3 -> Cycle / Long Press
const int BTN_SPEED = 4; // PB4 -> Speed Control

// --- Animation States ---
// 0=Off, 1=Rotate, 2=Fill, 3=Beat, 4=Sweep, 5=PingPong, 6=Sparkle, 7=Always ON
int currentAnim = 0; 
const int MAX_ANIM = 6; // 6 standard animations (1 through 6)

// --- Speed Control ---
int speedSetting = 1; // 0=Slow, 1=Normal, 2=Fast
unsigned long animDelay = 80; // Time between frames

// --- Timing & Variables ---
unsigned long lastUpdate = 0;
int animStep = 0;
bool draining = false;

// --- Button Timing (Long Press) ---
unsigned long btn1PressTime = 0;
bool btn1IsPressed = false;
bool longPressHandled = false;
const unsigned long LONG_PRESS_TIME = 800; // 0.8 seconds

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_SPEED, INPUT_PULLUP);
  
  writeLEDs(0x0000); // All off
}

void loop() {
  checkModeButton();
  checkSpeedButton();
  runAnimation();
}

// --- Mode Button (P3) ---
void checkModeButton() {
  unsigned long currentTime = millis();
  int state = digitalRead(BTN_MODE);
  
  if (state == LOW) {
    if (!btn1IsPressed) {
      btn1IsPressed = true;
      btn1PressTime = currentTime;
      longPressHandled = false;
    }
    
    // Check for long press
    if (!longPressHandled && (currentTime - btn1PressTime > LONG_PRESS_TIME)) {
      longPressHandled = true;
      currentAnim = 7; // Jump to ALWAYS ON
      writeLEDs(0xFFFF); // Turn all ON instantly
    }
  } 
  else {
    if (btn1IsPressed) {
      btn1IsPressed = false;
      // Short press: Cycle through animations 0 to 6
      if (!longPressHandled) {
        currentAnim++;
        if (currentAnim > MAX_ANIM) currentAnim = 0; 
        animStep = 0;
        draining = false;
        writeLEDs(0x0000);
      }
    }
  }
}

// --- Speed Button (P4) ---
void checkSpeedButton() {
  if (digitalRead(BTN_SPEED) == LOW) {
    speedSetting++;
    if (speedSetting > 2) speedSetting = 0; // Cycle 0, 1, 2
    
    // Set the delay based on speed
    if (speedSetting == 0) animDelay = 150; // Slow
    else if (speedSetting == 1) animDelay = 80; // Normal
    else if (speedSetting == 2) animDelay = 30; // Fast
    
    delay(250); // Debounce
  }
}

// --- Animation Engine ---
void runAnimation() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastUpdate > animDelay) {
    lastUpdate = currentTime;
    animStep++;
    
    switch (currentAnim) {
      case 1: // ROTATE
        writeLEDs(1 << (animStep % 16));
        break;
        
      case 2: // FILL AND DRAIN
        if (animStep > 16) { 
          draining = !draining; 
          animStep = draining ? 16 : 0; 
        }
        writeLEDs(draining ? ((1 << (16 - animStep)) - 1) : ((1 << animStep) - 1));
        break;

      case 3: // HEARTBEAT
        if (animStep % 25 == 1 || animStep % 25 == 5) writeLEDs(0xFFFF); // Thump
        if (animStep % 25 == 3 || animStep % 25 == 8) writeLEDs(0x0000); // Rest
        break;

      case 4: // SWEEP
        { 
          int pos = animStep % 30;
          if (pos > 15) pos = 30 - pos; 
          writeLEDs(1 << pos);
        }
        break;

      case 5: // PING PONG
        {
          int pos = animStep % 16;
          writeLEDs((1 << pos) | (1 << (15 - pos)));
        }
        break;

      case 6: // SPARKLE
        writeLEDs((1 << random(0, 16)) | (1 << random(0, 16)));
        break;

      case 7: // ALWAYS ON (Long Press)
        writeLEDs(0xFFFF);
        break;

      case 0: // OFF
      default:
        writeLEDs(0x0000);
        break;
    }
  }
}

// --- Shift Register Helper ---
void writeLEDs(uint16_t pattern) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, (uint8_t)(pattern >> 8));
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, (uint8_t)(pattern & 0xFF));
  digitalWrite(LATCH_PIN, HIGH);
}
