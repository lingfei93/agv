// Generated by gencpp from file taobot_link/Taobot.msg
// DO NOT EDIT!


#ifndef TAOBOT_LINK_MESSAGE_TAOBOT_H
#define TAOBOT_LINK_MESSAGE_TAOBOT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace taobot_link
{
template <class ContainerAllocator>
struct Taobot_
{
  typedef Taobot_<ContainerAllocator> Type;

  Taobot_()
    : motorA_encoder(0)
    , motorA_dir(0)
    , motorB_encoder(0)
    , motorB_dir(0)
    , motorC_encoder(0)
    , motorC_dir(0)
    , voltage(0.0)  {
    }
  Taobot_(const ContainerAllocator& _alloc)
    : motorA_encoder(0)
    , motorA_dir(0)
    , motorB_encoder(0)
    , motorB_dir(0)
    , motorC_encoder(0)
    , motorC_dir(0)
    , voltage(0.0)  {
  (void)_alloc;
    }



   typedef uint8_t _motorA_encoder_type;
  _motorA_encoder_type motorA_encoder;

   typedef uint8_t _motorA_dir_type;
  _motorA_dir_type motorA_dir;

   typedef uint8_t _motorB_encoder_type;
  _motorB_encoder_type motorB_encoder;

   typedef uint8_t _motorB_dir_type;
  _motorB_dir_type motorB_dir;

   typedef uint8_t _motorC_encoder_type;
  _motorC_encoder_type motorC_encoder;

   typedef uint8_t _motorC_dir_type;
  _motorC_dir_type motorC_dir;

   typedef float _voltage_type;
  _voltage_type voltage;





  typedef boost::shared_ptr< ::taobot_link::Taobot_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::taobot_link::Taobot_<ContainerAllocator> const> ConstPtr;

}; // struct Taobot_

typedef ::taobot_link::Taobot_<std::allocator<void> > Taobot;

typedef boost::shared_ptr< ::taobot_link::Taobot > TaobotPtr;
typedef boost::shared_ptr< ::taobot_link::Taobot const> TaobotConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::taobot_link::Taobot_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::taobot_link::Taobot_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace taobot_link

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'taobot_link': ['/home/eee/lingfei_ws/agv/src/taobot_link/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::taobot_link::Taobot_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::taobot_link::Taobot_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::taobot_link::Taobot_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::taobot_link::Taobot_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::taobot_link::Taobot_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::taobot_link::Taobot_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::taobot_link::Taobot_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8683fead56235780b4aa5f54f5f7b789";
  }

  static const char* value(const ::taobot_link::Taobot_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8683fead56235780ULL;
  static const uint64_t static_value2 = 0xb4aa5f54f5f7b789ULL;
};

template<class ContainerAllocator>
struct DataType< ::taobot_link::Taobot_<ContainerAllocator> >
{
  static const char* value()
  {
    return "taobot_link/Taobot";
  }

  static const char* value(const ::taobot_link::Taobot_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::taobot_link::Taobot_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 motorA_encoder\n\
uint8 motorA_dir\n\
uint8 motorB_encoder\n\
uint8 motorB_dir\n\
uint8 motorC_encoder\n\
uint8 motorC_dir\n\
float32 voltage\n\
";
  }

  static const char* value(const ::taobot_link::Taobot_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::taobot_link::Taobot_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.motorA_encoder);
      stream.next(m.motorA_dir);
      stream.next(m.motorB_encoder);
      stream.next(m.motorB_dir);
      stream.next(m.motorC_encoder);
      stream.next(m.motorC_dir);
      stream.next(m.voltage);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Taobot_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::taobot_link::Taobot_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::taobot_link::Taobot_<ContainerAllocator>& v)
  {
    s << indent << "motorA_encoder: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motorA_encoder);
    s << indent << "motorA_dir: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motorA_dir);
    s << indent << "motorB_encoder: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motorB_encoder);
    s << indent << "motorB_dir: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motorB_dir);
    s << indent << "motorC_encoder: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motorC_encoder);
    s << indent << "motorC_dir: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.motorC_dir);
    s << indent << "voltage: ";
    Printer<float>::stream(s, indent + "  ", v.voltage);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TAOBOT_LINK_MESSAGE_TAOBOT_H
