#include <stdio.h>
#include <stdlib.h>
#include "map.h"

#define TABLE_SIZE 1000

struct map {
	List table[TABLE_SIZE];
	int (*hash)(void *); //hash function
	int (*equals)(void *, void *); //equality function
};

struct mapentry {
	void *key;
	void *value;
};

typedef struct mapentry *MapEntry;

static MapEntry newEntry(void *key, void *value);
static List getList(Map m, int index);

Map Map_new(int (*equals)(void *key1, void *key2), int (*hash)(void *key)) {
	Map m = (Map) malloc(sizeof(struct map));
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		m->table[i] = List_new();
	}
	m->hash = hash;
	m->equals = equals;
	return m;
}

void *Map_get(Map m, void *key) {
	int (*hash)(void *) = m->hash;
	int (*equal)(void *, void *) = m->equals;
	int index = hash(key);
	if (index >= TABLE_SIZE)
		index = index%TABLE_SIZE;

	List list = getList(m,index);
	Iterator iter = List_iterator(list);
	while (Iterator_hasNext(iter)) {
		//printf("we made it\n");
		MapEntry entry = (MapEntry) Iterator_next(iter);
		if (equal(entry->key,key)) {
			Iterator_free(iter);
			return entry->value;
		}
	}
	return NULL;
}

void Map_put(Map m, void *key, void *value) {

	void *item = Map_get(m,key);
	int (*hash)(void *) = m->hash;
	int index = hash(key);
	if (index >= TABLE_SIZE)
		index = index%TABLE_SIZE;
		
	List list = getList(m,index);
	if (item == NULL) {
		MapEntry entry = newEntry(key,value);
		List_add(list,entry);
	}

	else {
		Iterator iter = List_iterator(list);
		int (*equal)(void *, void *) = m->equals;
		while (Iterator_hasNext(iter)) {
			MapEntry entry = (MapEntry) Iterator_next(iter);
			if (equal(entry->key,key)) {
				entry->value = value;
				Iterator_free(iter);
				return;
			}
		}
	}
	return;
}

List Map_keys(Map m) {
	int i;
	List keys = List_new();
	List *list = m->table;
	for (i = 0; i < TABLE_SIZE; i++) {
		List l = list[i];
		Iterator iter = List_iterator(l);
		while (Iterator_hasNext(iter)) {
			MapEntry entry = (MapEntry) Iterator_next(iter);
			List_add(keys,entry->key);
		}
		Iterator_free(iter);
	}
	return keys;
}

void Map_free(Map m) {
	int i;
	for (i = 0; i < TABLE_SIZE; i++) {
		List_free(m->table[i]);
		free(m->table[i]);
	}
	free(m);
}

static List getList(Map m, int index) {
	List list = m->table[index];
	return list;
}

static MapEntry newEntry(void *key, void *value) {
	MapEntry entry = (MapEntry) malloc(sizeof(struct mapentry));
	entry->key = key;
	entry->value = value;
	return entry;
}