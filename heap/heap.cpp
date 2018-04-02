#include<iostream>
#include<cstdlib>
#include<cassert>

using namespace std;

//用数组实现最大堆
template<typename T>
class MaxHeap
{
public:	
	MaxHeap(int capacity)
	{
		//第一个元素从1开始
		data = (T *)new T[capacity+1]; 
		size = capacity;
		count = 0;
	}
	
	MaxHeap(T arr[],int n)
	{
		data = new T[n+1];
		size = n;
		for(int i=0;i<n;i++)
		{
			data[i+1] = arr[i];
		}
		count = n;
		for(int j=n/2;j>=1;j--)
		{
			shiftdown(j);
		}
	}
	
	~MaxHeap()
	{
		delete [] data;
	}
	void swap(T &a,T &b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	
	void insert(T k)
	{
		assert(count+1 < size);//保证不会越界
		data[count+1] = k;
		count++;
		shiftup();
	}
	
	T pushroot()
	{
		T ret = data[1];
		data[1] = data[count];
		count--;
		shiftdown(1);
		return ret;
	}
	
	T getelement(int k)
	{
		assert(k >0 && k<=size);
		return data[k];
	}
	
private:
	T* data;
	int count;//当前元素个数
	int size;
	
	void shiftup()
	{
		int j = count;
		while(j>1 && data[j] > data[j/2])
		{
			swap(data[j],data[j/2]);//和父节点交换
			j = j/2;
		}
	}
	
	void shiftdown(int j)
	{
		while(2*j <= count)
		{
			if(2*j+1<=count && data[2*j+1]>data[2*j])
			{
				if(data[j]<data[2*j+1])
				{
					swap(data[2*j+1],data[j]);
					j = 2*j+1;
				}
				else
					break;
			}
			else
			{
				if(data[j]<data[2*j])
				{
					swap(data[2*j],data[j]);
					j = 2*j;
				}
				else
					break;
			}		
		}
	}
};
template<typename T>
void heap_sort(T arr[],int n)
{
	MaxHeap<T> maxheap(n+1);
	for(int i=0;i<n;i++)
	{
		maxheap.insert(arr[i]);
	}
	for(int j=n-1;j>=0;j--)
	{
		arr[j] = maxheap.pushroot();
	}
}

template<typename T>
void heap_sort2(T arr[],int n)
{
	MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
	for(int j=n-1;j>=0;j--)
	{
		arr[j] = maxheap.pushroot();
	}
}

template<typename T>
bool isSorted(T a[],int n)
{
	for(int i=0;i<n-1;i++)
	{
		if(a[i]>a[i+1])
			return false;
	}
	return true;
}

template<typename T>
void testSort(string sortName,void(*sort)(T[],int),T a[],int n)
{
	clock_t start = clock();
	sort(a,n);
	clock_t end = clock();
	
	assert(isSorted(a,n));
	double timetap = (double)(end-start)/CLOCKS_PER_SEC;
	cout<<sortName<<" : "<<(double)(end-start)/CLOCKS_PER_SEC<<" s"<<endl;
}

int main()
{
	int n =100000;
	srand(time(NULL));
	int *arr = new int[n];
	for(int i=0;i<n;i++)
	{
		arr[i] = rand()%10000;
	}
	testSort("heap_sort",heap_sort,arr,n);
	testSort("heap_sort2",heap_sort2,arr,n);
	delete [] arr;
	return 0;
}