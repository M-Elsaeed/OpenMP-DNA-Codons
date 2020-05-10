sequential(string inStr)
    // Record starting time
	start <- getTime()
	for each 3 characters
		temp <- form codon from 3 characters
        // Increment protein count by 1
		countMapSeq[codonMap[temp]] += 1;
	// Record starting time
    end <- getTime()
    // Print consumed time
    print(end-start)

parallel(string inStr)
    // Record starting time
	start <- getTime()
    // Parallelize loop iterations
	for each 3 characters
		temp <- form codon from 3 characters
        // Increment protein count by 1
		countMapSeq[codonMap[temp]] += 1;
	// Record starting time
    end <- getTime()
    // Print consumed time
    print(end-start)

parallelSections(string inStr)
    // Record starting time
	start <- getTime()
	for each 3 characters
        // Form codon in parallel section 1
        {
            temp <- form codon from 3 characters
        }
        // Increment protein count by 1 in parallel section 1
        {
            countMapSeq[codonMap[temp]] += 1;
        }
	// Record starting time
    end <- getTime()
    // Print consumed time
    print(end-start)