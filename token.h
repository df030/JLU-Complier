#ifndef TOKEN_H
#define TOKEN_H
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include "QString"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include<ActiveQt/QAxObject>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
using namespace std;
struct Token
{
    int type;
    string str;
    Token(int _type, string _str):type(_type),str(_str){}
};
vector<Token> tokenList;
string wrong;

//判断是否是无符号整数
bool judgeInteger(string test)
{
    for (unsigned long long i = 0; i < test.size(); i++)
    {
        if (test[i] <= '9' && test[i] >= '0')
        {
            continue;
        }
        else return false;
    }
    return true;
}
//判断是否是单字符分界符
bool judgeSingleClassify(string str)
{
    //@表示空
    if(str == "+" || str == "-" || str == "*" ||str == "/"
            || str == "(" || str == ")" || str == "[" ||
            str == "]" || str == ";" || str == "." || str == "<" ||
            str == "=" || str == "@" || str == "EOF" || str == ",")
    {
        return true;
    }
    else return false;
}

//判断是否是双字符分界符
bool judgeDoubleClassify(string str)
{
    if(str == ":=") return true;
    else return false;
}

//判断是否是注释符头符号
bool judgeBeginNote(string str)
{
    if(str == "{") return true;
    else return false;
}

//判断是否是注释符结束符号
bool judgeEndNote(string str)
{
    if(str == "}") return true;
    else return false;
}

//判断是否是字符标示符
bool judgeCharMark(string str)
{
    char startChar = *str.begin();
    char endChar = *(str.end()-1);
    if(startChar == '\'' && endChar == '\'') return true;
    else return false;
}

//判断是否是数组下标界限符
bool judgeArrayBoundary(string str)
{
    if(str == "..") return true;
    else return false;
}

//判断是否是标识符
bool judgeIdentifier(string str)
{
    bool judge_flag = true;
    //判断是否属于字母
    if((str[0]>=65 && str[0]<=90) || (str[0]>=97 && str[0]<=122))
    {
        judge_flag = true;
    }
    else
    {
        judge_flag = false;
        return judge_flag;
    }
    for(unsigned long long i=1;i < str.length();i++)
    {
        //判断是否属于字母或数字
        if((str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122))
        {
            judge_flag = true;
        }
        else
        {
            judge_flag = false;
            break;
        }
    }
    return judge_flag;
}

//判断是否是保留字
bool judgeReserved(string str)
{
    if(str == "PROGRAM" || str == "PROCEDURE" || str == "TYPE" || str == "VAR" ||
            str == "IF" || str == "THEN" || str == "ELSE" || str == "FI" ||
            str == "WHILE" || str == "DO" || str == "ENDWH" || str == "BEGIN" ||
            str == "END" || str == "READ" || str == "WRITE" || str == "ARRAY" ||
            str == "OF" || str == "RECORD" || str == "RETURN" || str == "INTEGER" ||
            str == "CHAR" )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Token序列创建函数
bool createTokenList(vector<string> words)
{
    tokenList.clear();
    bool flag = true;
    for(unsigned long long i=0;i<words.size();i++)
    {
        string s=words[i];

        if(judgeReserved(s))
        {
            tokenList.push_back(Token(7,s));
        }else if(judgeArrayBoundary(s)){
            tokenList.push_back(Token(6,s));
        }else if(judgeCharMark(s)){
            //string tt= "\'";
            //tokenList.push_back(Token(5,tt));
            s = s.substr(1,s.length()-2);
            //cout<<temp<<endl;
            tokenList.push_back(Token(8,s));
            //tokenList.push_back(Token(5,tt));
        }else if(judgeDoubleClassify(s)){
            tokenList.push_back(Token(4,s));
        }else if(judgeSingleClassify(s)){
            tokenList.push_back(Token(3,s));
        }else if(judgeInteger(s))
        {
            tokenList.push_back(Token(2,s));
        }else if(judgeIdentifier(s))
        {
            tokenList.push_back(Token(1,s));
        }else{
            wrong = s;
            flag = false;
            break;
        }
    }

    return flag;
}

vector<string> word_segmentation(string strFile)  //按分界符分词，放到vector<string> words中
{
    char lastch='\0',ch='\0';        //前一个字符缓存和当前字符记录
    string s;
    vector<string> words;
    int mode=-1;
    unsigned long long Loc=0;

    while(Loc<=strFile.length())
    {
        if(lastch=='\0')
        {
            if(Loc>=strFile.length())
                break;
            ch=strFile[Loc];
            Loc++;
        }
        else
        {
            ch=lastch;
        }
        lastch='\0';
        if(ch=='}')
            break;
        else if(ch=='\n'||ch=='\t'||ch==' ')
            continue;
        else if(ch=='{')           //mode =0 ::注释
        {
            mode=0;
        }
        else if(ch=='\'')          //mode =1 ::字符
        {
            mode =1;
        }
        else if(ch != '{' && ch != '\'' &&
                ch != '+' && ch != '-'  && ch != '*'  && ch != '/' &&
                ch != '<'  && ch != '>'  && ch != '(' && ch != ')'  && ch != '['  && ch != ']' &&
                ch != ';'  && ch != '='  &&ch!=','&&
                ch != ':' && ch != '.'  )            //mode =2 ::普通按空格分词
        {
            mode =2;
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'
                ||ch=='('||ch==')'||ch=='['||ch==']'||ch=='<'||ch=='>'
                ||ch==','||ch=='='||ch==';')           //mode =3 ::普通分界符
        {
            mode=3;
        }
        else if(ch==':')          //mode =4 ::特殊分界符:=
        {
            mode=4;
        }
        else if(ch=='.')          //mode =4 ::特殊分界符.和..
        {
            mode =5;
        }


        switch(mode)
        {
        case 0: do
            {
                if(Loc>=strFile.length())break;
                ch=strFile[Loc];
                Loc++;
            }while(ch!='}');
            break;          //注释在分词时被抛弃

        case 1:  s = "\'";

            do
            {
                if(Loc>=strFile.length())break;
                ch=strFile[Loc];
                s += ch;
                Loc++;
            }while(ch!='\'');
            words.push_back(s);
            break;
        case 2:
            s = ch;
            while(true)
            {
                //if(Loc>=strFile.length())break;
                ch=strFile[Loc];
                Loc++;
                if(ch == '+' || ch == '-'  || ch == '*'  ||
                        ch == '/' || ch == '<'  || ch == '>'  ||
                        ch == '(' || ch == ')'  || ch == '['  ||
                        ch == ']' || ch == ';'  ||ch == '='   ||
                        ch == '.' || ch == ':'  || ch == ',')
                {
                    lastch = ch;
                    break;
                }
                if(ch == ' ' || ch == '\n' || ch == '\t')
                {
                    break;
                }
                s += ch;
            }

            words.push_back(s);
            break;

        case 3:
            s = ch;
            words.push_back(s);
            break;

        case 4:
            s = ch;
            if(Loc<strFile.length())
            {
                ch=strFile[Loc];
                Loc++;
                if(ch == '=')
                {
                    s += ch;
                }
                if(ch != '=')
                {
                  lastch = ch;   //为防止已经读进ch的字符丢失,将其保存在lastch中
                }
            }
            words.push_back(s);
            break;

        case 5:      //再读一次,如果还是.的话,说明是..分界符,否则为.分界符
            if(Loc==strFile.length())
            {
                s = ".";
                words.push_back(s);
                break;
            }
            ch=strFile[Loc];
            Loc++;
            if(ch == ' ' || ch == '\n' || ch == '\t')
            {
                s = ".";
                words.push_back(s);
                break;
            }
            if(ch == '.')
            {
                s = "..";
            }
            if(ch != '.')
            {
                s = ".";
                lastch = ch;   //为防止已经读进ch的字符丢失,将其保存在lastch中
            }
            words.push_back(s);
            break;

        default: break;
        }
    }
    return words;
}


QStandardItemModel* showTokenList()
{
    QStandardItemModel* model = new QStandardItemModel();

    model->setHorizontalHeaderLabels({QString::fromLocal8Bit("类型"),
                                      QString::fromLocal8Bit("单词")});
    for(unsigned long long i=0;i<tokenList.size();i++)
    {
        int type=tokenList[i].type;
        switch(type)
        {
        case 1:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("标识符")));
            break;
        case 2:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("无符号整数")));
            break;
        case 3:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("单字符分界符")));
            break;
        case 4:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("双字符分界符")));
            break;
        case 6:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("数组下标界限")));
            break;
        case 7:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("保留字")));
            break;
        case 8:
            model->setItem(i,0,new QStandardItem(QString::fromLocal8Bit("字符串")));;
            break;
        default:
            break;
        }
        model->setItem(i,1,new QStandardItem(QString::fromStdString(tokenList[i].str)));
    }

    return model;
}

#endif // TOKEN_H
