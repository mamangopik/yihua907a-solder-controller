#include "global_variable.h"
#include "navigation.h"
#include "display.h"
#include "serial_debug.h"

void control(void *param)
{
	unsigned long cnt = 0;
	pinMode(35, INPUT);
	analogReadResolution(12);
	while (skp < -1 || ski < -1 || skd < -1)
	{
		vTaskDelay(1 / portTICK_PERIOD_MS);
	}
INIT_CONTROL:
	if (control_mode == PID_CONTROL)
	{
		ledcSetup(0, 10000, PWM_RES); // Channel 0, 8-bit PWM
		ledcAttachPin(25, 0);		  // Attach PWM to pin
		TEMP = temperature;
		SP_proc = (double)SP;
		KP = skp;
		KI = ski;
		KD = skd;
		pid.begin();		  // initialize the PID instance
		pid.tune(KP, KI, KD); // Tune the PID, arguments: kP, kI, kD
		pid.limit(0, MAX_PWM);
	}
	else
	{
		pinMode(25, OUTPUT);
		SP_proc = (double)SP;
		TEMP = temperature;
	}
	while (1)
	{
		float voltage = analogReadMilliVolts(35);
		voltage = voltage / 100;
		temperature = kalman.updateEstimate((voltage * 25.0)) + offset;
		// temperature = voltage * 25.0;
		SP_proc = (double)SP;
		TEMP = temperature;
		cnt++;

		if (control_param_change == 1)
		{
			if (control_mode == PID_CONTROL)
			{
				ledcWrite(0, MAX_PWM - 0);
			}
			else
			{
				digitalWrite(25, 1); // turn off the mosfet
			}
			control_param_change = 0;
			goto INIT_CONTROL;
		}

		if (control_mode == PID_CONTROL)
		{
			pid.setpoint(SP_proc); // The "goal" the PID controller tries to "reach"
			PWM = pid.compute(TEMP);
			ledcWrite(0, MAX_PWM - PWM);
		}
		else
		{
			// if temperature below the set point
			if (TEMP >= SP_proc)
			{
				digitalWrite(25, 1); // turn on the mosfet
			}
			else
			{
				digitalWrite(25, 0); // turn off the mosfet
			}
		}

		if (TEMP < SP)
			heating_flag = 1;
		else
			heating_flag = 0;
		vTaskDelay(5 / portTICK_PERIOD_MS);
	}
}
void setup()
{
	esp_task_wdt_init(0xffffffff, false);
	EEPROM.begin(512);
	pinMode(SW, INPUT_PULLUP);

	xTaskCreatePinnedToCore(display_task, "display task", 2048, NULL, 5, &DISPLAY_TASK, 1);
	xTaskCreatePinnedToCore(enc_read, "encoder reader", 2048, NULL, 7, &ENCODER_TASK, 1);
	xTaskCreatePinnedToCore(debug, "serial debug", 2048, NULL, 2, NULL, 1);
	xTaskCreatePinnedToCore(control, "PID controller", 4096, NULL, 7, &CONTROL_TASK, 0);
	pinMode(0, INPUT);
}

void loop()
{
}