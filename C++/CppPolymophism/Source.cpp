#include <string>
#include <iostream>

using namespace std;

class A {
	string str;

public:
	A(string s) : str(s) { cout << "A::" << str << endl; }
	~A() { cout << "~A::" << str << endl; }
	void foo() { cout << "A::" << str << "foo()" << endl; }
	virtual void bar() { cout << "A::" << str << "bar()" << endl; }

};

class B : public A {
	string str;

public:
	B(string s) : A(s), str(s) { cout << "B::" << str << endl; }
	~B() { cout << "~B::" << str << endl; }
	void foo() { cout << "B::" << str << "foo()" << endl; }
	void bar() { cout << "B::" << str << "bar()" << endl; }

};

static void func(A param) {
	param.foo();
	param.bar();
	{
		auto_ptr<A> p(new B("auto_ptrB"));
		p->foo();
		p->bar();
	}
}

int main() {
	B b("mainB");
	A *a;
	a = &b;
	a->foo();
	a->bar();
	func(b);
	return 0;
}