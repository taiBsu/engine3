/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include "ref/Reference.h"
#include "ref/WeakReference.h"

#include "system/thread/Locker.h"
#include "system/mm/MemoryManager.h"

#include "Object.h"

#include "system/util/SortedVector.h"
#include "system/util/HashSet.h"

#include "engine/stm/TransactionalReference.h"
#include "engine/stm/TransactionalObjectHeader.h"

#include "StackTrace.h"

Object::Object() : ReferenceCounter(), Variable() {
#ifdef MEMORY_PROTECTION
	_destroying = new AtomicBoolean(false);
	referenceMutex = new Mutex();
#endif

	//deletedByTrace = NULL;

	weakReferences = NULL;

	//MemoryManager::getInstance()->create(this);

#ifdef TRACE_REFERENCES
	referenceHolders.setNullValue(NULL);
#endif
}

Object::Object(const Object& obj) : ReferenceCounter(), Variable() {
#ifdef MEMORY_PROTECTION
	_destroying = new AtomicBoolean(false);
	referenceMutex = new Mutex();
#endif

	//deletedByTrace = NULL;

	weakReferences = NULL;

	//MemoryManager::getInstance()->create(this);

#ifdef TRACE_REFERENCES
	referenceHolders.setNullValue(NULL);
#endif
}

Object::~Object() {
#ifdef TRACE_REFERENCES
	for (int i = 0; i < referenceHolders.size(); ++i)
		delete referenceHolders.get(i);
#endif

	if (getReferenceCount() > 0)
		assert(0 && "Deleting object with reference > 0");

//#ifndef WITH_STM
#ifdef MEMORY_PROTECTION
	Locker locker(referenceMutex);
#else
	Locker locker(&referenceMutex);
#endif
//#endif

	if (weakReferences != NULL) {
		/*Vector<WeakReferenceBase*>* vector = weakReferences;

		for (int i = 0; i < vector->size(); ++i) {
			WeakReferenceBase* ref = vector->get(i);
			ref->clearObject();
		}

		delete weakReferences;
		weakReferences = NULL;*/

		HashSetIterator<WeakReferenceBase*> iterator = weakReferences->iterator();

		while (iterator.hasNext())
			iterator.getNextKey()->clearObject();

		delete weakReferences;
		weakReferences = NULL;
	}		
	
	locker.release();
#ifdef MEMORY_PROTECTION
	delete referenceMutex;
	referenceMutex = NULL;

//	delete weakReferences;
//	weakReferences = NULL;

	delete _destroying;
	_destroying = NULL;
#endif

	finalize();

	//deletedByTrace = new StackTrace();
}

void Object::release() {
	if (getReferenceCount() == 0)
		assert(0 && "Object already delted");

	if (decreaseCount()) {
		if (notifyDestroy()) {
#ifdef WITH_STM
			MemoryManager::getInstance()->reclaim(this);
#else
			destroy();
#endif
		}
	}
}

void Object::acquireWeak(WeakReferenceBase* ref) {
#ifdef MEMORY_PROTECTION
	Locker locker(referenceMutex);
#else
	Locker locker(&referenceMutex);
#endif

	if (weakReferences == NULL)
		weakReferences = new HashSet<WeakReferenceBase*>();

	weakReferences->add(ref);
/*#else
	if (weakReferences == NULL) {
		weakReferences = new TransactionalReference<Vector<WeakReferenceBase*>*>(new Vector<WeakReferenceBase*>());
	}

	(*weakReferences).getForUpdate()->add(ref);
#endif*/

}

void Object::releaseWeak(WeakReferenceBase* ref) {
#ifdef MEMORY_PROTECTION
	Locker locker(referenceMutex);
#else
	Locker locker(&referenceMutex);
#endif

	if (weakReferences == NULL)
		return;

//#ifndef WITH_STM
	//Vector<WeakReferenceBase*>* vector = weakReferences;
//#else
	//Vector<WeakReferenceBase*>* vector = (*weakReferences).getForUpdate();
//#endif
	/*for (int i = 0; i < vector->size(); ++i) {
		WeakReferenceBase* reference = vector->get(i);

		if (reference == ref) {
			vector->remove(i);

			break;
		}
	}*/

	weakReferences->remove(ref);
}

void Object::destroy() {
#ifdef MEMORY_PROTECTION
	_destroying->set(true);

	Locker locker(referenceMutex);
#else
	_destroying.set(true);

	Locker locker(&referenceMutex);
#endif

	if (weakReferences != NULL) {
		/*Vector<WeakReferenceBase*>* vector = weakReferences;

		for (int i = 0; i < vector->size(); ++i) {
			WeakReferenceBase* ref = vector->get(i);
			ref->clearObject();
		}

		delete weakReferences;
		weakReferences = NULL;*/

		HashSetIterator<WeakReferenceBase*> iterator = weakReferences->iterator();

		while (iterator.hasNext())
			iterator.getNextKey()->clearObject();

		delete weakReferences;
		weakReferences = NULL;
	}


//#ifndef WITH_STM
	locker.release();
//#endif

	if (getReferenceCount() > 0)
		assert(0 && "Deleting object with reference > 0");

	free();
}

void Object::free() {
	delete this;
}

#ifdef TRACE_REFERENCES
void Object::addHolder(void* obj) {
#ifndef WITH_STM
	Locker locker(&referenceMutex);
#endif

	StackTrace* trace = new StackTrace();
	referenceHolders.put(obj, trace);
}

void Object::removeHolder(void* obj) {
#ifndef WITH_STM
	Locker locker(&referenceMutex);
#endif

	StackTrace* trace = referenceHolders.get(obj);

	if (trace != NULL) {
		delete trace;
		referenceHolders.drop(obj);
	}
}

void Object::printReferenceHolders() {
	for (int i = 0; i < referenceHolders.size(); ++i) {
		StackTrace* trace = referenceHolders.get(i);

		trace->print();
	}
}
#endif

String Object::toString() {
	char buf[20];

	sprintf(buf, "%p", this);

	return String(buf);
}
