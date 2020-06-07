#pragma once
#ifndef DIGUI_H
#define DIGUI_H
//本页功能根据实验书上教材的定义，递归下降进行语义分析并构建语法分析树
//语义分析插入在递归下降程序之间，仅可检查重复定义或未定义先使用两类错误
//语法分析树的定义主要是参照实验教材59页 5.2.2语法分析树的结构
//在此生成的语法分析树可以以深度遍历的以生成四元式
//语义分析符号表为简化程序没有保留，采用的是散列表外拉链的方式，错误检测机制包括本层和非本层
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<iostream>
#include<set>
#include <sstream>
#include<stack>
#include"token.h"
#include "ui_mainwindow.h"
#include "SemanticError.h"



using namespace std;
namespace DiguiSpace {
    typedef enum {
        ProK, PheadK, TypeK, VarK, ProcDecK,
        StmLk, DecK, StmtK, ExpK
    }NodeKind;

    typedef enum {
        ArrayK, CharK, IntegerK, RecordK, IdK
    }Dec;

    typedef enum {
        IfK, WhileK, AssignK, ReadK, WriteK,
        CallK, ReturnK
    }Stmt;

    typedef enum {
        OpK, ConstK, IdEK
    }Expp;

    typedef enum {
        ValParamType, VarParamType
    }Paramt;

    typedef enum {
        IdV, ArrayMembV, FieldMembV
    }Varkind;

    typedef enum {
        Void, Integer, Boolean
    }ExpType;

    typedef struct {
        int low;
        int up;
        string childType;
    }ArrayAttr;

    typedef struct {
        Paramt paramt;
    }ProcAttr;

    typedef struct {
        string op;
        int val;
        Varkind varkind;
        ExpType type;
    }ExpAttr;

    typedef struct {
        Dec dec;
        Stmt stmt;
        Expp exp;
    }Kind;

    typedef struct {
        ArrayAttr arrayAttr;
        ProcAttr procAttr;
        ExpAttr expAttr;
    }Attr;

    struct TreeNode {
        TreeNode* child[3];
        TreeNode* Sibling;
        int Lineno;
        NodeKind nodeKind;
        Kind kind;
        int idnum;
        vector<string> name;
        vector<void*> table;
        string type_name;
        Attr attr;
        TreeNode() {
            type_name = "";
            Sibling = NULL;
            child[0] = NULL;
                child[1] = NULL;
                child[2] = NULL;
            idnum = 0;
        }
    };



    struct SymbolTable{
        string ID;
        int level;
        SymbolTable* next;
        SymbolTable() {
            next = NULL;
        }
    };
    map<string, SymbolTable*> Table;

    int now_level = 0;
    bool FindSymbol(string Id) {
        if (Table.find(Id) == Table.end())return false;
        else {
            return true;
        }
    }
    bool FindSymbol1(string Id) {
        if (Table.find(Id) == Table.end())return false;
        else {
            if (Table[Id]->level == now_level)return true;
            return false;
        }
    }
    void ProcedureSym(string Id) {
        Table[Id]->level--;
    }
    void InsertSymbol(string Id) {
        SymbolTable* temp = new SymbolTable();
        if (Table.find(Id) == Table.end()) {
            Table[Id] = temp;
            temp->ID = Id;
            temp->level = now_level;
        }
        else {
            temp->next = Table[Id];
            Table[Id] = temp;
            temp->ID = Id;
            temp->level = now_level;
        }
    }
    void UpdateSymbol() {
        for (map<string, SymbolTable*>::iterator i = Table.begin(); i != Table.end();) {
            if (i->second->level == now_level && i->second->next == NULL) {
                Table.erase(i++);
            }
            else if (i->second->level == now_level) {
                i->second = i->second->next;
                i++;
            }
            else i++;
        }
        now_level--;
    }
    int Loc = 0;
    TreeNode* Program();
    TreeNode* ProgramHead();
    TreeNode* DeclarePart();
    TreeNode* ProgramBody();
    TreeNode* TypeDecPart();
    TreeNode* TypeDec();
    TreeNode* TypeDecList();
    TreeNode* TypeDecMore();
    void TypeId(TreeNode*);
    void TypeDef(TreeNode*);
    void BaseType(TreeNode*);
    void StructureType(TreeNode*);
    void ArrayType(TreeNode*);
    void RecType(TreeNode*);
    TreeNode* FieldDecList();
    TreeNode* FieldDecMore();
    void IdList(TreeNode*);
    void IdMore(TreeNode*);
    TreeNode* VarDecpart();
    TreeNode* VarDec();
    TreeNode* VarDecList();
    TreeNode* VarDecMore();
    void VarIdList(TreeNode*);
    void VarIdMore(TreeNode*);
    TreeNode* ProcDecpart();
    TreeNode* ProcDec();
    void ParamList(TreeNode*);
    TreeNode* ParamDecList();
    TreeNode* ParamMore();
    TreeNode* Param();
    void FormList(TreeNode*);
    void FidMore(TreeNode*);
    TreeNode* ProcDecPart();
    TreeNode* ProcBody();
    TreeNode* StmList();
    TreeNode* StmMore();
    TreeNode* Stm();
    TreeNode* AssCall();
    TreeNode* AssignmentRest();
    TreeNode* ConditionalStm();
    TreeNode* LoopStm();
    TreeNode* InputStm();
    TreeNode* OutputStm();
    TreeNode* ReturnStm();
    TreeNode* CallStmRest();
    TreeNode* ActParamList();
    TreeNode* ActParamMore();
    TreeNode* RelExp();
    TreeNode* Exp();
    TreeNode* Term();
    TreeNode* Factor();
    TreeNode* Variable();
    void VariMore(TreeNode*);
    TreeNode* Fieldvar();
    void FieldvarMore(TreeNode*);
    bool getNextToken() {
        if (Loc < tokenList.size()) {
            Loc++;
            return true;
        }
        return false;
    }
    TreeNode* root = NULL;
    //1)  Program	::=	ProgramHead  DeclarePart ProgramBody .
    TreeNode* Program() {
        now_level++;
        Table.clear();
        stack<TreeNode*> temp;
        if(root!=NULL)temp.push(root);
        while(!temp.empty()){
            TreeNode* d=temp.top();
            temp.pop();
            if(d->child[0]!=NULL)temp.push(d->child[0]);
            if(d->child[1]!=NULL)temp.push(d->child[1]);
            if(d->child[2]!=NULL)temp.push(d->child[2]);
            if(d->Sibling!=NULL)temp.push(d->Sibling);
            delete d;
        }
        TreeNode* t = ProgramHead();
        TreeNode* q = DeclarePart();
        TreeNode* s = ProgramBody();
        root = new TreeNode();
        root->nodeKind = ProK;
        root->child[0] = t;
        root->child[1] = q;
        root->child[2] = s;
        if (tokenList[Loc].str == ".") {
            getNextToken();
        }
        else {
            cout << "Line " << " need \'.\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'.\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        cout << "Success" << endl;
        return root;
    }

    //2)  ProgramHead	:: = PROGRAM	ProgramName
    //3) ProgramName      ::=       ID
    TreeNode* ProgramHead() {
        TreeNode* t = new TreeNode();
        t->nodeKind = PheadK;
        if (tokenList[Loc].str != "PROGRAM") {
            cout << "Line " << " need \'PROGRAM\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'PROMGRAM\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        else {
            if (!getNextToken()) {
                cout << "Runtime Error" << endl;
            }
        }
        if (tokenList[Loc].type != 1) {
            cout << "Line " << " need an ID" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("缺少ID\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        else {
            //此处判定程序名称是否已定义,范围：全局
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
            if (FindSymbol(tokenList[Loc].str)) {
                cout<<"标识符重复定义"<<endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);

                //ui->textEdit_ErrorWin->setText(ui->textEdit_ErrorWin->toPlainText()+FILE_PATH+s);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
        }

        if (!getNextToken()) {
            cout << "Runtime Error" << endl;
        }
        return t;
    }


    //4)	DeclarePart	::=	TypeDecPart  VarDecpart  ProcDecpart
    TreeNode* DeclarePart() {
        TreeNode* t = NULL, * typep = NULL, * varp = NULL;
        TreeNode* tp1 = TypeDecPart();
        TreeNode* tp2 = VarDecpart();
        TreeNode* funcp = ProcDecpart();
        TreeNode* temp=funcp;
        while (tokenList[Loc].str == "PROCEDURE") {
            funcp->Sibling = ProcDecpart();
            funcp = funcp->Sibling;
        }
        funcp = temp;
        if (tp1 != NULL) {
            typep = new TreeNode();
            typep->nodeKind = TypeK;
            typep->idnum++;
            typep->child[0] = tp1;
        }
        if (tp2 != NULL) {
            varp = new TreeNode();
            varp->nodeKind = VarK;
            varp->idnum++;
            varp->child[0] = tp2;
        }
        if (varp == NULL) {
            varp = funcp;
        }
        if (typep == NULL) {
            typep = varp;
        }
        t = typep;
        if (typep != varp) {
            typep->Sibling = varp;
        }
        if (varp != funcp) {
            varp->Sibling = funcp;
        }
        return t;
    }
    //5)TypeDecPart		::=	@
    //6)                     | TypeDec
    TreeNode* TypeDecPart() {
        TreeNode* t = NULL;
        do {
            if (tokenList[Loc].str == "TYPE") {
                t = TypeDec();
                return t;
            }
            if (tokenList[Loc].str == "VAR" || tokenList[Loc].str == "PROCEDURE" || tokenList[Loc].str == "BEGIN") {
                return NULL;
            }
        } while (getNextToken());

        return NULL;
    }
    //7)	TypeDec::= 	TYPE	TypeDecList
    TreeNode* TypeDec() {
        if (tokenList[Loc].str != "TYPE") {
            cout << "Line " << " need \'type\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'type\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
            return NULL;
        }
        getNextToken();
        TreeNode* t = TypeDecList();
        return t;
    }
    //8)TypeDecList	::=	TypeId = TypeDef ; TypeDecMore
    TreeNode* TypeDecList() {
        TreeNode* t = new TreeNode();
        t->nodeKind = DecK;
        TypeId(t);

        if (tokenList[Loc].str != "=") {
            cout << "Line " << " need \'=\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'=\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
            return t;
        }
        getNextToken();
        TypeDef(t);
        if (tokenList[Loc].str != ";") {
            cout << "Line " << " need \';\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\';\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
            return t;
        }
        getNextToken();
        TreeNode* p = TypeDecMore();
        if (p != NULL) {
            t->Sibling = p;
        }
        return t;
    }
    //9)TypeDecMore	::= 	@
    //10)                       | TypeDecList
    TreeNode* TypeDecMore() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "VAR" || tokenList[Loc].str == "PROCEDURE" ||
            tokenList[Loc].str == "BEGIN")
            return t;
        if (tokenList[Loc].type == 1) {
            //此处判定类型定义左侧是否已定义，范围：本层
            if (FindSymbol1(tokenList[Loc].str)) {
                cout << "标识符重复定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
            t=TypeDecList();
        }
        else
            getNextToken();
        return t;
    }
    //11)	TypeId		::= 	ID
    void TypeId(TreeNode* t) {
        if (tokenList[Loc].type != 1) {
            cout << "Line " << " need an ID" << endl;
        }
        else {
            if (t != NULL) {
                t->idnum++;
                t->name.push_back(tokenList[Loc].str);
            }
            //此处判定类型定义左侧是否已定义，范围：本层
            if (FindSymbol1(tokenList[Loc].str)) {
                cout << "标识符重复定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
        }
        getNextToken();
    }
    //12)TypeDef	::= 	BaseType
    //13)                             | StructureType
    //14)                             | ID
    void TypeDef(TreeNode* t) {
        if (t == NULL) return;
        if (tokenList[Loc].str == "INTEGER" || tokenList[Loc].str == "CHAR") {
            BaseType(t);
        }
        else if (tokenList[Loc].str == "ARRAY" || tokenList[Loc].str == "RECORD") {
            StructureType(t);
        }
        else if (tokenList[Loc].type == 1) {
            //类型右侧是否已经定义，范围：全局
            if (!FindSymbol(tokenList[Loc].str)) {
                cout << "使用了没定义的标识符" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，使用了没定义的标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t->kind.dec = IdK;
            t->type_name = tokenList[Loc].str;
            getNextToken();
        }
        else
            getNextToken();
    }
    //15)	BaseType	::=	INTEGER
    //16) | CHAR
    void BaseType(TreeNode* t) {
        if (tokenList[Loc].str == "INTEGER") {
            t->kind.dec = IntegerK;
            getNextToken();
        }
        else if (tokenList[Loc].str == "CHAR") {
            t->kind.dec = CharK;
            getNextToken();
        }
        //352
    }
    //17)StructureType	::= 	ArrayType
    //18) | RecType
    void StructureType(TreeNode* t) {
        if (tokenList[Loc].str == "ARRAY") {
            t->kind.dec = ArrayK;
            ArrayType(t);
            /*if (TokenSpace::tokenList[Loc].type == 1) {
                if (FindSymbol1(TokenSpace::tokenList[Loc].str)) {
                    cout << "标识符重复定义" << endl;
                }
                else {
                    InsertSymbol(TokenSpace::tokenList[Loc].str);
                    cout << "成功进入符号表" << endl;
                }
            }*/
        }
        else if (tokenList[Loc].str == "RECORD") {
            t->kind.dec = RecordK;
            RecType(t);
            /*if (TokenSpace::tokenList[Loc].type == 1) {
                if (FindSymbol1(TokenSpace::tokenList[Loc].str)) {
                    cout << "标识符重复定义" << endl;
                }
                else {
                    InsertSymbol(TokenSpace::tokenList[Loc].str);
                    cout << "成功进入符号表" << endl;
                }
            }*/
        }
        else getNextToken();
    }
    //19)	ArrayType	::=	ARRAY [Low..Top ] OF BaseType
    //20)	Low          	::=  	INTC
    //21)Top             	:: = INTC
    void ArrayType(TreeNode* t) {
        if (tokenList[Loc].str != "ARRAY") {
            cout << "Line " << " need \'Array\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'Array\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].str != "[") {
            cout << "Line " << " need \'[\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'[\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].type == 2) {
            stringstream ss(tokenList[Loc].str);
            ss >> t->attr.arrayAttr.low;
        }
        else {
            cout << "Line " << " need an Integer" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少一个整数\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].str != "..") {
            cout << "Line " << " need \'..\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'..\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].type == 2) {
            stringstream ss(tokenList[Loc].str);
            ss >> t->attr.arrayAttr.up;
        }
        else {
            cout << "Line " << " need an INTEGER\n" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少一个整数\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].str != "]") {
            cout << "Line " << " need \']\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\']\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].str != "OF") {
            cout << "Line " << " need \'of\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'of\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        BaseType(t);
        t->attr.arrayAttr.childType = t->kind.dec;
        t->kind.dec = ArrayK;
    }
    //22)RecType		::=	RECORD  FieldDecList	 END
    void RecType(TreeNode* t) {
        if (tokenList[Loc].str != "RECORD") {
            cout << "Line " << " need \'record\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'record\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        TreeNode* p = FieldDecList();
        t->child[0] = p;
        if (tokenList[Loc].str != "END") {
            cout << "Line " << " need \'end\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'end\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
    }
    //23)FieldDecList	::=	BaseType  IdList ; FieldDecMore
    //24) | ArrayType IdList; FieldDecMore
    TreeNode* FieldDecList() {
        TreeNode* t = new TreeNode();
        t->nodeKind = DecK;
        TreeNode* p = NULL;
        if (tokenList[Loc].str == "END") {
            return t;
        }
        if (tokenList[Loc].str == "INTEGER" || tokenList[Loc].str == "CHAR") {
            BaseType(t);
            IdList(t);
            if (tokenList[Loc].str != ";") {
                cout << "Line " << " need \';\'" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("后缺少\';\'\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            getNextToken();
            p=FieldDecMore();
        }
        else if (tokenList[Loc].str == "ARRAY") {
            ArrayType(t);
            IdList(t);
            if (tokenList[Loc].str != ";") {
                cout << "Line " << " need \';\'" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\';\'\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            getNextToken();
            p=FieldDecMore();
        }
        else
            getNextToken();
        t->Sibling = p;
        return t;
    }
    //25)FieldDecMore	::=	@
    //26) | FieldDecList
    TreeNode* FieldDecMore() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "END") {
            return t;
        }
        if (tokenList[Loc].str == "INTEGER" || tokenList[Loc].str == "CHAR" || tokenList[Loc].str == "ARRAY") {
            if (tokenList[Loc].type == 1&&!FindSymbol(tokenList[Loc].str)) {
                cout << "使用了未定义的标识符" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，使用了未定义的标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t=FieldDecList();
        }
        else getNextToken();
        return t;
    }
    //27)	IdList		::= 	ID  IdMore
    void IdList(TreeNode* t) {
        if (tokenList[Loc].type == 1) {
            //标识符是否重复定义，范围：本层
            if (FindSymbol1(tokenList[Loc].str)) {
                cout << "标识符重复定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
            getNextToken();
            IdMore(t);
        }
    }
    //28)	IdMore		::=	 @
    //29) | , IdList
    void IdMore(TreeNode* t) {
        if (tokenList[Loc].str == ";") {
            return;
        }
        //cout << TokenSpace::tokenList[Loc].str << ' ';
        if (tokenList[Loc].str == ",") {
            getNextToken();
            IdList(t);
        }
        else
            getNextToken();
    }
    //30)	VarDecpart		::=	 @
    //31) | VarDec
    TreeNode* VarDecpart() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "PROCEDURE" || tokenList[Loc].str == "BEGIN") {
            return t;
        }
        if (tokenList[Loc].str == "VAR") {
            t=VarDec();
        }
        else getNextToken();
        return t;
    }
    //32)	VarDec	:: = VAR  VarDecList
    TreeNode* VarDec() {
        if (tokenList[Loc].str != "VAR") {
            cout << "Line " << " need \'var\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'var\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        TreeNode* t = VarDecList();
        //cout <<    endl;
        return t;
    }
    //33)	VarDecList	::=	TypeDef	VarIdList ;  VarDecMore
    TreeNode* VarDecList() {
        TreeNode* t = new TreeNode();
        t->nodeKind = DecK;
        TreeNode* p = NULL;
        TypeDef(t);
        VarIdList(t);
        if (tokenList[Loc].str != ";") {
            //printf("Line %d need \';\'\n",  TokenSpace::tokenList[Loc].Linenum);
        }
        else getNextToken();
        p = VarDecMore();
        t->Sibling = p;
        return t;
    }
    //34)	VarDecMore	:: = @|
    //35) | VarDecList
    TreeNode* VarDecMore() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "PROCEDURE" || tokenList[Loc].str == "BEGIN") {
            return t;
        }
        if (tokenList[Loc].str == "INTEGER" || tokenList[Loc].str == "CHAR" || tokenList[Loc].str == "ARRAY" || tokenList[Loc].str == "RECORD" || tokenList[Loc].type == 1) {
            if (tokenList[Loc].type == 1 && !FindSymbol(tokenList[Loc].str)) {
                cout << "使用了未定义的标识符" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，使用了未定义的标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t=VarDecList();
        }
        else getNextToken();
        return t;
    }
    //36)VarIdList	::=	ID  VarIdMore
    void VarIdList(TreeNode* t) {
        if (tokenList[Loc].type == 1) {
            if (FindSymbol1(tokenList[Loc].str)) {
                cout << "标识符重复定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
            getNextToken();
        }
        //变量是否重复定义，范围：本层
        VarIdMore(t);
    }
    //37)VarIdMore	::=	 @
    //38) | , VarIdList
    void VarIdMore(TreeNode* t) {
        if (tokenList[Loc].str == ";") {
            return;
        }
        if (tokenList[Loc].str == ",") {
            getNextToken();
            VarIdList(t);
        }
        //else printf("Line %d need \',\'\n",  TokenSpace::tokenList[Loc].Linenum);
    }
    //39)	ProcDecpart	::=	 @
    //40) | ProcDec
    TreeNode* ProcDecpart() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "BEGIN") {
            return t;
        }
        if (tokenList[Loc].str == "PROCEDURE") {
            t=ProcDec();
        }
        //getNextToken();
        return t;
    }
    //41)ProcDec::=	PROCEDURE		ProcName ( ParamList )  ; ProcDecPart ProcBody ProcDecMore
    //42) ProcDecMore::=	@
    //43) | ProcDec
    TreeNode* ProcDec() {
        now_level++;
        TreeNode* t = new TreeNode();
        if (tokenList[Loc].str != "PROCEDURE") {
            cout << "Line " << " need \'procedure\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'produce\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->nodeKind = ProcDecK;
        if (tokenList[Loc].type != 1)
        {cout << "Line " << " need an id" << endl;
        QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("缺少id\n");
        SemanticErrorPoint sp(0,s);
        SemErrorList->push_back(sp);}
        else {
            //函数过程重复定义，范围：全局
            if (FindSymbol(tokenList[Loc].str)) {
                cout << "标识符重复定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                ProcedureSym(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
        }
        getNextToken();
        if (tokenList[Loc].str != "(") {
            cout << "Line " << " need \'(\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'(\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        ParamList(t);
        if (tokenList[Loc].str != ")") {
            cout << "Line " << " need \')\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\')\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        if (tokenList[Loc].str != ";") {
            cout << "Line " << " need \';\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\';\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->child[1] = ProcDecPart();
        t->child[2] = ProcBody();
        return t;
    }
    //45) ParamList	::=	 @
    //46) | ParamDecList
    void ParamList(TreeNode* t) {
        if (tokenList[Loc].str == ")") {
            return;
        }
        if (tokenList[Loc].str == "INTEGER" || tokenList[Loc].str == "CHAR" || tokenList[Loc].str == "RECORD" ||
            tokenList[Loc].str == "ARRAY" || tokenList[Loc].type == 1 || tokenList[Loc].str == "VAR")
        {
            if (tokenList[Loc].type == 1 && !FindSymbol(tokenList[Loc].str)) {
                cout << "使用了未定义的标识符" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，使用了未定义的标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            ParamDecList();
        }
        else getNextToken();
    }
    //47)ParamDecList	::=	 Param  ParamMore
    TreeNode* ParamDecList() {
        TreeNode* t = Param();
        TreeNode* p = ParamMore();
        t->Sibling = p;
        return t;
    }
    //48)ParamMore	::=	 @
    //49) | ; ParamDecList
    TreeNode* ParamMore() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == ")") {
            return t;
        }
        if (tokenList[Loc].str == ";") {
            getNextToken();
            t=ParamDecList();
        }
        else {
            //printf("Line %d need \';\'",  TokenSpace::tokenList[Loc].Linenum);
            if (tokenList[Loc].type == 1) {
                if (FindSymbol1(tokenList[Loc].str)) {
                    cout << "标识符重复定义" << endl;
                    QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                    SemanticErrorPoint sp(0,s);
                    SemErrorList->push_back(sp);
                }
                else {
                    InsertSymbol(tokenList[Loc].str);
                    cout << "成功进入符号表" << endl;
                }
            }
            getNextToken();
        }
        return t;
    }
    //50)	Param		::=	TypeDef  FormList
    //51) | VAR TypeDef  FormList
    TreeNode* Param() {
        TreeNode* t = new TreeNode();
        t->nodeKind = DecK;
        if (tokenList[Loc].str == "INTEGER" || tokenList[Loc].str == "CHAR" || tokenList[Loc].str == "RECORD" ||
            tokenList[Loc].str == "ARRAY" || tokenList[Loc].type == 1) {
            if (tokenList[Loc].type == 1&& !FindSymbol(tokenList[Loc].str)) {
                cout << "使用了未定义的标识符" << endl;//范围：全局
                QString s=QString::fromLocal8Bit("::  语义分析错误，使用了未定义的标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t->attr.procAttr.paramt = ValParamType;
            TypeDef(t);
            FormList(t);
        }
        else if (tokenList[Loc].str == "VAR") {
            getNextToken();
            t->attr.procAttr.paramt = VarParamType;
            TypeDef(t);
        }
        else getNextToken();
        return t;
    }
    //52)	FormList	::= 	ID  FidMore
    void FormList(TreeNode* t) {
        if (tokenList[Loc].type == 1) {
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
            //此处判定是否已定义，范围：本层
            if (FindSymbol1(tokenList[Loc].str)) {
                cout << "标识符重复定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("重复定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            else {
                InsertSymbol(tokenList[Loc].str);
                cout << "成功进入符号表" << endl;
            }
            getNextToken();
        }
        FidMore(t);
    }
    //53)	FidMore	::=	 @
    //54) | , FormList
    void FidMore(TreeNode* t) {
        if (tokenList[Loc].str == ";" || tokenList[Loc].str == ")") {
            return;
        }
        if (tokenList[Loc].str == ",") {
            getNextToken();
            FormList(t);
        }
        else getNextToken();
    }
    //55)	ProcDecPart	::=	DeclarePart
    TreeNode* ProcDecPart() {
        return DeclarePart();
    }
    //56)	ProcBody		::=	ProgramBody
    TreeNode* ProcBody() {
        TreeNode* t = ProgramBody();
        return t;
    }
    //57)ProgramBody	::=	BEGIN  StmList END
    TreeNode* ProgramBody() {
        TreeNode* t = new TreeNode();
        if (tokenList[Loc].str != "BEGIN") {
            cout << tokenList[Loc].str << endl;
            cout << "Line " << " need \'begin\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'begin\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->nodeKind = StmLk;
        t->child[0] = StmList();
        if (tokenList[Loc].str != "END") {
            cout << "Line " << " need \'end\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'end\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        UpdateSymbol();
        getNextToken();
        return t;
    }
    //58)	StmList		::=	Stm		StmMore
    TreeNode* StmList() {
        TreeNode* t = Stm();
        TreeNode* p = StmMore();
        if (p != NULL)
            t->Sibling = p;
        return t;
    }
    //59)	StmMore		::=	 @
    //60) | ;  StmList
    TreeNode* StmMore() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "END") {
            return t;
        }
        //cout<< TokenSpace::tokenList[Loc].str <<endl;
        if (tokenList[Loc].str == "ENDWH") {
            return t;
        }
        if (tokenList[Loc].str == ";") {
            getNextToken();
            t=StmList();
        }
        else if (tokenList[Loc].str != "ELSE"
            && tokenList[Loc].str != "FI")
            getNextToken();
        return t;
    }
    string temp_name;
    //61)Stm		::=	ConditionalStm
    //62) | LoopStm
    //63) | InputStm
    //64) | OutputStm
    //65) | ReturnStm
    //66) | ID AssCall
    TreeNode* Stm() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == "IF") {
            t=ConditionalStm();
        }
        else if (tokenList[Loc].str == "WHILE") {
            t=LoopStm();
        }
        else if (tokenList[Loc].str == "RETURN") {
            t=ReturnStm();
        }
        else if (tokenList[Loc].str == "READ") {
            t=InputStm();
        }
        else if (tokenList[Loc].str == "WRITE") {
            t=OutputStm();
        }
        else if (tokenList[Loc].type == 1) {
            //范围：全局
            if (!FindSymbol(tokenList[Loc].str)) {
                cout << "标识符使用时没有定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("使用时没有定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            string str = tokenList[Loc].str;
            TreeNode* temp = NULL;
            //temp_name = TokenSpace::tokenList[Loc].str;
            if (tokenList[Loc+1].str == "[") {
                temp = new TreeNode();

                //temp->name.push_back(TokenSpace::tokenList[Loc].str);
                VariMore(temp);
                Loc--;
                //while (TokenSpace::tokenList[Loc].str != "]")getNextToken();
            }
            else if (tokenList[Loc + 1].str == ".") {
                getNextToken();
                getNextToken();
            }
            t=AssCall();
            if (temp != NULL&&t!=NULL) {
                t->child[1] = t->child[0];
                t->child[0] = temp;
            }
        }
        return t;
    }
    //67)	AssCall	:: = AssignmentRest(Fuzhi)
    //68) | CallStmRest(DiaoYong)
    TreeNode* AssCall() {
        TreeNode* t = NULL;
        getNextToken();
        if (tokenList[Loc].str == ":=") {
            t=AssignmentRest();
        }
        else if (tokenList[Loc].str == "(") {
            t=CallStmRest();
        }
        else getNextToken();
        return t;
    }
    //69)	AssignmentRest	::= VariMore	:= Exp
    TreeNode* AssignmentRest() {
        TreeNode* t = new TreeNode();
        if (tokenList[Loc].str != ":=") {
            cout << "Line " << " need \':=\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\':=\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);

        }
        getNextToken();
        t->nodeKind = StmtK;
        t->kind.stmt = AssignK;
        string strt = tokenList[Loc - 2].str;
        t->child[0] = RelExp();
        t->idnum++;
        t->name.push_back(strt);
        return t;
    }
    //70)	ConditionalStm	::=	IF RelExp THEN 					StmList ELSE StmList  FI
    TreeNode* ConditionalStm() {
        TreeNode* t = new TreeNode();
        getNextToken();
        t->nodeKind = StmtK;
        t->kind.stmt = IfK;
        t->child[0] = RelExp();
        if (tokenList[Loc].str != "THEN") {
            cout << "Line " << " need \'then\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'then\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->child[1] = StmList();
        if (tokenList[Loc].str == "ELSE") {
            getNextToken();
            t->child[2] = StmList();
        }
        if (tokenList[Loc].str != "FI") {
            cout << "Line " << " need \'fi\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'fi\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        return t;
    }
    //71)LoopStm::=	WHILE  RelExp DO StmList				ENDWH
    TreeNode* LoopStm() {
        TreeNode* t = new TreeNode();
        getNextToken();
        t->nodeKind = StmtK;
        t->kind.stmt = WhileK;
        t->child[0] = RelExp();
        if (tokenList[Loc].str != "DO") {
            cout << "Line " << " need \'do\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'do\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->child[1] = StmList();
        if (tokenList[Loc].str != "ENDWH") {
            cout << "Line " << " need \'fi\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'fi\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        return t;
    }
    //72)InputStm	::=	READ ( Invar)
    //73)Invar 		:: = ID
    TreeNode* InputStm() {
        TreeNode* t = new TreeNode();
        getNextToken();
        if (tokenList[Loc].str != "(") {
            cout << "Line " << " need \'(\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'(\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->nodeKind = StmtK;
        t->kind.stmt = ReadK;
        if (tokenList[Loc].type != 1) {
            cout << "Line " << " need an id" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("缺少id\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        else {
            //此处判定类型定义左侧是否已定义，范围：全局
            if (!FindSymbol(tokenList[Loc].str)) {
                cout << "标识符未定义" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("未定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
        }
        getNextToken();
        if (tokenList[Loc].str != ")") {
            cout << "Line " << " need \')\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\')\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        return t;
    }
    //74)OutputStm	::=	WRITE( Exp )
    TreeNode* OutputStm() {
        TreeNode* t = new TreeNode();
        getNextToken();
        if (tokenList[Loc].str != "(") {
            cout << "Line " << " need \'(\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'(\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->nodeKind = StmtK;
        t->kind.stmt = WriteK;
        t->child[0] = RelExp();
        if (tokenList[Loc].str != ")") {
            cout << "Line " << " need \')\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\')\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        return t;
    }
    //75)ReturnStm	::=	RETURN
    TreeNode* ReturnStm() {
        TreeNode* t = new TreeNode();
        if (t == NULL) {
            cout << "Runtime Error" << endl;
            return t;
        }
        t->nodeKind = StmtK;
        t->kind.stmt = ReturnK;
        return t;
    }
    //76)CallStmRest	::=	( ActParamList )
    TreeNode* CallStmRest() {
        TreeNode* t = new TreeNode();
        string temp_str = tokenList[Loc-1].str;
        if (tokenList[Loc].str != "(") {
            cout << "Line " << " need \'(\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\'(\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        t->nodeKind = StmtK;
        t->kind.stmt = CallK;
        t->child[0] = ActParamList();
        t->idnum++;
        t->name.push_back(temp_str);
        if (tokenList[Loc].str != ")") {
            cout << "Line " << " need \')\'" << endl;
            QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\')\'\n");
            SemanticErrorPoint sp(0,s);
            SemErrorList->push_back(sp);
        }
        getNextToken();
        return t;
    }
    //77)ActParamList::=	 @
    //78) | Exp  ActParamMore
    TreeNode* ActParamList() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == ")") {
            return t;
        }
        if (tokenList[Loc].type == 1 ||tokenList[Loc].type == 2) {
            if (tokenList[Loc].type == 1&&!FindSymbol(tokenList[Loc].str)) {
                cout << "标识符使用时没有定义" << endl;//全局
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("使用时没有定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t = RelExp();
            if (t != NULL) {
                t->Sibling = ActParamMore();
            }
        }
        else getNextToken();
        return t;
    }
    //79)ActParamMore::=@
    //80) | , ActParamList
    TreeNode* ActParamMore() {
        TreeNode* t = NULL;
        if (tokenList[Loc].str == ")") {
            return t;
        }
        if (tokenList[Loc].str == ",") {
            getNextToken();
            t = ActParamList();
        }
        else getNextToken();
        return t;
    }
    //81)RelExp	:: = Exp  OtherRelE
    //82)OtherRelE	:: = CmpOp   Exp
    //99)CmpOp	::=  	<
    //100) | =
    TreeNode* RelExp() {
        TreeNode* t = Exp();
        if (tokenList[Loc].str == "<" || tokenList[Loc].str == "=") {
            TreeNode* p = new TreeNode();
            if (p == NULL) {
                cout << "Runtime Error" << endl;
                return p;
            }
            p->nodeKind = ExpK;
            p->kind.exp = OpK;
            p->child[0] = t;
            p->attr.expAttr.op = tokenList[Loc].str;
            t = p;
            getNextToken();
            if (t != NULL) {
                t->child[1] = Exp();
            }
        }
        return t;
    }
    //83)Exp		::=  Term   OtherTerm
    //101)AddOp	::=  	+
    //102) | -
    TreeNode* Exp() {
        TreeNode* t = Term();
        while (tokenList[Loc].str == "+" ||tokenList[Loc].str == "-") {
            TreeNode* p = new TreeNode();
            if (p == NULL) {
                cout << "Runtime Error" << endl;
                return p;
            }
            p->nodeKind = ExpK;
            p->kind.exp = OpK;
            p->child[0] = t;
            p->attr.expAttr.op = tokenList[Loc].str;
            t = p;
            getNextToken();
            t->child[1] = Term();
        }
        return t;
    }
    //86)Term		::=   Factor   OtherFactor
    //103) MultOp	::=  	*
    //104)                 	|  /
    TreeNode* Term() {
        TreeNode* t = Factor();
        while (tokenList[Loc].str == "*" || tokenList[Loc].str == "/") {
            TreeNode* p = new TreeNode();
            if (p == NULL) {
                cout << "Runtime Error" << endl;
                return p;
            }
            p->nodeKind = ExpK;
            p->kind.exp = OpK;
            p->child[0] = t;
            p->attr.expAttr.op = tokenList[Loc].str;
            t = p;
            getNextToken();
            t->child[1] = Factor();
        }
        return t;
    }
    //89)Factor		::=   (  Exp  )
    //90) | INTC
    //91) | Variable
    TreeNode* Factor() {
        TreeNode* t = new TreeNode();
        if (tokenList[Loc].type == 2) {
            stringstream ss(tokenList[Loc].str);
            int tt;
            ss >> tt;
            t->nodeKind = ExpK;
            t->kind.exp = ConstK;
            t->attr.expAttr.val = tt;
            getNextToken();
        }
        else if (tokenList[Loc].type == 1) {
            if (tokenList[Loc].type == 1 && !FindSymbol(tokenList[Loc].str)) {
                cout << "使用了未定义的标识符" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，使用了未定义的标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t=Variable();
        }
        else if (tokenList[Loc].str == "(") {
            getNextToken();
            t=RelExp();
            if (tokenList[Loc].str != ")") {
                cout << "Line " << " need\')\'" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\')\'\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            getNextToken();
        }
        else {
            //cout << "unexpected word at line " << endl;
            //getNextToken();
            return NULL;
        }
        return t;
    }
    //92)	Variable	::=   ID   VariMore
    TreeNode* Variable() {
        TreeNode* t = new TreeNode();
        t->nodeKind = ExpK;
        t->kind.exp = IdEK;
        if (tokenList[Loc].type == 1) {
            if (!FindSymbol(tokenList[Loc].str)) {
                cout << "标识符使用时没有定义" << endl;//全局
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("使用时没有定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
            VariMore(t);
        }
        return t;
    }
    //93)VariMore	::= 	@
    //94) | [Exp]
    //95) | .FieldVar
    void VariMore(TreeNode* t) {
        getNextToken();
        if (tokenList[Loc].str == "[") {
            t->idnum++;
            t->name.push_back(tokenList[Loc-1].str);
            getNextToken();
            t->child[0] = RelExp();
            t->nodeKind = ExpK;
            t->attr.expAttr.varkind = ArrayMembV;
            t->child[0]->attr.expAttr.varkind = IdV;
            if (tokenList[Loc].str != "]") {
                cout << "Line" << "need \']\'" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\']\'\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            getNextToken();
        }
        else if (tokenList[Loc].str == ".") {
            getNextToken();
            t->nodeKind = ExpK;
            t->child[0] = Fieldvar();
            t->attr.expAttr.varkind = FieldMembV;
            t->child[0]->attr.expAttr.varkind = IdV;
        }
    }
    //96)FieldVar	::=  	ID   FieldVarMore
    TreeNode* Fieldvar() {
        TreeNode* t = new TreeNode();
        if (tokenList[Loc].type == 1) {
            if (!FindSymbol(tokenList[Loc].str)) {
                cout << "标识符使用时没有定义" << endl;//全局
                QString s=QString::fromLocal8Bit("::  语义分析错误，标识符")+QString::fromStdString(tokenList[Loc].str)+QString::fromLocal8Bit("使用时没有定义\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            t->nodeKind = ExpK;
            t->idnum++;
            t->name.push_back(tokenList[Loc].str);
            getNextToken();
            FieldvarMore(t);
        }
        return t;
    }
    //97)FieldVarMore::= 	@
    //98) | [Exp]
    void FieldvarMore(TreeNode* t) {
        if (tokenList[Loc].str == "[") {
            getNextToken();
            t->child[0] = RelExp();
            t->child[0]->attr.expAttr.varkind = ArrayMembV;
            if (tokenList[Loc].str != "]") {
                cout << "Line " << " need \']\'" << endl;
                QString s=QString::fromLocal8Bit("::  语义分析错误，")+QString::fromLocal8Bit("缺少\']\'\n");
                SemanticErrorPoint sp(0,s);
                SemErrorList->push_back(sp);
            }
            getNextToken();
        }
    }
}
#endif // DIGUI_H
