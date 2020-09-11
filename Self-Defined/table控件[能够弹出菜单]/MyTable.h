/*
* Copyright (c) 2018, 博众精工北京技术研究院
* All rights reserved.
*
* 文件名称： 智能建模软件算法部分
* 文件标识： 见配置管理计划书
* 摘要： 简要描述本文件的内容
*
* 当前版本： 1.0
* 作者： 李朋辉
* 完成日期： 2018年10月26日
*/

#ifndef MYTABEL_H
#define MYTABEL_H
#include <QObject>
#include <QWidget>
#include <QTableWidget>

#include <QContextMenuEvent>//加菜单
#include <QMenu>
#include <QAction>

#include <QGroupBox>
#include "QtModelConnect.h"

#pragma execution_character_set("utf-8")
class CMyTable : public QTableWidget
{
    Q_OBJECT
public:
    CMyTable(QGroupBox *parent);
    ~CMyTable();
    void CreateActions();

    CQtModelConnect *m_pQtModelConnect;

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;//给table加菜单，故添加到QTableWidget的重写之中

private slots:
    void DeleteRegion();
    void ChangeRegion();

private:
    QMenu *popMenu;
    QAction *actionDelete;
    QAction *actionChange;
};

#endif // MYLABEL_H
