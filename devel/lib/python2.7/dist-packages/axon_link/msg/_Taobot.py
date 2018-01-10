# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from axon_link/Taobot.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Taobot(genpy.Message):
  _md5sum = "7d650a23fc1ea1941c14405910e8d823"
  _type = "axon_link/Taobot"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint8 motorA_encoder
uint8 motorA_dir
uint8 motorB_encoder
uint8 motorB_dir
uint8 motorC_encoder
uint8 motorC_dir
uint8 voltage
"""
  __slots__ = ['motorA_encoder','motorA_dir','motorB_encoder','motorB_dir','motorC_encoder','motorC_dir','voltage']
  _slot_types = ['uint8','uint8','uint8','uint8','uint8','uint8','uint8']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       motorA_encoder,motorA_dir,motorB_encoder,motorB_dir,motorC_encoder,motorC_dir,voltage

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Taobot, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.motorA_encoder is None:
        self.motorA_encoder = 0
      if self.motorA_dir is None:
        self.motorA_dir = 0
      if self.motorB_encoder is None:
        self.motorB_encoder = 0
      if self.motorB_dir is None:
        self.motorB_dir = 0
      if self.motorC_encoder is None:
        self.motorC_encoder = 0
      if self.motorC_dir is None:
        self.motorC_dir = 0
      if self.voltage is None:
        self.voltage = 0
    else:
      self.motorA_encoder = 0
      self.motorA_dir = 0
      self.motorB_encoder = 0
      self.motorB_dir = 0
      self.motorC_encoder = 0
      self.motorC_dir = 0
      self.voltage = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_7B().pack(_x.motorA_encoder, _x.motorA_dir, _x.motorB_encoder, _x.motorB_dir, _x.motorC_encoder, _x.motorC_dir, _x.voltage))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 7
      (_x.motorA_encoder, _x.motorA_dir, _x.motorB_encoder, _x.motorB_dir, _x.motorC_encoder, _x.motorC_dir, _x.voltage,) = _get_struct_7B().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_7B().pack(_x.motorA_encoder, _x.motorA_dir, _x.motorB_encoder, _x.motorB_dir, _x.motorC_encoder, _x.motorC_dir, _x.voltage))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 7
      (_x.motorA_encoder, _x.motorA_dir, _x.motorB_encoder, _x.motorB_dir, _x.motorC_encoder, _x.motorC_dir, _x.voltage,) = _get_struct_7B().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_7B = None
def _get_struct_7B():
    global _struct_7B
    if _struct_7B is None:
        _struct_7B = struct.Struct("<7B")
    return _struct_7B
