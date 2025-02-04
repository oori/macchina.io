//
// EventDispatcherGenerator.h
//
// Definition of the EventDispatcherGenerator class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef RemoteGen_EventDispatcherGenerator_INCLUDED
#define RemoteGen_EventDispatcherGenerator_INCLUDED


#include "AbstractGenerator.h"
#include "Poco/CodeGeneration/CppGenerator.h"
#include <set>


class EventDispatcherGenerator: public AbstractGenerator
	/// EventDispatcherGenerator generates a proxy for a given class definition. C++ specific. 
{
public:
	struct ExtParam
	{
		std::string varName;
		/// The original name
		std::string name;
		/// The name after renaming.
		int namePos;
		std::string nameSpace;
		int nameSpacePos;
		const Poco::CppParser::Parameter* pParam;
		bool mandatory;
		std::string direction;
		ExtParam(const std::string& origName, const std::string& aName, const std::string& aNS, const Poco::CppParser::Parameter* aParam, bool isMandatory, const std::string& aDirection):
			varName(origName),
			name(aName),
			namePos(-1),
			nameSpace(aNS),
			nameSpacePos(-1),
			pParam(aParam),
			mandatory(isMandatory),
			direction(aDirection)
		{
			poco_check_ptr (pParam);
		}
	};

	typedef std::map<Poco::UInt32, ExtParam> OrderedParameters;
		/// maps orderid to a a pair of name and parameter

	EventDispatcherGenerator(Poco::CodeGeneration::CppGenerator& cppGen);
		/// Creates the EventDispatcherGenerator.

	~EventDispatcherGenerator();
		/// Destroys the EventDispatcherGenerator.

	static std::string generateClassName(const Poco::CppParser::Struct* pStruct);
		/// Generates for a given class, its interface class name.

	static std::string generateQualifiedClassName(const std::string& ns, const Poco::CppParser::Struct* pStruct);
		/// Generates for a given class, its interface class name.

	void structStart(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties);
		/// Must not write the namespace

	void methodStart(const Poco::CppParser::Function* pFunc, const CodeGenerator::Properties& properties);
		/// Writes the method header. Properties contains the properties found in the functions docuementation and in the class documentation.

	void registerCallbacks(Poco::CodeGeneration::GeneratorEngine& e);

	std::string newClassName(const Poco::CppParser::Struct* pStruct);
		/// generates the new class name based on the old one

	std::vector<std::string> newBaseClasses(const Poco::CppParser::Struct* pStruct);

	static std::string generateStaticIdString(const Poco::CppParser::Function* pFunc, const std::set<std::string>& nameSpaces, OrderedParameters& attrs, OrderedParameters& elems, std::map<std::string, int>& nsIndex);
	/// Generates a static ids vector containing as first element the fucntion name, followed by parameter names sorted by order. Set namespacePos and namePos in attrs and elems and converts the namespaces set to a map of namespaces ->stringIdx

	static void doElemAttrSplit(const Poco::CppParser::Function* pFunc, OrderedParameters& attrs, OrderedParameters& elems, std::set<std::string>& nameSpaces);

	static void writePrepareAttribute(const OrderedParameters& attrs, const std::map<std::string, const Poco::CppParser::Parameter*>& outParams, const std::string& indentation, CodeGenerator& gen);

	static void detectOutParams(const Poco::CppParser::Function* pFunc, std::map<std::string, const Poco::CppParser::Parameter*>& outParams);

	static void writeTypeDeserializers(const Poco::CppParser::Function* pFunc, 
		const OrderedParameters& params, 
		const std::map<std::string, const Poco::CppParser::Parameter*>& outParams, 
		const std::string& indentation,
		CodeGenerator& gen);

	static bool hasAnyOutParams(const Poco::CppParser::Function* pFunc);

	static std::string generateEventFunctionName(const std::string& eventVarname);
		/// generates a fct name for an event member

private:
	static void serializeCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);

	static void eventCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);

	static void constructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
		/// Code generator for constructor

	static void destructorCodeGen(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);
		/// Code generator for destructor

	static void staticMembersInitializer(const Poco::CppParser::Function* pFunc, const Poco::CppParser::Struct* pStruct, CodeGenerator& gen, void* addParam);

	static std::string generateOutParamName(const Poco::CppParser::Parameter* pParam, const std::string& functionName);

	static std::string generateRetParamName(const Poco::CppParser::Function* pFunc);

	static void writeSerializingBlock(const Poco::CppParser::Function* pFunc, const OrderedParameters& attrs, const OrderedParameters& elems, const std::map<std::string, int>& nsIdx, CodeGenerator& gen, bool isOneWay, bool isEvent);
	static void writeTypeSerializer(const Poco::CppParser::Function* pFunc, const OrderedParameters& params, bool isAttr, int funcNsIdx, CodeGenerator& gen);
	static void writeDeserializingBlock(const Poco::CppParser::Function* pFunc, const OrderedParameters& attrs, const OrderedParameters& elems, CodeGenerator& gen, bool isOneWay, bool isEvent);
		/// expireTime is in microsec

	static void writeDeserializeReturnParam(const Poco::CppParser::Function* pFunc, CodeGenerator& gen);

	void checkForEventMembers(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties);
	void checkForEventMembersImpl(const Poco::CppParser::Struct* pStruct, const CodeGenerator::Properties& properties);
		/// checks if the class or any parent contains public BasicEvents

	void methodStartImpl(Poco::CppParser::Function* pFunc, const CodeGenerator::Properties& methodProperties);
	

private:
	std::vector<std::string> _boolsToInit;
	std::vector<std::string> _events;
	std::vector<std::string> _outerEventFunctions;
};


//
// inlines
//
inline std::string EventDispatcherGenerator::newClassName(const Poco::CppParser::Struct* pStruct)
{
	return EventDispatcherGenerator::generateClassName(pStruct);
}


#endif // RemoteGen_EventDispatcherGenerator_INCLUDED
