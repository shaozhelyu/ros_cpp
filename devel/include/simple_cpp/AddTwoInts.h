// Generated by gencpp from file simple_cpp/AddTwoInts.msg
// DO NOT EDIT!


#ifndef SIMPLE_CPP_MESSAGE_ADDTWOINTS_H
#define SIMPLE_CPP_MESSAGE_ADDTWOINTS_H

#include <ros/service_traits.h>


#include <simple_cpp/AddTwoIntsRequest.h>
#include <simple_cpp/AddTwoIntsResponse.h>


namespace simple_cpp
{

struct AddTwoInts
{

typedef AddTwoIntsRequest Request;
typedef AddTwoIntsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct AddTwoInts
} // namespace simple_cpp


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::simple_cpp::AddTwoInts > {
  static const char* value()
  {
    return "6a2e34150c00229791cc89ff309fff21";
  }

  static const char* value(const ::simple_cpp::AddTwoInts&) { return value(); }
};

template<>
struct DataType< ::simple_cpp::AddTwoInts > {
  static const char* value()
  {
    return "simple_cpp/AddTwoInts";
  }

  static const char* value(const ::simple_cpp::AddTwoInts&) { return value(); }
};


// service_traits::MD5Sum< ::simple_cpp::AddTwoIntsRequest> should match
// service_traits::MD5Sum< ::simple_cpp::AddTwoInts >
template<>
struct MD5Sum< ::simple_cpp::AddTwoIntsRequest>
{
  static const char* value()
  {
    return MD5Sum< ::simple_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::simple_cpp::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::simple_cpp::AddTwoIntsRequest> should match
// service_traits::DataType< ::simple_cpp::AddTwoInts >
template<>
struct DataType< ::simple_cpp::AddTwoIntsRequest>
{
  static const char* value()
  {
    return DataType< ::simple_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::simple_cpp::AddTwoIntsRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::simple_cpp::AddTwoIntsResponse> should match
// service_traits::MD5Sum< ::simple_cpp::AddTwoInts >
template<>
struct MD5Sum< ::simple_cpp::AddTwoIntsResponse>
{
  static const char* value()
  {
    return MD5Sum< ::simple_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::simple_cpp::AddTwoIntsResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::simple_cpp::AddTwoIntsResponse> should match
// service_traits::DataType< ::simple_cpp::AddTwoInts >
template<>
struct DataType< ::simple_cpp::AddTwoIntsResponse>
{
  static const char* value()
  {
    return DataType< ::simple_cpp::AddTwoInts >::value();
  }
  static const char* value(const ::simple_cpp::AddTwoIntsResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // SIMPLE_CPP_MESSAGE_ADDTWOINTS_H
