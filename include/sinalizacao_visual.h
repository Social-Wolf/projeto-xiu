#include <stdint.h>
#include <stdbool.h>
#include "hardware_config.h"

void visual_signal(uint8_t selection);
uint8_t read_ad_to_limit_level(uint8_t leitura, uint8_t limit_abs);
uint8_t level_analisys(uint8_t limit_level);