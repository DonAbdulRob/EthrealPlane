#include "attributes.h"

Attributes::Attributes()
{
	 for (int i = 0; i < 4; i++) 
		 a[i] = 0;
}

Attributes::Attributes(int attributes[])
{
	for (int i = 0; i < 4; i++) {
		a[i] = attributes[i];
	}
}