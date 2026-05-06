#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/preferences.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace mt6701_i2c {

class MT6701Component : public PollingComponent, public i2c::I2CDevice, public sensor::Sensor
{
    public:
      void set_offset(float offset) { this->offset_ = offset; }
      void setup() override;
      void dump_config() override;
      void update() override;
      float read_position();
    protected:
      float offset_{0.0f};


};

template<typename... Ts>
class MT6701SetOffsetAction : public Action<Ts...> {
 public:
  MT6701SetOffsetAction(MT6701Component *parent) : parent_(parent) {}

  TEMPLATABLE_VALUE(float, offset)

  void play(Ts... x) override {
    this->parent_->set_offset(this->offset_.value(x...));
  }

 protected:
  MT6701Component *parent_;
};

}  // namespace mt6701_i2c
}  // namespace esphome