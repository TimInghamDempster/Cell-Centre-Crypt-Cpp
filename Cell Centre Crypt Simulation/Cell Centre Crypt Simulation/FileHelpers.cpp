
namespace Utils
{
	char* ReadBinaryFile(std::string filename, int& outFileLength, bool& outSuccess)
	{
		std::ifstream file;
		file.open(filename.c_str(), std::ios::binary);
		
		if(file.fail() || file.bad() || !file.good() || !file.is_open())
		{			
			//std::cerr << strerror(errno);
			outSuccess = false;
			outFileLength = 0;
			return new char[0];
		}

		// get length of file:
		file.seekg (0, file.end);
		outFileLength = (int)file.tellg();
		file.seekg (0, file.beg);

		// allocate memory:
		char * buffer = new char [outFileLength];

		// read data as a block:
		file.read (buffer,outFileLength);

		file.close();

		outSuccess = true;

		return buffer;
	}
}
