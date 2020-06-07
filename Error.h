﻿/*#ifndef ERROR_H
#define ERROR_H

#endif // ERROR_H*/
#pragma once
#include <map>
#include <string>
#include <QString>
using namespace std;


map<string, QString> ErrorMap{
    {"Program",QString::fromLocal8Bit("没有使用PROGRAM作为程序开始符")},
    {"ProgramHead",QString::fromLocal8Bit("没有使用PROGRAM作为程序开始符")},
    {"ProgramName",QString::fromLocal8Bit("没有使用标识符或错误使用其他符号定义程序名称")},
    {"DeclarePart",QString::fromLocal8Bit("声明部分使用了除类型声明，变量声明，过程声明之外的语句")},
    {"TypeDecpart",QString::fromLocal8Bit("声明部分使用了除类型声明，变量声明，过程声明之外的语句")},
    {"TypeDec",QString::fromLocal8Bit("类型定义没有使用Type关键字")},
    {"TypeDecList",QString::fromLocal8Bit("类型定义列表里使用了除标识符以外的符号")},
    {"TypeDecMore",QString::fromLocal8Bit("类型定义列表没有正确收尾")},
    {"TypeId",QString::fromLocal8Bit("没有使用标识符定义类型")},
    {"TypeDef",QString::fromLocal8Bit("类型定义时使用了除整型，字符型，数组型和标识符外的类型定义")},
    {"BaseType",QString::fromLocal8Bit("基本数据类型定义中使用了除整型，字符型外的的其他类型定义")},
    {"StructureType",QString::fromLocal8Bit("结构体定义没有使用数组定义关键字或记录定义关键字")},
    {"ArrayType",QString::fromLocal8Bit("数组定义没有使用array关键字")},
    {"Low",QString::fromLocal8Bit("数组下界不是无符号整数")},
    {"Top",QString::fromLocal8Bit("数组上界不是无符号整数")},
    {"RecType",QString::fromLocal8Bit("记录定义没有使用记录关键字")},
    {"FieldDecList",QString::fromLocal8Bit("记录域内定义了除整型，字符型，数组型以外的元素")},
    {"FieldDecMore",QString::fromLocal8Bit("记录域内定义了除整型，字符型，数组型以外的元素")},
    {"IdList",QString::fromLocal8Bit("标识符列表里出现了非标识符")},
    {"IdMore",QString::fromLocal8Bit("记录里标识符定义未使用分号或逗号分隔")},
    {"VarDecpart",QString::fromLocal8Bit("变量定义未使用VAR关键字")},
    {"VarDec",QString::fromLocal8Bit("变量定义未使用VAR关键字")},
    {"VarDecList",QString::fromLocal8Bit("变量类型使用了整型，字符型，数组型，记录型以外的类型")},
    {"VarDecMore",QString::fromLocal8Bit("变量类型使用了整型，字符型，数组型，记录型以外的类型")},
    {"VarIdList",QString::fromLocal8Bit("变量列表声明不是标识符")},
    {"VarIdMore",QString::fromLocal8Bit("变量声明时没有正确使用分号或逗号进行分隔")},
    {"ProcDecpart",QString::fromLocal8Bit("过程定义没有使用Procedure关键字")},
    {"ProcDec",QString::fromLocal8Bit("过程定义没有使用Procedure关键字")},
    {"ProcDecMore",QString::fromLocal8Bit("过程定义没有使用Procedure关键字")},
    {"ProcName",QString::fromLocal8Bit("过程名不是标识符")},
    {"ParamList",QString::fromLocal8Bit("参数列表中参数类型定义不正确")},
    {"ParamDecList",QString::fromLocal8Bit("参数列表中参数类型定义不正确")},
    {"ParamMore",QString::fromLocal8Bit("没有使用逗号分割不同参数或括号不匹配")},
    {"Param",QString::fromLocal8Bit("参数列表中参数类型定义不正确")},
    {"FormList",QString::fromLocal8Bit("参数声明没有指定标识符")},
    {"FidMore",QString::fromLocal8Bit("没有使用分号，逗号或括号对不同标识符进行分隔")},
    {"ProcDecPart",QString::fromLocal8Bit("过程声明不正确")},
    {"ProcBody",QString::fromLocal8Bit("程序体开始时没有使用Begin")},
    {"ProgramBody",QString::fromLocal8Bit("程序体开始时没有使用Begin")},
    {"StmList",QString::fromLocal8Bit("所写语句不属于赋值，条件，循环，输入，输出和返回语句")},
    {"StmMore",QString::fromLocal8Bit("语句没有书写结束符号或没有用分号分隔")},
    {"Stm",QString::fromLocal8Bit("所写语句不属于赋值，条件，循环，输入，输出和返回语句")},
    {"AssCall",QString::fromLocal8Bit("调用或赋值的语句格式不合法")},
    {"AssignmentRest",QString::fromLocal8Bit("赋值语句格式不合法")},
    {"ConditionalStm",QString::fromLocal8Bit("条件语句没有使用IF关键字")},
    {"LoopStm",QString::fromLocal8Bit("循环语句没有使用WHILE关键字")},
    {"InputStm",QString::fromLocal8Bit("读入语句没有使用READ关键字")},
    {"Invar",QString::fromLocal8Bit("输入语句的读取对象不是用标识符表示")},
    {"OutputStm",QString::fromLocal8Bit("输出语句没有使用WRITE关键字")},
    {"ReturnStm",QString::fromLocal8Bit("返回语句没有使用RETURN关键字")},
    {"CallStmRest",QString::fromLocal8Bit("调用语句没有使用左括号打头")},
    {"ActParamList",QString::fromLocal8Bit("调用的形参既不是无符号整数也不是标识符")},
    {"ActParamMore",QString::fromLocal8Bit("并列调用形参时没有使用逗号分隔或没有使用反括号结束调用语句")},
    {"RelExp",QString::fromLocal8Bit("条件表达式左部对象不是标识符或无符号整数，或运算对象没有用括号拉起")},
    {"OtherRelE",QString::fromLocal8Bit("条件表达式没有使用比较运算符")},
    {"Exp",QString::fromLocal8Bit("条件表达式右部对象不是标识符或无符号整数，或运算对象没有用括号拉起")},
    {"OtherTerm",QString::fromLocal8Bit("算术表达式使用了保留字")},
    {"Term",QString::fromLocal8Bit("运算表达式左部对象不是标识符或无符号整数，或运算对象没有用括号拉起")},
    {"OtherFactor",QString::fromLocal8Bit("算术表达式使用了保留字")},
    {"Factor",QString::fromLocal8Bit("运算表达式左部对象不是标识符或无符号整数，或运算对象没有用括号拉起")},
    {"Variable",QString::fromLocal8Bit("变量名不是标识符")},
    {"VariMore",QString::fromLocal8Bit("变量类型使用关键字或无符号整数")},
    {"FieldVar",QString::fromLocal8Bit("变量使用了除标识符以外符号")},
    {"FieldVarMore",QString::fromLocal8Bit("变量类型使用关键字或无符号整数")},
    {"CmpOp",QString::fromLocal8Bit("当前符号不是比较运算符")},
    {"AddOp",QString::fromLocal8Bit("当前符号不是加法运算符")},
    {"MulOp",QString::fromLocal8Bit("当前符号不是乘法运算符")}
};

