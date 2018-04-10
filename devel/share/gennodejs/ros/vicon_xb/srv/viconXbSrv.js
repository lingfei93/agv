// Auto-generated. Do not edit!

// (in-package vicon_xb.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class viconXbSrvRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.block = null;
      this.logfile_idx = null;
    }
    else {
      if (initObj.hasOwnProperty('block')) {
        this.block = initObj.block
      }
      else {
        this.block = false;
      }
      if (initObj.hasOwnProperty('logfile_idx')) {
        this.logfile_idx = initObj.logfile_idx
      }
      else {
        this.logfile_idx = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type viconXbSrvRequest
    // Serialize message field [block]
    bufferOffset = _serializer.bool(obj.block, buffer, bufferOffset);
    // Serialize message field [logfile_idx]
    bufferOffset = _serializer.int32(obj.logfile_idx, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type viconXbSrvRequest
    let len;
    let data = new viconXbSrvRequest(null);
    // Deserialize message field [block]
    data.block = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [logfile_idx]
    data.logfile_idx = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vicon_xb/viconXbSrvRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ed681b93b567be83d5e7ee5788d064f3';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool block
    int32 logfile_idx
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new viconXbSrvRequest(null);
    if (msg.block !== undefined) {
      resolved.block = msg.block;
    }
    else {
      resolved.block = false
    }

    if (msg.logfile_idx !== undefined) {
      resolved.logfile_idx = msg.logfile_idx;
    }
    else {
      resolved.logfile_idx = 0
    }

    return resolved;
    }
};

class viconXbSrvResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.result = null;
    }
    else {
      if (initObj.hasOwnProperty('result')) {
        this.result = initObj.result
      }
      else {
        this.result = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type viconXbSrvResponse
    // Serialize message field [result]
    bufferOffset = _serializer.uint8(obj.result, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type viconXbSrvResponse
    let len;
    let data = new viconXbSrvResponse(null);
    // Deserialize message field [result]
    data.result = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'vicon_xb/viconXbSrvResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '25458147911545c320c4c0a299eff763';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 result
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new viconXbSrvResponse(null);
    if (msg.result !== undefined) {
      resolved.result = msg.result;
    }
    else {
      resolved.result = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: viconXbSrvRequest,
  Response: viconXbSrvResponse,
  md5sum() { return '690ec01b63ec02305afae8d102907248'; },
  datatype() { return 'vicon_xb/viconXbSrv'; }
};
