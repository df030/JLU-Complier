#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    bool FILE_CHANGE;
    bool FILE_EXIST;
    QString FILE_PATH;
    QStandardItemModel* model = new QStandardItemModel();
    QStandardItemModel* intercodeModel=new QStandardItemModel();
    QStandardItemModel* objcodeModel=new QStandardItemModel();


private:
    Ui::MainWindow *ui;

private:
    void saveas();
    bool grammar_cr();
    void closeEvent(QCloseEvent *event);
private slots:
    void observer_lex();
    bool observer_grammar();
    void observer_gramtable();
    void observer_first();
    void observer_follow();
    void observer_predict();
    void observer_open();
    void observer_save();
    void observer_saveas();
    void observer_about();
    bool observer_yuyi();
    void observer_intercode();
    void observer_objcode();
    void observer_const();
    void observer_gonggong();
    void observer_xunhuan();


    void on_textEdit_textChanged();
};
#endif // MAINWINDOW_H
