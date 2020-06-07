#pragma once
//主要是翻译部分
//为了简单起见，本报告所有的变量都是直接变量，而不是间接变量
//模拟单寄存器机器，寄存器为R，且不考虑过程活动记录的问题
#include"DFS.h"
namespace target {
    struct HuiBian {
        string op;
        string str1;
        string str2;
        HuiBian() {
            str1 = "";
            str2 = "";
        }
    };

    vector<HuiBian*> TargetCode;
    stack<int> while1;//开头地址
    stack<HuiBian*> while2;//没填完的四元式
    stack<HuiBian*> if_s;//条件语句四元式

    void Translation(vector<DFS::SiYuanStyle*> temp) {
        TargetCode.clear();
        while(!while1.empty())while1.pop();
        while(!while2.empty())while2.pop();
        while(!if_s.empty())if_s.pop();
        //初始化
        for (auto i : temp) {
            if (i->operation == "ADDI" || i->operation == "SUBI" || i->operation == "MULTI"
                || i->operation == "DIVI" || i->operation == "LT" || i->operation == "EQ") {
                HuiBian* s1=new HuiBian();
                s1->op = "LD";
                s1->str2 = i->left;
                s1->str1 = "R";
                TargetCode.push_back(s1);
                HuiBian* s2 = new HuiBian();
                s2->op = i->operation;
                s2->str2 = i->right;
                s2->str1 = "R";
                TargetCode.push_back(s2);
                HuiBian* s3 = new HuiBian();
                s3->op = "ST";
                s3->str2 = "R";
                s3->str1 = i->id;
                TargetCode.push_back(s3);
            }
            else if (i->operation == "ASSIG") {
                HuiBian* s1 = new HuiBian();
                s1->op = "LD";
                s1->str2 = i->left;
                s1->str1 = "R";
                TargetCode.push_back(s1);
                HuiBian* s3 = new HuiBian();
                s3->op = "ST";
                s3->str2 = "R";
                s3->str1 = i->id;
                TargetCode.push_back(s3);
            }
            else if (i->operation == "READ") {
                HuiBian* s1 = new HuiBian();
                s1->op = "IN";
                s1->str1 = "R";
                TargetCode.push_back(s1);
                HuiBian* s3 = new HuiBian();
                s3->op = "ST";
                s3->str2 = "R";
                s3->str1 = i->id;
                TargetCode.push_back(s3);
            }
            else if (i->operation == "WRITE") {
                HuiBian* s3 = new HuiBian();
                s3->op = "LD";
                s3->str1 = "R";
                s3->str2 = i->id;
                TargetCode.push_back(s3);
                HuiBian* s1 = new HuiBian();
                s1->op = "OUT";
                s1->str1 = "R";
                TargetCode.push_back(s1);
            }
            else if (i->operation == "ValACT") {
                HuiBian* s1 = new HuiBian();
                s1->op = "LD";
                s1->str2 = i->left;
                s1->str1 = "R";
                TargetCode.push_back(s1);
                HuiBian* s3 = new HuiBian();
                s3->op = "ST";
                s3->str2 = "R";
                s3->str1 ="sp("+i->id+")";
                TargetCode.push_back(s3);
            }
            else if (i->operation == "VarACT") {
                HuiBian* s1 = new HuiBian();
                s1->op = "LEA";
                s1->str2 = i->left;
                s1->str1 = "R";
                TargetCode.push_back(s1);
                HuiBian* s3 = new HuiBian();
                s3->op = "ST";
                s3->str2 = "R";
                s3->str1 = "sp(" + i->id + ")";
                TargetCode.push_back(s3);
            }
            else if (i->operation == "ENDPROC") {
                HuiBian* s1 = new HuiBian();
                s1->op = "ST";
                s1->str2 ="sp";
                s1->str1 = "top";
                TargetCode.push_back(s1);
                HuiBian* s2 = new HuiBian();
                s2->op = "LD";
                s2->str2 = "0(top)";
                s2->str1 = "sp";
                TargetCode.push_back(s2);
                HuiBian* s3 = new HuiBian();
                s3->op = "JMP";
                s3->str1 ="1(top)";
                TargetCode.push_back(s3);
            }
            else if (i->operation == "WHILE") {
                while1.push(TargetCode.size() + 1);
            }
            else if (i->operation == "DO") {
                HuiBian* s2 = new HuiBian();
                s2->op = "LD";
                s2->str1 = "R";
                s2->str2 = i->left;
                TargetCode.push_back(s2);
                HuiBian* s3 = new HuiBian();
                s3->op = "JUMP0";
                s3->str1 = "R";
                while2.push(s3);
                TargetCode.push_back(s3);
            }
            else if (i->operation == "ENDWHILE"){
                HuiBian* s3 = new HuiBian();
                s3->op = "JUMP0";
                s3->str1 = to_string(while1.top());
                while1.pop();
                HuiBian* ttt=while2.top();
                TargetCode.push_back(s3);
                ttt->str2 = to_string(TargetCode.size() + 1);
            }
            else if (i->operation == "IF") {
                HuiBian* s2 = new HuiBian();
                s2->op = "LD";
                s2->str1 = "R";
                s2->str2 = i->left;
                TargetCode.push_back(s2);
                HuiBian* s3 = new HuiBian();
                s3->op = "JUMP0";
                s3->str1 = "R";
                if_s.push(s3);
                TargetCode.push_back(s3);
            }
            else if (i->operation=="ELSE") {
                HuiBian* s3 = new HuiBian();
                s3->op = "JMP";
                if_s.push(s3);
                TargetCode.push_back(s3);
                HuiBian* t1 = if_s.top();
                if (t1->op == "JUMP0") {
                    if_s.pop();
                    t1->str2 = to_string(TargetCode.size() + 1);
                }
            }
            else if (i->operation=="ENDIF") {
                HuiBian* t1=if_s.top();
                if_s.pop();
                if (t1->op == "JMP") {
                    t1->str1 = to_string(TargetCode.size() + 1);
                }
                else if (t1->op == "JUMP0") {
                    t1->str2 = to_string(TargetCode.size() + 1);
                }
            }
        }
    }
}
