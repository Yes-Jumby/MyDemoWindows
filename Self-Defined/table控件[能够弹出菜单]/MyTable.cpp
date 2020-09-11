#include <QMessageBox>
#include "MyTable.h"
#include "QtModelForPage.h"
#include "AlgPageParamImpl.h"
#include "QtModelForRegion.h"
CMyTable::CMyTable(QGroupBox *parent):
    QTableWidget(parent)
{
    m_pQtModelConnect = nullptr;
    popMenu = nullptr;
    actionDelete = nullptr;
    actionChange = nullptr;
}

CMyTable::~CMyTable()
{
    if(popMenu != nullptr)
    {
        delete popMenu;
        popMenu = nullptr;
    }
    if(actionDelete != nullptr)
    {
        delete actionDelete;
        actionDelete = nullptr;
    }
    if(actionChange != nullptr)
    {
        delete actionChange;
        actionChange = nullptr;
    }
}

void CMyTable::DeleteRegion()
{
    QMessageBox::information(0,"删除位置信息","删除位置！");
    int PageNo = m_pQtModelConnect->m_pQtModelForPage->GetSelectedPageNo();
//    bool flag = m_pQtModelConnect->GetAlgObject(PageNo).pAlgPageParam->DelAlgGroupObjById(currentRow());
//    if(flag)
//    {
//        m_pQtModelConnect->m_pQtModelForRegion->GetAlgModelList().clear();
//        m_pQtModelConnect->GetAlgObject(PageNo).pAlgPageParam->GetAlgInspGroupList(m_pQtModelConnect->m_pQtModelForRegion->GetAlgModelList());
//        m_pQtModelConnect->m_pQtModelForRegion->UpdateRegionTable();
//    }


}

void CMyTable::ChangeRegion()
{
    int a = currentRow();
    ARect rect;
    QMessageBox::information(0,"修改位置信息","修改位置！");
    int PageNo = m_pQtModelConnect->m_pQtModelForPage->GetSelectedPageNo();
//    bool flag = m_pQtModelConnect->GetAlgObject(PageNo).pAlgPageParam->EditeAlgGroupObjRectById(currentRow(),rect);
//    if(flag)
//    {
//        m_pQtModelConnect->m_pQtModelForRegion->GetAlgModelList().clear();
//        m_pQtModelConnect->GetAlgObject(PageNo).pAlgPageParam->GetAlgInspGroupList(m_pQtModelConnect->m_pQtModelForRegion->GetAlgModelList());
//        m_pQtModelConnect->m_pQtModelForRegion->UpdateRegionTable();
//    }
}

void CMyTable::CreateActions()
{
    //创建Action
    popMenu = new QMenu();
    actionDelete = new QAction(this);
    actionChange = new QAction(this);
    actionDelete->setText(QString("删除区域"));
    actionChange->setText(QString("修改区域"));
    connect(actionDelete, SIGNAL(triggered()), this, SLOT(DeleteRegion()));
    connect(actionChange, SIGNAL(triggered()), this, SLOT(ChangeRegion()));
}

void CMyTable::contextMenuEvent(QContextMenuEvent *event)
{
    popMenu->clear(); //清除原有菜单
    QPoint point = event->pos(); //得到窗口坐标
    QTableWidgetItem *item = itemAt(point);
    if(item != NULL)
    {
       QString a = item->text();
       //菜单出现的位置为当前鼠标的位置
       popMenu->addAction(actionDelete);
       popMenu->addSeparator();
       popMenu->addAction(actionChange);
       popMenu->exec(QCursor::pos());
       event->accept();

    }
}


