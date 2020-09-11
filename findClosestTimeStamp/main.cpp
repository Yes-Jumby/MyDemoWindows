#include <QList>
#include <QVector>
#include <QDebug>
int binarySearchKey(QList<int> list,int goal,int &startIndex,int len)
{
    if(len <1)
    {
        return -1;
    }
    if(list.constLast()<=goal)
    {
        startIndex = len-1;
        return list.constLast();
    }
    if(list.constFirst()>=goal)
    {
        startIndex = 0;
        return list.constFirst();
    }
    qDebug()<<" binarySearchKey";
    int left = startIndex,right = 0;
    for(right = len - 1; right-left>1;)
    {
        int midIndex = (right + left)/2;
        //int mid = (right - left);

        int midValue = list.at(midIndex);
        qDebug()<<midIndex<<" midIndex";
        if(goal == midValue)
        {
            startIndex = midIndex;
            return midValue;
        }
        if(goal > midValue)
        {
            left = midIndex;
        }
        else
        {
            right = midIndex;
        }
//        if(mid <= 1)
//        {
//            break;
//        }
    }
    int rightnum = list.at(right);
    int leftnum = list.at(left);
    if(abs((rightnum - leftnum)/2) > abs(rightnum -goal))
    {
        startIndex = right;
        return rightnum;
    }
    else
    {
        startIndex = left;
        return leftnum;
    }
//    if(rightnum>goal && leftnum<goal)
//    {
//        return abs((rightnum - leftnum)/2) > abs(rightnum -goal) ? rightnum : leftnum;
//    }
////    if(rightnum<=goal)
////    {
////        return rightnum;
////    }
////    if(leftnum>=goal)
////    {
////        return leftnum;
////    }

}
int main()
{
    int u = 0;
    while(u<10)
    {
        u++;
        qDebug()<<u;//4
    }
    qDebug()<<"int size:"<<sizeof(int);//4
    qDebug()<<"long size:"<<sizeof(long);//4
    qDebug()<<"long int size:"<<sizeof(long int);//4
    QVector<int> vecProfiles;
    vecProfiles.push_back(10);
    vecProfiles.push_back(100);
    vecProfiles.push_back(300);
    vecProfiles.push_back(1000);

    QList<int> listIMUTimeStamp;
    QList<int> listIMUTimeReduced;
    listIMUTimeStamp.append(9);
    listIMUTimeStamp.append(19);
    listIMUTimeStamp.append(29);
    listIMUTimeStamp.append(39);
    listIMUTimeStamp.append(99);
    listIMUTimeStamp.append(101);
    listIMUTimeStamp.append(500);
    listIMUTimeStamp.append(999);
    listIMUTimeStamp.append(1001);
    listIMUTimeStamp.append(9999);
    listIMUTimeStamp.append(10500);
    qDebug()<<"vector size:"<<vecProfiles.size();
    qDebug()<<"list size:"<<listIMUTimeStamp.size();
    int startIndex =0;
    for(int i = 0;i < vecProfiles.size();i++)
    {
        //listIMUTimeReduced.push_back(binarySearchKey(listIMUTimeStamp,vecProfiles.at(i),listIMUTimeStamp.size()));
        qDebug()<<binarySearchKey(listIMUTimeStamp,vecProfiles.at(i),startIndex,listIMUTimeStamp.size());
        qDebug()<<"startIndex:"<<startIndex;
    }
    listIMUTimeStamp = listIMUTimeReduced;
    return 0;


    int temp,index;
    index = 0;
    bool needinit = true;
    for(int i = 0;i < vecProfiles.size();i++)
    {
        for(int j = index;j < listIMUTimeStamp.size();j++)
        {
            if(needinit)
            {
                temp = abs(vecProfiles.at(i)-listIMUTimeStamp.at(j));
                needinit=false;
            }
            else
            {
                if(abs(vecProfiles.at(i)-listIMUTimeStamp.at(j))>temp)
                {
                    if(j-1>=0)
                    {
                        listIMUTimeReduced.append(listIMUTimeStamp.at(j-1));
                        index = j;
                    }
                    else
                    {
                        listIMUTimeReduced.append(listIMUTimeStamp.at(0));
                        index = 0;
                    }
                    needinit = true;
                    qDebug()<<"index:"<<index;
                    break;
                }
                else
                {
                    temp = abs(vecProfiles.at(i)-listIMUTimeStamp.at(j));
                }
            }
        }
    }
    for(int i = 0;i < listIMUTimeReduced.size();i++)
    {
        qDebug()<<listIMUTimeReduced.at(i);
    }
    return 0;
}
