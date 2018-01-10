// Auto-generated. Do not edit!

// (in-package axon_link.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Taobot {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.motorA_encoder = null;
      this.motorA_dir = null;
      this.motorB_encoder = null;
      this.motorB_dir = null;
      this.motorC_encoder = null;
      this.motorC_dir = null;
      this.voltage = null;
    }
    else {
      if (initObj.hasOwnProperty('motorA_encoder')) {
        this.motorA_encoder = initObj.motorA_encoder
      }
      else {
        this.motorA_encoder = 0;
      }
      if (initObj.hasOwnProperty('motorA_dir')) {
        this.motorA_dir = initObj.motorA_dir
      }
      else {
        this.motorA_dir = 0;
      }
      if (initObj.hasOwnProperty('motorB_encoder')) {
        this.motorB_encoder = initObj.motorB_encoder
      }
      else {
        this.motorB_encoder = 0;
      }
      if (initObj.hasOwnProperty('motorB_dir')) {
        this.motorB_dir = initObj.motorB_dir
      }
      else {
        this.motorB_dir = 0;
      }
      if (initObj.hasOwnProperty('motorC_encoder')) {
        this.motorC_encoder = initObj.motorC_encoder
      }
      else {
        this.motorC_encoder = 0;
      }
      if (initObj.hasOwnProperty('motorC_dir')) {
        this.motorC_dir = initObj.motorC_dir
      }
      else {
        this.motorC_dir = 0;
      }
      if (initObj.hasOwnProperty('voltage')) {
        this.voltage = initObj.voltage
      }
      else {
        this.voltage = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Taobot
    // Serialize message field [motorA_encoder]
    bufferOffset = _serializer.uint8(obj.motorA_encoder, buffer, bufferOffset);
    // Serialize message field [motorA_dir]
    bufferOffset = _serializer.uint8(obj.motorA_dir, buffer, bufferOffset);
    // Serialize message field [motorB_encoder]
    bufferOffset = _serializer.uint8(obj.motorB_encoder, buffer, bufferOffset);
    // Serialize message field [motorB_dir]
    bufferOffset = _serializer.uint8(obj.motorB_dir, buffer, bufferOffset);
    // Serialize message field [motorC_encoder]
    bufferOffset = _serializer.uint8(obj.motorC_encoder, buffer, bufferOffset);
    // Serialize message field [motorC_dir]
    bufferOffset = _serializer.uint8(obj.motorC_dir, buffer, bufferOffset);
    // Serialize message field [voltage]
    bufferOffset = _serializer.uint8(obj.voltage, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Taobot
    let len;
    let data = new Taobot(null);
    // Deserialize message field [motorA_encoder]
    data.motorA_encoder = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [motorA_dir]
    data.motorA_dir = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [motorB_encoder]
    data.motorB_encoder = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [motorB_dir]
    data.motorB_dir = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [motorC_encoder]
    data.motorC_encoder = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [motorC_dir]
    data.motorC_dir = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [voltage]
    data.voltage = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 7;
  }

  static datatype() {
    // Returns string type for a message object
    return 'axon_link/Taobot';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7d650a23fc1ea1941c14405910e8d823';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 motorA_encoder
    uint8 motorA_dir
    uint8 motorB_encoder
    uint8 motorB_dir
    uint8 motorC_encoder
    uint8 motorC_dir
    uint8 voltage
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Taobot(null);
    if (msg.motorA_encoder !== undefined) {
      resolved.motorA_encoder = msg.motorA_encoder;
    }
    else {
      resolved.motorA_encoder = 0
    }

    if (msg.motorA_dir !== undefined) {
      resolved.motorA_dir = msg.motorA_dir;
    }
    else {
      resolved.motorA_dir = 0
    }

    if (msg.motorB_encoder !== undefined) {
      resolved.motorB_encoder = msg.motorB_encoder;
    }
    else {
      resolved.motorB_encoder = 0
    }

    if (msg.motorB_dir !== undefined) {
      resolved.motorB_dir = msg.motorB_dir;
    }
    else {
      resolved.motorB_dir = 0
    }

    if (msg.motorC_encoder !== undefined) {
      resolved.motorC_encoder = msg.motorC_encoder;
    }
    else {
      resolved.motorC_encoder = 0
    }

    if (msg.motorC_dir !== undefined) {
      resolved.motorC_dir = msg.motorC_dir;
    }
    else {
      resolved.motorC_dir = 0
    }

    if (msg.voltage !== undefined) {
      resolved.voltage = msg.voltage;
    }
    else {
      resolved.voltage = 0
    }

    return resolved;
    }
};

module.exports = Taobot;
