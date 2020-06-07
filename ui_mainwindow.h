/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFirst;
    QAction *actionFollow;
    QAction *actionPredict;
    QAction *GramTable;
    QAction *Lexical;
    QAction *Grammar;
    QAction *actionsave;
    QAction *actionopen;
    QAction *actionsaveas;
    QAction *actionabout111;
    QAction *actionabout;
    QAction *actionyuyi;
    QAction *actioninter;
    QAction *actionobj;
    QAction *actionchangliang;
    QAction *actiongonggong;
    QAction *actionxunhuan;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableView *tableView_lex;
    QTabWidget *tabWidget;
    QWidget *tab;
    QTextEdit *textEdit_ErrorWin;
    QWidget *tab_3;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QTableView *tableView_inter;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QTableView *tableView_obj;
    QWidget *tab_2;
    QTextEdit *textEdit_ConsoleWin;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuLL_1;
    QMenu *menu_3;
    QMenu *menu_5;
    QMenu *menu_4;
    QMenu *menu_6;
    QMenu *menu_7;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1040, 710);
        MainWindow->setMaximumSize(QSize(1222, 16777215));
        actionFirst = new QAction(MainWindow);
        actionFirst->setObjectName(QString::fromUtf8("actionFirst"));
        actionFollow = new QAction(MainWindow);
        actionFollow->setObjectName(QString::fromUtf8("actionFollow"));
        actionPredict = new QAction(MainWindow);
        actionPredict->setObjectName(QString::fromUtf8("actionPredict"));
        GramTable = new QAction(MainWindow);
        GramTable->setObjectName(QString::fromUtf8("GramTable"));
        Lexical = new QAction(MainWindow);
        Lexical->setObjectName(QString::fromUtf8("Lexical"));
        Grammar = new QAction(MainWindow);
        Grammar->setObjectName(QString::fromUtf8("Grammar"));
        actionsave = new QAction(MainWindow);
        actionsave->setObjectName(QString::fromUtf8("actionsave"));
        actionopen = new QAction(MainWindow);
        actionopen->setObjectName(QString::fromUtf8("actionopen"));
        actionsaveas = new QAction(MainWindow);
        actionsaveas->setObjectName(QString::fromUtf8("actionsaveas"));
        actionabout111 = new QAction(MainWindow);
        actionabout111->setObjectName(QString::fromUtf8("actionabout111"));
        actionabout = new QAction(MainWindow);
        actionabout->setObjectName(QString::fromUtf8("actionabout"));
        actionyuyi = new QAction(MainWindow);
        actionyuyi->setObjectName(QString::fromUtf8("actionyuyi"));
        actioninter = new QAction(MainWindow);
        actioninter->setObjectName(QString::fromUtf8("actioninter"));
        actionobj = new QAction(MainWindow);
        actionobj->setObjectName(QString::fromUtf8("actionobj"));
        actionchangliang = new QAction(MainWindow);
        actionchangliang->setObjectName(QString::fromUtf8("actionchangliang"));
        actiongonggong = new QAction(MainWindow);
        actiongonggong->setObjectName(QString::fromUtf8("actiongonggong"));
        actionxunhuan = new QAction(MainWindow);
        actionxunhuan->setObjectName(QString::fromUtf8("actionxunhuan"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout->addWidget(textEdit);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        tableView_lex = new QTableView(centralwidget);
        tableView_lex->setObjectName(QString::fromUtf8("tableView_lex"));

        verticalLayout_2->addWidget(tableView_lex);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::South);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        textEdit_ErrorWin = new QTextEdit(tab);
        textEdit_ErrorWin->setObjectName(QString::fromUtf8("textEdit_ErrorWin"));
        textEdit_ErrorWin->setGeometry(QRect(0, 0, 1011, 221));
        textEdit_ErrorWin->setReadOnly(true);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayoutWidget = new QWidget(tab_3);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1011, 221));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_4->addWidget(label_2);

        tableView_inter = new QTableView(horizontalLayoutWidget);
        tableView_inter->setObjectName(QString::fromUtf8("tableView_inter"));

        verticalLayout_4->addWidget(tableView_inter);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        tableView_obj = new QTableView(horizontalLayoutWidget);
        tableView_obj->setObjectName(QString::fromUtf8("tableView_obj"));

        verticalLayout_3->addWidget(tableView_obj);


        horizontalLayout_2->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        textEdit_ConsoleWin = new QTextEdit(tab_2);
        textEdit_ConsoleWin->setObjectName(QString::fromUtf8("textEdit_ConsoleWin"));
        textEdit_ConsoleWin->setGeometry(QRect(0, 0, 1011, 221));
        textEdit_ConsoleWin->setLayoutDirection(Qt::LeftToRight);
        textEdit_ConsoleWin->setReadOnly(true);
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 2);

        gridLayout->addLayout(verticalLayout, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1040, 26));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuLL_1 = new QMenu(menu_2);
        menuLL_1->setObjectName(QString::fromUtf8("menuLL_1"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_5 = new QMenu(menubar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        menu_6 = new QMenu(menu_4);
        menu_6->setObjectName(QString::fromUtf8("menu_6"));
        menu_7 = new QMenu(menu_4);
        menu_7->setObjectName(QString::fromUtf8("menu_7"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_4->menuAction());
        menubar->addAction(menu_5->menuAction());
        menu->addAction(Lexical);
        menu_2->addAction(Grammar);
        menu_2->addAction(GramTable);
        menu_2->addAction(menuLL_1->menuAction());
        menuLL_1->addAction(actionFirst);
        menuLL_1->addAction(actionFollow);
        menuLL_1->addAction(actionPredict);
        menu_3->addAction(actionopen);
        menu_3->addAction(actionsave);
        menu_3->addAction(actionsaveas);
        menu_5->addAction(actionabout);
        menu_4->addAction(actionyuyi);
        menu_4->addAction(menu_6->menuAction());
        menu_4->addAction(menu_7->menuAction());
        menu_6->addAction(actioninter);
        menu_6->addAction(actionobj);
        menu_7->addAction(actionchangliang);
        menu_7->addAction(actiongonggong);
        menu_7->addAction(actionxunhuan);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionFirst->setText(QCoreApplication::translate("MainWindow", "First\351\233\206", nullptr));
        actionFollow->setText(QCoreApplication::translate("MainWindow", "Follow\351\233\206", nullptr));
        actionPredict->setText(QCoreApplication::translate("MainWindow", "Predict\351\233\206", nullptr));
        GramTable->setText(QCoreApplication::translate("MainWindow", "LL(1)\350\257\255\346\263\225\345\210\206\346\236\220\350\241\250", nullptr));
        Lexical->setText(QCoreApplication::translate("MainWindow", "\350\257\215\346\263\225\345\210\206\346\236\220", nullptr));
        Grammar->setText(QCoreApplication::translate("MainWindow", "LL(1)\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        actionsave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
        actionopen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200...", nullptr));
        actionsaveas->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272...", nullptr));
        actionabout111->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216...", nullptr));
        actionabout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216...", nullptr));
        actionyuyi->setText(QCoreApplication::translate("MainWindow", "\350\257\255\344\271\211\345\210\206\346\236\220", nullptr));
        actioninter->setText(QCoreApplication::translate("MainWindow", "\344\270\255\351\227\264\344\273\243\347\240\201\347\224\237\346\210\220", nullptr));
        actionobj->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\344\273\243\347\240\201\347\224\237\346\210\220", nullptr));
        actionchangliang->setText(QCoreApplication::translate("MainWindow", "\345\270\270\351\207\217\350\241\250\350\276\276\345\274\217\344\274\230\345\214\226", nullptr));
        actiongonggong->setText(QCoreApplication::translate("MainWindow", "\345\205\254\345\205\261\350\241\250\350\276\276\345\274\217\344\274\230\345\214\226", nullptr));
        actionxunhuan->setText(QCoreApplication::translate("MainWindow", "\345\276\252\347\216\257\344\270\215\345\217\230\345\274\217\345\244\226\346\217\220", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "lexical analysis table:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Error Message", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "intermedicate code:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "object code:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Codes Table", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Console", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\257\215\346\263\225\345\210\206\346\236\220", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        menuLL_1->setTitle(QCoreApplication::translate("MainWindow", "LL(1)\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\350\257\255\344\271\211\345\210\206\346\236\220", nullptr));
        menu_6->setTitle(QCoreApplication::translate("MainWindow", "\344\270\255\351\227\264\344\273\243\347\240\201\347\224\237\346\210\220", nullptr));
        menu_7->setTitle(QCoreApplication::translate("MainWindow", "\344\270\255\351\227\264\344\273\243\347\240\201\344\274\230\345\214\226", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
