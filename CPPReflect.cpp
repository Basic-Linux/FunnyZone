#include <map>
#include <iostream>
#include <string>

using namespace std;

#define REGISTER(className,funcName) \
__attribute((constructor)) void before_main##className##funcName()	\
{																				\
	ReflectAction::getFuncInstance().registClassFunc(#className#funcName,className::funcName);	\
}	


class TestClassA{	
public:
	void m_func(int a,int b);
};
void TestClassA::m_func(int a,int b){
        cout<<"hello TestClassA" << a << b <<endl;
    };	
//第一步：定义函数指针
typedef void (TestClassA::*PTRDeclareFunc)(int,int);
//第二步：定义反射类，用于序列化方法
class ReflectAction{
	private:
	map<string,PTRDeclareFunc> m_classFuncMap;
	ReflectAction(){}
	public:
	//=============================================
	static ReflectAction& getFuncInstance();
	void getClassFuncByName(string className,int a,int b)
	{
		map<string, PTRDeclareFunc>::const_iterator iter;  
		iter = m_classFuncMap.find(className) ;  
		if ( iter == m_classFuncMap.end() )  
			return;  
		else  
		{
			TestClassA *q = new TestClassA;
			PTRDeclareFunc p = iter->second;
			(q->*p)(a,b);
		}
		return ;
	}
	//=============================================
	void registClassFunc(string name, PTRDeclareFunc method)
	{
		m_classFuncMap.insert(pair<string, PTRDeclareFunc>(name, method)) ;  
	}
};
ReflectAction& ReflectAction::getFuncInstance(){ static ReflectAction sigleClass; return sigleClass;}
//第三步：注册我们要反射的函数
REGISTER(TestClassA,m_func);

int main(int argc,char* argv[]){
	ReflectAction::getFuncInstance().getClassFuncByName("TestClassAm_func",1,1);
}