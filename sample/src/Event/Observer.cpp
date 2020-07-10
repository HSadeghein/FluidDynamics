#include "../pch.h"
#include "IObserver.h"
#include "Subject.cpp"

namespace FluidEngine
{
	class Observer : public IObserver
	{


	public:
		Observer(Subject& subject) : m_Subject(subject)
		{
			this->m_Subject.Attach(this);
		}
		virtual ~Observer()
		{

		}
		void Update(const char* message)
		{
		
		}
		void RemoveMeFromtheList()
		{
			m_Subject.Detach(this);
		}
	protected:
	private:
		const char* m_Message;
		Subject& m_Subject;
	};

}