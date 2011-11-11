/*
 * STMCommitStrategy.h
 *
 *  Created on: 11/11/2011
 *      Author: victor
 */

#ifndef STMCOMMITSTRATEGY_H_
#define STMCOMMITSTRATEGY_H_

namespace engine {
 namespace stm {

 	 class Transaction;

 	 class STMCommitStrategy {
 	 public:
 		STMCommitStrategy() {

 		}

 		virtual ~STMCommitStrategy() {

 		}

 		virtual bool doCommit(Transaction* transaction) = 0;

 	 };
 }
}


#endif /* STMCOMMITSTRATEGY_H_ */
