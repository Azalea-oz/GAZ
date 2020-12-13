#pragma once

namespace SINGLETON{
	
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
}