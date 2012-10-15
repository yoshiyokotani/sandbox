//
// Binary.h
//
// $Id$
//
// Library: MongoDB
// Package: MongoDB
// Module:  Binary
//
// Definition of the Binary class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#ifndef _MongoDB_Binary_included
#define _MongoDB_Binary_included

#include "Poco/MongoDB/MongoDB.h"
#include "Poco/MongoDB/Element.h"
#include "Poco/Base64Encoder.h"
#include "Poco/Buffer.h"
#include "Poco/StreamCopier.h"
#include "Poco/MemoryStream.h"

#include <sstream>

namespace Poco {
namespace MongoDB {

class MongoDB_API Binary
	/// Implements BSON Binary. It's a wrapper around a Poco::Buffer<unsigned char>.
{
public:
	typedef SharedPtr<Binary> Ptr;


	Binary();
		/// Constructor


	Binary(Poco::Int32 size, unsigned char subtype);
		/// Constructor


	virtual ~Binary();
		/// Destructor


	Buffer<unsigned char>& buffer();
		/// Returns a reference to the buffer


	unsigned char subtype() const;
		/// Returns the subtype


	void subtype(unsigned char type);
		/// Sets the subtype


	std::string toString() const;
		/// Returns the binary encoded in Base64


private:

	Buffer<unsigned char> _buffer;


	unsigned char _subtype;
};


inline unsigned char Binary::subtype() const
{
	return _subtype;
}


inline void Binary::subtype(unsigned char type)
{
	_subtype = type;
}


inline Buffer<unsigned char>& Binary::buffer()
{
	return _buffer;
}


// BSON Embedded Document
// spec: binary
template<>
struct ElementTraits<Binary::Ptr>
{
	enum { TypeId = 0x05 };

	static std::string toString(const Binary::Ptr& value)
	{
		return value.isNull() ? "" : value->toString();
	}
};

template<>
inline void BSONReader::read<Binary::Ptr>(Binary::Ptr& to)
{
	Poco::Int32 size;
	_reader >> size;

	to->buffer().resize(size);

	unsigned char subtype;
	_reader >> subtype;
	to->subtype(subtype);
	
	_reader.readRaw((char*) to->buffer().begin(), size);
}

template<>
inline void BSONWriter::write<Binary::Ptr>(Binary::Ptr& from)
{
	_writer << from->subtype();
	_writer.writeRaw((char*) from->buffer().begin(), from->buffer().size());
}


}} // Namespace Poco::MongoDB

#endif // _MongoDB_Binary_included
