#include <iostream>
#include <ctime>
using namespace std;

class MyBase //класс-предок
{
public:
	MyBase() //конструктор без параметров
	{
		printf("MyBase()\n");
	}
	virtual void showName()
	{
		printf("MyBase\n");
	}
	virtual~MyBase() //деструктор
	{
		printf("~MyBase()\n");
	}
};

class MyClass1 : public MyBase //первый класс-потомок
{
private:
	int x;
	int y;
public:
	MyClass1() //конструктор без параметров
	{
		printf("MyClass1()\n");
		x = 0;
		y = 0;
	}
	MyClass1(int x, int y) //конструктор с параметрами
	{
		printf("MyClass1(int x, int y)\n");
		this->x = x;
		this->y = y;
	}
	MyClass1(const MyClass1& obj) //конструктор копирования
	{
		printf("MyClass1(const MyClass1& obj)\n");
		x = obj.x;
		y = obj.y;
	}
	void showName()
	{
		printf("MyClass1\n");
	}
	~MyClass1() //деструктор
	{
		printf("~MyClass1()\n");
	}
};

class MyClass2 : public MyBase //второй класс-потомок
{
private:
	int x;
	int y;
	int color;
public:
	MyClass2() //конструктор без параметров
	{
		printf("MyClass2()\n");
		x = 0;
		y = 0;
		color = 0;
	}
	MyClass2(int x, int y, int color) //конструктор с параметрами
	{
		printf("MyClass2(int x, int y, int color)\n");
		this->x = x;
		this->y = y;
		this->color = color;
	}
	MyClass2(const MyClass2& obj) //конструктор копирования
	{
		printf("MyClass2(const MyClass2& obj)\n");
		x = obj.x;
		y = obj.y;
		color = obj.color;
	}
	~MyClass2() //деструктор
	{
		printf("~MyClass2()\n");
	}
	void showName()
	{
		printf("MyClass2\n");
	}
};

class MyStorage //класс хранилища
{
private:
	int size;
	MyBase** storage;
public:
	MyStorage(int size) //конструктор с параметром
	{
		printf("MyStorage(int size)\n");
		this->size = size;
		storage = new MyBase * [size]; //инициализация хранилища
		for (int i = 0; i < size; i++) 
			storage[i] = nullptr;
	}
	MyStorage(MyStorage& storage_copy) //конструктор копирования
	{
		printf("MyStorage(MyStorage& storage_copy)\n");
		size = storage_copy.size;
		storage = new MyBase * [size];
		for (int i = 0; i < size; i++)
			*storage[i] = storage_copy.GetObject(i);
	}
	~MyStorage() //деструктор
	{
		printf("~MyStorage()\n");
		for (int i = 0; i < size; i++)
			delete storage[i];
		delete storage;
	}
	int SizeStorage() 
	{
		return size;
	}
	void GetCount() 
	{
		int count = 0;
		for (int i = 0; i < size; i++)
			if (storage[i] != nullptr)
				count = count + 1;
		printf("Количество элементов: %d\nРазмер хранилища: %d\n", count, size);
	}
	void SetObject(int i, MyBase* object) 
	{
		printf("SetObject(int i, MyBase* object): i = %d\n", i);
		storage[i] = object;
	}
	void AddObject(MyBase* object) 
	{
		size = size + 1;
		printf("AddObject(MyBase* object): size = %d\n", size);
		MyBase** storage_copy = new MyBase * [size];
		for (int i = 0; i < size - 1; i++)
			storage_copy[i] = storage[i];
		storage_copy[size - 1] = object;
		for (int j = 0; j < size - 1; j++)
			storage[j] = nullptr;
		delete storage;
		storage = storage_copy;
	}
	MyBase& GetObject(int i)
	{
		return *storage[i];
	}
	void DeleteObject(int i)
	{
		printf("DeleteObject(int i): i = %d\n", i);
		storage[i] = nullptr;
	}
	void ShowObjectMethod(int i)
	{
		printf("ShowObjectMethod(int i): i = %d\n", i);
		if (storage[i] != nullptr)
			storage[i]->showName();
	}
	void ReplaceObject(int i, MyBase* object)
	{
		if (storage[i] == nullptr)
			storage[i] = object;
		else
		{
			delete storage[i];
			storage[i] = object;
		}
	}
	void ShowMyStorage()
	{
		for (int i = 0; i < size; i++)
			if (storage[i] != nullptr)
				storage[i]->showName();
			else printf("nullptr\n");
	}
};

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	MyStorage storage(10);

	for (int i = 0; i < storage.SizeStorage(); i++)
	{
		int r = rand() % 2;
		if (r)
			storage.SetObject(i, new MyClass1);
		else storage.SetObject(i, new MyClass2);
	}
	printf("\n\n");
	for (int i = 0; i < storage.SizeStorage(); i++)
		storage.GetObject(i).showName();
	printf("\n\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d\n", i);
		int action = rand() % 4;
		int rand_index = rand() % storage.SizeStorage();
		int c = rand() % 2;
		switch (action)
		{
		case 0:
			if (c)
			{
				storage.AddObject(new MyClass1);
				printf("AddObject: new MyClass1\n");
			}
			else
			{
				storage.AddObject(new MyClass2);
				printf("AddObject: new MyClass2\n");
			}
			break;
		case 1:
			storage.DeleteObject(rand_index);
			break;
		case 2:
			storage.ShowObjectMethod(rand_index);
			break;
		case 3:
			if (c)
			{
				storage.ReplaceObject(rand_index, new MyClass1);
				printf("ReplaceObject: new MyClass1\n");
			}
			else
			{
				storage.ReplaceObject(rand_index, new MyClass2);
				printf("ReplaceObject: new MyClass2\n");
			}
			break;
		}
		printf("\n\n");
	}
	printf("\n\n");
	storage.ShowMyStorage();
	printf("\n\n");
	storage.GetCount();
	printf("\n\n");
}
