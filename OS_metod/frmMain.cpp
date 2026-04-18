#include "SemantorMain.h"

using namespace OSmetod;
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main() {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    frmMain frmmain;

    Application::Run(% frmmain);

}
