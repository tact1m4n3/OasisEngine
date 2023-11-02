#pragma once

#include <string>

namespace Oasis {

	class Resource
	{
	protected:
		bool m_FailedFlag;
	private:
		static int m_LastId;

		int m_Id;
	public:
		Resource();

		inline int GetId() const { return m_Id; }
		inline bool Failed() const { return m_FailedFlag; }
	};

}