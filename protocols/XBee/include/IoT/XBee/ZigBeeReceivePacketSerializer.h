//
// ZigBeeReceivePacketSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_XBee_ZigBeeReceivePacket_INCLUDED
#define TypeSerializer_IoT_XBee_ZigBeeReceivePacket_INCLUDED


#include "IoT/XBee/XBeeNode.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::XBee::ZigBeeReceivePacket>
{
public:
	static void serialize(const std::string& name, const IoT::XBee::ZigBeeReceivePacket& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::XBee::ZigBeeReceivePacket& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"deviceAddress"s,"networkAddress"s,"options"s,"payload"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.deviceAddress, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.networkAddress, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES[2], value.options, ser);
		TypeSerializer<std::vector < Poco::UInt8 > >::serialize(REMOTING__NAMES[3], value.payload, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_XBee_ZigBeeReceivePacket_INCLUDED

