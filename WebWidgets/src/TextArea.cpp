//
// TextArea.cpp
//
// $Id: //poco/Main/WebWidgets/src/TextArea.cpp#3 $
//
// Library: WebWidgets
// Package: WebGUI
// Module:  TextArea
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
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


#include "Poco/WebWidgets/TextArea.h"
#include "Poco/WebWidgets/Visitor.h"
#include "Poco/DOM/Element.h"
#include "Poco/NumberParser.h"


namespace Poco {
namespace WebWidgets {


const std::string TextArea::FACTORY_ID("textArea");
const std::string TextArea::XML_ROWS("rows");
const std::string TextArea::XML_COLS("cols");


TextArea::TextArea(const std::string& uniqueName, Poco::UInt32 rows, Poco::UInt32 cols, const std::string& defTxt):
	InputField(uniqueName, defTxt),
	_rows(rows),
	_cols(cols)
{
}


TextArea::TextArea(const Poco::XML::Element* pElem):
	InputField(pElem),
	_rows(0),
	_cols(0)
{
	const std::string& rowStr = pElem->getAttribute(XML_ROWS);
	_rows = Poco::NumberParser::parseUnsigned(rowStr);
	const std::string& colStr = pElem->getAttribute(XML_COLS);
	_cols = Poco::NumberParser::parseUnsigned(colStr);
}


TextArea::~TextArea()
{
}


void TextArea::accept(Visitor& v)
{
	v.visit(*this);
}


Poco::AutoPtr<Widget> TextArea::clone() const
{
	Poco::AutoPtr<Widget> ptr = new TextArea(name(), _rows, _cols, getText());
	ptr->setAttributes(getAttributes());
	return ptr;
}


} } // namespace Poco::WebWidgets