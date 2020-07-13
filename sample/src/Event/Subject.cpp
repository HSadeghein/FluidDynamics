#include "pch.h"
#include "IObserver.h"
#include "../Log.h"
namespace FluidEngine
{

	class Subject : ISubject
	{
	public:
		virtual ~Subject()
		{
			Log::GetCoreLogger()->info("A subject deleted!!");
		}

		void Attach(IObserver* observer) override
		{
			m_ObserverList.push_back(observer);
		}
		void Detach(IObserver* observer) override
		{
			m_ObserverList.remove(observer);
		}

		void Notify() override
		{
			std::list<IObserver*>::iterator it = m_ObserverList.begin();

			while (it != m_ObserverList.end())
			{
				(*it)->Update(m_Message);
				++it;
			}
		}

		void CreateMessage(const char* message)
		{
			this->m_Message = message;
			Notify();
		}

	private:
		std::list<IObserver*> m_ObserverList;
		const char* m_Message;
	};
}