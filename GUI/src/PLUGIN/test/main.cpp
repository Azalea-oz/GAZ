#include"test.hpp"

#include<string>
#include<iostream>
#include<vector>
#include<memory>

int main(int argc, char **argv){
	std::vector<std::string> plugins;
	std::vector<void*> handles;
	
	plugins.push_back("Hoge.dll");
	plugins.push_back("Hoges.dll");
	plugins.push_back("HogeEx.dll");
	plugins.push_back("Test.dll");
	
	for(int i=0; i<plugins.size(); i++){
		void *handle;
		Test *(*create)(void);
		
		std::cout << "---- start point ----" << std::endl;
		
		handle = dlopen(plugins[i].c_str(), "");
		if(handle == nullptr){
			std::cout << "Can't load Plugins : " << plugins[i] << std::endl;
			continue;
		}
		
		create = (Test *(*)(void)) dlsym(handle, "Create");
		
		if(create == nullptr){
			std::cout << "Not found 'Craete' Function : " << plugins[i] << std::endl;
			dlclose(handle);
			continue;
		}
		std::cout << "Found 'Craete' Function : " << plugins[i] << std::endl;
		handles.push_back(handle);
		
		std::auto_ptr<Test> p(create());
		std::cout << "Version[" << p->version() << "]" << std::endl;
	}
	
	for(int i = 0; i < handles.size(); i++){
		dlclose(handles[i]);
		handles[i] = nullptr;
	}
}