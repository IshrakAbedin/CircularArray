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

	Vec3(const Vec3& other) : X(other.X), Y(other.Y), Z(other.Z) { std::printf("Vec3 Copy!\n"); }
	Vec3& operator=(const Vec3& other)
	{ 
		X = other.X;
		Y = other.Y;
		Z = other.Z;
		std::printf("Vec3 Copy!\n");
		return *this;
	}
	Vec3(Vec3&& other) noexcept : X(std::move(other.X)), Y(std::move(other.Y)), Z(std::move(other.Z)) { std::printf("Vec3 Move!\n"); }
	Vec3& operator=(Vec3&& other) noexcept
	{
		X = std::move(other.X);
		Y = std::move(other.Y);
		Z = std::move(other.Z);
		std::printf("Vec3 Move!\n");
		return *this;
	}

	~Vec3() { std::printf("\nVec3 {%g, %g, %g} Destroyed!\n", X, Y, Z); }
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

int main()
{
	/*intTest();
	StructTest();
	StructTestWithEmplace();*/
	IteratorTest();
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
		std::printf("Adding: %d ...", i);
		std::cin.get();
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
		std::printf("Removal %d ...", i);
		std::cin.get();
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
		std::printf("Adding: %d ...", i);
		std::cin.get();
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
	carray.Add(Vec3{5}); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({ 7, 8, 9 }); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({22}); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
	carray.Add({33}); for (int i = 0; i < carray.Count(); i++) carray[i].PrintSelf(); std::cout << std::endl;
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