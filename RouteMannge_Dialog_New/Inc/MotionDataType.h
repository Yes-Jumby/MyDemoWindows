#ifndef MOTIONDATATYPE_H
#define MOTIONDATATYPE_H
#pragma execution_character_set("utf-8")
/******************************************基本数据结构*******************************/
typedef struct
{
    long px;
    long py;
} My2DCompareData;

typedef struct
{
    short encx;
    short ency;
    short source;
    short outputType;
    short startLevel;
    short time;
    short maxerr;
    short threshold;
} My2DComparePrm;


#endif // ALGDATATYPE_H
