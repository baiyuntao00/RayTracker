#ifndef _COUNTDATA_H_
#define _COUNTDATA_H_
#include <assert.h>
#include <iostream>
#include <atomic>
#include <string>


#include<thread>
#include<mutex>
#include<condition_variable>
using namespace std;

 

class CountData{
public:
	CountData(const char* name)
		:m_name(name){
	};

	CountData(const CountData &co) { 
		m_name = co.m_name;
	}
	
	~CountData(){
		lock_guard<mutex> lock(mu);
		std::cout << m_name<<" leak num =" << counter_ << std::endl;
	};
	void inc(){
		lock_guard<mutex> lock(mu);
		++counter_;
	}
	void dec(){
		lock_guard<mutex> lock(mu);
			--counter_;
		assert(counter_ >= 0);
	}
private:
	int64_t counter_;
	std::string m_name;
	mutex mu;
};

template<typename T>
class Counter{
public:
	Counter() 
	{
		data_.inc();
	}
	~Counter() {
		data_.inc();
	}
	Counter(const Counter&){  ; data_.inc(); }
private:
	static CountData data_;
	

};
//TIPS:模板类的静态成员可以定义在头文件中，被链接程序特殊处理
template<typename T>
CountData Counter<T>::data_ = CountData(typeid(T).name());
#endif