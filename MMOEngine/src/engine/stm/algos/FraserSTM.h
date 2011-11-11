/*
 * FraserSTM.h
 *
 *  Created on: 11/11/2011
 *      Author: victor
 */

#ifndef FRASERSTM_H_
#define FRASERSTM_H_

#include "STMCommitStrategy.h"

namespace engine {
 namespace stm {

 	 class Transaction;

 	 class FraserSTM : public STMCommitStrategy {
 	 public:
 		bool doCommit(Transaction* transaction);
 		bool tryFinishCommit(int desiredStatus, Transaction* transaction);
 		bool validateReadOnlyObjects(Transaction* transaction);

 	 };
 }
}

#endif /* FRASERSTM_H_ */
