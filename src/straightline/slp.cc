#include "straightline/slp.h"

namespace A {
int A::CompoundStm::MaxArgs() const {
  // TODO: put your code here (lab1).
  int max1 = stm1->MaxArgs();
  int max2 = stm2->MaxArgs();
  if (max1 > max2) return max1;
  return max2;
}

Table *A::CompoundStm::Interp(Table *t) const {
  // TODO: put your code here (lab1).
  Table *t1 = stm1->Interp(t);
  Table *t2 = stm2->Interp(t1);
  return t2;
}

int A::AssignStm::MaxArgs() const {
  // TODO: put your code here (lab1).
  return exp->MaxArgs();
}

Table *A::AssignStm::Interp(Table *t) const {
  // TODO: put your code here (lab1).
  Table *newt = new Table(id,exp->Interp(t)->i,t);
  return newt;
}

int A::PrintStm::MaxArgs() const {
  int max1 = exps->NumExps();
  int max2 = exps->MaxArgs();
  if(max1 > max2) return max1;
  else return max2;
}

Table *A::PrintStm::Interp(Table *t) const {
  IntAndTable *it1 = exps->PrintExps(t);
  return it1->t;
}

int A::IdExp::MaxArgs() const {
  return 0;
}
IntAndTable *A::IdExp::Interp(Table *t) const {
  return new IntAndTable(t->Lookup(id),t);
}

int A::NumExp::MaxArgs() const {
  return 0;
}
IntAndTable *A::NumExp::Interp(Table *t) const {
  return new IntAndTable(num,t);
}

int A::OpExp::MaxArgs() const {
  int max1 = left->MaxArgs();
  int max2 = right->MaxArgs();
  if(max1 > max2) return max1;
  else return max2;
}
IntAndTable *A::OpExp::Interp(Table *t) const {
  IntAndTable *it1 = left->Interp(t);
  IntAndTable *it2 = right->Interp(it1->t);
  int res;
  switch(oper){
    case PLUS:
      res = it1->i + it2->i;
      break;
    case MINUS:
      res = it1->i - it2->i;
      break;
    case TIMES:
      res = it1->i * it2->i;
      break;
    case DIV:
      res = it1->i / it2->i;
      break;
    default:
      res = 0;
  }
  return new IntAndTable(res,it2->t);
}

int A::EseqExp::MaxArgs() const {
  int max1 = stm->MaxArgs();
  int max2 = exp->MaxArgs();
  if(max1 > max2) 
    return max1;
  else return max2;
}
IntAndTable *A::EseqExp::Interp(Table *t) const {
  Table *t1 = stm->Interp(t);
  return exp->Interp(t1);
}

int A::PairExpList::MaxArgs() const {
  int max1 = head->MaxArgs();
  int max2 = tail->MaxArgs();
  if(max1 > max2) return max1;
  else return max2;
}
int A::PairExpList::NumExps() const {
  return 1 + tail->NumExps();
}
IntAndTable *A::PairExpList::PrintExps(Table *t) const {
  IntAndTable *it1 = head->Interp(t);
  printf("%d ",it1->i);
  IntAndTable *it2 = tail->PrintExps(it1->t);
  return it2;
}
IntAndTable *A::PairExpList::Interp(Table *t) const {
  IntAndTable *it1 = head->Interp(t);
  IntAndTable *it2 = tail->Interp(it1->t);
  return it2;
}

int A::LastExpList::MaxArgs() const {
  return last->MaxArgs();
}
int A::LastExpList::NumExps() const {
  return 1;
}
IntAndTable *A::LastExpList::PrintExps(Table *t) const {
  IntAndTable *it1 = last->Interp(t);
  printf("%d\n",it1->i);
  return it1;
}
IntAndTable *A::LastExpList::Interp(Table *t) const {
  return last->Interp(t);
}


int Table::Lookup(std::string key) const {
  if (id == key) {
    return value;
  } else if (tail != nullptr) {
    return tail->Lookup(key);
  } else {
    assert(false);
  }
}

Table *Table::Update(std::string key, int value) const {
  return new Table(key, value, this);
}
}  // namespace A
