#include <Keyboard.h> //library for send signal to PC via USB

#define COLS_SIZE 10  //number of columns
#define ROWS_SIZE 4   //number of rows
#define MIN_MS 20     //minimum time in ms after which button can be active again
#define REPEAT_MS 600 //minimum time in ms after which button is automticly re-active
#define RELAY_TIME 1  //time duration of key press

//https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
#define K_CTRL  (uint8_t)128
#define K_SHFT  (uint8_t)129
#define K_ALT   (uint8_t)130
#define K_SUPR  (uint8_t)131
#define K_BACK  (uint8_t)178
#define K_RET   (uint8_t)176
#define K_ESC   (uint8_t)177
#define K_TAB   (uint8_t)179
#define K_DEL   (uint8_t)212

//arrows
#define K_UP    (uint8_t)218
#define K_DN    (uint8_t)217
#define K_LF    (uint8_t)216
#define K_RG    (uint8_t)215

//page up/down
#define K_PGUP    (uint8_t)211
#define K_PGDN    (uint8_t)214

//home/end
#define K_HOME    (uint8_t)210
#define K_END    (uint8_t)213

//mod key
#define K_MOD1 (uint8_t)1

const byte COLS[] = {3, 4, 5, 6, 7, 8, 10, 16, 14, 15};   //columns pins
const byte ROWS[] = {A0, A1, A2, A3};                     //rows pins

//keyboard layout - first one is default, next one is applied when K_MOD1 is pressed
uint8_t key_matrix[2][40] = {
{ K_TAB,  'q',    'w',    'f',    'p',    'g',    'j',    'l',    'u',    'y',
  K_BACK, 'a',    'r',    's',    't',    'd',    'h',    'n',    'e',    'i',
  K_SHFT, 'z',    'x',    'c',    'v',    'b',    'k',    'm',    ',',    '.', 
  K_CTRL, K_SUPR, K_ALT,  '[',    ']',    ' ',    K_MOD1,                            '/',    'o',    ';'},
                          
{ '`',    '1',    '2',    '3',    '=',    'g',    '\'',    K_HOME,  K_PGDN,  K_PGUP,
  K_ESC,  '4',    '5',    '6',    '-',    'd',    K_DEL,  K_LF,    K_DN,    K_UP,
  K_SHFT, '7',    '8',    '9',    '0',    'b',    'k',    'm',     ',',     '.', 
  K_CTRL, K_SUPR, K_ALT,  '[',    ']',    K_RET,  K_MOD1,                            '\\',    K_RG,    K_END},

};

uint8_t type_matrix[2][40] = {
{ 1,    0,      0,        0,      0,      0,       0,      0,      0,       0,
  0,    0,      0,        0,      0,      0,       0,      0,      0,       0,
  1,    0,      0,        0,      0,      0,       0,      0,      0,       0,
  1,    1,      1,        0,      0,      0,       2,                             0,      0,       0},

{ 1,    0,      0,        0,      0,      0,       0,      0,      0,       0,
  0,    0,      0,        0,      0,      0,       0,      0,      0,       0,
  1,    0,      0,        0,      0,      0,       0,      0,      0,       0,
  1,    1,      1,        0,      0,      0,       2,                             0,      0,       0},
};
//type of key
//0 - normal keys
//1 - special, often hold down keys like control, shift, etc
//2 - macro keys (they change layout if pressed)

uint8_t state[40] = {0};            //0 - non active, 1 - pushed, 2 - active
unsigned long saturation[40] = {0}; //time at the moment when the button is pressed

uint8_t pressed;                    //state flag in key_data_upate function
uint8_t modifier = 0;               //flag which point to current layout

void key_data_update(uint8_t idx, uint8_t V_state)
{
  pressed = 0;
  if(V_state == LOW)
  {
    if (millis() - saturation[idx] > MIN_MS)
    {
      if(state[idx] == 0)
      {
        state[idx] = 1;
        pressed = 1;
      }
      else if (state[idx] == 1 && (millis() - saturation[idx] > REPEAT_MS))
      {
          pressed = 1;
          state[idx] = 2;
      }
      else if (state[idx]== 2){pressed = 1;}
    }
  }
  else
  {
    if(type_matrix[modifier][idx] == 1 && state[idx]) Keyboard.release(key_matrix[modifier][idx]);
    if(type_matrix[modifier][idx] == 2 && state[idx]) modifier = 0;
    state[idx] = 0;
    saturation[idx] = 0;
  }
  
  if(pressed)
  {
    saturation[idx] = millis();
    if(type_matrix[modifier][idx] == 0)
    {
      Keyboard.press(key_matrix[modifier][idx]);
      delay(RELAY_TIME);
      Keyboard.release(key_matrix[modifier][idx]);
    }
    if(type_matrix[modifier][idx] == 1) { Keyboard.press(key_matrix[modifier][idx]); }
    if(type_matrix[modifier][idx] == 2) {modifier = key_matrix[modifier][idx];}
  }
}

void setup() {
  Keyboard.begin();
  for (int i = 0; i < COLS_SIZE; ++i) pinMode(COLS[i], INPUT_PULLUP);
  for (int i = 0; i < ROWS_SIZE; ++i) pinMode(ROWS[i], OUTPUT);
}

void loop()
{
  //all delays in loops are required to stabilize voltage in circuit
  for (int i = 0; i < ROWS_SIZE; ++i)
  {
    digitalWrite(ROWS[i], LOW);
    delay(1);
    for (int g = 0; g < COLS_SIZE; ++g)
    {
      pinMode(COLS[g], INPUT_PULLUP);
      key_data_update(g + COLS_SIZE * i, digitalRead(COLS[g]));
      digitalWrite(COLS[i], HIGH);
      delay(1);
    }
    digitalWrite(ROWS[i], HIGH);
    delay(1);
  }
}
