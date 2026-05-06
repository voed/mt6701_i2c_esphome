#include "mt6701_i2c.h"

namespace esphome {
namespace mt6701_i2c {

static const char *const TAG = "MT6701 I2C";
static uint8_t MT6701_REG_ANGLE  = 0x03;

void MT6701Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up MT6701...");
}

void MT6701Component::dump_config() {
  LOG_SENSOR("", "MT6701 Sensor", this);
}

void MT6701Component::update() {
  float angle = this->read_position();

  // apply offset + wrap
  angle = fmodf((angle - this->offset_ + 360.0f), 360.0f);

  this->publish_state(angle);
}

float MT6701Component::read_position() {
  uint8_t pos[2];
  if (this->read_register(MT6701_REG_ANGLE, pos, 2) != i2c::ERROR_OK ) {
    return NAN;
  }

  uint16_t raw = (pos[0] << 6) | pos[1];
  return raw * (360.0f / 16384.0f);
}


}  // namespace mt6701_i2c
}  // namespace esphome