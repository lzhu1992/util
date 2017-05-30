#ifndef BINCOMPRESSEDPATCH_HH_
#define BINCOMPRESSEDPATCH_HH_

#include <bzlib.h>
#include <bsdiff.h>

/**
	 Represent a binary file that is being changed and must be distributed.
	 Calculate the patches needed to modify the existing file of each version
	 to the latest one.


 */
class BinCompressedPatch {
public:
	/**
		 Initialize, loading in the existing file
	 */
	BinCompressedPatch(const char basefilename[]);

	/**
		 Add a new file, computing the version difference
	 */
	void diff(const char filename[], uint32_t version);
};
/*
  1. Compute diff from v1 to v2
  2. Compute patch to change v1 into v2
  2.5 compress (bz2)     system("bz2 patch"); --> patch.bz2
  3. save out patch file
  4. send the patch via socket (send a stream of bytes)
  5. client unpacks bz2 compression
  6. updates v1 to v2 using the patch you sent





 */
#endif
