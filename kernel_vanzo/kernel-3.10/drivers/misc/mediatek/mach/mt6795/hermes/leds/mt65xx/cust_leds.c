#include <cust_leds.h>
#include <cust_leds_def.h>
#include <mach/mt_pwm.h>

#include <linux/kernel.h>
#include <mach/upmu_common_sw.h>
#include <mach/upmu_hw.h>

//extern int mtkfb_set_backlight_level(unsigned int level);
//extern int mtkfb_set_backlight_pwm(int div);
extern int mtkfb_set_backlight_level(unsigned int level);
extern int disp_bls_set_backlight(unsigned int level);

// Only support 64 levels of backlight (when lcd-backlight = MT65XX_LED_MODE_PWM)
#define BACKLIGHT_LEVEL_PWM_64_FIFO_MODE_SUPPORT 64 
// Support 256 levels of backlight (when lcd-backlight = MT65XX_LED_MODE_PWM)
#define BACKLIGHT_LEVEL_PWM_256_SUPPORT 256 

// Configure the support type "BACKLIGHT_LEVEL_PWM_256_SUPPORT" or "BACKLIGHT_LEVEL_PWM_64_FIFO_MODE_SUPPORT" !!
#define BACKLIGHT_LEVEL_PWM_MODE_CONFIG BACKLIGHT_LEVEL_PWM_256_SUPPORT

/* Vanzo:wangfei on: Tue, 07 Apr 2015 11:26:10 +0800
 * port from wuzhiyong bootup
 */

#define LCM_BUTTON_GPIO_PIN         (GPIO140 | 0x80000000)
// End of Vanzo:wangfei
unsigned int Cust_GetBacklightLevelSupport_byPWM(void)
{
	return BACKLIGHT_LEVEL_PWM_MODE_CONFIG;
}
/* Vanzo:wangfei on: Tue, 07 Apr 2015 11:26:30 +0800
 * TODO: replace this line with your comment
 */

static int disp_button_set_backlight(unsigned int level)
{
  mt_set_gpio_pull_enable(LCM_BUTTON_GPIO_PIN,GPIO_PULL_ENABLE);
  mt_set_gpio_pull_select(LCM_BUTTON_GPIO_PIN,GPIO_PULL_UP);
  if(level == 0) {
       mt_set_gpio_out(LCM_BUTTON_GPIO_PIN, GPIO_OUT_ZERO);
   }
  else
   {
       mt_set_gpio_out(LCM_BUTTON_GPIO_PIN, GPIO_OUT_ONE);
   }
}


// End of Vanzo:wangfei

unsigned int brightness_mapping(unsigned int level)
{
    unsigned int mapped_level;
    
    mapped_level = level;
       
	return mapped_level;
}

static struct cust_mt65xx_led cust_led_list[MT65XX_LED_TYPE_TOTAL] = {
    {"green",             MT65XX_LED_MODE_PMIC,MT65XX_LED_PMIC_NLED_ISINK1,{0}},
    {"blue",              MT65XX_LED_MODE_PMIC,MT65XX_LED_PMIC_NLED_ISINK2,{0}},
    {"red",               MT65XX_LED_MODE_PMIC,MT65XX_LED_PMIC_NLED_ISINK0,{0}},
    {"button-backlight",  MT65XX_LED_MODE_CUST_LCM, (long)disp_button_set_backlight,{0}},
    {"lcd-backlight",     MT65XX_LED_MODE_CUST_BLS_PWM, (long)disp_bls_set_backlight,{0,5}},
    {"jogball-backlight", MT65XX_LED_MODE_NONE, -1,{0}},
    {"keyboard-backlight",MT65XX_LED_MODE_NONE, -1,{0}},

};

struct cust_mt65xx_led *get_cust_led_list(void)
{
	return cust_led_list;
}

