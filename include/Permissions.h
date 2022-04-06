#pragma once
#include <cstdint>
namespace ChineseWall {
	enum Permission : uint8_t {
		Read = 0,
		Write,
		ReadWrite,
		Execute,
		Owner,
		Delete
	};
}