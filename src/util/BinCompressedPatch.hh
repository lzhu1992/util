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
		 1. load in the existing file
		 2. compute difference to create version2 file
		 2a. temporarily write out file
		 3. compress difference using bzip2 library
		 4. Compute MAC (optional, using openssl library)
		 4. write out file
	 */
	BinCompressedPatch(const char basefilename[], const char version2[], );

	/**
		 Add a new file, computing the version difference
	 */
	void diff(const char filename[], uint32_t version);

#if 0
	void send(Patch p, Client& c) {}
	void update(const char oldfile[], Patch p, const char version2[]);
};

#endif
