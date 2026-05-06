import esphome.codegen as cg
from esphome.components import i2c, sensor
import esphome.config_validation as cv
import esphome.automation as automation
from esphome.const import (
    STATE_CLASS_MEASUREMENT,
)
DEPENDENCIES = ["i2c"]



mt6701_i2c_ns = cg.esphome_ns.namespace("mt6701_i2c")
MT6701Component = mt6701_i2c_ns.class_("MT6701Component", cg.PollingComponent, i2c.I2CDevice)
mt6701_set_offset_action = mt6701_i2c_ns.class_(
    "MT6701SetOffsetAction", automation.Action
)


CONFIG_SCHEMA = (
    sensor.sensor_schema(
        MT6701Component,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend({
        cv.Optional("offset", default=0.0): cv.float_range(min=-359.0, max=359.0),
    })
    .extend(cv.polling_component_schema("1s"))
    .extend(i2c.i2c_device_schema(0x06))
)

async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    cg.add(var.set_offset(config["offset"]))



@automation.register_action(
    "mt6701_i2c.set_offset",
    mt6701_set_offset_action,
    cv.Schema(
        {
            cv.Required("id"): cv.use_id(MT6701Component),
            cv.Required("offset"): cv.templatable(cv.float_range(min=-359.0, max=359.0)),
        }
    ),
    synchronous=True,
)
async def mt6701_set_offset_to_code(config, action_id, template_arg, args):
    var = cg.new_Pvariable(action_id)
    await cg.register_parented(var, config["id"])

    offset = await cg.templatable(config["offset"], args, float)
    cg.add(var.set_offset(offset))

    return var