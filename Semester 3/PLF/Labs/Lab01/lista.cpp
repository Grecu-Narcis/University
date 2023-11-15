#include "lista.h"
#include <iostream>

using namespace std;


int lcm(int a, int b)
{
	if (b == 0)
		return 0;

	int r, copy_a = a, copy_b = b;

	while (b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}

	return copy_a * copy_b / a;
}

int lcm_rec(PNod a, PNod b)
{
	if (b == nullptr)
		return a->e;

	if (b->urm == nullptr)
	{
		return lcm(a->e, b->e);
	}

	int rec_lcm = lcm_rec(b, b->urm);

	return lcm(a->e, rec_lcm);
}

int lcm(Lista l)
{
	return lcm_rec(l._prim, l._prim->urm);
}

void substitute_rec(PNod head, TElem old_value, TElem new_value)
{
	if (head == nullptr)
		return;

	if (head->e == old_value)
		head->e = new_value;

	substitute_rec(head->urm, old_value, new_value);
}

void substitute(Lista l)
{
	TElem old_value, new_value;

	cout << "Value to be replaced: ";
	cin >> old_value;

	cout << "Value used for replace: ";
	cin >> new_value;

	substitute_rec(l._prim, old_value, new_value);
}


PNod creare_rec(){
  TElem x;
  cout<<"x=";
  cin>>x;
  if (x==0)
    return NULL;
  else{
    PNod p=new Nod();
    p->e=x;
    p->urm=creare_rec();
    return p;
  }
}

Lista creare(){
   Lista l;
   l._prim=creare_rec();
   return l;
}

void tipar_rec(PNod p){
   if (p!=NULL){
     cout<<p->e<<" ";
     tipar_rec(p->urm);
   }
}

void tipar(Lista l){
   tipar_rec(l._prim);
}

void distrug_rec(PNod p){
   if (p!=NULL){
     distrug_rec(p->urm);
     delete p;
   }
}

void distrug(Lista l) {
	//se elibereaza memoria alocata nodurilor listei
    distrug_rec(l._prim);
}

