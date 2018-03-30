/*
*常见排序算法的实现
*/
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<assert.h>
using namespace std;

#define MIN(a,b) a<b?a:b

template<typename T>
//交换函数
void _swap(T &a,T &b)
{
	int temp = a;
	a = b;
	b = temp;	
}
//生成有n个元素int数组，范围[low,high]
int* CreatRandomArray(int n,int low,int high)
{
	assert(low <= high);
	int *arr = new int[n];
	srand(time(NULL));
	for(int i=0;i<n;i++)
	{
		arr[i] = rand()%(high - low+1)+low;
	}
	return arr;
}
//生成有n个元素近似已经排序的int数组，范围[low,high]
int* CreatNearlyOrderArray(int n,int swaptime)
{
	int *arr = new int[n];
	for(int i =0;i<n;i++)
		arr[i]=n;
	
	srand(time(NULL));
	for(int i=0;i<swaptime;i++)
	{
		int posx = rand()%n;
		int posy = rand()%n;
		swap(posx,posy);
	}
	return arr;
}
//打印数组函数
template<typename T>
void printf_array(T a[],int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
//验证排序正确性
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
//测试排序性能
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
//复制数组
template<typename T>
T* copy_array(T a[],int n)
{
	T *arr = new T[n];
	for(int i=0;i<n;i++)
	{
		arr[i] = a[i];
	}
	return arr;
}

//选择排序 O(n^2)
template<typename T>
void select_sort(T a[],int n)
{
	for (int i=0;i<n;i++)
	{
		int temp_min = i;
		for(int j = i+1;j<n;j++)
		{
			if(a[j]<a[temp_min])
				temp_min = j;
		}
		_swap(a[temp_min],a[i]);	
	}
}

//插入排序O(n^2)
template<typename T>
void insert_sort(T a[],int n)
{
	for(int i=1;i<n;i++)
	{
		//寻找第i个元素合适的位置
		//for(int j=i;j>0 && a[j]<a[j-1];j--)
		//{
			//_swap(a[j],a[j-1]);
		//}
		//改进算法,减少赋值操作
		T e = a[i];
		int j;
		for(j=i;j>0 && a[j-1] > e;j--)
		{
			a[j] = a[j-1];
		}
		a[j] = e;
	}
}

//希尔排序
template<typename T>
void hill_sort(T arr[],int n)
{
	for(int d=n/2;d>0;d/=2)
	{
		for(int i=d;i<n;i++)
		{
			int j = i;
			int temp_min = arr[j];
			while(j-d>=0 && arr[j-d]>temp_min)
			{
				arr[j] = arr[j-d];
				j = j-d;
			}
			arr[j]=temp_min;
		}
	}
}

//冒泡排序 O(n^2)
template<typename T>
void bubble_sort(T arr[],int n)
{
	for (int i=n-1;i>0;i--)
	{	
		for(int j = 0;j<i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				_swap(arr[j],arr[j+1]);
			}
		}
	}
}
//分段归并
template<typename T>
void merge(T arr[],int left,int mid,int right)
{
	T aux[right-left+1];
	for(int i = left;i<=right;i++)
	{
		aux[i-left] = arr[i];
	}
	int i = left,j = mid+1;
	for(int k=left;k<=right;k++)
	{
		if(i>mid)
		{
			arr[k] = aux[j-left];
			j++;
		}
		else if(j>right)
		{
			arr[k] = aux[i-left];
			i++;
		}
		else if(aux[i-left]<aux[j-left])
		{
			arr[k]=aux[i-left];
			i++;
		}
		else
		{
			arr[k]=aux[j-left];
			j++;
		}
	}
}

//对arr[left...right]进行排序
template<typename T>
void _merge_sort(T arr[],int left,int right)
{
	if(left >= right) return;
	int mid = (left+right)/2;//可能会溢出
	_merge_sort(arr,left,mid);
	_merge_sort(arr,mid+1,right);
	if (arr[mid]>arr[mid+1])
		merge(arr,left,mid,right);
}
//归并排序
template<typename T>
void merge_sort(T arr[],int n)
{
	_merge_sort(arr,0,n-1);
}
//归并排序自底部向上(适用于链表)
template<typename T>
void merge_sort2(T arr[],int n)
{
	for(int size=1;size<=n;size+=size)
	{
		for(int i=0;i<n-size;i+=2*size)
		{
			merge(arr,i,i+size-1,MIN(i+2*size-1,n-1));
		}
	}
}
template<typename T>
int _partition(T arr[],int l,int r)
{
	_swap(arr[l],arr[rand()%(r-l+1)+l]);
	T v = arr[l];
	int j = l;
	for(int i=l;i<=r;i++)
	{
		if(arr[i]<v)
		{
			j++;
			_swap(arr[i],arr[j]);
		}
	}
	_swap(arr[l],arr[j]);
	return j;
}
//最开始的快速排序
template<typename T>
void _quick_sort(T arr[],int l,int r)
{
	if(l>r) return;
	int p =_partition(arr,l,r);
	_quick_sort(arr,l,p-1);
	_quick_sort(arr,p+1,r);
}

template<typename T>
void quick_sort(T arr[],int n)
{
	srand(time(NULL));
	_quick_sort(arr,0,n-1);
}

template<typename T>
int _partition2(T arr[],int l,int r)
{
	_swap(arr[l],arr[rand()%(r-l+1)+l]);
	T v = arr[l];
	int i = l+1,j =r;
	while(1)
	{
		while(i<=r && arr[i]<v) i++;
		while(j>=l+1 && arr[j]>v) j--;
		if(i>j) break;
		_swap(arr[i],arr[j]);
		i++;
		j--;
	}
	_swap(arr[l],arr[j]);
	return j;
}
//双路快排
template<typename T>
void _quick_sort2(T arr[],int l,int r)
{
	if(l>r) return;
	int p =_partition(arr,l,r);
	_quick_sort(arr,l,p-1);
	_quick_sort(arr,p+1,r);
}

template<typename T>
void quick_sort2(T arr[],int n)
{
	srand(time(NULL));
	_quick_sort2(arr,0,n-1);
}

template<typename T>
void _quick_sort3(T arr[],int l,int r)
{	
	if(r-l<=15)
	{
		insert_sort(arr,r-l+1);
		return;
	}
	_swap(arr[l],arr[rand()%(r-l+1)+l]);
	T v = arr[l];
	int lt = l;
	int gt = r+1;
	int i = l+1;
	while(i<gt)
	{
		if(arr[i]<v)
		{
			_swap(arr[i],arr[lt+1]);
			lt++;
			i++;
		}
		else if(arr[i]>v)
		{
			_swap(arr[i],arr[gt-1]);//此处还可以再优化
			gt--;
		}
		else
			i++;
	}
	_swap(arr[l],arr[lt]);
	
	_quick_sort3(arr,l,lt-1);//容易出错
	_quick_sort3(arr,gt,r);
}
//三路快排
template<typename T>
void quick_sort3(T arr[],int n)
{
	srand(time(NULL));
	_quick_sort3(arr,0,n-1);
}

int main()
{
	int n = 100000;
	int *a = CreatRandomArray(n,1,100);
	int *a1 = copy_array(a,n);
	int *a2 = copy_array(a,n);
	int *a3 = copy_array(a,n);
	int *a4 = copy_array(a,n);
	int *a5 = copy_array(a,n);
	int *a6 = copy_array(a,n);
	int *a7 = copy_array(a,n);
	int *a8 = copy_array(a,n);
	testSort("select_sort",select_sort,a,n);
	testSort("insert_sort",insert_sort,a1,n);
	testSort("hill_sort",hill_sort,a2,n);
	testSort("bubble_sort",bubble_sort,a3,n);
	testSort("merge_sort",merge_sort,a4,n);
	testSort("merge_sort2",merge_sort2,a5,n);
	testSort("quick_sort",quick_sort,a6,n);
	testSort("quick_sort2",quick_sort2,a7,n);
	testSort("quick_sort3",quick_sort3,a8,n);
	delete []a;
	delete []a1;
	delete []a2;
	delete []a3;
	delete []a4;
	delete []a5;
	delete []a6;
	delete []a7;
	delete []a8;
	return 0;
}