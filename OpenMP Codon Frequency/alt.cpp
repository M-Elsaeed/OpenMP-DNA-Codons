
void parallelSections(string inStr)
{

	const int seqSize = inStr.size() - 3;

	const int n8 = seqSize / 6;
	const int n82 = 2 * n8, n83 = 3 * n8, n84 = 4 * n8, n85 = 5 * n8, n86 = 6 * n8, n87 = 7 * n8, n88 = 8 * n8;

	int formedCodons[8] = {0};
	int countedCodons[8] = {0};

	vector<vector<string>> codonsArr(8, vector<string>(seqSize / 3, ""));

	omp_set_num_threads(threads);

	auto start = chrono::steady_clock::now();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n8; i += 3)
			{
				codonsArr[0][formedCodons[0]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
				countMapSections[codonMap[codonsArr[0][formedCodons[0] - 1]]] += 1;
				// formedCodons[0]++;
			}
		}
// #pragma omp section
// 		{
// 			while ((formedCodons[0] < n8 / 3) || (countedCodons[0] < formedCodons[0]))
// 			{
// 				while (countedCodons[0] < formedCodons[0])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[0][countedCodons[0]]]] += 1;
// 					countedCodons[0]++;
// 				}
// 			}
// 		}
#pragma omp section
		{
			for (int i = n8; i < n82; i += 3)
			{
				// cout<<formedCodons[1]<<endl;
				codonsArr[1][formedCodons[1]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
				countMapSections[codonMap[codonsArr[1][formedCodons[1] - 1]]] += 1;
				// formedCodons[1]++;
			}
		}
// #pragma omp section
// 		{
// 			while ((formedCodons[1] < n82 / 3) || (countedCodons[1] < formedCodons[1]))
// 			{
// 				while (countedCodons[1] < formedCodons[1])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[1][countedCodons[1]]]] += 1;
// 					countedCodons[1]++;
// 				}
// 			}
// 		}
#pragma omp section
		{
			for (int i = n82; i < n83; i += 3)
			{
				codonsArr[2][formedCodons[2]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
				countMapSections[codonMap[codonsArr[2][formedCodons[2] - 1]]] += 1;
				// formedCodons[2]++;
			}
		}
// #pragma omp section
// 		{
// 			while ((formedCodons[2] < n83 / 3) || (countedCodons[2] < formedCodons[2]))
// 			{
// 				while (countedCodons[2] < formedCodons[2])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[2][countedCodons[2]]]] += 1;
// 					countedCodons[2]++;
// 				}
// 			}
// 		}
#pragma omp section
		{
			for (int i = n83; i < n84; i += 3)
			{
				codonsArr[3][formedCodons[3]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
				countMapSections[codonMap[codonsArr[3][formedCodons[3] - 1]]] += 1;
				// formedCodons[3]++;
			}
		}
// #pragma omp section
// 		{
// 			while ((formedCodons[3] < n84 / 3) || (countedCodons[3] < formedCodons[3]))
// 			{
// 				while (countedCodons[3] < formedCodons[3])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[3][countedCodons[3]]]] += 1;
// 					countedCodons[3]++;
// 				}
// 			}
// 		}
#pragma omp section
		{
			for (int i = n84; i < n85; i += 3)
			{
				codonsArr[4][formedCodons[4]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
				countMapSections[codonMap[codonsArr[4][formedCodons[4] - 1]]] += 1;
				// formedCodons[4]++;
			}
		}
// #pragma omp section
// 		{
// 			while ((formedCodons[4] < n85 / 3) || (countedCodons[4] < formedCodons[4]))
// 			{
// 				while (countedCodons[4] < formedCodons[4])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[4][countedCodons[4]]]] += 1;
// 					countedCodons[4]++;
// 				}
// 			}
// 		}
#pragma omp section
		{
			for (int i = n85; i < n86; i += 3)
			{
				codonsArr[5][formedCodons[5]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
				countMapSections[codonMap[codonsArr[5][formedCodons[5] - 1]]] += 1;
				// formedCodons[5]++;
			}
		}
// #pragma omp section
// 		{
// 			while ((formedCodons[5] < n86 / 3) || (countedCodons[5] < formedCodons[5]))
// 			{
// 				while (countedCodons[5] < formedCodons[5])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[5][countedCodons[5]]]] += 1;
// 					countedCodons[5]++;
// 				}
// 			}
// 		}
// #pragma omp section
// 		{
// 			for (int i = n86; i < n87; i += 3)
// 			{
// 				codonsArr[6][formedCodons[6]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
// #pragma omp atomic
// 				countMapSections[codonMap[codonsArr[6][formedCodons[6] - 1]]] += 1;
// 				// formedCodons[6]++;
// 			}
// 		}
// #pragma omp section
// 		{
// 			while ((formedCodons[6] < n87 / 3) || (countedCodons[6] < formedCodons[6]))
// 			{
// 				while (countedCodons[6] < formedCodons[6])
// 				{
// #pragma omp atomic
// 					countMapSections[codonMap[codonsArr[6][countedCodons[6]]]] += 1;
// 					countedCodons[6]++;
// 				}
// 			}
// 		}
// #pragma omp section
// 		{
// 			for (int i = n87; i < n88; i += 3)
// 			{
// 				codonsArr[7][formedCodons[7]++] = {inStr[i], inStr[i + 1], inStr[i + 2]};
// #pragma omp atomic
// 				countMapSections[codonMap[codonsArr[7][formedCodons[7] - 1]]] += 1;
// 				// formedCodons[7]++;
// 			}
// 		}
		// #pragma omp section
		// 		{
		// 			while ((formedCodons[7] < n88 / 3) || (countedCodons[7] < formedCodons[7]))
		// 			{
		// 				while (countedCodons[7] < formedCodons[7])
		// 				{
		// #pragma omp atomic
		// 					countMapSections[codonMap[codonsArr[7][countedCodons[7]]]] += 1;
		// 					countedCodons[7]++;
		// 				}
		// 			}
		// 		}
	}
	// int rem = seqSize - n88;
	// string temp;
	// if (!(rem % 3))
	// {
	// 	for (int i = n88; i < inStr.size(); i += 3)
	// 	{
	// 		temp = {inStr[i], inStr[i + 1], inStr[i + 2]};
	// 		countMapSections[codonMap[temp]] += 1;
	// 	}
	// }
	// else
	// {
	// 	for (int i = n88 - (rem%3); i < inStr.size(); i += 3)
	// 	{
	// 		temp = {inStr[i], inStr[i + 1], inStr[i + 2]};
	// 		countMapSections[codonMap[temp]] += 1;
	// 	}
	// }
	auto end = chrono::steady_clock::now();
	cout << "Sections time in milliseconds : "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;
}
