#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include <iostream>

void testAll() {
	MultiMap m;
	m.add(1, 100);
	m.add(2, 200);
	m.add(3, 300);
	m.add(1, 500);
	m.add(2, 600);
	m.add(4, 800);

	assert(m.size() == 6);

	assert(m.remove(5, 600) == false);
	assert(m.remove(1, 500) == true);

	assert(m.size() == 5);

    vector<TValue> v;
	v=m.search(6);
	assert(v.size()==0);

	v=m.search(1);
	assert(v.size()==1);

	assert(m.isEmpty() == false);

	MultiMapIterator im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.getCurrent();
		im.next();
	}
	assert(im.valid() == false);
	im.first();
	assert(im.valid() == true);


	//TEST Bonus
	MultiMap bonus;
	bonus.add(1, 100);
	bonus.add(2, 200);
	bonus.add(4, 300);
	bonus.add(3, 200);
	bonus.add(10, 200);
	bonus.add(5, 200);
	//cout << bonus.minKey()<<endl;
	assert(bonus.minKey() == 1);
	
	MultiMap bonus1;
	assert(bonus1.minKey() == 0);
}
