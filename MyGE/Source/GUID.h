#pragma once

#include <xhash>

class GUID {
public:
	GUID();
	GUID(uint64_t guid);
	GUID(const GUID&) = default;

	uint64_t ID();

	operator uint64_t() const { return mID; };
private:
	uint64_t mID = 0;
}; 

namespace std {
	//Override how this class is hashed, just hash the mID through the operator override
	template <>
	struct hash<GUID>
	{
		std::size_t operator()(const GUID& guid) const {
			return hash<uint64_t>()((uint64_t)guid);
		}
	};
}