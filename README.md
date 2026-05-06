# MT6701 I2C ESPHome Component

Custom ESPHome component for the MT6701 magnetic rotary encoder using I2C.

## Features

- Reads angle position from an MT6701 sensor over I2C
- Publishes a sensor value in degrees
- Supports an optional zero offset
- Default polling interval is `1s`
- Includes an automation action to update the offset at runtime

## Component parameters

| Parameter | Default | Notes |
|---|---|---|
| `i2c_address` | `0x06` | Fixed I2C address for MT6701 |
| `offset` | `0.0` | Calibration offset in degrees |
| `update_interval` | `1s` | Polling interval for the sensor |

## Installation

Place this component in your ESPHome custom components folder.

Example folder layout:

```text
config/
  esphome.yaml
  custom_components/
    mt6701_i2c/
      __init__.py
      mt6701_i2c.cpp
      mt6701_i2c.h
      sensor.py
```

If you use a local directory for custom components, ensure ESPHome can see it by using `custom_component:` or `external_components:` as appropriate.

## YAML configuration

```yaml
i2c:
  sda: D2
  scl: D1
  scan: false

sensor:
  - platform: mt6701_i2c
    name: "MT6701 Angle"
    id: mt6701_sensor
    offset: 0.0
    update_interval: 1s
```

## Example automation

```yaml
script:
  - id: set_mt6701_offset
    then:
      - mt6701_i2c.set_offset:
          id: mt6701_sensor
          offset: 45.0
```

Or use it in a lambda/automation:

```yaml
automation:
  - alias: "Reset MT6701 Offset"
    trigger:
      - ...
    then:
      - mt6701_i2c.set_offset:
          id: mt6701_sensor
          offset: 0.0
```

## Notes

- The component publishes the wrapped angle value in the range `0` to `360` after applying the offset.
- If I2C reads fail, the sensor will publish `NaN`.
