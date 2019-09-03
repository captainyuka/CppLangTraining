#include<iostream>
/*
 *   If you are writing a database that may contain terabytes
 * of data in its internal structures, you might want to ensure that a client of this class
 * cannot instantiate it on the stack; instead it is forced to create instances only on the free
 * store. The key to ensuring this is declaring the destructor private
*/
class MonsterDB {
private:
	~MonsterDB(){}		// private destructor
	//... members that consume a huge amount of data

public:
	static void DestroyInstance(MonsterDB* monsterDB) {
		delete monsterDB;			// member can invoke private destructor
	}

	void doSomething() {}
};

int main() {
//	MonsterDB myDatabase;					 // compile error
	MonsterDB* myDatabase = new MonsterDB(); // no error
	myDatabase->doSomething();
	MonsterDB::DestroyInstance(myDatabase);		// release the allocated memory using static method
} 


