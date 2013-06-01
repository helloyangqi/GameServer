/*
 * Packet.h
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */

#ifndef PACKET_H_
#define PACKET_H_

#include "Opcodes.h"

class Packet : public ByteBuffer
{
public:
	Packet()
	{

	}

	explicit Packet(Opcodes opcode, size_t res = 200)
	:ByteBuffer(res), m_opcode(opcode)
	{

	}

	Packet(const Packet& pakcet)
	:ByteBuffer(pakcet), m_opcode(packet.m_opcode)
	{

	}

	void Initialize(Opcodes opcode, size_t newres = 200)
	{
		clear();
		m_storage.reserve(newres);
		m_opcode = opcode;
	}

	Opcodes GetOpcode() const
	{
		return m_opcode;
	}

	void SetOpcode(Opcodes opcode)
	{
		m_opcode = opcode;
	}

	inline const char* GetOpcodeName() const
	{
		return LookupOpcodeName(m_opcode);
	}

protected:
	Opcodes m_opcode;
};

#endif /* PACKET_H_ */
