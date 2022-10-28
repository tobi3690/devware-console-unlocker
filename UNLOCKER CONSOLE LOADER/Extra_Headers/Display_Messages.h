#pragma once

namespace Message
{
	void Cout(const char* text)
	{
		std::cout << text << "\n\n";
	}

	void CoutColor(const char* text, int iColor)
	{
		SetConsoleTextAttribute(GlobalVars::hConsole, iColor);
		std::cout << text << "\n\n";
	}

	void CoutColorSoloSpace(const char* text, int iColor)
	{
		SetConsoleTextAttribute(GlobalVars::hConsole, iColor);
		std::cout << text;
	}

	void CoutColorInput(const char* text, int iColor)
	{
		SetConsoleTextAttribute(GlobalVars::hConsole, iColor);
		std::cout << text;
	}

	void Space()
	{
		std::cout << "\n";
	}
}

namespace Console
{
	void Clear()
	{
		system("cls");
	}
}