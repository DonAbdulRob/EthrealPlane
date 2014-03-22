/* Defines the class MyList. */

#ifndef _LIST_H_
#define _LIST_H_

class MyList
{
protected:
	int size_;
	int index_;

public:
	MyList();

	/* General */
	void setSize (int x);
	void resetIndex() {index_ = 0;}

	/* Gets */
	int getSize() {return size_;}
	int getIndex() {return index_;}
	
	/* Icreases */
	void increaseIndex() {index_++;}

	/* Decreases */
	void decreaseIndex() {index_--;}
};

/*
class StringList: public MyList
{
protected:
	string* element_;

public:
	StringList(int size);


};
*/

class IntegerList: public MyList
{
protected:
	int* element_;

public:
	IntegerList();

	/* General */
	void resetList ();
	bool isFull    ();
	void popBack   ();
	void pushBack  (int x);
	void insert    (int newElement, int position);

	/* Gets */
	int getSize    () {return size_;}

	int getElement (int element) {return element_[element];}

	/* Sets */
	int setElement (int element, int newValue) {element_[element] = newValue;}
};


#endif
