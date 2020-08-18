#include<windows.h>
#include<locale.h>

#define USE_UTF_8
#define USE_SJIS
#define USE_EUC

namespace AZ{
	namespace CUI{
		namespace CHCODE{

			///////////////////////////////////////////////////////////
			//  How to use
			//  
			//  class A : public UTF8{
			//      A() : UTF8{
			//      }
			//  }
			//

			class UTF8{
			private:
				
			public:
				UTF8(){
					//set charcode to use in cmd.
					system("chcp 65001");
					system("cls");
				}
				~UTF8(){
					//reset charcode
					system("chcp 932");
					system("cls");
				}
			};

			class SJIS{
			private:
				
			public:
				SJIS(){
					//set charcode to use in cmd.
					system("chcp 932");
					system("cls");
				}
				~SJIS(){
					//reset charcode
					system("chcp 932");
					system("cls");
				}
			};

			class EUCJP{
			private:
				
			public:
				EUCJP(){
					//set charcode to use in cmd.
					system("chcp 51932");
					system("cls");
				}
				~EUCJP(){
					//reset charcode
					system("chcp 932");
					system("cls");
				}
			};
		};
	};
}