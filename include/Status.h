#pragma once
#include <cstdint>
namespace ChineseWall {
	enum Status : uint8_t {
		Success = 0,
		Failure,
		BadAllocation,
		PermissionDenied
	};
}