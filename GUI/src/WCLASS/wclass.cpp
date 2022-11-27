#include"wclass.hpp"

namespace AZ{
	namespace GUI{
		
		STATE::STATE(){
			Size = UTIL::POINT2<int>({300, 200});
			Pos = UTIL::POINT2<int>({CW_USEDEFAULT, CW_USEDEFAULT});
		}
		STATE::STATE(const int width, const int height){
			Size = UTIL::POINT2<int>({width, height});
			Pos = UTIL::POINT2<int>({CW_USEDEFAULT, CW_USEDEFAULT});
		}
		STATE::STATE(UTIL::POINT2<int> size){
			Size = size;
			Pos = UTIL::POINT2<int>({CW_USEDEFAULT, CW_USEDEFAULT});
		}
		STATE::STATE(const int width, const int height, const int x, const int y){
			Size = UTIL::POINT2<int>({width, height});
			Pos = UTIL::POINT2<int>({x, y});
		}
		STATE::STATE(UTIL::POINT2<int> size, UTIL::POINT2<int> pos){
			Size = size;
			Pos = pos;
		}
		STATE::~STATE(){}
		
		void STATE::SetSize(int width, int height){
			Size.Set({width, height});
		}
		void STATE::SetSize(UTIL::POINT2<int> size){
			Size = size;
		}
		void STATE::SetPos(int x, int y){
			Pos.Set({x, y});
		}
		void STATE::SetPos(UTIL::POINT2<int> pos){
			Pos = pos;
		}
		std::array<int, 2> STATE::GetSize(){
			return Size.Get();
		}
		std::array<int, 2> STATE::GetPos(){
			return Pos.Get();
		}
		void STATE::SetHandle(HWND tmp){
			hwnd = tmp;
		}
		HWND STATE::GetHandle(){
			return hwnd;
		}
	}
}