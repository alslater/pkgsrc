#ifndef LINKLIST_H
#define LINKLIST_H

template < class C >
struct lstElem {
	lstElem *next;
	lstElem *prev;
	C *c;

    lstElem ()
	{
		next = 0;
		prev= 0;
		c = 0;
	}

	lstElem (C *newC, lstElem *lst)
	{
		c = newC;
		next = lst;

        if (lst)
		   lst->prev = this;
	}
};

template <class C>
class ElemLstIterator {
private:
	lstElem<C> *lst;
public:
	ElemLstIterator (lstElem<C> *newLst)
    {
       lst = newLst;
    }

    C *getThis ()
    {
       return lst ? lst->c : 0;
    }

    C *getNext ()
    {
       if (lst)
          lst = lst->next;

       return getThis ();
    }
};

template <class C>
class ElemLst {
private:
	lstElem<C> *lst;
public:
	ElemLst ()
    {
       lst = 0;
    }

    lstElem<C> *getLst ()
    {
       return lst;
    }

	void Add (C *c)
	{
	   lst = new lstElem<C>(c, lst);
	   lst->prev=0;
	}

    ElemLstIterator<C> *getIter ()
    {
       return new ElemLstIterator<C>(lst);
    }
};

#endif

