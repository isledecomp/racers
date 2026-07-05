#include "golscenenode.h"

#include "golbinparser.h"
#include "golerror.h"
#include "golmath.h"
#include "goltransformbase.h"

#include <string.h>

DECOMP_SIZE_ASSERT(GolSceneNode, 0x18)
DECOMP_SIZE_ASSERT(GolSceneNode::DdfTxtParser, 0x1fc)

// FUNCTION: GOLDP 0x10029980
GolSceneNode::GolSceneNode()
{
	m_capacity = 0;
	m_composer = 0;
	m_updateSerial = 0;
}

// FUNCTION: GOLDP 0x100299c0
GolSceneNode::~GolSceneNode()
{
	GolNameTable::Clear();
	m_capacity = 0;
	m_updateSerial = 0;
}

// FUNCTION: GOLDP 0x10029a20
void GolSceneNode::Load(const LegoChar* p_name, LegoBool32 p_binary)
{
	if (m_capacity != 0) {
		Clear();
	}

	GolFileParser* parser;
	if (p_binary) {
		parser = new GolBinParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		parser->SetSuffix(".sdb");
	}
	else {
		parser = new DdfTxtParser;
		if (parser == NULL) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}
	}

	parser->OpenFileForRead(p_name);

	GolFileParser::ParserTokenType token;
	while ((token = parser->GetNextToken()) != GolFileParser::e_syntaxerror) {
		if (token != DdfTxtParser::e_node) {
			parser->HandleUnexpectedToken(GolFileParser::e_syntaxerror);
		}

		Parse(parser);
	}

	parser->Dispose();
	if (parser != NULL) {
		delete parser;
	}
}

// FUNCTION: GOLDP 0x10029b50
void GolSceneNode::CopyFrom(GolSceneNode* p_node)
{
	if (m_capacity != 0) {
		Clear();
	}

	m_capacity = p_node->m_capacity;
	GolNameTable::Allocate(m_capacity);
	AllocateTransforms();

	for (LegoU32 i = 0; i < m_capacity; i++) {
		GolTransformBase* sourceOrbit = p_node->GetTransform(i);

		GolName name;
		p_node->GetNameByValue(sourceOrbit, name);

		GolTransformBase* destOrbit = GetTransform(i);
		AddName(name, destOrbit);

		if (sourceOrbit->m_parent != NULL) {
			GolName parentName;
			p_node->GetNameByValue(sourceOrbit->m_parent, parentName);
			static_cast<GolTransformBase*>(GetName(parentName))->AttachChild(destOrbit);
		}

		destOrbit->CopyFrom(sourceOrbit);
	}
}

// FUNCTION: GOLDP 0x10029c10
void GolSceneNode::Allocate(LegoU32 p_capacity)
{
	if (m_capacity != 0) {
		Clear();
	}

	m_capacity = p_capacity;
	GolNameTable::Allocate(m_capacity);
	AllocateTransforms();
}

// FUNCTION: GOLDP 0x10029c40
void GolSceneNode::Clear()
{
	GolNameTable::Clear();
	m_capacity = 0;
	m_updateSerial = 0;
}

// FUNCTION: GOLDP 0x10029c60
void GolSceneNode::Parse(GolFileParser* p_parser)
{
	m_capacity = p_parser->ReadBracketedCountAndLeftCurly();
	if (m_capacity == 0) {
		p_parser->HandleUnexpectedToken(GolFileParser::e_int);
	}

	GolNameTable::Allocate(m_capacity);
	AllocateTransforms();

	for (LegoU32 i = 0; i < m_capacity; i++) {
		GolTransformBase* orbit = GetTransform(i);
		GolName name;

		p_parser->AssertNextTokenIs(static_cast<GolFileParser::ParserTokenType>(DdfTxtParser::e_node));
		::strncpy(name, p_parser->ReadStringWithMaxLength(sizeOfArray(name)), sizeOfArray(name));
		GolNameTable::AddName(name, orbit);
		p_parser->ReadLeftCurly();

		GolFileParser::ParserTokenType token;
		while ((token = p_parser->GetNextToken()) != GolFileParser::e_rightCurly) {
			switch (token) {
			case DdfTxtParser::e_parent: {
				::strncpy(name, p_parser->ReadStringWithMaxLength(sizeOfArray(name)), sizeOfArray(name));

				GolTransformBase* parent = static_cast<GolTransformBase*>(GetName(name));
				if (parent == NULL) {
					p_parser->HandleUnexpectedToken(GolFileParser::e_invalidString);
				}

				parent->AttachChild(orbit);
				break;
			}
			case DdfTxtParser::e_rotation: {
				LegoFloat values[4];
				values[0] = p_parser->ReadFloat();
				values[1] = p_parser->ReadFloat();
				values[2] = p_parser->ReadFloat();
				values[3] = p_parser->ReadFloat();
				orbit->SetRotation(values);
				break;
			}
			case DdfTxtParser::e_position: {
				GolVec3 position;
				position.m_x = p_parser->ReadFloat();
				position.m_y = p_parser->ReadFloat();
				position.m_z = p_parser->ReadFloat();
				orbit->SetPosition(&position);
				break;
			}
			}
		}
	}

	p_parser->ReadRightCurly();
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
// FUNCTION: LEGORACERS 0x004113b0 FOLDED
LegoU32 GolSceneNode::IndexOf(const GolTransformBase&) const
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolSceneNode::UpdateWorldMatrices(const GolMatrix4&)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void GolSceneNode::UpdateWorldMatricesAffine(const GolMatrix34* p_m)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolSceneNode::VTable0x28(undefined4, undefined4)
{
	// empty
}

// FUNCTION: GOLDP 0x1002c010 FOLDED
void GolSceneNode::GetWorldMatrix(LegoU32 p_index, GolMatrix34* p_dest) const
{
	// empty
}

// FUNCTION: LEGORACERS 0x00413230
void GolSceneNode::TransformPointToWorld(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3)
{
	*p_param3 = *p_param2;

	GolVec3 vec;
	for (GolTransformBase* current = GetTransform(p_param1); current != NULL; current = current->m_parent) {
		vec = *p_param3;
		current->TransformPoint(&vec, p_param3);
	}
}

// FUNCTION: LEGORACERS 0x004132a0
void GolSceneNode::TransformVectorToWorld(undefined4 p_param1, GolVec3* p_param2, GolVec3* p_param3)
{
	*p_param3 = *p_param2;

	GolVec3 vec;
	for (GolTransformBase* current = GetTransform(p_param1); current != NULL; current = current->m_parent) {
		vec = *p_param3;
		current->TransformVector(&vec, p_param3);
	}
}

// FUNCTION: LEGORACERS 0x00413310
void GolSceneNode::MirrorY()
{
	for (LegoU32 i = 0; i < m_capacity; i++) {
		GolTransformBase* transform = GetTransform(i);

		GolVec3 position;
		transform->GetPosition(&position);
		position.m_y = -position.m_y;
		transform->SetPosition(&position);

		GolVec3 right;
		GolVec3 forward;
		transform->GetRightDirection(&right, &forward);
		right.m_y = -right.m_y;
		forward.m_y = -forward.m_y;
		transform->SetRightDirection(&right, &forward);
	}
}
