//
// SharedPtrTest.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/SharedPtrTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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

#include "Poco/SharedPtr.h"
#include <assert.h>
#include <iostream>

using Poco::SharedPtr;
using Poco::NullPointerException;

namespace
{
    class TestObject
    {
    public:
        TestObject(const int& data = 0) : _data(data)
        {
            ++_count;
            std::cout << "current counter : " << _count << "\n";
        }

        virtual ~TestObject()
        {
            --_count;
            std::cout << "current counter : " << _count << "\n";
        }

        void set(const int& data)
        {
            _data = data;
        }

        int& data()
        {
            return _data;
        }

        static int count()
        {
            return _count;
        }

		static void destory(TestObject* p){
			std::cout << "TestObject::destory delete" << std::endl;
			delete p;
		}

    private:
        int _data;
        static int _count;
    };

    int TestObject::_count = 0;

	class DerivedObject: public TestObject
	{
	public:
		DerivedObject(int i): _number(i)
		{
		}

		int number() const
		{
			return _number;
		}
	private:
		int _number;
	};
}


template<typename T>
void dummyDeleter(T* p)
{
	std::cout << "dummyDeleter delete" << std::endl;
	delete p;
}

template<typename T>
struct DummyFunctorDeleter
{
	void operator()(T* p){
		std::cout << "dummyFunctorDeleter delete" << std::endl;
		delete p;
	}
};

void testConstruction()
{
	std::cout << "\n-- test construction --\n" ;
	
	{
		SharedPtr<TestObject> ptr(new TestObject, dummyDeleter<TestObject>);
		poco_assert(ptr.get() != 0);
	}

	{
		SharedPtr<TestObject> ptr(new TestObject, DummyFunctorDeleter<TestObject>() );
		poco_assert(ptr.get() != 0);
	}

	{
		SharedPtr<TestObject> ptr(new TestObject, TestObject::destory);
		poco_assert(ptr.get() != 0);
	}

}

void testSwap()
{
	std::cout << "\n-- test swap --\n" ;
	{
		SharedPtr<TestObject> ptr1; 
		{
			SharedPtr<TestObject> ptr2 = SharedPtr<TestObject> (new TestObject, dummyDeleter<TestObject>); 
			ptr1 =  ptr2;
			poco_assert(ptr1.get() != 0);
			poco_assert(ptr2.get() != 0);
			poco_assert(TestObject::count() == 1);
		}
		poco_assert(TestObject::count() == 1);
	}
	poco_assert(TestObject::count() == 0);

}

int logFileCloser(FILE *fp)
{
	std::cout << "logFileCloser:: doing fclose" << std::endl;
	return fclose(fp);
}

struct logFileFunctorCloser
{
	int operator()(FILE *fp){
		std::cout << "logFileFunctorCloser:: doing fclose" << std::endl;
		return fclose(fp);
	}
};

void testCustomResource()
{

	std::cout << "\n-- test other resource --\n" ;

	char buf[256] = {"this is a test"};
	std::size_t n = 0;

	// fp is used to test fclose;
	FILE* fp = 0;

	// test other resource with raw function pointer
	{
		SharedPtr<FILE> p(fp = fopen("./a.txt", "wb"), fclose);
		poco_assert(p.get() != 0);
		n = fwrite(buf, sizeof(buf), 1, p.get());
		poco_assert(n == 1);
	}

	// read back must fail, since the file was closed.
	n = fread((void*)buf, sizeof(buf), 1, fp);
	poco_assert(n < 1);

	// test other resource with customized function pointer deleter
	{
		SharedPtr<FILE> p(fp = fopen("./a.txt", "wb"), logFileCloser);
		poco_assert(p.get() != 0);
		n = fwrite(buf, sizeof(buf), 1, p.get());
		poco_assert(n == 1);
	}

	// read back must fail, since the file was closed.
	n = fread((void*)buf, sizeof(buf), 1, fp);
	poco_assert(n < 1);

	// test other resource with customized functor deleter
	{
		SharedPtr<FILE> p(fp = fopen("./a.txt", "wb"), logFileFunctorCloser());
		poco_assert(p.get() != 0);
		n = fwrite(buf, sizeof(buf), 1, p.get());
		poco_assert(n == 1);
	}

	// read back must fail, since the file was closed.
	n = fread((void*)buf, sizeof(buf), 1, fp);
	poco_assert(n < 1);

}

void testRegression()
{

	SharedPtr<TestObject> ptr1;
	assert(ptr1.get() == 0);
	TestObject* pTO1 = new TestObject(1);
	TestObject* pTO2 = new TestObject(2);
	if (pTO2 < pTO1)
	{
		TestObject* pTmp = pTO1;
		pTO1 = pTO2;
		pTO2 = pTmp;
	}
	assert (pTO1 < pTO2);
	ptr1 = pTO1;
	SharedPtr<TestObject> ptr2 = pTO2;
	SharedPtr<TestObject> ptr3 = ptr1;
	SharedPtr<TestObject> ptr4;
	assert (ptr1.get() == pTO1);
	assert (ptr1 == pTO1);
	assert (ptr2.get() == pTO2);
	assert (ptr2 == pTO2);
	assert (ptr3.get() == pTO1);
	assert (ptr3 == pTO1);
	
	assert (ptr1 == pTO1);
	assert (ptr1 != pTO2);
	assert (ptr1 < pTO2);
	assert (ptr1 <= pTO2);
	assert (ptr2 > pTO1);
	assert (ptr2 >= pTO1);
	
	assert (ptr1 == ptr3);
	assert (ptr1 != ptr2);
	assert (ptr1 < ptr2);
	assert (ptr1 <= ptr2);
	assert (ptr2 > ptr1);
	assert (ptr2 >= ptr1);
	
	ptr1.swap(ptr2);
	assert (ptr2 < ptr1);
	ptr2.swap(ptr1);

	assert (ptr1->data() == 1 && ptr2->data() == 2 || ptr1->data() == 2 && ptr2->data() == 1);
	
	try
	{
		assert (ptr4->data() == 4);
		assert (!"must throw NullPointerException");
	}
	catch (NullPointerException&)
	{
	}
	
	assert (!(ptr4 == ptr1));
	assert (!(ptr4 == ptr2));
	assert (ptr4 != ptr1);
	assert (ptr4 != ptr2);
	
	ptr4 = ptr2;
	assert (ptr4 == ptr2);
	assert (!(ptr4 != ptr2));
	
	assert (TestObject::count() == 2);
	ptr1 = 0;
	ptr2 = 0;
	ptr3 = 0;
	ptr4 = 0;
	assert (TestObject::count() == 0);
	
	{
		SharedPtr<TestObject> ptr = new TestObject(0);
		assert (TestObject::count() == 1);
	}
	assert (TestObject::count() == 0);

	// test ImplicitCast
	{
		{
			// null assign test
			SharedPtr<DerivedObject> ptr2;
			assert(ptr2.get() == 0);
			SharedPtr<TestObject> ptr1 = ptr2;
		}
		{
			SharedPtr<DerivedObject> ptr2(new DerivedObject(666));
			assert (TestObject::count() == 1);
			SharedPtr<TestObject> ptr1 = ptr2;
			assert (TestObject::count() == 1);
		}
		assert (TestObject::count() == 0);
		SharedPtr<TestObject> ptr1 = new DerivedObject(666);
		assert (TestObject::count() == 1);
		ptr1 = 0;
		assert (TestObject::count() == 0);
	}

	// testExplicitCast()
	{
		SharedPtr<TestObject> ptr1 = new DerivedObject(666);
		SharedPtr<DerivedObject> ptr2 = ptr1.cast<DerivedObject>();
		assert (ptr2.get() != 0);

		// cast the other way round must fail
		ptr1 = new TestObject(0);
		assert (TestObject::count() == 2);
		ptr2 = ptr1.cast<DerivedObject>();
		assert (TestObject::count() == 1);
		assert (ptr2.get() == 0);
	}

}

void testVoid()
{
	{
		SharedPtr<void> ptr(new TestObject);
		assert(ptr.get() != 0);
		assert(TestObject::count() == 1);
	}
	assert(TestObject::count() == 0);
}

int main()
{

	testRegression();

	testVoid();

	testConstruction();

	testSwap();

	testCustomResource();

}
