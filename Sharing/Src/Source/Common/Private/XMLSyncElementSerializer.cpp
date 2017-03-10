//////////////////////////////////////////////////////////////////////////
// XMLElementSerializer.cpp
//
// Copyright (C) 2014 Microsoft Corp.  All Rights Reserved
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Public/XMLSyncElementSerializer.h>
#include <TinyXml2.h>

using namespace tinyxml2;

XTOOLS_NAMESPACE_BEGIN
NAMESPACE_BEGIN(Sync)

namespace // Intentionally Anonymous
{
	const char* cAttributeName_Type = "type";
	const char* cAttributeName_GUID = "guid";
	const char* cAttributeName_Name = "name";
	const char* cAttributeName_Version = "version";

	const char* cElementName_Value = "value";
	const char* cElementName_SyncNode = "SyncNode";
	const char* cElementName_SyncDocument = "SyncDocument";

	const int cVersion_SyncDocument = 1; // Initial version

	void OpenXMLElement(XMLPrinter& printer, const ElementConstPtr& root)
	{
		printer.OpenElement(cElementName_SyncNode);
		printer.PushAttribute(cAttributeName_Name, root->GetName()->GetString().c_str());
		printer.PushAttribute(cAttributeName_Type, (int)root->GetElementType());
		printer.PushAttribute(cAttributeName_GUID, (int64_t)root->GetGUID());
	}

	template<class T>
	void Serialize(XMLPrinter& printer, const ref_ptr<const T>& root)
	{
		OpenXMLElement(printer, root);
		printer.PushText(root->GetValue());
		printer.CloseElement();
	}

	void Serialize(XMLPrinter& printer, const StringElementConstPtr& root)
	{
		OpenXMLElement(printer, root);
		printer.PushText(root->GetValue()->GetString().c_str(), /*cdata=*/true);
		printer.CloseElement();
	}

	void Serialize(XMLPrinter& printer, const IntArrayElementConstPtr& root)
	{
		OpenXMLElement(printer, root);
		for (int i = 0; i < root->GetCount(); ++i)
		{
			printer.OpenElement(cElementName_Value);
			printer.PushText(root->GetValue(i));
			printer.CloseElement();
		}
		printer.CloseElement();
	}

	// Declare to avoid calling template from ObjectElementConstPtr
	void Serialize(XMLPrinter& printer, const ElementConstPtr& root, bool saveUserData);

	void Serialize(XMLPrinter& printer, const ObjectElementConstPtr& root, bool saveUserData)
	{
		// Elements owned by a user are not persistent and thus not serialized
		if (!saveUserData && root->GetOwnerID() != User::kInvalidUserID)
		{
			return;
		}

		OpenXMLElement(printer, root);

		const int elementCount = root->GetElementCount();
		for (int i = 0; i < elementCount; ++i)
		{
			const ElementConstPtr child = root->GetElementAt(i);
			Serialize(printer, child, saveUserData);
		}

		printer.CloseElement();
	}

	void Serialize(XMLPrinter& printer, const ElementConstPtr& root, bool saveUserData)
	{
		switch (root->GetElementType())
		{
		case BoolType: Serialize(printer, BoolElement::Cast(root)); break;
		case Int32Type: Serialize(printer, IntElement::Cast(root)); break;
		case Int64Type: Serialize(printer, LongElement::Cast(root)); break;
		case FloatType: Serialize(printer, FloatElement::Cast(root)); break;
		case DoubleType: Serialize(printer, DoubleElement::Cast(root)); break;
		case StringType: Serialize(printer, StringElement::Cast(root)); break;
		case ObjectType: Serialize(printer, ObjectElement::Cast(root), saveUserData); break;
		case Int32ArrayType: Serialize(printer, IntArrayElement::Cast(root)); break;
		default:
			LogError("Element(%s) has unknown element type(%d)",
				root->GetName()->GetString().c_str(), root->GetElementType());
			break;
		}
	}

	void Print(XMLPrinter& printer, const ObjectElementConstPtr& root, bool writeHeader, bool saveUserData)
	{
		if (writeHeader)
		{
			printer.PushHeader(/*writeBOM=*/false, /*writeDeclaration=*/true);
		}

		printer.OpenElement(cElementName_SyncDocument);
		printer.PushAttribute(cAttributeName_Version, cVersion_SyncDocument);

		if( root != nullptr)
		{
			Serialize(printer, root, saveUserData);
		}

		printer.CloseElement();
	}

	template<class T>
	bool RunGuidsTest(XMLElement* element, const ref_ptr<T>& root, const char * file, int line)
	{
		XGuid xmlGuid = (XGuid)element->Int64Attribute(cAttributeName_GUID);
		if (xmlGuid != root->GetGUID())
		{
			LogFormat(
				LogSeverity::Error, file, line,
				"Element(%s) has mismatched guid(xml->%d vs sync->%d)",
				root->GetName()->GetString().c_str(), xmlGuid, root->GetGUID());

			return false;
		}

		return true;
	}

#define RUN_GUIDS_TEST(e, r) RunGuidsTest((e), (r), __FILE__, __LINE__ )


	template<class T>
	void Deserialize(XMLElement* element, const ref_ptr<T>& root)
	{
		if (!RUN_GUIDS_TEST(element, root))
		{
			return;
		}
	}

	void Deserialize(XMLElement* element, const IntArrayElementPtr& root)
	{
		if (!RUN_GUIDS_TEST(element, root))
		{
			return;
		}

		XMLElement* child = element->FirstChildElement(cElementName_Value);
		while (child != nullptr)
		{
			root->InsertValue(root->GetCount(), child->IntText());
			child = child->NextSiblingElement(cElementName_Value);
		}
	}

	void Deserialize(XMLElement* element, const ObjectElementPtr& root)
	{
		if (!RUN_GUIDS_TEST(element, root))
		{
			return;
		}

		XMLElement* child = element->FirstChildElement(cElementName_SyncNode);
		while (child != nullptr)
		{
			int type = child->IntAttribute(cAttributeName_Type);
			XStringPtr name = new XString(child->Attribute(cAttributeName_Name));

			switch (type)
			{
			case BoolType: Deserialize(child, root->CreateBoolElement(name, child->BoolText()));  break;
			case Int32Type: Deserialize(child, root->CreateIntElement(name, child->IntText())); break;
			case Int64Type: Deserialize(child, root->CreateLongElement(name, child->Int64Text())); break;
			case FloatType: Deserialize(child, root->CreateFloatElement(name, child->FloatText())); break;
			case DoubleType: Deserialize(child, root->CreateDoubleElement(name, child->DoubleText())); break;
			case StringType: Deserialize(child, root->CreateStringElement(name, new XString(child->GetText()))); break;
			case ObjectType: Deserialize(child, root->CreateObjectElement(name, new XString("Object"))); break;
			case Int32ArrayType: Deserialize(child, root->CreateIntArrayElement(name)); break;
			default:
				LogError("Element(%s) has unknown element type(%d)", child->Name(), type);
				break;
			}

			child = child->NextSiblingElement(cElementName_SyncNode);
		}
	}

	void Parse(XMLDocument& document, const ObjectElementPtr& root)
	{
		XMLElement* docElement = document.FirstChildElement(cElementName_SyncDocument);
		if (docElement == nullptr)
		{
			LogError("Could not find sync document root (%s)", cElementName_SyncDocument);
			return;
		}

		int version = docElement->IntAttribute(cAttributeName_Version);
		if (version != cVersion_SyncDocument)
		{
			LogError("Could not parse sync document - version(%s) did not match expected(%s)", version, cVersion_SyncDocument);
			return;
		}

		// If we have a sync node then deserialize
		XMLElement* nodeElement = docElement->FirstChildElement(cElementName_SyncNode);
		if (nodeElement != nullptr)
		{
			Deserialize(nodeElement, root);
		}
	}

} // anonymous 


XMLSyncElementSerializer::XMLSyncElementSerializer(bool writeHeader, bool saveUserData)
	: m_writeHeader(writeHeader)
	, m_saveUserData(saveUserData)
{

}

bool XMLSyncElementSerializer::Save(FILE* file, const ObjectElementConstPtr& root)
{
	if (!XTVERIFY(file != nullptr)) { return false; }

	XMLPrinter printer(file);
	Print(printer, root, m_writeHeader, m_saveUserData);

	return true;
}

bool XMLSyncElementSerializer::Save(std::ostream& stream, const ObjectElementConstPtr& root)
{
	XMLPrinter printer;
	Print(printer, root, m_writeHeader, m_saveUserData);

	stream.write(printer.CStr(), printer.CStrSize()-1);
	return true;
}

bool XMLSyncElementSerializer::Save(std::string& xmlStr, const ObjectElementConstPtr& root)
{
	XMLPrinter printer;
	Print(printer, root, m_writeHeader, m_saveUserData);

	xmlStr.append(printer.CStr(), printer.CStrSize() - 1);
	return true;
}

bool XMLSyncElementSerializer::Load(FILE* file, const ObjectElementPtr& root)
{
	if (!XTVERIFY(file != nullptr)) { return false; }
	if (!XTVERIFY(root != nullptr)) { return false; }

	XMLDocument document;
	XMLError error = document.LoadFile(file);
	if (error != XML_SUCCESS)
	{
		LogError("Parsing of file failed due to an error(%d)", (int)error);
		return false;
	}

	Parse(document, root);

	return true;
}

bool XMLSyncElementSerializer::Load(std::istream& stream, const ObjectElementPtr& root)
{
	if (!XTVERIFY(root != nullptr)) { return false; }

	stream.seekg(0, stream.end);
	const std::streampos length = stream.tellg();
	stream.seekg(0, stream.beg);

	if (length == std::streampos(0))
	{
		LogError("Stream is zero length");
		return false;
	}

	std::vector<char> buffer((std::vector<char>::size_type)length);
	stream.read(&buffer[0], buffer.size());

	if (!stream)
	{
		LogError("Failed to read full stream(%d bytes), only read(%d bytes)", (int)length, (int)stream.gcount());
		return false;
	}

	XMLDocument document;
	XMLError error = document.Parse(&buffer[0], buffer.size());
	if (error != XML_SUCCESS)
	{
		LogError("Parsing of file failed due to an error(%d)", (int)error);
		return false;
	}

	Parse(document, root);
	return true;
}

bool XMLSyncElementSerializer::Load(const std::string& xmlStr, const ObjectElementPtr& root)
{
	if (!XTVERIFY(root != nullptr)) { return false; }

	XMLDocument document;
	XMLError error = document.Parse(xmlStr.c_str(), xmlStr.size());
	if (error != XML_SUCCESS)
	{
		LogError("Parsing of file failed due to an error(%d)", (int)error);
		return false;
	}

	Parse(document, root);
	return true;
}


NAMESPACE_END(Sync)
XTOOLS_NAMESPACE_END