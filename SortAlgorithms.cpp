// SortAlgorithms.cpp : Defines the entry point for the console application.
//九大排序算法
//排序的基本操作：比较，交换
//其中，稳定排序包括：
//不稳定排序包括：
#include "stdafx.h"
#include<vector>
using std::vector;
using std::swap;
#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;

//一·bubbleSort，稳定排序
//时间复杂度：O(n^2)次比较，O(n^2)次交换（最坏情况下）
//空间复杂度：O(1)，原位排序
//过程：
//2, 3, 7, 1, 6
//i=0,j=size-1~i: 
//2, 3, 7, 1, 6...2, 3, 1, 7, 6;2, 1, 3, 7, 6; (1),2, 3, 7, 6//稳定排序
//i=1,j=size-1~i:(1),2, 3, 7, 6     ...     (1),(2), 3, 6, 7
//i=2,j=size-1~i:(1),(2), 3, 6, 7   ...     (1),(2),(3), 6, 7
//i=3,j=size-1~i:(1),(2),(3), 6, 7 ; (1),(2),(3),(6), 7
//i=4,j=size-1~i:(1),(2),(3),(6), 7; (1),(2),(3),(6), (7)
//结束
void bubbleSort(vector<int>& arr, int left, int right){
	//int size = arr.size();
	for (int i = left; i < right; i++){//从小到大排列，每次把当前最小的数字放在位置i
		for (int j = right; j>i; j--){//内循环从右向左遍历元素
			if (arr[j] < arr[j - 1]){//对相邻的元素进行比较-交换操作
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

//二.selectionSort，不稳定排序
//时间复杂度：O(n^2)次比较，O(n)次交换（最坏情况下）
//空间复杂度：O(1)，原位排序
//过程：
//2, 3, 7, 1, 6
//i=0,j=i~size-1:...minInd = 3; (1), 3, 7, 2, 6//不稳定排序
//i=1,j=i~size-1:...minInd = 3; (1),（2）, 7, 3, 6
//i=2,j=i~size-1:...minInd = 3; (1),（2）,（3）, 7, 6
//i=3,j=i~size-1:...minInd = 4; (1),（2）,（3）,（6）, 7
// (1),（2）,（3）,（6）, （7）
//结束
void selectionSort(vector<int>& arr, int left, int right){
	for (int i = left; i < right; i++){//从小到大排列
		int minInd = i;//寻找下标，减少了交换操作
		for (int j = i; j <= right; j++){//内循环从左到右遍历元素
			if (arr[j] < arr[minInd]){//每次找到第i小的元素的下标minInd
				minInd = j;
			}
		}
		swap(arr[i], arr[minInd]);//交换
	}
}

//三.insertSort，稳定排序
//时间复杂度：O(n^2)次比较，O(n^2)次交换（最坏情况下）
//空间复杂度：O(1)，原位排序
//2, 3, 7, 1, 6
//设置观察哨：...（1）,2,3,7,6
//i=2,cur=3：（1）,2,3|7,6
//i=2,cur=7：（1）,2,3,7|6
//i=2,cur=3：（1）,2,3,(),7; (1）,2,3,(6),7;     //while(true),7游移一位
// 1,2,4,6,7
//结束
void insertSort(vector<int>& arr, int left, int right){
	for (int i = right; i > 0; i--){
		if (arr[i] < arr[i - 1]){//设置一个观察哨：把最小的元素放在第一位
			swap(arr[i], arr[i - 1]);
		}
	}
	for (int i = left + 2; i <= right; i++){//该循环使得前i个元素有序
		int j = i;
		int cur = arr[i];//把当前值插入到前i个位置的合适位置，使得前i个元素有序
		while (cur < arr[j-1]){//在arr[1]...arr[i-1]中，存在比cur更大的值，将该值及其后面的值后移一位
			arr[j] = arr[j - 1];//后移一位
			j--;
		}
		arr[j] = cur;//
	}
}

//四.shellSort，不稳定排序
//时间复杂度：O(n^2)次比较，O(n^2)次交换（最坏情况下）
//空间复杂度：O(1)，原位排序
//2, 3, 7, 1, 6
//increment=2,i=2,j=2,cur=7：2, 3, 7, 1, 6
//			  i=3,j=3,cur=1：2,3,7,(3),6
//                j=1,cur=1：2,(1),7,(3),6
//            i=4,j=4,cur=6：2,(1),7,(3),(7)
//                j=2,cur=6：2,(1),6,(3),(7)
//increment=1,i=1,j=1,cur=1: 2,(2),6,(3),(7) 
//                j=0,cur=1: 1,(2),6,(3),(7) 
//            i=2,j=2,cur=6: 1,(2),6,(3),(7) 
//            i=3,j=3,cur=3: 1,(2),6,(6),(7) 
//                j=2,cur=3: 1,(2),(3),(6),(7) 
//			  i=4,j=4,cur=7: 1,(2),(3),(6),(7)
//            i=3,j=3,cur=6: 1,(2),(3),(6),(7)
//            i=2,j=2,cur=3: 1,(2),(3),(6),(7) 
//            i=1,j=1,cur=2: 1,(2),(3),(6),(7) 
//            i=1,j=1,cur=1: 1,(2),(3),(6),(7) 
//结束
void shellSort(vector<int>& arr, int left, int right){
	int increment = (right - left + 1)/2;
	while (increment){//在insertSort的基础上，改变步长
		for (int i = left + increment; i <= right; i++){
			int j = i;
			int cur = arr[i];
			while (j >= left + increment && cur<arr[j - increment]){
				arr[j] = arr[j - increment];
				j -= increment;
			}
			arr[j] = cur;
		}
		increment /= 2;//随着子序列有序，步长递减
	}

	//for (int i = left + 2; i <= right; i++){//该循环使得前i个元素有序
	//	int j = i;
	//	int cur = arr[i];//把当前值插入到前i个位置的合适位置，使得前i个元素有序
	//	while (cur < arr[j - 1]){//在arr[1]...arr[i-1]中，存在比cur更大的值，将该值及其后面的值后移一位
	//		arr[j] = arr[j - 1];//后移一位
	//		j--;
	//	}
	//	arr[j] = cur;//
	//}
}

//五.binaryInsertSort,不稳定排序
//利用前i-1个数有序,进行二分查找得到arr[i]的插入位置
//时间复杂度：O(nlgn)次比较，O(nlgn)次交换（最坏情况下）
//空间复杂度：O(1)，原位排序
//2, 3, 7, 1, 6
//设置观察哨：...（1）,2,3,7,6
//i=2,cur=3,toSortLeft=0,toSortRight=1,middle=0
//			toSortLeft=1,toSortRight=1,middle=1
//			toSortLeft=2,						toSortLeft=i//arr[i]已在所属位置
//...i=7同上...
//i=4,cur=6,toSortLeft=0,toSortRight=3,middle=1
//			toSortLeft=1,toSortRight=3,middle=2
//			toSortLeft=2,toSortRight=3,middle=2
//			toSortLeft=3,toSortRight=3,middle=3
//						 toSortRight=2         //toSortLeft=3
//												(1）,2,3,7,(7)
//												(1）,2,3,(6),(7)
//结束
void binaryInsertSort(vector<int>& arr, int left, int right){
	for (int i = right; i > 0; i--){
		if (arr[i] < arr[i - 1]){//设置一个观察哨：把最小的元素放在第一位
			swap(arr[i], arr[i - 1]);
		}
	}
	int middle = 0;
	for (int i = left+2; i <= right; i++){
		//前i-1个元素已经有序
		//利用前i-1个数有序,进行二分查找得到arr[i]的插入位置
		int cur = arr[i];//带插入元素，插入到前i-1个元素中;
		int toSortLeft = left;
		int toSortRight = i - 1;
		while (toSortLeft <= toSortRight){
			middle = (toSortLeft + toSortRight) / 2;
			if (cur>arr[middle]){
				toSortLeft = middle + 1;
			}
			else{
				toSortRight = middle - 1;//不稳定排序
			}
		}
		if (toSortLeft == i) continue;
		for (int j = i; j > toSortLeft; j--){
			arr[j] = arr[j - 1];
		}
		arr[toSortLeft] = cur;
	}
}

//六.quickSort，不稳定排序
//
//时间复杂度：O(nlgn)次比较，O(nlgn)次交换（最坏情况下）
//存在最坏情况
//空间复杂度：O(1)，原位排序
int partition(vector<int> &arr, int left, int right){
	int low = left - 1;
	int high = right;
	int cur = arr[right];
	while(low<high){
		//前置（++low）运算符，返回递增“后”对象的应用
		while (arr[++low] < cur);
		while (cur < arr[--high]){
			if (high == left) break;
		}
		if (low >= high) break;
		swap(arr[low], arr[high]);
	}
	swap(arr[low], arr[right]);
	return low;
}

void quickSort(vector<int>& arr, int left, int right){
	int dex = 0;
	if (left >= right) return;
	dex = partition(arr, left, right);
	quickSort(arr, left, dex - 1);
	quickSort(arr, dex + 1, right);
}

//七.mergeSort
//https://www.cnblogs.com/chengxiao/p/6194356.html
void merge(vector<int>& array, int left, int middle, int right)
{
	int left_len = middle - left+1;
	int right_len = right - middle;
	vector<int> left_array(left_len,0);
	vector<int> right_array(right_len,0);
	int i, j, k;

	//复制两个有序序列
	for (i = 0; i < left_len; i++)
		left_array[i] = array[i + left];

	for (j = 0; j < right_len; j++)
		right_array[j] = array[j + middle + 1];

	//将两个有序序列变成一个有序序列
	k = left;//定位关键
	i = 0; j = 0;
	while (i < left_len && j < right_len)
	{
		if (left_array[i] < right_array[j])
			array[k++] = left_array[i++];
		else
			array[k++] = right_array[j++];
	}
	while (i < left_len)
		array[k++] = left_array[i++];
	while (j < right_len)
		array[k++] = right_array[j++];
}

void mergeSort(vector<int>& arr, int left, int right){
	if (right <= left) return;
	int mid = (right + left) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

//八.heapSort，不稳定排序
//时间复杂度：O(nlgn)次比较，O(nlgn)次交换
//评价：不存在最坏情况下运行时间特别慢的输入实例
//空间复杂度：原位排序
//关键:
//堆：表示为数组；其中关键字按照堆有序的完全二叉树的形式排列
//构造一个堆所用的比较次数少宇2N次
//过程：
//（1）首先，for循环先构造大顶堆
//（2）接着，for循环交换最大元素与数组中的最后一个元素，并修正堆
//for循环先构造大顶堆
//arr = { 2, 3, 7, 1, 6 }; size=5
//fatherInd=1,fixDown(arr, fatherInd, size):
//								    cur=(3),sonInd=3:
//										  sonInd=4;
//										2, (6), 7, 1, 6;       //arr[fatherInd] = arr[sonInd];
//										fatherInd=4,sonInd=9;
//										2, (6), 7, 1, (3);	   //arr[fatherInd] = cur;
//fatherInd=0,fixDown(arr, fatherInd, size):
//								    cur=(2),sonInd=1:
//										  sonInd=2;
//										(7), (6), 7, 1, (3);	
//										fatherInd=2,sonInd=5; 
//										(7), (6), (2), 1, (3);   //大顶堆构建完成
//接着，while循环交换最大元素与数组中的最后一个元素，并修正堆
//swap(arr[0], arr[size-1]):3,6,2,1,7
//fixDown(arr, 0, size-1):size=4,cur=3,sonInd=1:
//										       (6),6,2,1,7
//										       fatherInd=1,sonInd=3;
//                                             ...（break）
//                                             (6),(3),2,1,7
//1,(3),2,6,7
//...
//1,2,3,6,7
//自上而下构建大顶堆
void fixDown(vector<int>& arr, int fatherInd, int size){
	int sonInd = 2 * fatherInd + 1;
	int cur = arr[fatherInd];
	while (sonInd < size){
		if (sonInd + 1 < size && arr[sonInd] < arr[sonInd + 1]) sonInd++;
		if (cur > arr[sonInd]) break;
		arr[fatherInd] = arr[sonInd];//否则
		fatherInd = sonInd;
		sonInd = 2 * fatherInd + 1;
	}
	arr[fatherInd] = cur;
}
void heapSort(vector<int>& arr, int left, int right){
	//1.构建大顶堆
	int size = arr.size();
	for (int fatherInd = size / 2 - 1; fatherInd >= 0; fatherInd--){
		//从第一个非叶子结点从下至上，从右至左调整结构
		fixDown(arr, fatherInd, size);
	}
	//2.调整堆结构+交换堆顶元素与末尾元素
	for (int j = size - 1; j>0; j--){
		swap(arr[0], arr[j]);//将堆顶元素与末尾元素进行交换
		fixDown(arr, 0, j);//重新对堆进行调整
	}
}

//九.radixSort,稳定排序
//概念：多关键字，基，采用“分配-收集”的过程进行排序
//"分配排序"的基本思想：说白了就是进行多次的桶式排序。
//特征: (1)基数排序过程无须比较关键字，而是通过“分配”和“收集”过程来实现排序;
//	    (2)它们的时间复杂度可达到线性阶：O(n);
//		(3)可以对字符串类型的关键字进行快速的操作
//分类：最高位优先(Most Significant Digit first)法，简称MSD 法；
//	    最低位优先(Least Significant Digit first)法，简称LSD 法：
#define bytesword 4
#define bitsbyte 8
#define bitsword 32
#define R 26//(1<<bitsbyte)
//#define RA  26       /*字符串基数*/
//#define digit(A,B) (((A) >> (bitsword-((B)+1)*bitsbyte))&(R-1))
#define digit(A,B) A[B]
#define dia(arr,ind)   ((arr[ind])?arr[ind]-'a'+1:0) /*将字母转化成数字(0~25)*/
#define bin(A)      (left+count[A])/*取得第ind个箱子的元素个数*/
vector<string> aux(256); /*全局数组*/
void radixMSDSort(vector<string>& arr, int left, int right, int keysNum){
	int i;
	vector<int> count(R + 1, 0);//计数箱子
	if (keysNum > bytesword) return;
	//M
	//使用索引计数排序的方法进行划分
	for (i = left; i <= right; i++){
		count[digit(arr[i], keysNum) + 1]++;
		//count[dia(arr[i], w) + 1]++;
	}
	for (i = 1; i < R; i++) count[i] += count[i - 1];//
	for (i = left; i <= right; i++) aux[count[digit(arr[i], keysNum)]++] = arr[i];
	for (i = left; i <= right; i++)
		arr[i] = aux[i-1];
	//if (count[0] == (right - left + 1)) return;
	//递归对每个箱子进行划分，第一个箱子单独循环，其余通过循环 
	radixMSDSort(arr, left, bin(0) - 1, keysNum + 1);
	for (i = 0; i < R - 1; i++){
		radixMSDSort(arr, bin(i), bin(i + 1) - 1, keysNum + 1);
	}
}

//附注：
//https://www.cnblogs.com/openeim/p/3921645.html
//https://www.cnblogs.com/fnlingnzb-learner/p/9374732.html
void main(int argc, _TCHAR* argv[])
{
	//vector<int> arr = { 2, 3, 7, 1, 6 };
	vector<int> arr = { 21, 34, 74, 3, 20, 2, 56, 46, 6 };
	int size = arr.size();
	//...
	//bubbleSort(arr, 0, size - 1);
	//selectionSort(arr, 0, size - 1);
	//insertSort(arr, 0, size - 1);
	//shellSort(arr, 0, size - 1);
	//binaryInsertSort(arr, 0, size - 1);
	//quickSort(arr, 0, size - 1);
	//heapSort(arr, 0, size - 1);
	mergeSort(arr, 0, size - 1);
	/*vector<string> arr = { "now", "for", "ilk", "dim", "ace", "bet", "ago", "dug", "and" };
	int size = arr.size();
	radixMSDSort(arr, 0, size, 3);*/
	for (int i = 0; i < size; i++){
		cout << arr[i] << " ";
	}
	//cout << digit("abcd", 3) << " ";
	cout <<"\n"<<endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
	system("pause");
	//return 0;
}