/**************************************************
* Author: Yao Yao @ 114183
* Date: 2019-03-24
* Contaction: yaoy@cug.edu.cn
* Attention 1: 未调试，仅作为C++作业demo参考语法。内可能有大量逻辑错误。
* Attention 2: 请勿抄袭。
* Attention 3: 学会内存操作函数（memset, memcpy）
************************************************/

#ifndef YY_CPP_QUESTION_ARRAY
#define YY_CPP_QUESTION_ARRAY

class CArray{
public:
	//默认构造函数
	CArray(){
		mpData = NULL;
		mnLength = 0;
	}
	
	//带有长度的构造函数
	CArray(int nLength){
		mpData = new int[nLength];
		//数组内全部置零
		memset(mpData, 0, nLength*sizeof(int));
		mnLength = nLength;
	}
	
	//析构函数，delete时调用，释放内存
	~CArray(){
		reset();
	}
	
	//复制构造函数，非常重要，重载时需要
	CArray(CArray& arr){
		//复制到本内存中
		copyMemory(arr.getData(), arr.getLength());
	}
	
	//获取元素
	int at(int nIdx){
		return mpData[nIdx];
	}
	
public:
	CArray& operator=(CArray& arr){
		copyMemory(arr.getData(), arr.getLength());
		return *this;
	}
	
	//注意，没有做范围限定
	int& operator[](int nIdx){
		return mpData[nIdx];
	}
	
	//可能有bug
	CArray& operator+(CArray& arr){
		//目标数组
		CArray* pArr = new CArray(mnLength + arr.getLength());
		//内存拷贝1
		memcpy((unsigned char*)pArr, mpData, mnLength*sizeof(int));
		//内存拷贝2（可能有错，老老实实用for循环）
		memcpy((unsigned char*)pArr+mnLength*sizeof(int), arr.getData(), arr.getLength()*sizeof(int));		
		return* pArr;
	}
	
	//可能有bug
	CArray& operator+=(CArray& arr){
		//临时存储
		CArray* pArr = new CArray(mnLength + arr.getLength());
		//内存拷贝1
		memcpy((unsigned char*)pArr, mpData, mnLength*sizeof(int));
		//内存拷贝2
		memcpy((unsigned char*)pArr+mnLength*sizeof(int), arr.getData(), arr.getLength()*sizeof(int));		
		//相加
		copyMemory(pArr->getData(), pArr->getLength());
		//清空新建内存
		delete pArr;
		//返回
		return *this;
		
	}
	
//取子串
public:
	CArray& getSubArray(int nStartIdx, int nEndIdx){
		int nLength = nEndIdx - nStartIdx;
		CArray* arr = new CArray(nLength);
		for(int  i = nStartIdx; i < nEndIdx; i++)
			arr[i-nStartIdx] = this->mpData[nStartIdx];	
		return *arr;
	}
	
	CArray& operator() (int nStartIdx, int nEndIdx){
		return getSubArray(nStartIdx, nEndIdx);
	}


public:
	int* getData(){
		return mpData;
	}
	
	int getLength(){
		return mnLength;
	}
	
protected:
	//清空内存，inline提升效率
	inline void reset(){
		if (mpData != NULL)
			delete []mpData;
		mpData = NULL;
		mnLength = 0;
	}
	
	//复制内存，inline提升效率
	inline void copyMemory(int* pData, int nLen){
		//先清空内存
		reset();
		
		if(pData == NULL || nLen == 0)
			return;
		
		//创建空间
		mpData = new int[nLen];
		
		//复制
		mnLength = nLen;
		for (int i=0; i<nLen; i++)
			mpData[i] = pData[i];	

		//复制用内存操作(memcpy)可以写成
		//memcpy(mpData, pData, nLen*sizeof(int));
	}
	
	
private:
	//存储数据指针
	int* mpData;
	//存储数据长度
	int mnLength;
	
};

#endif