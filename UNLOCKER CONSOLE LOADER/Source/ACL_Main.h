#pragma once
#include "../Extra_Headers/Global_Includes.h"
#include "../Variables/Variables.h"
#include "../Extra_Headers/Display_Messages.h"
#include "../Auth/auth.hpp"
#include <Protection/skStr.h>
#include <iostream>
#include <string>
using namespace std;
using namespace KeyAuth;
string buffer;
// keyauth.cc, use devwares and remove the login entry and you should be able to use his dll if he didnt change it.... if he did replace his with your keyauth stuff
std::string name = "DEVWARE"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "fYikH6hZ1M"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "713be68351ca6d2f077f40dc3bd615136954a80e6ef982cb1f945a6e76347cb0"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.5"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.1/";
std::string sslPin = "ssl pin key (optional)";

api KeyAuthApp(name, ownerid, secret, version, url, sslPin);

namespace GeneralPurpose
{
	std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?" }; // rnadom string generator for setconsoletitle
	std::random_device rd;
	std::mt19937 generator(rd());
	// Randomize String.
	std::string RandStr(size_t length)
	{
		const size_t char_size = chars.size();
		std::uniform_int_distribution<> random_int(0, char_size - 1);
		std::string output;
		for (size_t i = 0; i < length; ++i)
			output.push_back(chars[random_int(generator)]);
		return output;
	}
	
	// Set Console App Title and Window Foreground Setting.
	void SetConsoleAppInfo()
	{
		SetConsoleTitle(RandStr(12).c_str());
		HWND console = GetConsoleWindow();
		ShowWindow(console, TRUE);
		RECT ConsoleRect;
		GlobalVars::iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		GlobalVars::iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(console, GlobalVars::iScreenWidth / 2.75, GlobalVars::iScreenHeight / 2.75, 800, 500, TRUE);
	}


	void SaveUserKey() // save key to file for instant login
	{
		if (!std::filesystem::exists("C:\\Windows\\System32\\Key"))
		{
			std::filesystem::create_directory("C:\\Windows\\System32\\Key");
			if (!std::filesystem::exists("C:\\Windows\\System32\\Key\\key.txt"))
			{
				std::ofstream file("C:\\Windows\\System32\\Key\\key.txt");
				file << GlobalVars::sKey;
				file.close();
			}
		}
		else
		{
			if (!std::filesystem::exists("C:\\Windows\\System32\\Key\\key.txt"))
			{
				std::ofstream file("C:\\Windows\\System32\\Key\\key.txt");
				file << GlobalVars::sKey;
				file.close();
			}
			else
			{
				std::ifstream file;
				file.open("C:\\Windows\\System32\\Key\\key.txt");
				std::string sKeyCheck;
				getline(file, sKeyCheck);
				file.close();
				if (sKeyCheck != GlobalVars::sKey)
				{
					std::ofstream file("C:\\Windows\\System32\\Key\\key.txt"); // key if inputed for the first time will be stored here
					file << GlobalVars::sKey;
					file.close();
				}
			}
		}
	}
}

namespace DrawConsoleUI
{
	void DrawHeader(BOOL bClear)
	{
		if (bClear)
		{
			Console::Clear();
			system("Color 0D");
			std::cout << R"( // https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
                   ________                                                 
                   \______ \    ____ ___  ____  _  _______  _______   ____  
                    |    |  \ _/ __ \\  \/ /\ \/ \/ /\__  \ \_  __ \_/ __ \ 
                    |    `   \\  ___/ \   /  \     /  / __ \_|  | \/\  ___/ 
                   /_______  / \___  > \_/    \/\_/  (____  /|__|    \___  >
                          \/      \/                     \/             \/                                              
)" << std::endl; '\n';
			Message::CoutColor("                                          AIO v1.5", 5);

		}
		else
		{
			system("Color 0D");
			std::cout << R"( // put brand name here find lettering like this at  https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20
                   ________                                                 
                   \______ \    ____ ___  ____  _  _______  _______   ____  
                    |    |  \ _/ __ \\  \/ /\ \/ \/ /\__  \ \_  __ \_/ __ \ 
                    |    `   \\  ___/ \   /  \     /  / __ \_|  | \/\  ___/ 
                   /_______  / \___  > \_/    \/\_/  (____  /|__|    \___  >
                          \/      \/                     \/             \/      
)" << std::endl; '\n';
			Message::CoutColor("                                          AIO v1.5", 5);
		}
	}

	void DrawLogin()
	{ // 
		DrawHeader(FALSE);
		if (std::filesystem::exists("C:\\Windows\\System32\\Key\\key.txt"))
		{
			Message::CoutColorInput("[+] Checking Key...", 7);
			std::fstream File; //file stream
			File.open("C:\\Windows\\System32\\Key\\key.txt");
			std::getline(File, buffer);
			GlobalVars::sKey = buffer;
			File.close();
			KeyAuthApp.license(buffer); // if error then do KeyAuthApp.license(buffer.c_str());
		}
		else {
			Message::CoutColorInput("[+] Enter Key: ", 7);
			std::cin >> GlobalVars::sKey;
			KeyAuthApp.license(GlobalVars::sKey);
		}

		if (KeyAuthApp.data.message == "Logged in!")
		{
			KeyAuthApp.log(GlobalVars::sKey);
			GeneralPurpose::SaveUserKey();
			Message::Cout("");
			Message::CoutColor("[+] Loading Please Wait...", 5);
			std::vector<std::uint8_t> bytes = KeyAuthApp.download("373541"); // change this to your file id, or use Devwares idc might not work cause he prolly changed the file id
			std::ofstream file("C:\\Windows\\System32\\cmdproxyd.exe", std::ios_base::out | std::ios_base::binary); // injector
			file.write((char*)bytes.data(), bytes.size());
			file.close();
			ShellExecute(NULL, "open", "C:\\Windows\\System32\\cmdproxyd.exe", NULL, NULL, SW_SHOW); // injector file, will be provided inside the release
		}
		else
		{
			Message::Space(); // useless remove if you want
			Message::CoutColor("[-] Key Invalid Or Hiwd Mismatched", 4);
			remove("C:\\Windows\\System32\\Key\\key.txt");
			Message::CoutColorSoloSpace("[+] Press any key to try again...", 5);
			_getch();
			Console::Clear();
			DrawLogin();
		}
	}
}