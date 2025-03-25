#include "Loading.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args){
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    BoyApp::Loading loadingForm;
    Application::Run(% loadingForm);

    return 0;
}