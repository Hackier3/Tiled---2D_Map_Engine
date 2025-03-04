#include "../hdr/Decoder.h"
#include <zlib.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <stdexcept>

void Decoder::DecodeGID(uint32_t gid, uint32_t& tileID, bool& flipHorizontal, bool& flipVertical, bool& flipDiagonal) {
    // Maska do wyodrębnienia 3 najważniejszych bitów
    const uint32_t FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
    const uint32_t FLIPPED_VERTICALLY_FLAG = 0x40000000;
    const uint32_t FLIPPED_DIAGONALLY_FLAG = 0x20000000;

    // Sprawdź, czy bity są ustawione
    flipHorizontal = (gid & FLIPPED_HORIZONTALLY_FLAG) != 0;
    flipVertical = (gid & FLIPPED_VERTICALLY_FLAG) != 0;
    flipDiagonal = (gid & FLIPPED_DIAGONALLY_FLAG) != 0;

    // Odcięcie 3 najważniejszych bitów, aby uzyskać prawdziwy identyfikator kafelka
    tileID = gid & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);
}

void Decoder::DecompressZlib(const std::string& compressedData, std::vector<uint8_t>& decompressedData) {
    const size_t BUFFER_SIZE = 1024 * 1024;
    decompressedData.resize(BUFFER_SIZE);

    z_stream zs;
    zs.zalloc = Z_NULL;
    zs.zfree = Z_NULL;
    zs.opaque = Z_NULL;
    zs.avail_in = compressedData.size();
    zs.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(compressedData.data()));

    if (inflateInit(&zs) != Z_OK) {
        throw std::runtime_error("Błąd podczas inicjalizacji zlib");
    }

    int ret;
    size_t totalOut = 0;

    do {
        zs.avail_out = BUFFER_SIZE - totalOut;
        zs.next_out = decompressedData.data() + totalOut;

        ret = inflate(&zs, Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR || ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            inflateEnd(&zs);
            throw std::runtime_error("Błąd podczas dekompresji zlib");
        }

        totalOut += BUFFER_SIZE - zs.avail_out;
    } while (ret != Z_STREAM_END);

    inflateEnd(&zs);
    decompressedData.resize(totalOut);
}

std::string Decoder::Base64_decode(const std::string& encoded_string) {
    BIO* bio = BIO_new_mem_buf(encoded_string.data(), encoded_string.size());
    BIO* b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    // Nie dodawaj znaków nowej linii
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    std::vector<char> decoded(encoded_string.size());
    int decoded_length = BIO_read(bio, decoded.data(), decoded.size());
    if (decoded_length < 0) {
        BIO_free_all(bio);
        throw std::runtime_error("Failed to decode Base64");
    }

    BIO_free_all(bio);
    return std::string(decoded.data(), decoded_length);
}