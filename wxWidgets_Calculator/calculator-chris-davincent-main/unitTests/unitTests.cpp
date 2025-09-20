#include "../SWE_App/ButtonFactory.h"
#include "../SWE_App/ProcessorSingleton.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unitTests
{
	TEST_CLASS(unitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(true, true);
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("1 + 1"), "2");
		}
	};
}
