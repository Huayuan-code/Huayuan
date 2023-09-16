#include "pch.h"
#include "CppUnitTest.h"
#include "../paperpass/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int ret;
			ret = lcs();
			Assert::AreEqual(0, ret);
		}
	};
}
