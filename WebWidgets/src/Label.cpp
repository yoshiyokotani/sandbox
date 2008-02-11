//
// Label.cpp
//
// $Id: //poco/Main/WebWidgets/src/Label.cpp#2 $
//
// Library: WebWidgets
// Package: WebGUI
// Module:  Label
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


#include "Poco/WebWidgets/Label.h"
#include "Poco/WebWidgets/Visitor.h"
#include "Poco/WebWidgets/XMLUtil.h"
#include "Poco/DOM/Element.h"


namespace Poco {
namespace WebWidgets {


const std::string Label::FACTORY_ID("label");


Label::Label():
	_text()
{
}


Label::Label(const std::string& txt):
	_text(txt)
{
}


Label::Label(const Poco::XML::Element* pElem):
	Widget(pElem),
	_text(XMLUtil::getText(pElem))
{
}


Label::~Label()
{
}


void Label::accept(Visitor& v)
{
	v.visit(*this);
}


Poco::AutoPtr<Widget> Label::clone() const
{
	Poco::AutoPtr<Widget> ptr = new Label(getText());
	ptr->setAttributes(getAttributes());
	return ptr;
}


} } // namespace Poco::WebWidgets