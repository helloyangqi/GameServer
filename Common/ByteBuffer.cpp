/*
 * ByteBuffer.cpp
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */


#include "ByteBuffer.h"
#include "Log.h"

void ByteBufferException::PrintPosError() const
{
	sLog.OutError(
			"Attempted to %s in ByteBUffer (pos:%d size:%d)"
			"value with size:%d",
			(add ? "put" : "get"),pos, size, esieze);

}
