



namespace AZ{
	namespace GUI{
		namespace COMPO{
			
			class BUTTON{
				bool state;
			public:
				BUTTON() : state(false){}
				~BUTTON(){}
				
				virtual void OnClick() = 0;
				
			private:
				virtual void View() = 0;
				
			};
			
		}
	}
}

class TESTBUTTON : public AZ::GUI::COMPO{
	
public:
	
	
};