#include <arpa/inet.h>

#include "ngtcp2_conn_test.h"
#include "ngtcp2_test_helper.h"

const size_t nbRounds = 32;

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
	ngtcp2_conn *conn;
	ngtcp2_path_storage path;
	ngtcp2_cid scid;
	ngtcp2_cid dcid;
	struct in_addr local_addr;
	struct in_addr remote_addr;
	ngtcp2_pkt_info packet_info = {0};
	ngtcp2_tstamp ts;
	uint8_t buffer[2048];
	ngtcp2_crypto_aead_ctx   aead_ctx = {0};
    ngtcp2_crypto_cipher_ctx hp_ctx = {0};
    static uint8_t           null_iv[16] = {0};
	const uint8_t src_id[]  = "\xDD\x5A\xBA\x8B\x71\xA2\x46\x7F\xA6\x45\x15\x8E\x4C\x73\x63\xC7";
	const uint8_t dest_id[] = "\xD0\xF6\x0C\xAD\x47\x16\x41\x40\xAF\x0A\x60\x2E\xDE\x47\x79\x79";

	if (Size == 0) return 0;
	ngtcp2_cid_init(&scid, src_id, sizeof(src_id) - 1);
	ngtcp2_cid_init(&dcid, dest_id, sizeof(dest_id) - 1);

	// ngtcp2_conn_install_initial_key(conn, &aead_ctx, null_iv, &hp_ctx, &aead_ctx, null_iv, &hp_ctx, sizeof(null_iv));
    // ngtcp2_conn_install_rx_handshake_key(conn, &aead_ctx, null_iv, sizeof(null_iv), &hp_ctx);
    // ngtcp2_conn_install_tx_handshake_key(conn, &aead_ctx, null_iv, sizeof(null_iv), &hp_ctx);
    // ngtcp2_conn_set_aead_overhead(conn, NGTCP2_INITIAL_AEAD_OVERHEAD);


	inet_pton(AF_INET, "192.0.2.1", &local_addr);
	inet_pton(AF_INET, "127.0.0.1", &remote_addr);
	path_init(&path, local_addr.s_addr, 6666, remote_addr.s_addr, 5555);
	path_init(&path, local_addr.s_addr, 6666, remote_addr.s_addr, 5555);
	setup_handshake_server_with_ids(&conn, &dcid, &scid, &path);

	ts = 1;
	for (size_t round = 0; round < nbRounds; ++round)
	{
		ngtcp2_conn_read_pkt(conn, &path.path, &packet_info, Data, Size, ++ts);
		ngtcp2_conn_write_pkt(conn, 0, &packet_info, buffer, sizeof(buffer), ++ts);
	}

	ngtcp2_conn_del(conn);
	return 0;  // Non-zero return values are reserved for future use.
}

