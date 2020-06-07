#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DFS.h"
#include "token.h"
#include "LL1.h"
#include "QFileDialog"
#include <iostream>
#include<ActiveQt/QAxObject>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QCloseEvent>
#include "Error.h"
#include "target.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FILE_EXIST=false;
    FILE_CHANGE=false;
    setFixedSize(this->width(),this->height());



    connect(ui->actionsave,SIGNAL(triggered()),this,SLOT(observer_save()));
    connect(ui->actionsaveas,SIGNAL(triggered()),this,SLOT(observer_saveas()));
    connect(ui->actionopen,SIGNAL(triggered()),this,SLOT(observer_open()));
    connect(ui->actionabout,SIGNAL(triggered()),this,SLOT(observer_about()));
    connect(ui->actionyuyi,SIGNAL(triggered()),this,SLOT(observer_yuyi()));


    connect(ui->actionFirst,SIGNAL(triggered()),this,SLOT(observer_first()));
    connect(ui->actionFollow,SIGNAL(triggered()),this,SLOT(observer_follow()));
    connect(ui->actionPredict,SIGNAL(triggered()),this,SLOT(observer_predict()));

    connect(ui->GramTable,SIGNAL(triggered()),this,SLOT(observer_gramtable()));
    connect(ui->Lexical,SIGNAL(triggered()),this,SLOT(observer_lex()));
    connect(ui->Grammar,SIGNAL(triggered()),this,SLOT(observer_grammar()));

    connect(ui->actiongonggong,SIGNAL(triggered()),this,SLOT(observer_gonggong()));
    connect(ui->actionchangliang,SIGNAL(triggered()),this,SLOT(observer_const()));
    connect(ui->actionxunhuan,SIGNAL(triggered()),this,SLOT(observer_xunhuan()));
    connect(ui->actionobj,SIGNAL(triggered()),this,SLOT(observer_objcode()));
    connect(ui->actioninter,SIGNAL(triggered()),this,SLOT(observer_intercode()));

    QStringList temp;

    model->setHorizontalHeaderLabels({//QString::fromLocal8Bit("序号"),
                                      QString::fromLocal8Bit("类型"),
                                      QString::fromLocal8Bit("单词")});
    ui->tableView_lex->setModel(model);

    intercodeModel->setHorizontalHeaderLabels({QString::fromLocal8Bit("操作符"),
                                               QString::fromLocal8Bit("左操作数"),
                                               QString::fromLocal8Bit("右操作数"),
                                              QString::fromLocal8Bit("ID")});
    ui->tableView_inter->setModel(intercodeModel);

    objcodeModel->setHorizontalHeaderLabels({QString::fromLocal8Bit("操作符"),
                                               QString::fromLocal8Bit("左操作数"),
                                               QString::fromLocal8Bit("右操作数")});
    ui->tableView_obj->setModel(objcodeModel);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(FILE_CHANGE)
    {
        switch(QMessageBox::information(this,tr(QString::fromLocal8Bit("文件未保存").toStdString().c_str()),tr(QString::fromLocal8Bit("当前文件未保存，是否要保存文件？").toStdString().c_str()),tr(QString::fromLocal8Bit("是").toStdString().c_str()),tr(QString::fromLocal8Bit("否").toStdString().c_str()),0,1))
        {
        case 0:{
            observer_save();
            if(FILE_CHANGE)
            {
                event->ignore();
            }

            //if()
            break;
        }
        case 1:{
            break;
        }
        default:event->ignore();
        }
    }

}

QStandardItemModel* interCodeModel(vector<DFS::SiYuanStyle*> sy)
{
    QStandardItemModel* sm=new QStandardItemModel();
    sm->setHorizontalHeaderLabels({QString::fromLocal8Bit("操作符"),
                                               QString::fromLocal8Bit("左操作数"),
                                               QString::fromLocal8Bit("右操作数"),
                                              QString::fromLocal8Bit("ID")});
    int j=0;
    for(auto i:sy)
    {
        sm->setItem(j,0,new QStandardItem(QString::fromStdString(i->operation)));
        sm->setItem(j,1,new QStandardItem(QString::fromStdString(i->left)));
        sm->setItem(j,2,new QStandardItem(QString::fromStdString(i->right)));
        sm->setItem(j,3,new QStandardItem(QString::fromStdString(i->id)));
        j++;
    }
    return sm;
}
QStandardItemModel* objectCodeModel(vector<DFS::SiYuanStyle*> sy)
{
    target::Translation(sy);
    QStandardItemModel* sm=new QStandardItemModel();
    sm->setHorizontalHeaderLabels({QString::fromLocal8Bit("操作符"),
                                               QString::fromLocal8Bit("左操作数"),
                                               QString::fromLocal8Bit("右操作数")});
    int j=0;
    for(auto i:target::TargetCode)
    {
        sm->setItem(j,0,new QStandardItem(QString::fromStdString(i->op)));
        sm->setItem(j,1,new QStandardItem(QString::fromStdString(i->str1)));
        sm->setItem(j,2,new QStandardItem(QString::fromStdString(i->str2)));

        j++;
    }
    return sm;
}
void MainWindow::observer_objcode()
{
    if(grammar_cr())
    {
        ui->tableView_obj->setModel(objectCodeModel(DFS::SiYuan));
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  目标代码生成已完成，结果输出在 Codes Table\n"));
    }

}
void MainWindow::observer_intercode()
{
    if(grammar_cr())
    {
        ui->tableView_inter->setModel(interCodeModel(DFS::SiYuan));
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  中间代码生成已完成，结果输出在 Codes Table\n"));
    }

}
void MainWindow::observer_gonggong()
{
    if(grammar_cr())
    {
        DFS::GongGongYouHua();
        ui->tableView_inter->setModel(interCodeModel(DFS::GGYH_res));
        ui->tableView_obj->setModel(objectCodeModel(DFS::GGYH_res));
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  公共表达式优化完成，结果输出在 Codes Table\n"));
    }

}
void MainWindow::observer_const()
{
    if(grammar_cr())
    {
        DFS::ChangLiangYouHua();
        ui->tableView_inter->setModel(interCodeModel(DFS::CLYH_res));
        ui->tableView_obj->setModel(objectCodeModel(DFS::CLYH_res));
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  常量表达式优化完成，结果输出在 Codes Table\n"));
    }

}
void MainWindow::observer_xunhuan()
{
    if(grammar_cr())
    {
        DFS::XunHuanYouHua();
        ui->tableView_inter->setModel(interCodeModel(DFS::XHYH_res));
        ui->tableView_obj->setModel(objectCodeModel(DFS::XHYH_res));
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  循环不变式外提完成，结果输出在 Codes Table\n"));
    }

}

bool MainWindow::observer_yuyi()
{
    if(grammar_cr())
    {
        DiguiSpace::root=NULL;
        DiguiSpace::Loc=0;
        string all=ui->textEdit->toPlainText().toStdString();
            vector<string> words=word_segmentation(all);
            createTokenList(words);
            DiguiSpace::Program();
            DFS::DFS_all(DiguiSpace::root);

            if(SemErrorList->empty())
            {
                ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  语义分析正确\n"));
            }
            while(!SemErrorList->empty())
            {
                SemanticErrorPoint sp=SemErrorList->front();
                SemErrorList->pop_front();
                ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+sp.E_Mess);
            }
    }
    else {
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+QString::fromLocal8Bit("::  语法分析过程有错误，无法进行语义分析\n"));
        return false;
    }
    return true;

}
void MainWindow::observer_about()
{
    QMessageBox::information(NULL,QString::fromLocal8Bit("产品信息"),
                             QString::fromLocal8Bit("\n名称：SNL编译器\n作者：夏睿 张诗珧 施季中   \n版本：20200525\n"),
                             QMessageBox::Ok);
}

void MainWindow::observer_open()
{
    QString filepath;
    QFileDialog* filedialog=new QFileDialog(this);
    filedialog->setWindowTitle(QString::fromLocal8Bit("选择文件"));
    filedialog->setNameFilter("*.txt");
    filedialog->setViewMode(QFileDialog::Detail);


    if(filedialog->exec()==QDialog::Accepted)
        filepath=filedialog->selectedFiles()[0];

    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string name = code->fromUnicode(filepath).data();

    qDebug(filepath.toStdString().c_str());
    FILE* fp;

    if((fp=fopen(name.c_str(),"r+"))==NULL)
    {
        qDebug("open_file_failed\n");
    }
    else {
        qDebug("open_file_success\n");
        FILE_EXIST=true;
        FILE_PATH=filepath;
        char ch;
        /*QString string;
        while ((ch=fgetc(fp))!=EOF) {
            //fputc(ch,)
            string+=ch;
        }*/
        QFile file(FILE_PATH);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        QString strAll=codec->toUnicode(file.readAll());
        ui->textEdit->setText(strAll);
        fclose(fp);
    }


}
void MainWindow::saveas()
{
    QString path=QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("文件另存为"),"../filename",tr("(*.txt)"));
    qDebug(path.toStdString().c_str());

    if(path!="")
    {
        QFile *savefile=new QFile(path);
        savefile->open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text);
        savefile->write(ui->textEdit->toPlainText().toStdString().c_str());
        savefile->close();
        FILE_EXIST=true;
        FILE_CHANGE=false;
        qDebug("FILE_NOT_CHANGE");
        FILE_PATH=path;
    }
    else {
        qDebug("cancel save");
    }
}
void MainWindow::observer_saveas()
{
    saveas();
}
void MainWindow::observer_save()
{
    FILE* fp;
    if(FILE_EXIST==true)
    {
        if((fp=fopen(FILE_PATH.toStdString().c_str(),"w+"))==NULL)
        {
            qDebug("save_open_file_failed\n");
        }
        else {
            qDebug("save_open_file_success\n");
            FILE_CHANGE=false;
            qDebug("FILE_NOT_CHANGE");
            fprintf(fp,"%s",ui->textEdit->toPlainText().toStdString().c_str());
            fclose(fp);

        }
    }
    else
    {
        saveas();
    }
}

void MainWindow::observer_lex()
{
    qDebug("lex");
    QString strTxtEdt = ui->textEdit->toPlainText();
    vector<string> words=word_segmentation(strTxtEdt.toStdString());
    bool flag = createTokenList(words);
    if(!flag){
        QString s=QString::fromLocal8Bit("::  词法分析错误，错误的单词是")+QString::fromStdString(wrong)+QString::fromLocal8Bit("\n");
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
       ui->tableView_lex->setModel(model);


    }else{
        QString s=QString::fromLocal8Bit("::  词法分析成功\n");

       ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);

       ui->tableView_lex->setModel(showTokenList());
    }

}
bool MainWindow::observer_grammar()
{
    qDebug("grammar");
    QString strTxtEdt = ui->textEdit->toPlainText();
    vector<string> words=word_segmentation(strTxtEdt.toStdString());
    bool flag = createTokenList(words);
    if(!flag){
        QString s=QString::fromLocal8Bit("::  语法分析错误，错误的单词是")+QString::fromStdString(wrong)+QString::fromLocal8Bit("\n");
        ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
        return false;
    }else{
       LLanylis();
       string start=Grammar[0].left;
       QStringList h;
       h.push_back(QString::fromLocal8Bit("分析栈"));
       h.push_back(QString::fromLocal8Bit("输入流"));
       h.push_back(QString::fromLocal8Bit("矩阵元素"));
       QStandardItemModel* model = new QStandardItemModel();
       QStringList temp;
       QTableView *tableView = new QTableView;
       model->setHorizontalHeaderLabels(h);

       vector<string> analysStack;
       analysStack.push_back("#");
       analysStack.push_back(start);
       tokenList.push_back(Token(3,"#"));
       int row=0;
       for(int i=0;i<tokenList.size();i++){
           string res="";
           for(int j=0;j<analysStack.size();j++){
               res=res+analysStack[j];
           }
           model->setItem(row,0,new QStandardItem(QString::fromStdString(res)));
           res="";
           for(int j=i;j<tokenList.size();j++)
           {
               res=res+tokenList[j].str;
           }
           model->setItem(row,1,new QStandardItem(QString::fromStdString(res)));

           string inputWord = tokenList[i].str;
           if(tokenList[i].type==8) inputWord="CHAR";
           else if(tokenList[i].type==1) inputWord="ID";
           else if(tokenList[i].type==2) inputWord="INTC";
           string x = analysStack[analysStack.size()-1];
           analysStack.pop_back();
           //x属于非终极符的情形
           if(inputWord == "#" && x=="#")
           {
               //匹配结束
               res="Success";
               model->setItem(row,2,new QStandardItem(QString::fromStdString(res)));
               tableView->setModel(model);
               tableView->setColumnWidth(0,1500);
               tableView->setColumnWidth(1,4000);
               tableView->setColumnWidth(2,500);
               tableView->setWindowTitle(QString::fromLocal8Bit("语法分析过程"));
               tableView->showMaximized();
               QString s=QString::fromLocal8Bit("::  语法分析成功\n");
               ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
               return true;
           }
           else if(!judgeTerminalVocabulary(x))
           {
               if(llTable.find(x) != llTable.end())
               {
                   if(llTable[x].find(inputWord)!=llTable[x].end())
                   {
                       vector<string> ruleRight;

                       res="["+QString::number(llTable[x][inputWord]+1).toStdString()+"]";
                       model->setItem(row,2,new QStandardItem(QString::fromStdString(res)));
                       ruleRight = Grammar[llTable[x][inputWord]].right;
                       row++;
                       for(int j=ruleRight.size()-1;j>=0;j--)
                       {
                           if(ruleRight[j]!="@") analysStack.push_back(ruleRight[j]);
                       }
                       i--; //输入字符不变
                   }
                   else
                   {
                       QString reason = ErrorMap[x];
                       res="Error";
                       model->setItem(row,2,new QStandardItem(QString::fromStdString(res)));
                       tableView->setModel(model);
                       tableView->setColumnWidth(0,1500);
                       tableView->setColumnWidth(1,4000);
                       tableView->setColumnWidth(2,500);
                       tableView->setWindowTitle(QString::fromLocal8Bit("语法分析过程"));
                       tableView->showMaximized();
                       QString s=QString::fromLocal8Bit("::  语法分析错误，原因为：")+reason+QString::fromLocal8Bit("\n");
                       ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);

                       return false;
                   }
               }
               else
               {
                   res="Error";
                   model->setItem(row,2,new QStandardItem(QString::fromStdString(res)));
                   tableView->setModel(model);
                   tableView->setColumnWidth(0,1500);
                   tableView->setColumnWidth(1,4000);
                   tableView->setColumnWidth(2,500);
                   tableView->setWindowTitle(QString::fromLocal8Bit("语法分析过程"));
                   tableView->showMaximized();
                   QString s=QString::fromLocal8Bit("::  语法分析成功\n");
                   ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
                   return true;
               }

           }
           //x属于终极符
           else{
               //匹配错误
               if(x != inputWord)
               {
                   res="Error";
                   model->setItem(row,2,new QStandardItem(QString::fromStdString(res)));
                   tableView->setModel(model);
                   tableView->setColumnWidth(0,1500);
                   tableView->setColumnWidth(1,4000);
                   tableView->setColumnWidth(2,500);
                   tableView->setWindowTitle(QString::fromLocal8Bit("语法分析过程"));
                   tableView->showMaximized();
                   QString s=QString::fromLocal8Bit("::  语法分析错误，原因为：终极符")+QString::fromStdString(x)+QString::fromLocal8Bit("与输入")+
                           QString::fromStdString(inputWord)+QString::fromLocal8Bit("不匹配\n");
                   ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);


                   return false;
               }
               res="Match";
               model->setItem(row,2,new QStandardItem(QString::fromStdString(res)));
               row++;
           }
       }
       return true;
    }

}
bool MainWindow::grammar_cr()
{
    QString strTxtEdt = ui->textEdit->toPlainText();
    vector<string> words=word_segmentation(strTxtEdt.toStdString());
    bool flag = createTokenList(words);
    if(!flag){
        return false;
    }else{
       LLanylis();
       string start=Grammar[0].left;
       vector<string> analysStack;
       analysStack.push_back("#");
       analysStack.push_back(start);
       tokenList.push_back(Token(3,"#"));
       int row=0;
       for(int i=0;i<tokenList.size();i++){
           string res="";
           for(int j=0;j<analysStack.size();j++){
               res=res+analysStack[j];
           }
           res="";
           for(int j=i;j<tokenList.size();j++)
           {
               res=res+tokenList[j].str;
           }
           string inputWord = tokenList[i].str;
           if(tokenList[i].type==8) inputWord="CHAR";
           else if(tokenList[i].type==1) inputWord="ID";
           else if(tokenList[i].type==2) inputWord="INTC";
           string x = analysStack[analysStack.size()-1];
           analysStack.pop_back();
           //x属于非终极符的情形
           if(inputWord == "#" && x=="#")
           {
               //匹配结束
               return true;
           }
           else if(!judgeTerminalVocabulary(x))
           {
               if(llTable.find(x) != llTable.end())
               {
                   if(llTable[x].find(inputWord)!=llTable[x].end())
                   {
                       vector<string> ruleRight;

                       res="["+QString::number(llTable[x][inputWord]+1).toStdString()+"]";
                       ruleRight = Grammar[llTable[x][inputWord]].right;
                       row++;
                       for(int j=ruleRight.size()-1;j>=0;j--)
                       {
                           if(ruleRight[j]!="@") analysStack.push_back(ruleRight[j]);
                       }
                       i--; //输入字符不变
                   }
                   else
                   {
                       QString reason = ErrorMap[x];

                       return false;
                   }
               }
               else
               {
                   return true;
               }
           }
           //x属于终极符
           else{
               //匹配错误
               if(x != inputWord)
               {
                   return false;
               }
           }
       }
       return true;
    }
}

void MainWindow::observer_gramtable()
{
    QString s=QString::fromLocal8Bit("::  显示LL(1)语法分析表成功\n");
    ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
    showLLtable();
}
void MainWindow::observer_first()
{
    qDebug("first");
    QString s=QString::fromLocal8Bit("::  显示First集成功\n");
    ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
    showFirst();
}
void MainWindow::observer_follow()
{
    qDebug("follow");
    QString s=QString::fromLocal8Bit("::  显示Follow集成功\n");
    ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
    showFollow();
}
void MainWindow::observer_predict()
{
    qDebug("predict");
    QString s=QString::fromLocal8Bit("::  显示Predict集成功\n");
    ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
    showPredict();
}

void MainWindow::on_textEdit_textChanged()
{
    FILE_CHANGE=true;
    qDebug("FILE_CHANGE");
}
