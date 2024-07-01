#include "global_variable.h"
void debug(void *param)
{
    Serial.begin(115200);
    while (1)
    {
        Serial.print('$');
        Serial.print(SP);
        Serial.print(' ');
        Serial.print(TEMP);
        Serial.print(' ');
        Serial.print(PWM);
        Serial.println(';');
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}