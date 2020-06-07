#ifndef SEMANTICERROR_H
#define SEMANTICERROR_H
#include <string>
#include <list>
#include <QString>
using namespace std;
struct SemanticErrorPoint
{
    int lineN;
    QString E_Mess;

    SemanticErrorPoint(int l0,QString s)
    {
        lineN=l0;
        E_Mess=s;
    }

};
list<SemanticErrorPoint>* SemErrorList=new list<SemanticErrorPoint>();
#endif // SEMANTICERROR_H
