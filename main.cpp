#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
char s[100];
int i=0;
struct tree
{
    char id;
    tree *l,*r;
};
tree *A=NULL;
tree* form();
tree* term();
tree* gen(char c)
{
    tree* tmp=new tree;
    tmp->id=c;
    tmp->l=NULL;
    tmp->r=NULL;
    return tmp;

}
tree* atom()
{
    if(s[i]=='1'||s[i]=='0')
    {
        i++;
        return gen(s[i-1]);

    }
    if(s[i]=='!')
    {
        tree* tmp=gen(s[i]);
        i++;
        tree* t1=atom();
        tmp->l=t1;
        tmp->r=NULL;
        return tmp;
    }
    if(s[i]=='(')
    {
        i++;
        tree* t1=form();
        i++;
        return t1;
    }
}
tree* form()
{
    tree* t1=term();
    while(s[i]=='+')
    {
        tree* p=gen(s[i]);
        i++;
        p->l=t1;
        t1=term();
        p->r=t1;
        t1=p;
    }
    return t1;

}
tree* term()
{
    tree* t1=atom();
    while(s[i]=='*')
    {
        tree* p=gen(s[i]);
        i++;
        p->l=t1;
        t1=atom();
        p->r=t1;
        t1=p;
    }
    return t1;

}
void show(tree *t, int n)
{
    if(t!=NULL)
    {
        show(t->l,n+1);
        cout <<setw(n*3)<<t->id<<endl;
        show(t->r,n+1);
    }

}
bool znach(tree* tr)
{
    if(tr->id=='0')return 0;
    if(tr->id=='1')return 1;
    if(tr->id=='!')return !znach(tr->l);
    if(tr->id=='+')return znach(tr->l)+znach(tr->r);
    if(tr->id=='*')return znach(tr->l)*znach(tr->r);

}

int main()
{
    ifstream fin("input.txt");
    fin.getline(s,100);
    fin.close();
    A=form();
    show(A,1);
    cout<<"Znachenie vyrazheniya: "<<znach(A);
    return 0;
}
