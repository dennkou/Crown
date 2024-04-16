#pragma once
#include <mutex>
#include <memory>

namespace Crown
{
	//	�C�ӂ̃}���`�X���b�h��Ή��N���X���}���`�X���b�h�ɊȈՓI�ɑΉ�������ׂ̃C���^�[�t�F�[�X���恙
	template<class T>
	class MultiThreadedInterface
	{
	public:
		MultiThreadedInterface()
			:
			m_t(nullptr)
		{
		}

		template<class ...Args>
		MultiThreadedInterface(Args... args)
			:
			m_t(new T(args...))
		{

		}

		~MultiThreadedInterface()
		{
		}

		template<class ...Args>
		void Reset(T* t)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_t.reset(t);
		}

		//	�X���b�h�Z�[�t�Ɋ֐����Ăяo����
		template<class Return, class ...Args>
		Return CallFunction(Return(T::* function)(Args...), Args ...args)
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return (m_t.get()->*function)(args...);
		}
	private:
		std::mutex m_mutex;
		std::shared_ptr<T> m_t;
	};
}