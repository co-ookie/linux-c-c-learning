#include<iostream>
using namespace std;

template<typename T>
int Binary_Search(T arr[],int n,T target)
{
	int l,r;
	l = 0;
	r = n-1;	
	while (l<=r) {
		int mid = l+(r-l)/2;
		if (arr[mid] == target) {
			return mid;
		}
		else if (arr[mid] > target) {
			r = mid-1;
		}
		else 
			l = mid+1;
	}
	return -1;
}

//递归版本
template<typename T>
int _Binary_Search2(T arr[],int l,int r,T target)
{
	int mid = l + (r - l) / 2;
	if (l>=r && arr[mid] != target) return -1;

	if (arr[mid] == target)
		return mid;
	else if (arr[mid]>target)
		_Binary_Search2(arr,l,mid-1,target);
	else 
		_Binary_Search2(arr,mid+1,r,target);
}


template<typename T>
int Binary_Search2(T arr[],int n,T target)
{
	_Binary_Search2(arr,0,n-1,target);
}

int main()
{
	int arr[10] ={0,2,4,6,8,10,12,14,16,18};
	int target = 16;
	cout << "Binary_Search:" << Binary_Search(arr, 10, target)<<endl;
	cout << "Binary_Search2:" << Binary_Search2(arr, 10, target)<<endl;
	return 0;
}