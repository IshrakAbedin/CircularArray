#include <iostream>
#include <vector>
#include "CircularArray.h"

struct Vec3
{
	float X = 0;
	float Y = 0;
	float Z = 0;

	Vec3() {}
	Vec3(float val) : X(val), Y(val), Z(val) {}
	Vec3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	Vec3(const Vec3& other) : X(other.X), Y(other.Y), Z(other.Z)
	{
#ifdef DEBUG
		std::printf("Vec3 Copy!\n");
#endif
	}

	Vec3& operator=(const Vec3& other)
	{
		X = other.X;
		Y = other.Y;
		Z = other.Z;
#ifdef DEBUG
		std::printf("Vec3 Copy!\n");
#endif
		return *this;
	}

	Vec3(Vec3&& other) noexcept : X(std::move(other.X)), Y(std::move(other.Y)), Z(std::move(other.Z))
	{
#ifdef DEBUG
		std::printf("Vec3 Move!\n");
#endif
	}

	Vec3& operator=(Vec3&& other) noexcept
	{
		X = std::move(other.X);
		Y = std::move(other.Y);
		Z = std::move(other.Z);
#ifdef DEBUG
		std::printf("Vec3 Move!\n");
#endif
		return *this;
	}

	~Vec3()
	{
#ifdef DEBUG
		std::printf("\nVec3 {%g, %g, %g} Destroyed!\n", X, Y, Z);
#endif
	}
	inline void PrintSelf()
	{
		std::printf("{%g, %g, %g}", X, Y, Z);
	}
};

template<typename T, size_t S>
void DebugPrintInfo(const ish::CircularArray<T, S> carray);
void intTest();
void StructTest();
void StructTestWithEmplace();
void IteratorTest();
void IteratorOperatorPlusAndPlusAssignTest();
void IteratorWithStructTest();
void InitializerListTest();

int main()
{
	intTest();
	StructTest();
	StructTestWithEmplace();
	IteratorTest();
	IteratorOperatorPlusAndPlusAssignTest();
	IteratorWithStructTest();
	InitializerListTest();
}

template<typename T, size_t S>
void DebugPrintInfo<T, S>(const ish::CircularArray<T, S> carray)
{
	std::printf("Capacity: %zu | Count: %zu | Start : %zu | Next: %zu\n",
		carray.Capacity(), carray.Count(), carray.Start(), carray.Next());
}

void intTest()
{
	std::printf("########## BEGIN INT TEST ##########\n\n");
	ish::CircularArray<int, 5> carray;

	DebugPrintInfo(carray);
	for (int i = 0; i < 15; i++)
	{
		std::printf("Adding: %d ...\n", i);
		carray.Add(i);
		for (int j = 0; j < carray.Count(); j++)
		{
			std::printf("%d, ", carray[j]);
		}
		std::printf("\n");
		DebugPrintInfo(carray);
		std::printf("\n");
	}

	std::printf("--------\nREMOVING\n--------\n");

	for (int i = 0; i < 10; i++)
	{
		std::printf("Removal %d ...\n", i);
		carray.RemoveLastItem();
		for (int j = 0; j < carray.Count(); j++)
		{
			std::printf("%d, ", carray[j]);
		}
		std::printf("\n");
		DebugPrintInfo(carray);
		std::printf("\n");
	}

	std::printf("--------\nAdding Again\n--------\n");

	for (int i = 0; i < 10; i++)
	{
		std::printf("Adding: %d ...\n", i);
		carray.Add(i);
		for (int j = 0; j < carray.Count(); j++)
		{
			std::printf("%d, ", carray[j]);
		}
		std::printf("\n");
		DebugPrintInfo(carray);
		std::printf("\n");
	}

	std::printf("########## END INT TEST ##########\n\n");
}

void StructTest()
{
	std::printf("########## BEGIN STRUCT TEST ##########\n\n");
	ish::CircularArray<Vec3, 5> carray;

	carray.Add(Vec3{ 1, 2, 3 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add(Vec3{ 5 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({ 7, 8, 9 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({ 22 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({ 33 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.RemoveLastItem();
	carray.RemoveLastItem();
	carray.Add({ 0, 1, 0 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({ 22, 33, 44 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;

	std::printf("########## END STRUCT TEST ##########\n\n");
}

void StructTestWithEmplace()
{
	std::printf("########## BEGIN STRUCT EMPLACE TEST ##########\n\n");
	ish::CircularArray<Vec3, 5> carray;

	carray.EmplaceBack(1, 2, 3); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.EmplaceBack(5); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.EmplaceBack(7, 8, 9); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.EmplaceBack(22); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.EmplaceBack(33); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.RemoveLastItem();
	carray.RemoveLastItem();
	carray.EmplaceBack(0, 1, 0); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.EmplaceBack(22, 33, 44); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;

	std::printf("########## END STRUCT EMPLACE TEST ##########\n\n");
}

void IteratorTest()
{
	std::printf("########## BEGIN ITERATOR TEST ##########\n\n");

	ish::CircularArray<int, 4> carray;
	std::vector<int> refVector{ 1, 2, 3, 4 };

	carray.Add(1);
	carray.Add(2);
	carray.Add(3);
	carray.Add(4);
	carray.Add(5);


	std::printf(">> Index based for loop:\n");
	for (int i = 0; i < carray.Count(); i++)
	{
		std::cout << carray[i] << ',';
	}
	std::cout << std::endl;

	std::printf(">> Iterator based for loop:\n");
	for (ish::CircularArray<int, 4>::ForwardIterator it = carray.begin(); it != carray.end(); it++)
	{
		std::cout << *it << ',';
	}
	std::cout << std::endl;

	std::printf(">> Ranged for loop:\n");
	for (auto& val : carray)
	{
		std::cout << val << ',';
		val = 2;
	}
	std::cout << std::endl;

	std::printf("########## END ITERATOR TEST ##########\n\n");
}

void IteratorOperatorPlusAndPlusAssignTest()
{
	std::printf("########## BEGIN ITERATOR + and += TEST ##########\n\n");

	ish::CircularArray<int, 5> carray;
	for (int i = 0; i < 10; i++)
	{
		carray.Add(i);
	}
	for (auto val : carray)
	{
		std::printf("%d, ", val);
	}
	std::printf("\n\n");

	auto it = carray.begin();

	std::cout << "Begin: " << *it << std::endl;
	std::cout << "Begin + 1: " << *(it + 1) << std::endl;
	std::cout << "Begin + 2: " << *(it + 2) << std::endl;
	std::cout << "Begin + 3: " << *(it + 3) << std::endl << std::endl;

	std::cout << "Begin = Begin + 1: " << *(it = it + 1) << std::endl;
	std::cout << "Begin: " << *it << std::endl;
	std::cout << "Begin += 1: " << *(it += 1) << std::endl;
	std::cout << "Begin += 2: " << *(it += 2) << std::endl;
	std::cout << "Begin += -2: " << *(it += -2) << std::endl;
	std::cout << "Begin += 3(garbage expected): " << *(it + 3) << std::endl;

	std::printf("########## END ITERATOR + and += TEST ##########\n\n");
}

void IteratorWithStructTest()
{
	std::printf("########## BEGIN ITERATOR WITH STRUCT TEST ##########\n\n");

	ish::CircularArray<Vec3, 4> carray;

	for (int i = 0; i < 5; i++)
	{
		if (i % 2)
			carray.EmplaceBack(i, i + 1, i + 2);
		else
			carray.EmplaceBack(i * i);
	}

	for (auto& val : carray)
		std::printf("{%g, %g, %g}\n", val.X, val.Y, val.Z);

	std::printf("########## END ITERATOR WITH STRUCT TEST ##########\n\n");
}

void InitializerListTest()
{
	std::printf("########## BEGIN INITIALIZER LIST TEST ##########\n\n");

	std::printf(">> For primitive types (int): \n");

	ish::CircularArray<int, 5> carrayInt{ 1, 2, 3, 4, 5, 6, 7 };
	for (int item : carrayInt)
	{
		std::printf("%d, ", item);
	}
	std::printf("\n");

	std::printf(">> For structs (Vec3): \n");

	ish::CircularArray<Vec3, 6> carrayVec3{ {1}, {2}, {3}, {4} };

	carrayVec3 = {
		{1, 2, 3},
		Vec3(4, 5, 6)
	};

	for (auto& item : carrayVec3)
	{
		std::printf("{%g, %g, %g}, ", item.X, item.Y, item.Z);
	}
	std::printf("\n");

	std::printf("########## END INITIALIZER LIST TEST ##########\n\n");
}