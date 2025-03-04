#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Decoder
{
public:
	static void DecodeGID(uint32_t gid, uint32_t& tileID, bool& flipHorizontal, bool& flipVertical, bool& flipDiagonal);
	static void DecompressZlib(const std::string& compressedData, std::vector<uint8_t>& decompressedData);
	static std::string Base64_decode(const std::string& encoded_string);

private:
	Decoder();
	~Decoder();
};

