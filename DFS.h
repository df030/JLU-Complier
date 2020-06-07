#pragma once
#include"Digui.h"
#include<cmath>
//本页功能：从语法树上构建四元式
//本页功能实现：通过深度遍历语法树完成四元式的构建
//事先说明：本页的四元式仅对过程定义和函数主体翻译
//结果存在于vector<SiYuanStyle*> SiYuan中
//ProK, PheadK, TypeK, VarK, ProcDecK,
//StmLk, DecK, StmtK, ExpK
//	typedef enum {
//IfK, WhileK, AssignK, ReadK, WriteK,
//CallK, ReturnK
//	}Stmt;

//	typedef enum {
//		OpK, ConstK, IdEK
//	}Expp;
namespace DFS {
    void FuzhiStyle(DiguiSpace::TreeNode* s);
    void FuncProcCall(DiguiSpace::TreeNode* s);
    void DFS(DiguiSpace::TreeNode* root);
    void DFS_all(DiguiSpace::TreeNode* root);
    void FunProcDef(DiguiSpace::TreeNode* s);
    void IfStyle(DiguiSpace::TreeNode* s);
    void readStyle(DiguiSpace::TreeNode* s);
    void writeStyle(DiguiSpace::TreeNode* s);
    string array(DiguiSpace::TreeNode* s, int i);
    void StmtK(DiguiSpace::TreeNode* s, string ID);
    void WhileStyle(DiguiSpace::TreeNode* s);
    int offset = 0;
    stack<DiguiSpace::TreeNode*> tree_s;
    struct SiYuanStyle {
        string operation;
        string left;
        string right;
        string id;
    };
    vector<SiYuanStyle*> SiYuan;
    int num = 0;
    string IDcreate() {
        num++;
        return "t" + to_string(num);
    }
    DiguiSpace::TreeNode* t_root;
    void DFS_all(DiguiSpace::TreeNode* root) {
        num=0;
        t_root = root;
        SiYuan.clear();
        if (root->child[0])DFS(root->child[0]);
        if (root->child[1])DFS(root->child[1]);
        if (root->child[2]&& root->child[2]->child[0])DFS(root->child[2]->child[0]);
    }
    void DFS(DiguiSpace::TreeNode* root) {
        if (root == NULL)return;
        tree_s.push(root);
        DiguiSpace::TreeNode* temp = root;
        while (temp != NULL) {
            if (temp->nodeKind == DiguiSpace::ProcDecK)FunProcDef(temp);
            else if (temp->kind.stmt == DiguiSpace::AssignK)FuzhiStyle(temp);
            else if (temp->kind.stmt == DiguiSpace::ReadK)readStyle(temp);
            else if (temp->kind.stmt == DiguiSpace::WriteK)writeStyle(temp);
            else if (temp->kind.stmt == DiguiSpace::IfK)IfStyle(temp);
            else if (temp->kind.stmt == DiguiSpace::WhileK)WhileStyle(temp);
            else if (temp->kind.stmt == DiguiSpace::CallK)FuncProcCall(temp);
            temp = temp->Sibling;
        }
        return;
    }
    //赋值语句四元式
    void FuzhiStyle(DiguiSpace::TreeNode* s) {
        if (s->child[1] != NULL) {
            SiYuanStyle* hh1 = new SiYuanStyle();
            hh1->operation = "ASSIG";
            hh1->left = array(s, 0);
            string temp1;

                if (s->child[0]->kind.exp == DiguiSpace::OpK) {
                    temp1 = IDcreate();
                    StmtK(s->child[0], temp1);
                }
                else if (s->child[0]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
                    temp1 = array(s, 0);
                }
                else if (s->child[0]->kind.exp == DiguiSpace::IdEK) {
                    temp1 = s->child[0]->name[0];
                }
                else if (s->child[0]->kind.exp == DiguiSpace::ConstK) {
                    temp1 = to_string(s->child[0]->attr.expAttr.val);
                }

            hh1->id = temp1;

            if (s->child[1]->kind.exp == DiguiSpace::OpK) {
                temp1 = IDcreate();
                StmtK(s->child[1], temp1);
            }
            else if (s->child[1]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
                temp1 = array(s, 1);
            }
            else if (s->child[1]->kind.exp == DiguiSpace::IdEK) {
                temp1 = s->child[1]->name[0];
            }
            else if (s->child[1]->kind.exp == DiguiSpace::ConstK) {
                temp1 = to_string(s->child[1]->attr.expAttr.val);
            }
            hh1->left = temp1;
            SiYuan.push_back(hh1);
        }
        else {
            SiYuanStyle* hh1 = new SiYuanStyle();
            hh1->operation = "ASSIG";
            hh1->id = s->name[0];
            string temp1;

            if (s->child[0]->kind.exp == DiguiSpace::OpK) {
                temp1 = IDcreate();
                StmtK(s->child[0], temp1);
            }
            else if (s->child[0]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
                temp1 = array(s, 0);
            }
            else if (s->child[0]->kind.exp == DiguiSpace::IdEK) {
                temp1 = s->child[0]->name[0];
            }
            else if (s->child[0]->kind.exp == DiguiSpace::ConstK) {
                temp1 = to_string(s->child[0]->attr.expAttr.val);
            }
            hh1->left = temp1;

            SiYuan.push_back(hh1);
        }
    }
    //过函调用四元式
    void FuncProcCall(DiguiSpace::TreeNode* s) {
        SiYuanStyle* hh1 = new SiYuanStyle();
        hh1->operation = "CALL";
        hh1->id = s->name[0];
        DiguiSpace::TreeNode* temp = s->child[0];
        DiguiSpace::TreeNode* temp2 = t_root->child[1];
        while (temp2!=NULL) {
            if (temp2->nodeKind == DiguiSpace::ProcDecK && temp2->name[0] == s->name[0])
                break;
            temp2 = temp2->Sibling;
        }
        //temp2 = temp2->child[0];
        while (temp != NULL&&temp2!=NULL) {
            string str1;

            if (temp->kind.exp == DiguiSpace::OpK) {
                str1 = IDcreate();
                StmtK(temp, str1);
            }
            else if (temp->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
                str1 = array(temp, 0);
            }
            else if (temp->kind.exp == DiguiSpace::IdEK) {
                str1 = temp->name[0];
            }
            else if (temp->kind.exp == DiguiSpace::ConstK) {
                str1 = to_string(temp->attr.expAttr.val);
            }
            if (temp2->attr.procAttr.paramt == DiguiSpace::VarParamType) {
                SiYuanStyle* hh2 = new SiYuanStyle();
                hh2->operation = "VARACT";
                hh2->left = str1;
                hh2->right = to_string(offset);
                hh2->id = "1";
                offset++;
                SiYuan.push_back(hh1);
            }
            else {
                SiYuanStyle* hh1 = new SiYuanStyle();
                hh1->operation = "VALACT";
                hh1->left = str1;
                hh1->right = to_string(offset);
                hh1->id = "1";
                offset++;
                SiYuan.push_back(hh1);
            }
            temp = temp->Sibling;
            temp2 = temp2->Sibling;
        }//形参与值参
        SiYuan.push_back(hh1);
        offset += 10;
    }
    //过函定义四元式
    void FunProcDef(DiguiSpace::TreeNode* s) {
        SiYuanStyle* hh1 = new SiYuanStyle();
        hh1->operation = "ENTRY";
        hh1->left = s->name[0];
        SiYuan.push_back(hh1);
        DFS(s->child[2]->child[0]);
        SiYuanStyle* hh2 = new SiYuanStyle();
        hh2->operation = "ENDPROC";
        SiYuan.push_back(hh2);
    }
    //循环语句四元式
    void WhileStyle(DiguiSpace::TreeNode* s) {
        string temp1;
        SiYuanStyle* hh1 = new SiYuanStyle();
        hh1->operation = "WHILE";
        SiYuan.push_back(hh1);
        temp1 = IDcreate();
        StmtK(s->child[0], temp1);
        SiYuanStyle* hh2 = new SiYuanStyle();
        hh2->operation = "DO";
        hh2->left = temp1;
        SiYuan.push_back(hh2);
        DFS(s->child[1]);
        SiYuanStyle* hh3 = new SiYuanStyle();
        hh3->operation = "ENDWHILE";
        SiYuan.push_back(hh3);
    }
    //条件语句四元式
    void IfStyle(DiguiSpace::TreeNode* s) {
        string temp1 = IDcreate();
        StmtK(s->child[0], temp1);
        SiYuanStyle* hh2 = new SiYuanStyle();
        hh2->operation = "THEN";
        hh2->left = temp1;
        SiYuan.push_back(hh2);
        DFS(s->child[1]);
        if (s->child[2] != NULL) {
            SiYuanStyle* hh3 = new SiYuanStyle();
            hh3->operation = "ELSE";
            SiYuan.push_back(hh3);
            DFS(s->child[2]);
        }
        SiYuanStyle* hh3 = new SiYuanStyle();
        hh3->operation = "ENDIF";
        SiYuan.push_back(hh3);
    }
    //输入语句四元式
    void readStyle(DiguiSpace::TreeNode* s) {
        SiYuanStyle* hh1 = new SiYuanStyle();
        hh1->operation = "READ";
        hh1->id = s->name[0];
        SiYuan.push_back(hh1);
    }
    //输出语句四元式
    void writeStyle(DiguiSpace::TreeNode* s) {
        SiYuanStyle* hh1 = new SiYuanStyle();
        hh1->operation = "WRITE";
        string temp1;
        if (s->child[0]->kind.exp == DiguiSpace::OpK) {
            temp1 = IDcreate();
            StmtK(s->child[0], temp1);
        }
        else if (s->child[0]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
            temp1 = array(s, 0);
        }
        else if (s->child[0]->kind.exp == DiguiSpace::IdEK) {
            temp1 = s->child[0]->name[0];
        }
        else if (s->child[0]->kind.exp == DiguiSpace::ConstK) {
            temp1 = to_string(s->child[0]->attr.expAttr.val);
        }
        hh1->id = temp1;
        SiYuan.push_back(hh1);
    }
    //下标变量四元式
    string array(DiguiSpace::TreeNode* s,int i) {
        string temp11="";
        DiguiSpace::TreeNode* s1 = s->child[i];
        //StmtK(s->child[i], temp11);
        if (s1->child[0]->kind.exp == DiguiSpace::OpK) {
            temp11 = IDcreate();
            StmtK(s1->child[0], temp11);
        }
        else if (s1->child[0]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
            temp11 = array(s1->child[0], 0);
        }
        else if (s1->child[0]->kind.exp == DiguiSpace::IdEK) {
            temp11 = s1->child[0]->name[0];
        }
        else if (s1->child[0]->kind.exp == DiguiSpace::ConstK) {
            temp11 = to_string(s1->child[0]->attr.expAttr.val);
        }

        SiYuanStyle* hh1 = new SiYuanStyle();
        hh1->operation = "SUBI";
        hh1->right = "1";
        hh1->left = temp11;
        string temp12 = IDcreate();
        hh1->id = temp12;
        SiYuan.push_back(hh1);

        SiYuanStyle* hh2 = new SiYuanStyle();
        hh2->operation = "MULTI";
        hh2->right = "1";
        hh2->left = temp12;
        string temp13 = IDcreate();
        hh2->id = temp13;
        SiYuan.push_back(hh2);

        SiYuanStyle* hh3 = new SiYuanStyle();
        hh3->operation = "AADD";
        hh3->right = s->child[i]->name[0];
        hh3->left = temp13;
        string temp14 = IDcreate();
        hh3->id = temp14;
        SiYuan.push_back(hh3);

        SiYuanStyle* hh4 = new SiYuanStyle();
        hh4->operation = "ASSIG";
        hh4->left = temp14;
        string temp1 = IDcreate();
        hh4->id = temp1;
        SiYuan.push_back(hh4);
        return temp1;
    }
    //运算四元式
    void StmtK(DiguiSpace::TreeNode* s, string ID) {
        string temp1, temp2;

        if (s->child[0]->kind.exp == DiguiSpace::OpK) {
            temp1 = IDcreate();
            StmtK(s->child[0], temp1);
        }
        else if (s->child[0]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
            temp1 = array(s, 0);
        }
        else if (s->child[0]->kind.exp == DiguiSpace::IdEK) {
            temp1 = s->child[0]->name[0];
        }
        else if (s->child[0]->kind.exp == DiguiSpace::ConstK) {
            temp1 = to_string(s->child[0]->attr.expAttr.val);
        }

        if (s->child[1]->kind.exp == DiguiSpace::OpK) {
            temp2 = IDcreate();
            StmtK(s->child[1], temp2);
        }
        else if (s->child[1]->attr.expAttr.varkind == DiguiSpace::ArrayMembV) {
            temp2 = array(s, 1);
        }
        else if (s->child[1]->kind.exp == DiguiSpace::IdEK) {
            temp2 = s->child[1]->name[0];
        }
        else if (s->child[1]->kind.exp == DiguiSpace::ConstK) {
            temp2 = to_string(s->child[1]->attr.expAttr.val);
        }

        SiYuanStyle* hh = new SiYuanStyle();
        if (s->attr.expAttr.op == "\\") {
            hh->operation = "DIVI";
        }
        else if (s->attr.expAttr.op == "*") {
            hh->operation = "MULTI";
        }
        else if (s->attr.expAttr.op == "+") {
            hh->operation = "ADDI";
        }
        else if (s->attr.expAttr.op == "-") {
            hh->operation = "SUBI";
        }
        else if (s->attr.expAttr.op == "<") {
            hh->operation = "LT";
        }
        else if (s->attr.expAttr.op == "=") {
            hh->operation = "EQ";
        }
        hh->left = temp1;
        hh->right = temp2;
        hh->id = ID;
        SiYuan.push_back(hh);
        return;
    }
    //这是施季中的两个函数
    bool isNum(string str)
    {
        stringstream sin(str);
        double d;
        char c;
        if (!(sin >> d))
            return false;
        if (sin >> c)
            return false;
        return true;
    }
    int StringToNum(string str) {
        if (isNum(str)) {
            return stoi(str, 0, 10);
        }
        else
        {
            return -1;
        }
    }

    //以下是常量表达式的优化，结果在CLYH_Res中
    vector<SiYuanStyle*> CLYH_res;
    void ChangLiangYouHua() {
        CLYH_res.clear();
        map<string, int> conDef;
        //基本思路是一边进行基本块划分，一边进行优化，为了简化程序，默认ASSIG的第二个参数不为引用形参
        for (auto i : SiYuan) {
            if (i->operation == "ENTRY" || i->operation == "WHILE" || i->operation == "JMP" ||
                i->operation == "JUMP0" || i->operation == "JUMP1" || i->operation == "ENDPROC" ||
                i->operation == "THEN" || i->operation == "ELSE" || i->operation == "DO" || i->operation == "ENDWHILE")
            {
                conDef.clear();
                CLYH_res.push_back(i);
            }
            else if (i->operation == "ASSIG") {
                if (i->operation == "ASSIG" && isNum(i->left)) {
                    conDef[i->id] = StringToNum(i->left);
                    CLYH_res.push_back(i);
                }
                else if (conDef.find(i->left) != conDef.end()) {
                    conDef[i->id] = conDef[i->left];
                    SiYuanStyle* temp = new SiYuanStyle();
                    temp->operation = i->operation;
                    temp->right = i->right;
                    temp->id = i->id;
                    temp->left = to_string(conDef[i->id]);
                    CLYH_res.push_back(temp);
                }
                else {
                    if (conDef.find(i->id) != conDef.end()) {
                        conDef.erase(conDef.find(i->id));
                    }
                    CLYH_res.push_back(i);
                }
            }
            else if (i->operation == "ADDI" || i->operation == "MULTI" || i->operation == "SUBI" || i->operation == "DIVI") {
                if (isNum(i->left) && isNum(i->right)) {
                    if (i->operation == "ADDI")conDef[i->id] = StringToNum(i->left) + StringToNum(i->right);
                    else if (i->operation == "MULTI")conDef[i->id] = StringToNum(i->left) * StringToNum(i->right);
                    else if (i->operation == "SUBI")conDef[i->id] = StringToNum(i->left) - StringToNum(i->right);
                    else if (i->operation == "DIVI")conDef[i->id] = StringToNum(i->left) / StringToNum(i->right);
                }
                else if (isNum(i->left) && conDef.find(i->right) != conDef.end()) {
                    if (i->operation == "ADDI")conDef[i->id] = StringToNum(i->left) + conDef[i->right];
                    else if (i->operation == "MULTI")conDef[i->id] = StringToNum(i->left) * conDef[i->right];
                    else if (i->operation == "SUBI")conDef[i->id] = StringToNum(i->left) - conDef[i->right];
                    else if (i->operation == "DIVI")conDef[i->id] = StringToNum(i->left) / conDef[i->right];
                }
                else if (isNum(i->right) && conDef.find(i->left) != conDef.end()) {
                    if (i->operation == "ADDI")conDef[i->id] = conDef[i->left] + StringToNum(i->right);
                    else if (i->operation == "MULTI")conDef[i->id] = conDef[i->left] * StringToNum(i->right);
                    else if (i->operation == "SUBI")conDef[i->id] = conDef[i->left] - StringToNum(i->right);
                    else if (i->operation == "DIVI")conDef[i->id] = conDef[i->left] / StringToNum(i->right);
                }
                else if (conDef.find(i->right) != conDef.end() && conDef.find(i->left) != conDef.end()) {
                    if (i->operation == "ADDI")conDef[i->id] = conDef[i->left] + conDef[i->right];
                    else if (i->operation == "MULTI")conDef[i->id] = conDef[i->left] * conDef[i->right];
                    else if (i->operation == "SUBI")conDef[i->id] = conDef[i->left] - conDef[i->right];
                    else if (i->operation == "DIVI")conDef[i->id] = conDef[i->left] / conDef[i->right];
                }
                else {
                    SiYuanStyle* temp = new SiYuanStyle();
                    temp->operation = i->operation;
                    temp->right = i->right;
                    temp->id = i->id;
                    temp->left = i->left;
                    if (conDef.find(i->left) != conDef.end())temp->left = to_string(conDef[i->left]);
                    if (conDef.find(i->right) != conDef.end())temp->right = to_string(conDef[i->right]);
                    CLYH_res.push_back(temp);
                }
            }
        }
    }

    //以下是公共表达式优化，结果在GGYH_Res
    int value = 0;
    map<string, int> ValuNum;
    vector<int> UE;//优衣对不起
    vector<SiYuanStyle*> GGYH_res;
    map<string, string> PAIR;
    void GongGongYouHua() {
        ValuNum.clear();
        UE.clear();
        GGYH_res.clear();
        PAIR.clear();
        map<string, int> conDef;
        //基本思路是一边进行基本块划分，一边进行优化，为了简化程序，默认ASSIG的第二个参数不为引用形参
        for (auto i : SiYuan) {
            if (i->operation == "ENTRY" || i->operation == "WHILE" || i->operation == "JMP" ||
                i->operation == "JUMP0" || i->operation == "JUMP1" || i->operation == "ENDPROC" ||
                i->operation == "THEN" || i->operation == "ELSE" || i->operation == "DO" || i->operation == "ENDWHILE")
            {
                ValuNum.clear();
                UE.clear();
                GGYH_res.push_back(i);
            }//基本块划分
            else if (i->operation == "ASSIG") {
                //从UE中删除与该语句id相同的，同时也删除PAIR值为id的式子
                vector<int>::iterator j = UE.begin();
                while (j!=UE.end() ){
                    if (GGYH_res[*j]->left == i->id || GGYH_res[*j]->right == i->id || GGYH_res[*j]->id == i->id) {
                        j=UE.erase(j);
                    }
                    j++;
                }
                map<string,string>::iterator h = PAIR.begin();
                while (h != PAIR.end()) {
                    if (h->second==i->id) {
                        h = PAIR.erase(h);
                    }
                    h++;
                }
                //如果A没在里面且不为数字，就填到里面去
                if (!isNum(i->left)&&ValuNum.find(i->left) == ValuNum.end()) {
                    ValuNum[i->left] = value;
                    value++;
                }
                //让B和A的码保持一致
                ValuNum[i->id] = ValuNum[i->left];
                SiYuanStyle* temp = new SiYuanStyle();
                temp->operation = i->operation;
                temp->right = i->right;
                temp->left = i->left;
                temp->id = i->id;
                if (!isNum(i->left) && PAIR.find(i->left) != PAIR.end()) {
                    temp->left = PAIR[i->left];
                }
                GGYH_res.push_back(temp);//保存语句
            }
            else if (i->operation == "ADDI" || i->operation == "MULTI" || i->operation == "SUBI" || i->operation == "DIVI") {
                //查找UE中有没有等价的
                if (!isNum(i->left) && ValuNum.find(i->left) == ValuNum.end()) {
                    ValuNum[i->left] = value;
                    value++;
                }//左侧不为数字首次出现
                if (!isNum(i->right) && ValuNum.find(i->right) == ValuNum.end()) {
                    ValuNum[i->right] = value;
                    value++;
                }//右侧不为数字首次出现
                if (!isNum(i->left) && !isNum(i->right)) {
                    bool flag = false;
                    vector<int>::iterator j = UE.begin();
                    while (j != UE.end()) {
                        if (ValuNum[GGYH_res[*j]->left] == ValuNum[i->left]
                            && ValuNum[GGYH_res[*j]->right] == ValuNum[i->right] ){
                            PAIR[i->id] = GGYH_res[*j]->id;
                            ValuNum[i->id] = ValuNum[GGYH_res[*j]->id];
                            flag = true;
                            break;
                        }
                        j++;
                    }
                    if (flag == false) {
                        ValuNum[i->id] = value;
                        value++;
                        UE.push_back(GGYH_res.size());
                        SiYuanStyle* temp = new SiYuanStyle();
                        temp->operation = i->operation;
                        temp->right = i->right;
                        temp->left = i->left;
                        temp->id = i->id;
                        if (!isNum(i->left) && PAIR.find(i->left) != PAIR.end()) {
                            temp->left = PAIR[i->left];
                        }
                        if (!isNum(i->right) && PAIR.find(i->right) != PAIR.end()) {
                            temp->right = PAIR[i->right];
                        }
                        if (!isNum(i->id) && PAIR.find(i->id) != PAIR.end()) {
                            temp->id = PAIR[i->id];
                        }
                        GGYH_res.push_back(temp);//保存语句
                    }
                }
                else {
                    SiYuanStyle* temp = new SiYuanStyle();
                    temp->operation = i->operation;
                    temp->right = i->right;
                    temp->left = i->left;
                    temp->id = i->id;
                    if (!isNum(i->left) && PAIR.find(i->left) != PAIR.end()) {
                        temp->left = PAIR[i->left];
                    }
                    if (!isNum(i->right) && PAIR.find(i->right) != PAIR.end()) {
                        temp->right = PAIR[i->right];
                    }
                    if (!isNum(i->id) && PAIR.find(i->id) != PAIR.end()) {
                        temp->id = PAIR[i->id];
                    }
                    GGYH_res.push_back(temp);//保存语句
                }
            }
        }
    }

    //以下是循环不变式外提，结果存储在XHYH_res;
    struct Loopdef {
        set<string> str;
        Loopdef* front;
        vector<Loopdef*> inside;//可能有多个嵌套循环
        vector<SiYuanStyle*> vec;
        vector<SiYuanStyle*> t1;
        int read_num;
        int read_num1;
        Loopdef() {
            front = NULL;
            read_num = 0;
            read_num1 = 0;
        }
    };
    map<int, int>waiti;
    Loopdef* head = new Loopdef();//表头，不是循环，也就是最外层
    vector<SiYuanStyle*> XHYH_res;
    void DFSS(Loopdef* tempptr) {
        bool flag = true;
        for (auto i : tempptr->vec) {
            if (tempptr==head&&i->operation == "WHILE") {
                int ti = head->read_num1;
                head->read_num1++;
                DFSS(head->inside[ti]);
            }else if(tempptr != head &&flag == false && i->operation == "WHILE") {
                int ti = tempptr->read_num1;
                tempptr->read_num1++;
                DFSS(tempptr->inside[ti]);
            }else if(tempptr != head &&flag==true){
                flag = false;
                XHYH_res.push_back(i);
            }
            else XHYH_res.push_back(i);
        }
    }
    void DFSS1(Loopdef* now) {
        for (auto &i : now->vec) {
            now->t1.push_back(i);
        }
        now->vec.clear();
        bool flag = false;
        for (auto &i : now->t1) {
            set<string>::iterator result = find(now->str.begin(), now->str.end(), i->left);
            set<string>::iterator result1 = find(now->str.begin(), now->str.end(), i->right);
            if (now != head && result == now->str.end() && result1 == now->str.end() &&
                (i->operation == "LT" || i->operation == "ADDI" || i->operation == "MULTI"
                    || i->operation == "SUBI" || i->operation == "EQ")) {
                //把id从str中抹掉,产生式不进入vec,而进入最前面满足要求的
                set<string>::iterator result2 = find(now->str.begin(), now->str.end(), i->id);
                if(result2!=now->str.end())now->str.erase(result2);
                Loopdef* temp = now;
                temp = temp->front;
                while (temp != head) {
                    set<string>::iterator result3 = find(temp->str.begin(), temp->str.end(), i->left);
                    set<string>::iterator result4 = find(temp->str.begin(), temp->str.end(), i->right);
                    if (result3 == temp->str.end() && result4 == temp->str.end()) {
                        temp = temp->front;
                    }
                    else break;
                }
                temp->vec.push_back(i);
                temp->str.insert(i->id);
            }else if(i->operation == "WHILE" && (now != head && flag == false)){
                flag = true;
                now->vec.push_back(i);
            }else if (i->operation == "WHILE"&&((now==head)||(now!=head&&flag==true))) {
                int ti = now->read_num;
                now->read_num++;
                DFSS1(now->inside[ti]);
                now->vec.push_back(i);
            }else now->vec.push_back(i);
        }
        now->t1.clear();
    }
    void XunHuanYouHua() {
        //第一遍扫描，建立Loopdef表
        waiti.clear();
        XHYH_res.clear();
        int h = 0;
        head = new Loopdef();
        Loopdef* now = head;
        int num = 0;
        int level=0;
        for (auto i : SiYuan) {
            if (i->operation == "WHILE") {
                Loopdef* xr = new Loopdef();
                now->vec.push_back(i);
                xr->vec.push_back(i);
                now->inside.push_back (xr);
                xr->front = now;
                now = xr;
                h++;
                level = max(level, h);
            }
            else if (i->operation == "ENDWHILE") {
                now->vec.push_back(i);
                h--;
                now = now->front;//返回。
            }
            else if (h > 0) {
                if(i->operation!="WHILE"&&i->operation!="ENDWHILE"&&i->operation!="DO")now->str.insert(i->id);
                now->vec.push_back(i);
            }
            else now->vec.push_back(i);
            num++;
        }
        //第二遍扫描，循环不变式外提
        DFSS1(head);
        DFSS(head);
    }


}
