#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

class Attributes
{
protected:
	int a[4];

public:
	Attributes();
	Attributes(int[]);

	/* Gets */
	int getAttribute(int x) {return a[x];}

	/* Sets */
	void setAttribute(int x, int y) {a[x] = y;}

	/*Increases */
	void increaseAttribute(int x, int y) {a[x] += y;}
	void incrementAttribute(int x) {a[x]++;}

	/* Decreases */
	void decreaseAttribute(int x, int y) {a[x] += y;}
	void decrementAttributde(int x) {a[x]--;}
};

#endif