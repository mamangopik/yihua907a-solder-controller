#include "global_variable.h"
void enc_read(void *param)
{
    pinMode(DT, INPUT_PULLUP);
    pinMode(CLK, INPUT_PULLUP);
    byte aState = 0;
    byte aLastState = 0;

    offset = EEPROM.readFloat(0);
    skp = (double)EEPROM.readFloat(8);
    ski = (double)EEPROM.readFloat(16);
    skd = (double)EEPROM.readFloat(24);
    control_mode = EEPROM.read(28);

    while (1)
    {
        if (digitalRead(SW) == 0)
        {
            if (millis() - SW_debounce_timer > 500)
            {
                if (layer == 0)
                {
                    layer = 1;
                }

                else if (layer == 1)
                {
                    if (menu_pos == 1)
                    {
                        layer = 0;
                        menu_pos = 2;
                    }
                    else
                    {
                        layer = 2;
                    }
                }
                else
                {
                    if (layer == 2 && menu_pos == 2)
                    {
                        layer = 1;
                        EEPROM.writeFloat(0, offset);
                        EEPROM.commit();
                    }
                    if (layer == 2 && menu_pos == 3)
                    {
                        layer = 1;
                        EEPROM.writeFloat(8, skp);
                        EEPROM.commit();
                        control_param_change = 1;
                    }
                    if (layer == 2 && menu_pos == 4)
                    {
                        layer = 1;
                        EEPROM.writeFloat(16, ski);
                        EEPROM.commit();
                        control_param_change = 1;
                    }
                    if (layer == 2 && menu_pos == 5)
                    {
                        layer = 1;
                        EEPROM.writeFloat(24, skd);
                        EEPROM.commit();
                        control_param_change = 1;
                    }
                    if (layer == 2 && menu_pos == 6)
                    {
                        layer = 1;
                        EEPROM.write(28, control_mode);
                        EEPROM.commit();
                        control_param_change = 1;
                    }
                }

                SW_debounce_timer = millis();
            }
        }

        aState = digitalRead(CLK);
        if (aState != aLastState)
        {
            // if at home screen
            if (layer == 0)
            {
                if (digitalRead(DT) != aState)
                {
                    SP++;
                }
                else
                {
                    if (SP > 100)
                    {
                        SP--;
                    }
                }
                if (SP >= 550)
                {
                    SP = 550;
                }
            }
            if (layer == 1)
            {
                if (digitalRead(DT) != aState)
                {
                    menu_pos++;
                }
                else
                {
                    menu_pos--;
                }
                if (menu_pos > 6)
                {
                    menu_pos = 1;
                }
                if (menu_pos < 1)
                {
                    menu_pos = 6;
                }
            }

            if (layer == 2 && menu_pos == 2)
            {
                if (digitalRead(DT) != aState)
                {
                    if (offset < 255)
                    {
                        offset++;
                    }
                }
                else
                {
                    offset--;
                }
            }

            if (layer == 2 && menu_pos == 3)
            {
                if (digitalRead(DT) != aState)
                {
                    skp += 0.1;
                    if (skp > 50)
                        skp = 0;
                }
                else
                {
                    skp -= 0.1;
                    if (skp < 0)
                        skp = 50;
                }
            }

            if (layer == 2 && menu_pos == 4)
            {
                if (digitalRead(DT) != aState)
                {
                    ski += 0.1;
                    if (ski > 50)
                        ski = 0;
                }
                else
                {
                    ski -= 0.1;
                    if (ski < 0)
                        ski = 50;
                }
            }

            if (layer == 2 && menu_pos == 5)
            {
                if (digitalRead(DT) != aState)
                {
                    skd += 0.1;
                    if (skd > 50)
                        skd = 0;
                }
                else
                {
                    skd -= 0.1;
                    if (skd < 0)
                        skd = 50;
                }
            }
            if (layer == 2 && menu_pos == 6)
            {
                if (digitalRead(DT) != aState)
                {
                    control_mode += 1;
                    if (control_mode > 1)
                        control_mode = 0;
                }
                else
                {
                    control_mode -= 1;
                    if (control_mode < 0)
                        control_mode = 1;
                }
            }
        }
        aLastState = aState;

        if (millis() - fire_timer > fire_delay)
        {
            if (SP != last_SP_before_fire)
                last_SP_before_fire = SP;
            fire_timer = millis();
        }
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
}