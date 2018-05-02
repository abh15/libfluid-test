#include "OFClient.hh"
uint64_t generate_dp_id() {
	srand (time(NULL));
	return (((uint64_t) rand() <<  0) & 0x000000000000FFFFull) ^ 
		  (((uint64_t) rand() << 16) & 0x00000000FFFF0000ull) ^ 
		  (((uint64_t) rand() << 32) & 0x0000FFFF00000000ull) ^
		  (((uint64_t) rand() << 48) & 0xFFFF000000000000ull);
}

int main() {
    uint64_t dp_id = generate_dp_id();

    OFClient client(0, "127.0.0.1", 6653,dp_id, OFServerSettings().supported_version(0x01));
    client.start(true);
}
