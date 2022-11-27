#pragma once

#include<string>
#include<windows.h>
#include<vector>
#include<array>
#include<typeinfo>
#include<cxxabi.h>

#include"../defines.hpp"


namespace AZ{
	namespace UTIL{
		
		//テンプレートクラスのため、実装はここに書く。
		template<class U>
		class Singleton{
			static U *instance;
		protected:
			Singleton() = default;
			~Singleton() = default;
			
		public:
			Singleton(const Singleton&) = delete;
			Singleton& operator=(const Singleton&) = delete;
			Singleton(Singleton&&) = delete;
			Singleton& operator=(Singleton&&) = delete;
		
			static void Create(){
				if(!instance){
					instance = new U;
				}
			}
			
			static U& Get_Instance(){
				if(!instance){
					Create();
				}
				return *instance;
			}
			
			static void Destroy(){
				delete instance;
				instance = nullptr;
			}
			
		};
		
		template<class U>
		U *Singleton<U>::instance = nullptr;
		
		
		std::wstring StoWS(std::string);
		std::string WStoS(std::wstring);
		
		
		
		template<typename T, size_t size = 1>
		class POINT{
			std::array<T, size> point;
			
		public:
			POINT();
			POINT(std::array<T, size>);
			~POINT();
			
			std::array<T, size> Get();
			void Set(std::array<T, size>);
		};
		
		template<typename T>
		using POINT2 = POINT<T, (int)2>;
		
		template<typename T, size_t size>
		POINT<T, size>::POINT(){}
		
		template<typename T, size_t size>
		POINT<T, size>::POINT(std::array<T, size> p) : point(p){}
		
		template<typename T, size_t size>
		POINT<T, size>::~POINT(){}
		
		template<typename T, size_t size>
		std::array<T, size> POINT<T, size>::Get(){
			return point;
		}
		
		template<typename T, size_t size>
		void POINT<T, size>::Set(std::array<T, size> p){
			point = p;
		}
		
		template<class T>
		class TREE{
			TREE<T> *right, *left;
			T &data;
			
		public:
			TREE<T> Right();
			TREE<T> Left();
			void Insert(T&);
			
		};
		
		template<typename T>
		class TYPE{
		public:
			static std::string Name(){
				char *buf = new char[64];
				int status;
				std::string str = "Type[";
				str += abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
				str += "]";
				delete[] buf;
				return str;
			}
		};
		template<typename T>
		std::string GetTypeStr(){
			std::string str = "Type[";
			str += typeid(T).name();
			str += "]";
			return str;
		}
		
		
		// 多重起動防止
		class NoMultiWindow{
			HANDLE hMutex;
			
		public:
			NoMultiWindow();
			~NoMultiWindow();
		};
	}
}