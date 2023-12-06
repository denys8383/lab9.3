#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.3/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Office offices[MAX_OFFICES];
			int officeCount = 1;
			offices[0].addEmployee("123456789", "Doe");
			Employee foundEmployee;
			int result = findEmployeeByPhoneNumber(offices, officeCount, "123456789", foundEmployee);
			Assert::AreEqual(1, result);
		}
	};
}
