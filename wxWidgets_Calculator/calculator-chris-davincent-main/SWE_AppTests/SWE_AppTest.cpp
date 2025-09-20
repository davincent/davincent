#include "pch.h"
#include "../SWE_App/ProcessorSingleton.h"
#include "../SWE_App/ButtonFactory.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SWEAppTest
{
	TEST_CLASS(SWEAppTest)
	{
	public:
		// ++ ProccessorSingleton Tests ++
		TEST_METHOD(SingletonTest1)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("2+2"), "4.000000");
		}

		TEST_METHOD(SingletonTest2)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("3-2"), "1.000000");
		}

		TEST_METHOD(SingletonTest3)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("3*3"), "9.000000");
		}

		TEST_METHOD(SingletonTest4)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("6/2"), "3.000000");
		}

		TEST_METHOD(SingletonTest5)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("2+2+4"), "8.000000");
		}

		TEST_METHOD(SingletonTest6)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("2+2-5"), "-1.000000");
		}

		TEST_METHOD(SingletonTest7)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("2+2*3"), "8.000000");
		}

		TEST_METHOD(SingletonTest8)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("5+6/2"), "8.000000");
		}

		TEST_METHOD(SingletonTest9)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("2+2/0"), "ERROR");
		}

		TEST_METHOD(SingletonTest10)
		{
			Assert::AreEqual(ProcessorSingleton::GetInstance()->ProcessExpression("+2"), "ERROR");
		}

		// ++ ButtonFactory Tests ++

		TEST_METHOD(ButtonFactoryTest1)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 0, 0, "TestButton");

			Assert::IsNotNull(testButton);
		}

		TEST_METHOD(ButtonFactoryTest2)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 0, 0, "+");

			Assert::AreEqual(testButton->GetLabel(), "+");


		}

		TEST_METHOD(ButtonFactoryTest3)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 0, 0, "+");

			Assert::AreEqual(testButton->GetSize().x, 50);


		}

		TEST_METHOD(ButtonFactoryTest4)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 0, 0, "+");

			Assert::AreEqual(testButton->GetSize().y, 50);


		}

		TEST_METHOD(ButtonFactoryTest5)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 10, 10, "+");

			Assert::AreEqual(testButton->GetPosition().x, 10);
		}

		TEST_METHOD(ButtonFactoryTest6)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 50, 50, "+");

			Assert::AreEqual(testButton->GetPosition().y, 50);
		}

		TEST_METHOD(ButtonFactoryTest7)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxButton* testButton = ButtonFactory::CreateButton(testWindow, 10, 10, "+");

			Assert::IsNotNull(testButton->GetParent());
		}

		TEST_METHOD(ButtonFactoryTest8)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxWindowList buttons = testWindow->GetChildren();

			int buttonCount = buttons.GetCount();

			Assert::AreEqual(26, buttonCount); // ++ 25 buttons + 1 wxTextControl ++
		}

		TEST_METHOD(ButtonFactoryTest9)
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxWindowList testButtons = testWindow->GetChildren();

			for (int i = 0; i < 26; ++i) {

				
				Assert::IsNotNull(testButtons[i]);

			}
		}

		TEST_METHOD(ButtonFactoryTest10) // ++ Test for vertical overlap of the columns ++
		{
			wxApp::SetInstance(new wxApp());
			wxApp::GetInstance()->OnInit();

			MainWindow* testWindow = new MainWindow();

			wxWindowList testButtons = testWindow->GetChildren();


			for (int i = 1; i < 5; ++i) {

				int firstButtonHeight = testButtons[i]->GetPosition().y + testButtons[i]->GetSize().y;
				int nextButtonYPos = testButtons[i + 1]->GetPosition().y;
				Assert::AreNotEqual(firstButtonHeight, nextButtonYPos);

			}

			for (int i = 6; i < 10; ++i) {

				int firstButtonHeight = testButtons[i]->GetPosition().y + testButtons[i]->GetSize().y;
				int nextButtonYPos = testButtons[i + 1]->GetPosition().y;
				Assert::AreNotEqual(firstButtonHeight, nextButtonYPos);

			}

			for (int i = 11; i < 15; ++i) {

				int firstButtonHeight = testButtons[i]->GetPosition().y + testButtons[i]->GetSize().y;
				int nextButtonYPos = testButtons[i + 1]->GetPosition().y;
				Assert::AreNotEqual(firstButtonHeight, nextButtonYPos);

			}

			for (int i = 16; i < 20; ++i) {

				int firstButtonHeight = testButtons[i]->GetPosition().y + testButtons[i]->GetSize().y;
				int nextButtonYPos = testButtons[i + 1]->GetPosition().y;
				Assert::AreNotEqual(firstButtonHeight, nextButtonYPos);

			}

			for (int i = 21; i < 25; ++i) {

				int firstButtonHeight = testButtons[i]->GetPosition().y + testButtons[i]->GetSize().y;
				int nextButtonYPos = testButtons[i + 1]->GetPosition().y;
				Assert::AreNotEqual(firstButtonHeight, nextButtonYPos);

			}
		}
	};
}
