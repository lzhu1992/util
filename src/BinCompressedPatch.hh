#ifndef BINCOMPRESSEDPATCH_HH_
#define BINCOMPRESSEDPATCH_HH_

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

#endif
