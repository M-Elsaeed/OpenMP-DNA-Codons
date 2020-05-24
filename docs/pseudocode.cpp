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
    // Codons 2D Array of size (2, sequence length / 3)
    codonsArr
    // Array of Counters of formed codons
    formedCodons[0] <- 0
    formedCodons[1] <- 0
    // Array of Counters of counted codons
    countedCodons[0] <- 0
    countedCodons[1] <- 0
    // Record starting time
	start <- getTime()
    
    // Parallel section 1, forms codons
    {
        for each 3 characters in the first half of the array
            codonsArr[0][formedCodons[0]] <- codon from 3 characters
            formedCodons[0] <- formedCodons[0] + 1
    }


    // Parallel section 2, counts proteins of formed codons
    {
        while( (not all codons formed) or (not all formed codons counted) )
            while(not all formed codons counted)
                countMapSeq[codonMap[codonsArr[0][countedCodons[0]]]] += 1;
                countedCodons[0] <- countedCodons[0]+1
    }

    // Parallel section 3, forms codons
    {
        for each 3 characters in the second half of the array
            codonsArr[1][formedCodons[1]] <- codon from 3 characters
            formedCodons[1] <- formedCodons[1] + 1
    }


    // Parallel section 4, counts proteins of formed codons
    {
        while( (not all codons formed) or (not all formed codons counted) )
            while(not all formed codons counted)
                countMapSeq[codonMap[codonsArr[1][countedCodons[1]]]] += 1;
                countedCodons[1] <- countedCodons[1]+1
    }

	// Record starting time
    end <- getTime()
    // Print consumed time
    print(end-start)