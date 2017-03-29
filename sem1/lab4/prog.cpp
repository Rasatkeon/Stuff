#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{	
	string wovels = "eyuioa";
	fstream file;

	file.open ("input", fstream::in);
	string buff;
	getline(file, buff);
	file.close();

	int i = 0;
	while (i < buff.size())
	{
		if (wovels.find(buff[i]) != -1)	buff.erase(buff.begin() + i);
		else i++;
	}

	file.open("input", fstream::out | fstream::trunc);
	file << buff;
	file.close();
	
	return 0;
}