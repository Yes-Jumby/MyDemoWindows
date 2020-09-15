#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "cloud.h"
#include "SpendTime.h"
using namespace std;
class CReadAndWriteDat{
public:
    CReadAndWriteDat(void){}
    ~CReadAndWriteDat(void){}
    //new version
    bool writeToCloudfast(const std::string &path, int size_);
    bool writeToCloudslow(const std::string &path, int size_);
    bool readbinToCloud(const std::string &path);
    bool readbinToCloud1(const std::string &path);
    void writebin(const std::string & path,const Cloud3D &cloud,void *pbuffer3D,void *pbuffer2D);

    //old version
    bool transformToCloudWin(const std::string & inpath);
    bool transformToCloudLinux(const std::string & inpath);
private:
    CSpendTime m_SpendTime;
};
