#include "unique_id_generator.h"

void UniqueIDGenerator::Reset() {
	mIdSource = 0;
}

uint64_t UniqueIDGenerator::GetNextID() {
	return mIdSource++;
}
