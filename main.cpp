#include "mbed.h"
#include "stm32_standby.h"

static DigitalOut led(LED1);

int main() {
    stm32_standby_init();

    wait_ms(1000);

    led = 1;
    wait_ms(200);
    led = 0;
    wait_ms(200);
    led = 1;

    printf("before sleep\r\n");

    stm32_rtc_set_wake_up_timer_s(5);

    // Disable IRQs
    core_util_critical_section_enter();

    // Stop HAL tick to avoid to exit sleep in 1ms
    HAL_SuspendTick();
    // Request to enter SLEEP mode
    HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
    // Restart HAL tick
    HAL_ResumeTick();

    // Enable IRQs
    core_util_critical_section_exit();

    printf("after sleep\r\n");

    led = 0;
}
