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
        // Increment protein count by 1 atomically
		countMapSeq[codonMap[temp]] += 1;
	// Record starting time
    end <- getTime()
    // Print consumed time
    print(end-start)

parallelSections(string inStr)
    // Codons Arr of size (sequence length / 3)
    codonsArr
    // Counter of formed codons
    formedCodons <- 0
    // Counter of counted codons
    countedCodons <- 0
    // Record starting time
	start <- getTime()
    
    // Parallel section 1, forms codons
    {
        // NESTED PARALLISM of for loop to use as much threads as possible
        for each 3 characters
            codonsArr[formedCodons] <- codon from 3 characters
            formedCodons <- formedCodons + 1
    }


    // Parallel section 2, counts proteins of formed codons
    {
        while( (not all codons formed) or (not all formed codons counted) )
            while(not all formed codons counted)
                countMapSeq[codonMap[codonsArr[countedCodons]]] += 1;
                countedCodons <- countedCodons+1
    }

	// Record starting time
    end <- getTime()
    // Print consumed time
    print(end-start)