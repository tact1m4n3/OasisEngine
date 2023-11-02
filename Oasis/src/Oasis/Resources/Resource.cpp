#include <Oasis/Resources/Resource.h>

namespace Oasis {

	int Resource::m_LastId = 0;

	Resource::Resource()
		: m_Id(m_LastId++), m_FailedFlag(false)
	{
	}

}