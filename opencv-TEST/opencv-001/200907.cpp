#include <string>
#include <fstream>
#include <iostream>
bool readToImage(std::string path,int size_ = 2560 * 832)
{
    // buffer
    char *pBuffer = new char[2560 * 832];
    //read
    std::string infilePath = path;
    int pos = infilePath.find(".");
    std::string outfilePath = infilePath.substr(0, pos) + ".png";

    std::ifstream mDataInput(path, std::ifstream::binary);
    if (!mDataInput.is_open())
    {
        std::cout << "read bin failed" << std::endl;
        return false;
    }

    //// get length of file:
    mDataInput.seekg(0, mDataInput.end);
    int length = mDataInput.tellg();
    mDataInput.seekg(0, mDataInput.beg);
    std::cout << "11" << std::endl;
    mDataInput.read((char*)&pBuffer, size_);
    std::cout << "12" << std::endl;
    mDataInput.close();
    std::cout << "13" << std::endl;
    return true;

}
int main200907()
{

    std::cout << readToImage("E://temp//200907//2//20.dat") << std::endl;

    return 0;
}