// SubtitleUpdater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

//c:\temp\The.Thundermans.S01E01.Adventures.in.Supersitting.WEBRip.NF.en.srt
//5

static long long int secs;

void addSecondsAndFormat(std::string str, int start, int count, char* resBuf)
{
	std::string temp = str.substr(start, count);
	struct tm tm = { 0 };
	//1
	//char extra[10] = ",799";
	//tm.tm_hour = 12;
	//tm.tm_min = 32;
	//tm.tm_sec = 34;
	//tm.tm_year = 2006 - 1900; //2006 - 05 - 19
	//tm.tm_mon = 5 - 1;
	//tm.tm_mday = 19;
	
	//2
	char extra[10];
	sscanf(temp.c_str(), "%02d:%02d:%02d%4s", &tm.tm_hour, &tm.tm_min, &tm.tm_sec, &extra);
	tm.tm_year = 2006 - 1900; //2006 - 05 - 19
	tm.tm_mon = 5 - 1;
	tm.tm_mday = 19;

	const time_t resPeriod = mktime(&tm) + secs;
	//char buf[128];
	strftime(resBuf, 128, "%H:%M:%S", std::localtime(&resPeriod));
	strcat(resBuf, extra);
}

int main()
{
	std::string path;

	std::cout << "Hello, pidor :}\n";
	std::cout << "Please enter full path to srt file: ";
	std::getline(std::cin, path);

	unsigned int indStartFileName = path.rfind("\\") + 1;
	std::string newFileName = path.substr(indStartFileName, path.length() - indStartFileName);
	std::ifstream srcFile(path);
	std::ofstream newFile(newFileName);


	std::cout << "Now enter seconds to add (+5) or substract (-5) from subtitles path: ";
	std::cin >> secs;

	std::string line;
	while (std::getline(srcFile, line))
	{
		//std::cout << line << '\n';
		if (line.find("-->") != std::string::npos)
		{
			char fstline[128];
			char sndline[128];
			addSecondsAndFormat(line, 0, 12, fstline);
			addSecondsAndFormat(line, 17, 12, sndline);
			newFile << fstline << " --> " << sndline << '\n';
		}
		else
		{
			newFile << line.c_str() << '\n';
		}

	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
