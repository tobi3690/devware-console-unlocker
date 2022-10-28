#include "ACL_Main.h"

int main()
{
	GeneralPurpose::SetConsoleAppInfo();
	KeyAuthApp.init();
	DrawConsoleUI::DrawLogin();
}