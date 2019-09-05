#include <stdio.h>
#include <stdlib.h> /* malloc, realoc */
#include <assert.h> /* assert */

#include "binheap.h"

/******************************************************************************/

int CreateDestroyTest();
int InsertTest();
int DeleteMinTest();
int PruneTest();

/******************************************************************************/
int main()
{
	int res = 0;
	
	res = CreateDestroyTest();
	if (0 != res)
	{
		printf("problem in line: %d\n", res);
		return (1);
	}

	res = InsertTest();
	if (0 != res)
	{
		printf("problem in line: %d\n", res);
		return (1);
	}
	
	res = DeleteMinTest();
	if (0 != res)
	{
		printf("problem in line: %d\n", res);
		return (1);
	}
	
	res = PruneTest();
	if (0 != res)
	{
		printf("problem in line: %d\n", res);
		return (1);
	}
	
	puts("good!");
	
	return (0);
}

/******************************************************************************/

int Cmp(const void *data1, const void *data2, void *param)
{	
	assert (NULL != data1);
	assert (NULL != data2);
	
	return (*(int *)data1 - *(int *)data2);
}

/******************************************************************************/
int CreateDestroyTest()
{
	bheap_t *b_heap = BHeapCreate(&Cmp, NULL);
	
	if ((1 != BHeapIsEmpty(b_heap)) && (0 != BHeapSize(b_heap)))
	{
		printf ("Failed in CreateDestroyTest %d\n", __LINE__);
		
		return (__LINE__);
	}
	
	BHeapDestroy(b_heap);

	return (0);
}

/******************************************************************************/

int InsertTest()
{
	bheap_t *b_heap = BHeapCreate(&Cmp, NULL);
	int arr[] = { 9, 7, 5, 3, 1, 0 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		BHeapInsert(b_heap, (void *)&arr[i]);
		if (arr[i] != *(int *)BHeapMin(b_heap))
		{
			printf("problem in insert, needs to be %d, but root is: %d\n",
												arr[i], *(int *)BHeapMin(b_heap));
			
			return (__LINE__);
		}
	}
	
	if ((0 != BHeapIsEmpty(b_heap)) && (size != BHeapSize(b_heap)))
	{
		printf ("Failed in InsertTest");
		
		return (__LINE__);
	}
	
/*	Print(b_heap);*/
	
	BHeapDestroy(b_heap);
	
	return (0);
}

/******************************************************************************/

int DeleteMinTest()
{
	bheap_t *b_heap = BHeapCreate(&Cmp, NULL);
	int arr[] = { 9, 7, 5, 3, 1, 0 };
	int arr2[] = { 1, 3, 5, 7, 9 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		BHeapInsert(b_heap, (void *)&arr[i]);
	}
	
	for (i = 0; i < size - 1; ++i)
	{
		BHeapDeleteMin(b_heap);
		if (arr2[i] != *(int *)BHeapMin(b_heap))
		{
			printf("problem in delete, needs to be %d, but root is: %d and i is: %lu\n",
												arr2[i], *(int *)BHeapMin(b_heap), i);	
			return (__LINE__);
		}
	}
	
	if ((0 != BHeapIsEmpty(b_heap)) && (1 != BHeapSize(b_heap)))
	{
		printf ("Failed in DeleteMinTest");
		
		return (__LINE__);
	}
	
	/* to delete the last item */
	BHeapDeleteMin(b_heap);
	if ((1 != BHeapIsEmpty(b_heap)) && (0 != BHeapSize(b_heap)))
	{
		printf ("Failed in DeleteMinTest");
		
		return (__LINE__);
	}

	/* to delete from empty heap */
	if (NULL != BHeapDeleteMin(b_heap))
	{
		printf("Failed in DeleteMinTest");
		
		return (__LINE__);	
	}
	
	BHeapDestroy(b_heap);
	
	return (0);
}

/******************************************************************************/

int IsMatch(void *data, void *param)
{
	return (*(int *)param == *(int *)data);
}

/******************************************************************************/

int PruneTest()
{
	bheap_t *b_heap = BHeapCreate(&Cmp, NULL);
	int arr[] = { 5, 5, 5, 3, 5, 6, 7, 9, 0, 5, 6, 1, 5, 5, 6, 0, 0 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0;
	size_t param = 5;
	
	for (i = 0; i < size; ++i)
	{
		BHeapInsert(b_heap, (void *)&arr[i]);
	}

	if (17 != BHeapSize(b_heap))
	{
		printf("Failed in PruneTest");
		
		return (__LINE__);
	}

	BHeapPrune(b_heap, &IsMatch, &param);
	if (10 != BHeapSize(b_heap))
	{
		printf("Failed in PruneTest, size is: %lu\n", BHeapSize(b_heap));
		
		return (__LINE__);
	}
	
	/* to prune where the item doesn't exist */
	BHeapPrune(b_heap, &IsMatch, &param);
	if (10 != BHeapSize(b_heap))
	{
		printf("Failed in PruneTest, size is: %lu\n", BHeapSize(b_heap));
		
		return (__LINE__);
	}
	
	BHeapDestroy(b_heap);
	
	return (0);
}
















