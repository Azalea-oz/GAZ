#include"wclass.hpp"

namespace AZ{
	namespace GUI{
		POINT2::POINT2(){
			point[0] = 0;
			point[1] = 0;
		}
		POINT2::POINT2(int x, int y){
			point[0] = x;
			point[1] = y;
		}
		POINT2::~POINT2(){}
		std::array<int, 2> POINT2::Get(){
			return point;
		}
		void POINT2::Set(int x, int y){
			point[0] = x;
			point[1] = y;
		}
		
		STATE::STATE(){
			Size = POINT2(300, 200);
			Pos = POINT2(CW_USEDEFAULT, CW_USEDEFAULT);
		}
		STATE::STATE(const int width, const int height){
			Size = POINT2(width, height);
			Pos = POINT2(CW_USEDEFAULT, CW_USEDEFAULT);
		}
		STATE::STATE(POINT2 size){
			Size = size;
			Pos = POINT2(CW_USEDEFAULT, CW_USEDEFAULT);
		}
		STATE::STATE(const int width, const int height, const int x, const int y){
			Size = POINT2(width, height);
			Pos = POINT2(x, y);
		}
		STATE::STATE(POINT2 size, POINT2 pos){
			Size = size;
			Pos = pos;
		}
		STATE::~STATE(){}
		
		void STATE::SetSize(int width, int height){
			Size.Set(width, height);
		}
		void STATE::SetSize(POINT2 size){
			Size = size;
		}
		void STATE::SetPos(int x, int y){
			Pos.Set(x, y);
		}
		void STATE::SetPos(POINT2 pos){
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