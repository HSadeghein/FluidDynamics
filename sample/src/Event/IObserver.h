#pragma once


namespace FluidEngine
{
	class IObserver
	{
	public:
		virtual ~IObserver();
		virtual void Update(const char* message) = 0;
	protected:
	};

	class ISubject
	{
	public:
		virtual ~ISubject();
		virtual void Attach(IObserver* observer) = 0;
		virtual void Detach(IObserver* observer) = 0;
		virtual void Notify() = 0;
	};
}
