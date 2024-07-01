#ifndef _global_variable_h
#define _global_variable_h
#include <Arduino.h>
#include <EEPROM.h>
#include <SimpleKalmanFilter.h>
#include <LiquidCrystal_I2C.h>
#include <esp_task_wdt.h>
#include <PIDController.h>
PIDController pid;

SimpleKalmanFilter kalman(1, 1, 0.001);

TaskHandle_t ENCODER_TASK;
TaskHandle_t DISPLAY_TASK;
TaskHandle_t SENSOR_TASK;
TaskHandle_t CONTROL_TASK;

#define DT 16
#define CLK 17
#define SW 4
#define MENU1 "   HOME SCREEN  "
#define MENU2 "CALIBRATE SENSOR"
#define MENU3 "    P GAIN      "
#define MENU4 "    I GAIN      "
#define MENU5 "    D GAIN      "
#define MENU6 "  CONTROL MODE  "

#define PID_CONTROL 0
#define BANG_BANG_CONTROL 1

short SP = 200;
short last_SP = 200;
short PWM_RES = 12;
short MAX_PWM = 4095;

byte heating_flag = 0;

float temperature = 0;
float last_temperature = 0;

double TEMP;
double PWM;
double SP_proc;

double KP = 40;
double KI = 10;
double KD = 10;

byte layer = 0;
byte last_layer = 0;
byte menu_pos = 1;
byte last_menu_pos = 1;
byte control_param_change = 0;

short last_SP_before_fire = 0;

short offset = 0;
double skp = -2;
double ski = -2;
double skd = -2;
short last_offset = 0;
double last_skp = 0;
double last_ski = 0;
double last_skd = 0;

byte control_mode = 0;

unsigned long CLK_debounce_timer = 0;
unsigned long SW_debounce_timer = 0;

int fire_delay = 3000;
unsigned long fire_timer = 0;

void bigNumber(int val);
void printDigits(int digits, int col);

LiquidCrystal_I2C lcd(0x27, 16, 2);
// Define custom characters for digits 0-9
byte LT[8] =
    {
        B00111,
        B01111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
byte UB[8] =
    {
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000};
byte RT[8] =
    {
        B11100,
        B11110,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
byte LL[8] =
    {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B01111,
        B00111};
byte LB[8] =
    {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111,
        B11111};
byte LR[8] =
    {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11110,
        B11100};
byte MB[8] =
    {
        B11111,
        B11111,
        B11111,
        B00000,
        B00000,
        B00000,
        B11111,
        B11111};
byte block[8] =
    {
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111,
        B11111};
byte dot[8] = {
    B00000,
    B00000,
    B01110,
    B11111,
    B11111,
    B11111,
    B01110,
    B00000};

void bigNumber(int val)
{
    int col = 0;
    printDigits(val / 100, col);
    printDigits((val % 100) / 10, col + 4);
    printDigits((val % 100) % 10, col + 8);
}

void animation()
{
}

void custom0(int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(1);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
}
void custom1(int x)
{
    lcd.setCursor(x, 0);
    lcd.write(1);
    lcd.write(2);
    lcd.print(" ");
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(7);
    lcd.write(4);
}
void custom2(int x)
{
    lcd.setCursor(x, 0);
    lcd.write(6);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(4);
}
void custom3(int x)
{
    lcd.setCursor(x, 0);
    lcd.write(6);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(4);
    lcd.write(5);
}
void custom4(int x)
{
    lcd.setCursor(x, 0);
    lcd.write(3);
    lcd.write(4);
    lcd.write(7);
    lcd.setCursor(x, 1);
    lcd.print(" ");
    lcd.print(" ");
    lcd.write(7);
}
void custom5(int x)
{
    lcd.setCursor(x, 0);
    lcd.write(3);
    lcd.write(6);
    lcd.write(6);
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(4);
    lcd.write(5);
}
void custom6(int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(6);
    lcd.write(6);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
}
void custom7(int x)
{
    lcd.setCursor(x, 0);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.print(" ");
    lcd.print(" ");
    lcd.write(7);
}
void custom8(int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
}
void custom9(int x)
{
    lcd.setCursor(x, 0);
    lcd.write((byte)0);
    lcd.write(6);
    lcd.write(2);
    lcd.setCursor(x, 1);
    lcd.write(4);
    lcd.write(4);
    lcd.write(7);
}
void printDigits(int digits, int col)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    switch (digits)
    {
    case 0:
        custom0(col);
        break;
    case 1:
        custom1(col);
        break;
    case 2:
        custom2(col);
        break;
    case 3:
        custom3(col);
        break;
    case 4:
        custom4(col);
        break;
    case 5:
        custom5(col);
        break;
    case 6:
        custom6(col);
        break;
    case 7:
        custom7(col);
        break;
    case 8:
        custom8(col);
        break;
    case 9:
        custom9(col);
        break;
    }
}
#endif