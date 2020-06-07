#ifndef LL1_H
#define LL1_H

#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>
#include<set>
#include"QFile"
#include"QTextCodec"
#include"token.h"
#include<stack>
#include<QDir>
#include<ActiveQt/QAxObject>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
using namespace std;
bool start=false;
set<string> Not_terminal_symbol;
map<string, map<string,int> > llTable;
bool judgeTerminalVocabulary(string str)
{
    if(str == "ID" || str == "INTC" || judgeSingleClassify(str) ||
        judgeArrayBoundary(str) || judgeDoubleClassify(str) || judgeReserved(str))
    {
        return true;
    }
    else return false;
}

struct Rule
{
    string left;
    vector<string> right;
    vector<string> Predict;
};

vector<Rule> Grammar;
map<string, set<string> > First;
map<string, set<string> > Follow;


string  trim(string s) {

    if (s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;

}

string remove_surplus_spaces(const string& s)
{
    string src = "";
    src=trim(s);
    string result = "";
    for (int i = 0; src[i] != '\0'; i++)
    {
        if (src[i] != ' ')
        {
            result.append(1, src[i]);

        }
        else
        {
            if (src[i + 1] != ' ')
                result.append(1, src[i]);
        }
    }
    return result;
}

void readGrammar(){
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString path=QDir::currentPath();
    path=path+"/wenfa.txt";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))return;
    string left;string right;
    while(!file.atEnd()){
        //读取一行文本数据
        struct Rule cRule;
        QByteArray line = file.readLine();
        QString str = codec->toUnicode(line);
        string temp_str=str.toStdString();
        for (int i = 0; i < temp_str.length(); i++)//将所有的字符串中的制表符\t转换为空格
            if (temp_str[i] == '\t'||temp_str[i] == '\n')temp_str=temp_str.replace(i, 1, " ");
        int split=temp_str.find("::=");
        if(split!=-1){
            left=temp_str.substr(0, split);
            right = temp_str.substr(split + 3, temp_str.length());
            split = left.find(")");
            left = left.substr(1 + split, left.length());//去掉括号及左侧
            left =remove_surplus_spaces(left);//规范化与格式化
            right = remove_surplus_spaces(right);
            cRule.left = left;//产生式左部
        }else{
            cRule.left = left;
            split = temp_str.find("|");
            right = temp_str.substr(split + 1, 9999);
            right = remove_surplus_spaces(right);
        }
        int kind=0;
        int loc1=0;
        int loc2=0;
        for(int i=0;i<right.length();i++,loc2++){
            if ((right[i] <= 'Z'&&right[i] >= 'A') || (right[i] <= 'z'&&right[i] >= 'a')){//是否是英文{
                if (kind != 0){
                    string x = right.substr(loc1, loc2 - loc1);//计算前一个应该保存的字母
                    if (!x.empty())cRule.right.push_back(x);//放入结构体
                    loc1 = i;
                    loc2 = i;
                    kind = 0;
                }
                else continue;
            }
            else {
                if (kind != 1){
                    string x = right.substr(loc1, loc2 - loc1);
                    if (!x.empty())cRule.right.push_back(x);
                    if (right[i] == '\0' || right[i] == 32)//是空格或空字符，应该无视他，直接跳过
                    {
                        loc1 = i + 1;
                        loc2 = i;
                        kind = 3;
                    }else{
                        loc1 = i;
                        loc2 = i;
                        kind = 1;
                    }
                    continue;
                }else if (right[i] == '\0' || right[i] == 32)//遇到有空格，应该将字母末尾设置为空格前一字符的位置，所以z-1
                {
                    loc2--;
                    kind = 3;
                }
                continue;
            }
        }
        string x1 = right.substr(loc1, 999);//对到末尾的字母进行处理
        if (!x1.empty())
            cRule.right.push_back(x1);
        Grammar.push_back(cRule);
    }
    file.close();
}

void calculateFirst(){
    for(int i=0;i<Grammar.size();i++){
        if(!judgeTerminalVocabulary(Grammar[i].left)&&Not_terminal_symbol.find(Grammar[i].left) == Not_terminal_symbol.end()){
            Not_terminal_symbol.insert(Grammar[i].left);
        }
        for(int j=0;j<Grammar[i].right.size();j++){
            if(!judgeTerminalVocabulary(Grammar[i].right[j])&&Not_terminal_symbol.find(Grammar[i].right[j]) == Not_terminal_symbol.end()){
                Not_terminal_symbol.insert(Grammar[i].right[j]);
            }
        }
    }
    for(auto i:Not_terminal_symbol){
        set<string> temp;
        First[i]=temp;
    }
    bool change_flag=true;
    while(change_flag){
        change_flag=false;
        for(int i=0;i<Grammar.size();i++){
            for(int j=0;j<Grammar[i].right.size();j++){
                string first_right=Grammar[i].right[j];
                if(judgeTerminalVocabulary(first_right)&&First[Grammar[i].left].find(first_right) != First[Grammar[i].left].end()){
                    break;
                }
                if(judgeTerminalVocabulary(first_right)&&First[Grammar[i].left].find(first_right) == First[Grammar[i].left].end()){
                    First[Grammar[i].left].insert(first_right);
                    change_flag=true;
                    break;
                }
                if(!judgeTerminalVocabulary(first_right)){
                    for(auto k:First[first_right]){
                        if(k!="@"&&First[Grammar[i].left].find(k)==First[Grammar[i].left].end()){
                            First[Grammar[i].left].insert(k);
                            change_flag=true;
                        }
                    }
                    if(First[first_right].find("@")==First[first_right].end())break;
                    if(j==Grammar[i].right.size()-1&&First[first_right].find("@")!=First[first_right].end()){
                        if(First[Grammar[i].left].find("@")==First[Grammar[i].left].end()){
                            First[Grammar[i].left].insert("@");
                            change_flag=true;
                        }
                    }
                }
            }
        }
    }
}

void calculateFollow(){
    string start = Grammar[0].left;
    for(auto i:First){
        set<string> temp;
        Follow[i.first]=temp;
    }
    Follow[start].insert("#");
    bool change_flag=true;
    while(change_flag){
        change_flag=false;
        for(int i=0;i<Grammar.size();i++){
            for(int j=0;j<Grammar[i].right.size();j++){
                int temp=j;
                if(!judgeTerminalVocabulary(Grammar[i].right[j])){
                    string temp_f=Grammar[i].right[j];
                    j++;
                    if(j==Grammar[i].right.size()){
                        for(auto k:Follow[Grammar[i].left]){
                            if(Follow[temp_f].find(k)==Follow[temp_f].end()){
                                Follow[temp_f].insert(k);
                                change_flag=true;
                            }
                        }
                    }else{
                       while(j<Grammar[i].right.size()){
                           if(judgeTerminalVocabulary(Grammar[i].right[j])){
                               if(Follow[temp_f].find(Grammar[i].right[j])==Follow[temp_f].end()){
                                    Follow[temp_f].insert(Grammar[i].right[j]);
                                    change_flag=true;
                               }
                               break;
                           }else{
                               if(First[Grammar[i].right[j]].find("@")==First[Grammar[i].right[j]].end()){
                                   for(auto k:First[Grammar[i].right[j]]){
                                       if(Follow[temp_f].find(k)==Follow[temp_f].end()){
                                           Follow[temp_f].insert(k);
                                           change_flag=true;
                                       }
                                   }
                                   break;
                               }else{
                                   for(auto k:First[Grammar[i].right[j]]){
                                       if(k!="@"&&Follow[temp_f].find(k)==Follow[temp_f].end()){
                                           Follow[temp_f].insert(k);
                                           change_flag=true;
                                       }
                                   }
                                   if(j==Grammar[i].right.size()-1){
                                       for(auto k:Follow[Grammar[i].left]){
                                           if(Follow[temp_f].find(k)==Follow[temp_f].end()){
                                               Follow[temp_f].insert(k);
                                               change_flag=true;
                                           }
                                       }
                                       break;
                                   }
                               }
                           }
                           j++;
                       }
                    }
                }
                j=temp;
            }
        }
    }
}
void calculatePredict(){
    for(int i=0;i<Grammar.size();i++){
        for(int j=0;j<Grammar[i].right.size();j++){
            if(Grammar[i].right[j]=="@"){
                for(auto h:Follow[Grammar[i].left]){
                    vector<string>::iterator it = find(Grammar[i].Predict.begin(), Grammar[i].Predict.end(), h);
                    if(it==Grammar[i].Predict.end()){
                        Grammar[i].Predict.push_back(h);
                    }
                }
                break;
            }
            if(judgeTerminalVocabulary(Grammar[i].right[j])){
                vector<string>::iterator it = find(Grammar[i].Predict.begin(), Grammar[i].Predict.end(), Grammar[i].right[j]);
                if(it==Grammar[i].Predict.end()){
                    Grammar[i].Predict.push_back(Grammar[i].right[j]);
                }
            }
            if(First[Grammar[i].right[j]].find("@")==First[Grammar[i].right[j]].end()){
                for(auto k:First[Grammar[i].right[j]]){
                    vector<string>::iterator it = find(Grammar[i].Predict.begin(), Grammar[i].Predict.end(), k);
                    if(it==Grammar[i].Predict.end()){
                        Grammar[i].Predict.push_back(k);
                    }
                }
                break;
            }else{
                for(auto k:First[Grammar[i].right[j]]){
                    if(k!="@"){
                        vector<string>::iterator it = find(Grammar[i].Predict.begin(), Grammar[i].Predict.end(), k);
                        if(it==Grammar[i].Predict.end()){
                            Grammar[i].Predict.push_back(k);
                        }
                    }
                }
                if(j==Grammar[i].right.size()-1){
                    for(auto h:Follow[Grammar[i].left]){
                        vector<string>::iterator it = find(Grammar[i].Predict.begin(), Grammar[i].Predict.end(), h);
                        if(it==Grammar[i].Predict.end()){
                            Grammar[i].Predict.push_back(h);
                        }
                    }
                }
            }
        }
    }
}
void createLLtable(){
    for(int i=0;i<Grammar.size();i++){
        for(int j=0;j<Grammar[i].Predict.size();j++){
            llTable[Grammar[i].left][Grammar[i].Predict[j]]=i;
        }
    }
    llTable["ProcDecPart"]["PROCEDURE"]=39;
}
void showFirst(){
    if(start==false){
        readGrammar();
        calculateFirst();
        calculateFollow();
        calculatePredict();
        createLLtable();
        start=true;
    }
    string s;
    QStandardItemModel* model = new QStandardItemModel();
    QStringList temp;
    QTableView *tableView = new QTableView;
    model->setHorizontalHeaderLabels({QString::fromLocal8Bit("终极符"),
                                      QString::fromLocal8Bit("First集")});
    int loc=0;
    for(auto i:Not_terminal_symbol){
        s=i;
        model->setItem(loc,0,new QStandardItem(QString::fromStdString(s)));
        s="";
        for(auto j:First[i]){
            s=s+j+" ";
        }
        model->setItem(loc,1,new QStandardItem(QString::fromStdString(s)));
        s="";
        loc++;
    }
    tableView->setModel(model);
    tableView->setColumnWidth(0,500);
    tableView->setColumnWidth(1,1000);
    tableView->setWindowTitle(QString::fromLocal8Bit("First集"));
    tableView->showMaximized();
}
void showFollow(){
    if(start==false){
        readGrammar();
        calculateFirst();
        calculateFollow();
        calculatePredict();
        createLLtable();
        start=true;
    }
    string s;
    QStandardItemModel* model = new QStandardItemModel();
    QStringList temp;
    QTableView *tableView = new QTableView;
    model->setHorizontalHeaderLabels({QString::fromLocal8Bit("终极符"),
                                      QString::fromLocal8Bit("Follow集")});
    int loc=0;
    for(auto i:Not_terminal_symbol){
        s=i;
        model->setItem(loc,0,new QStandardItem(QString::fromStdString(s)));
        s="";
        for(auto j:Follow[i]){
            s=s+j+" ";
        }
        model->setItem(loc,1,new QStandardItem(QString::fromStdString(s)));
        s="";
        loc++;
    }
    tableView->setModel(model);
    tableView->setColumnWidth(0,500);
    tableView->setColumnWidth(1,1000);
    tableView->setWindowTitle(QString::fromLocal8Bit("Follow集"));
    tableView->showMaximized();
}
void showPredict(){
    if(start==false){
        readGrammar();
        calculateFirst();
        calculateFollow();
        calculatePredict();
        createLLtable();
        start=true;
    }
    string s;
    QStandardItemModel* model = new QStandardItemModel();
    QStringList temp;
    QTableView *tableView = new QTableView;
    model->setHorizontalHeaderLabels({QString::fromLocal8Bit("产生式"),
                                      QString::fromLocal8Bit("Predict集")});
    int i=0;
    for(auto c:Grammar){
        s=s+c.left+"->";
        for(auto e:c.right){
            s=s+e;
        }
        model->setItem(i,0,new QStandardItem(QString::fromStdString(s)));
        s="";
        for(auto d:c.Predict){
            s=s+d+" ";
        }
        model->setItem(i,1,new QStandardItem(QString::fromStdString(s)));
        s="";
        i++;
    }
    tableView->setModel(model);
    tableView->setColumnWidth(0,1000);
    tableView->setColumnWidth(1,1000);
    tableView->setWindowTitle(QString::fromLocal8Bit("Predict集"));
    tableView->showMaximized();
}
void showLLtable(){
    if(start==false){
        readGrammar();
        calculateFirst();
        calculateFollow();
        calculatePredict();
        createLLtable();
        start=true;
    }
    string s;
    set<QString> temp;
    QStandardItemModel* model = new QStandardItemModel();
    QTableView *tableView = new QTableView;
    for(auto c:llTable){
        for(auto d:c.second){
            string s=d.first;
            temp.insert(QString::fromStdString(s));
        }
    }
    QStringList templist;
    templist.push_back("");
    for(auto c:temp){
        templist.push_back(c);
    }
    model->setHorizontalHeaderLabels(templist);
    int row=0;
    for(auto c:llTable){
        string s1=c.first;
        model->setItem(row,0,new QStandardItem(QString::fromStdString(s1)));
        for(auto d:c.second){
            string s=d.first;
            int tempint=d.second;
            model->setItem(row,templist.indexOf(QString::fromStdString(s)),new QStandardItem(QString::number(tempint+1)));
        }
        row++;
    }
    tableView->setModel(model);
    row=0;
    for(auto c:templist){
        tableView->setColumnWidth(row,110);
        row++;
    }
    tableView->setWindowTitle(QString::fromLocal8Bit("LL1分析表"));
    tableView->showMaximized();
}
void LLanylis(){
    if(start==false){
        readGrammar();
        calculateFirst();
        calculateFollow();
        calculatePredict();
        createLLtable();
        start=true;
    }
}
#endif // LL1_H
