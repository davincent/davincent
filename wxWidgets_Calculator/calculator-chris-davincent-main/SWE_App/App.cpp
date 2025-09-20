#include "App.h"
#include "MainWindow.h"
#include "ButtonFactory.h"


wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {

	window = new MainWindow();
	window->Show();
	return true;
}