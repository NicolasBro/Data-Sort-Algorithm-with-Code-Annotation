// SortAlgorithms.cpp : Defines the entry point for the console application.
//�Ŵ������㷨
//����Ļ����������Ƚϣ�����
//���У��ȶ����������
//���ȶ����������
#include "stdafx.h"
#include<vector>
using std::vector;
using std::swap;
#include<iostream>
using std::cout;
using std::endl;
#include<string>
using std::string;

//һ��bubbleSort���ȶ�����
//ʱ�临�Ӷȣ�O(n^2)�αȽϣ�O(n^2)�ν����������£�
//�ռ临�Ӷȣ�O(1)��ԭλ����
//���̣�
//2, 3, 7, 1, 6
//i=0,j=size-1~i: 
//2, 3, 7, 1, 6...2, 3, 1, 7, 6;2, 1, 3, 7, 6; (1),2, 3, 7, 6//�ȶ�����
//i=1,j=size-1~i:(1),2, 3, 7, 6     ...     (1),(2), 3, 6, 7
//i=2,j=size-1~i:(1),(2), 3, 6, 7   ...     (1),(2),(3), 6, 7
//i=3,j=size-1~i:(1),(2),(3), 6, 7 ; (1),(2),(3),(6), 7
//i=4,j=size-1~i:(1),(2),(3),(6), 7; (1),(2),(3),(6), (7)
//����
void bubbleSort(vector<int>& arr, int left, int right){
	//int size = arr.size();
	for (int i = left; i < right; i++){//��С�������У�ÿ�ΰѵ�ǰ��С�����ַ���λ��i
		for (int j = right; j>i; j--){//��ѭ�������������Ԫ��
			if (arr[j] < arr[j - 1]){//�����ڵ�Ԫ�ؽ��бȽ�-��������
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

//��.selectionSort�����ȶ�����
//ʱ�临�Ӷȣ�O(n^2)�αȽϣ�O(n)�ν����������£�
//�ռ临�Ӷȣ�O(1)��ԭλ����
//���̣�
//2, 3, 7, 1, 6
//i=0,j=i~size-1:...minInd = 3; (1), 3, 7, 2, 6//���ȶ�����
//i=1,j=i~size-1:...minInd = 3; (1),��2��, 7, 3, 6
//i=2,j=i~size-1:...minInd = 3; (1),��2��,��3��, 7, 6
//i=3,j=i~size-1:...minInd = 4; (1),��2��,��3��,��6��, 7
// (1),��2��,��3��,��6��, ��7��
//����
void selectionSort(vector<int>& arr, int left, int right){
	for (int i = left; i < right; i++){//��С��������
		int minInd = i;//Ѱ���±꣬�����˽�������
		for (int j = i; j <= right; j++){//��ѭ�������ұ���Ԫ��
			if (arr[j] < arr[minInd]){//ÿ���ҵ���iС��Ԫ�ص��±�minInd
				minInd = j;
			}
		}
		swap(arr[i], arr[minInd]);//����
	}
}

//��.insertSort���ȶ�����
//ʱ�临�Ӷȣ�O(n^2)�αȽϣ�O(n^2)�ν����������£�
//�ռ临�Ӷȣ�O(1)��ԭλ����
//2, 3, 7, 1, 6
//���ù۲��ڣ�...��1��,2,3,7,6
//i=2,cur=3����1��,2,3|7,6
//i=2,cur=7����1��,2,3,7|6
//i=2,cur=3����1��,2,3,(),7; (1��,2,3,(6),7;     //while(true),7����һλ
// 1,2,4,6,7
//����
void insertSort(vector<int>& arr, int left, int right){
	for (int i = right; i > 0; i--){
		if (arr[i] < arr[i - 1]){//����һ���۲��ڣ�����С��Ԫ�ط��ڵ�һλ
			swap(arr[i], arr[i - 1]);
		}
	}
	for (int i = left + 2; i <= right; i++){//��ѭ��ʹ��ǰi��Ԫ������
		int j = i;
		int cur = arr[i];//�ѵ�ǰֵ���뵽ǰi��λ�õĺ���λ�ã�ʹ��ǰi��Ԫ������
		while (cur < arr[j-1]){//��arr[1]...arr[i-1]�У����ڱ�cur�����ֵ������ֵ��������ֵ����һλ
			arr[j] = arr[j - 1];//����һλ
			j--;
		}
		arr[j] = cur;//
	}
}

//��.shellSort�����ȶ�����
//ʱ�临�Ӷȣ�O(n^2)�αȽϣ�O(n^2)�ν����������£�
//�ռ临�Ӷȣ�O(1)��ԭλ����
//2, 3, 7, 1, 6
//increment=2,i=2,j=2,cur=7��2, 3, 7, 1, 6
//			  i=3,j=3,cur=1��2,3,7,(3),6
//                j=1,cur=1��2,(1),7,(3),6
//            i=4,j=4,cur=6��2,(1),7,(3),(7)
//                j=2,cur=6��2,(1),6,(3),(7)
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
//����
void shellSort(vector<int>& arr, int left, int right){
	int increment = (right - left + 1)/2;
	while (increment){//��insertSort�Ļ����ϣ��ı䲽��
		for (int i = left + increment; i <= right; i++){
			int j = i;
			int cur = arr[i];
			while (j >= left + increment && cur<arr[j - increment]){
				arr[j] = arr[j - increment];
				j -= increment;
			}
			arr[j] = cur;
		}
		increment /= 2;//�������������򣬲����ݼ�
	}

	//for (int i = left + 2; i <= right; i++){//��ѭ��ʹ��ǰi��Ԫ������
	//	int j = i;
	//	int cur = arr[i];//�ѵ�ǰֵ���뵽ǰi��λ�õĺ���λ�ã�ʹ��ǰi��Ԫ������
	//	while (cur < arr[j - 1]){//��arr[1]...arr[i-1]�У����ڱ�cur�����ֵ������ֵ��������ֵ����һλ
	//		arr[j] = arr[j - 1];//����һλ
	//		j--;
	//	}
	//	arr[j] = cur;//
	//}
}

//��.binaryInsertSort,���ȶ�����
//����ǰi-1��������,���ж��ֲ��ҵõ�arr[i]�Ĳ���λ��
//ʱ�临�Ӷȣ�O(nlgn)�αȽϣ�O(nlgn)�ν����������£�
//�ռ临�Ӷȣ�O(1)��ԭλ����
//2, 3, 7, 1, 6
//���ù۲��ڣ�...��1��,2,3,7,6
//i=2,cur=3,toSortLeft=0,toSortRight=1,middle=0
//			toSortLeft=1,toSortRight=1,middle=1
//			toSortLeft=2,						toSortLeft=i//arr[i]��������λ��
//...i=7ͬ��...
//i=4,cur=6,toSortLeft=0,toSortRight=3,middle=1
//			toSortLeft=1,toSortRight=3,middle=2
//			toSortLeft=2,toSortRight=3,middle=2
//			toSortLeft=3,toSortRight=3,middle=3
//						 toSortRight=2         //toSortLeft=3
//												(1��,2,3,7,(7)
//												(1��,2,3,(6),(7)
//����
void binaryInsertSort(vector<int>& arr, int left, int right){
	for (int i = right; i > 0; i--){
		if (arr[i] < arr[i - 1]){//����һ���۲��ڣ�����С��Ԫ�ط��ڵ�һλ
			swap(arr[i], arr[i - 1]);
		}
	}
	int middle = 0;
	for (int i = left+2; i <= right; i++){
		//ǰi-1��Ԫ���Ѿ�����
		//����ǰi-1��������,���ж��ֲ��ҵõ�arr[i]�Ĳ���λ��
		int cur = arr[i];//������Ԫ�أ����뵽ǰi-1��Ԫ����;
		int toSortLeft = left;
		int toSortRight = i - 1;
		while (toSortLeft <= toSortRight){
			middle = (toSortLeft + toSortRight) / 2;
			if (cur>arr[middle]){
				toSortLeft = middle + 1;
			}
			else{
				toSortRight = middle - 1;//���ȶ�����
			}
		}
		if (toSortLeft == i) continue;
		for (int j = i; j > toSortLeft; j--){
			arr[j] = arr[j - 1];
		}
		arr[toSortLeft] = cur;
	}
}

//��.quickSort�����ȶ�����
//
//ʱ�临�Ӷȣ�O(nlgn)�αȽϣ�O(nlgn)�ν����������£�
//��������
//�ռ临�Ӷȣ�O(1)��ԭλ����
int partition(vector<int> &arr, int left, int right){
	int low = left - 1;
	int high = right;
	int cur = arr[right];
	while(low<high){
		//ǰ�ã�++low������������ص������󡱶����Ӧ��
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

//��.mergeSort
//https://www.cnblogs.com/chengxiao/p/6194356.html
void merge(vector<int>& array, int left, int middle, int right)
{
	int left_len = middle - left+1;
	int right_len = right - middle;
	vector<int> left_array(left_len,0);
	vector<int> right_array(right_len,0);
	int i, j, k;

	//����������������
	for (i = 0; i < left_len; i++)
		left_array[i] = array[i + left];

	for (j = 0; j < right_len; j++)
		right_array[j] = array[j + middle + 1];

	//�������������б��һ����������
	k = left;//��λ�ؼ�
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

//��.heapSort�����ȶ�����
//ʱ�临�Ӷȣ�O(nlgn)�αȽϣ�O(nlgn)�ν���
//���ۣ�����������������ʱ���ر���������ʵ��
//�ռ临�Ӷȣ�ԭλ����
//�ؼ�:
//�ѣ���ʾΪ���飻���йؼ��ְ��ն��������ȫ����������ʽ����
//����һ�������õıȽϴ�������2N��
//���̣�
//��1�����ȣ�forѭ���ȹ���󶥶�
//��2�����ţ�forѭ���������Ԫ���������е����һ��Ԫ�أ���������
//forѭ���ȹ���󶥶�
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
//										(7), (6), (2), 1, (3);   //�󶥶ѹ������
//���ţ�whileѭ���������Ԫ���������е����һ��Ԫ�أ���������
//swap(arr[0], arr[size-1]):3,6,2,1,7
//fixDown(arr, 0, size-1):size=4,cur=3,sonInd=1:
//										       (6),6,2,1,7
//										       fatherInd=1,sonInd=3;
//                                             ...��break��
//                                             (6),(3),2,1,7
//1,(3),2,6,7
//...
//1,2,3,6,7
//���϶��¹����󶥶�
void fixDown(vector<int>& arr, int fatherInd, int size){
	int sonInd = 2 * fatherInd + 1;
	int cur = arr[fatherInd];
	while (sonInd < size){
		if (sonInd + 1 < size && arr[sonInd] < arr[sonInd + 1]) sonInd++;
		if (cur > arr[sonInd]) break;
		arr[fatherInd] = arr[sonInd];//����
		fatherInd = sonInd;
		sonInd = 2 * fatherInd + 1;
	}
	arr[fatherInd] = cur;
}
void heapSort(vector<int>& arr, int left, int right){
	//1.�����󶥶�
	int size = arr.size();
	for (int fatherInd = size / 2 - 1; fatherInd >= 0; fatherInd--){
		//�ӵ�һ����Ҷ�ӽ��������ϣ�������������ṹ
		fixDown(arr, fatherInd, size);
	}
	//2.�����ѽṹ+�����Ѷ�Ԫ����ĩβԪ��
	for (int j = size - 1; j>0; j--){
		swap(arr[0], arr[j]);//���Ѷ�Ԫ����ĩβԪ�ؽ��н���
		fixDown(arr, 0, j);//���¶Զѽ��е���
	}
}

//��.radixSort,�ȶ�����
//�����ؼ��֣��������á�����-�ռ����Ĺ��̽�������
//"��������"�Ļ���˼�룺˵���˾��ǽ��ж�ε�Ͱʽ����
//����: (1)���������������ȽϹؼ��֣�����ͨ�������䡱�͡��ռ���������ʵ������;
//	    (2)���ǵ�ʱ�临�Ӷȿɴﵽ���Խף�O(n);
//		(3)���Զ��ַ������͵Ĺؼ��ֽ��п��ٵĲ���
//���ࣺ���λ����(Most Significant Digit first)�������MSD ����
//	    ���λ����(Least Significant Digit first)�������LSD ����
#define bytesword 4
#define bitsbyte 8
#define bitsword 32
#define R 26//(1<<bitsbyte)
//#define RA  26       /*�ַ�������*/
//#define digit(A,B) (((A) >> (bitsword-((B)+1)*bitsbyte))&(R-1))
#define digit(A,B) A[B]
#define dia(arr,ind)   ((arr[ind])?arr[ind]-'a'+1:0) /*����ĸת��������(0~25)*/
#define bin(A)      (left+count[A])/*ȡ�õ�ind�����ӵ�Ԫ�ظ���*/
vector<string> aux(256); /*ȫ������*/
void radixMSDSort(vector<string>& arr, int left, int right, int keysNum){
	int i;
	vector<int> count(R + 1, 0);//��������
	if (keysNum > bytesword) return;
	//M
	//ʹ��������������ķ������л���
	for (i = left; i <= right; i++){
		count[digit(arr[i], keysNum) + 1]++;
		//count[dia(arr[i], w) + 1]++;
	}
	for (i = 1; i < R; i++) count[i] += count[i - 1];//
	for (i = left; i <= right; i++) aux[count[digit(arr[i], keysNum)]++] = arr[i];
	for (i = left; i <= right; i++)
		arr[i] = aux[i-1];
	//if (count[0] == (right - left + 1)) return;
	//�ݹ��ÿ�����ӽ��л��֣���һ�����ӵ���ѭ��������ͨ��ѭ�� 
	radixMSDSort(arr, left, bin(0) - 1, keysNum + 1);
	for (i = 0; i < R - 1; i++){
		radixMSDSort(arr, bin(i), bin(i + 1) - 1, keysNum + 1);
	}
}

//��ע��
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