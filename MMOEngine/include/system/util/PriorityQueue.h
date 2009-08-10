/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include "../platform.h"

#include "../lang/Exception.h"

namespace sys {
  namespace util {

	class PriorityQueue;

	class PriorityQueueEntry {
		PriorityQueueEntry* parentNode;

		PriorityQueueEntry* leftNode;
		PriorityQueueEntry* rightNode;

		int	npl;

		bool enqueued;

	public:
		PriorityQueueEntry(PriorityQueueEntry* parent = NULL, PriorityQueueEntry* lnode = NULL,
				PriorityQueueEntry* rnode = NULL, int np = 0);

		virtual ~PriorityQueueEntry() {
			enqueued = false;
		}

		virtual int compareTo(PriorityQueueEntry* node) = 0;

		inline void setQueued() {
			enqueued = true;
		}

		inline void setUnqueued() {
			enqueued = false;
		}

		inline bool isQueued() {
			return enqueued;
		}

		friend class PriorityQueue;

	};

	class PriorityQueue {
	private:
		PriorityQueueEntry* root;

		int count;

	public:
		PriorityQueue();
		PriorityQueue(const PriorityQueue& heap);

		virtual ~PriorityQueue();

		void add(PriorityQueueEntry* node);

		const PriorityQueueEntry* peak() const;
		const PriorityQueueEntry* poll();

		const bool remove(PriorityQueueEntry* node);

		void clear();

		inline bool isEmpty() const {
			return root == NULL;
		}

		inline bool isFull() const {
			return false;
		}

		inline int size() {
			return count;
		}

	private:
		void merge(PriorityQueue& heap);

		PriorityQueueEntry* merge(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const;
		PriorityQueueEntry* merge1(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const;

		void swapChildren(PriorityQueueEntry* node) const;

		void reclaimMemory(PriorityQueueEntry* node) const;
	};

  } // namespace util
} // namespace sys;

using namespace sys::util;

#endif /* PRIORITYQUEUE_H_ */
