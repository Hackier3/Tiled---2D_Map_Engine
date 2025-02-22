#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Decoder
{
public:
	static void decodeGID(uint32_t gid, uint32_t& tileID, bool& flipHorizontal, bool& flipVertical, bool& flipDiagonal);
	static void decompressZlib(const std::string& compressedData, std::vector<uint8_t>& decompressedData);
	static std::string base64_decode(const std::string& encoded_string);

private:
	Decoder();
	~Decoder();
};

