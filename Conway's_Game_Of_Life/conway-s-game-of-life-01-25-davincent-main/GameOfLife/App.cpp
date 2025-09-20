#include "App.h"
#include "MainWindow.h"



wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {

	

	// ++ This is done following the videos provided as they seem to be different from the original instructions ++
	MainWindow* window1 = new MainWindow();
	window1->Show();

	return true;
}