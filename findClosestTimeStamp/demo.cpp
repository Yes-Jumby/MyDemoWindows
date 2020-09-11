#include <QList>
#include <QVector>
#include <QDebug>
int binarySearchKey1(QList<int> list,int goal,int len)
{
    int left = 0,right = 0;
    for(right = len - 1; right -left>1;)
    {
        int midIndex = (right + left)/2;
        int mid = (right - left);

        int midValue = list.at(midIndex);
        qDebug()<<midIndex<<" midIndex";
        if(goal == midValue)
        {
            return midIndex;
        }
        if(goal > midValue)
        {
            left = midIndex+1;
        }
        else
        {
            right = midIndex-1;
        }
        if(mid <= 1)
        {
            break;
        }
    }
    int rightnum = list.at(right);
    int leftnum = list.at(left);
    return abs((rightnum - leftnum)/2) > abs(rightnum -goal) ? rightnum : leftnum;
}
int main111()
{
    QList<int> listIMUTimeStamp;
    listIMUTimeStamp.append(1);
    listIMUTimeStamp.append(2);
    listIMUTimeStamp.append(3);
    listIMUTimeStamp.append(6);
    listIMUTimeStamp.append(7);
    qDebug()<<binarySearchKey1(listIMUTimeStamp,4,listIMUTimeStamp.size());
    return 0;
}
