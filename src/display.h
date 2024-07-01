#include "global_variable.h"
void display_task(void *param)
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.createChar(0, LT);
    lcd.createChar(1, UB);
    lcd.createChar(2, RT);
    lcd.createChar(3, LL);
    lcd.createChar(4, LB);
    lcd.createChar(5, LR);
    lcd.createChar(6, MB);
    lcd.createChar(7, block);
    vTaskDelay(500 / portTICK_PERIOD_MS);

    byte toggle_heat_blink = 0;

    while (1)
    {
        if (SP != last_SP)
        {
            lcd.clear();
            last_SP = SP;
            fire_timer = millis();
        }
        if (menu_pos != last_menu_pos)
        {
            lcd.clear();
            last_menu_pos = menu_pos;
        }
        if (layer != last_layer)
        {
            lcd.clear();
            last_layer = layer;
        }
        if (offset != last_offset)
        {
            lcd.clear();
            last_offset = offset;
        }

        if (layer == 0)
        {
            lcd.setCursor(11, 0);
            lcd.print("C");
            bigNumber(SP);
            lcd.setCursor(13, 1);
            lcd.print(temperature, 0);
            if (temperature < 100)
                lcd.print(' ');
            if (heating_flag == 1 && SP == last_SP_before_fire)
            {
                lcd.setCursor(13, 0);
                lcd.print(">");
            }
            else
            {
                lcd.setCursor(15, 0);
                lcd.print(" ");
            }
        }

        if (layer == 1)
        {
            lcd.setCursor(0, 0);
            switch (menu_pos)
            {
            case 1:
                lcd.print(MENU1);
                break;
            case 2:
                lcd.print(MENU2);
                break;
            case 3:
                lcd.print(MENU3);
                break;
            case 4:
                lcd.print(MENU4);
                break;
            case 5:
                lcd.print(MENU5);
                break;
            case 6:
                lcd.print(MENU6);
                break;
            }
        }

        if (layer == 2 && menu_pos == 2)
        {
            lcd.setCursor(0, 0);
            lcd.print(MENU2);
            lcd.setCursor(0, 1);
            lcd.print("OFFSET:");
            lcd.setCursor(8, 1);
            lcd.print(offset);
        }
        if (layer == 2 && menu_pos == 3)
        {
            lcd.setCursor(0, 0);
            lcd.print(MENU3);
            lcd.setCursor(0, 1);
            lcd.print("GAIN:");
            lcd.setCursor(8, 1);
            lcd.print(skp);
        }
        if (layer == 2 && menu_pos == 4)
        {
            lcd.setCursor(0, 0);
            lcd.print(MENU4);
            lcd.setCursor(0, 1);
            lcd.print("GAIN:");
            lcd.setCursor(8, 1);
            lcd.print(ski);
        }
        if (layer == 2 && menu_pos == 5)
        {
            lcd.setCursor(0, 0);
            lcd.print(MENU5);
            lcd.setCursor(0, 1);
            lcd.print("GAIN:");
            lcd.setCursor(8, 1);
            lcd.print(skd);
        }
        if (layer == 2 && menu_pos == 6)
        {
            lcd.setCursor(0, 0);
            lcd.print(MENU6);
            lcd.setCursor(0, 1);
            if (control_mode == 0)
                lcd.print("       PID      ");
            else
            {
                lcd.setCursor(0, 1);
                lcd.print("    BANG-BANG   ");
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}