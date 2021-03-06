#include "WebRTCPeerNative.hpp"

const godot_gdnative_ext_net_3_2_api_struct *WebRTCPeerNative::_net_api = NULL;

void WebRTCPeerNative::register_interface(const godot_net_webrtc_peer *p_interface) {
	ERR_FAIL_COND(!_net_api);
	_net_api->godot_net_bind_webrtc_peer(_owner, p_interface);
}

void WebRTCPeerNative::_register_methods() {}

void WebRTCPeerNative::_init() {
	register_interface(&interface);
}

WebRTCPeerNative::~WebRTCPeerNative() {
	if (_owner) {
		register_interface(NULL);
	}
}

/*
 * The C interface that implements WebRTCPeer.
 * In this case it forwards calls to our C++ class, but could be plain C,
 * and you could use void *user for any kind of state struct pointer you have.
 */
godot_error get_packet_wp(void *user, const uint8_t **r_buffer, int *r_len) {
	return ((WebRTCPeerNative *)user)->get_packet(r_buffer, r_len);
}

godot_error put_packet_wp(void *user, const uint8_t *p_buffer, int p_len) {
	return ((WebRTCPeerNative *)user)->put_packet(p_buffer, p_len);
}

godot_int get_available_packet_count_wp(const void *user) {
	return ((WebRTCPeerNative *)user)->get_available_packet_count();
}

godot_int get_max_packet_size_wp(const void *user) {
	return ((WebRTCPeerNative *)user)->get_max_packet_size();
}

void set_write_mode_wp(void *user, godot_int write_mode) {
	((WebRTCPeerNative *)user)->set_write_mode(write_mode);
}

godot_int get_write_mode_wp(const void *user) {
	return ((WebRTCPeerNative *)user)->get_write_mode();
}

bool was_string_packet_wp(const void *user) {
	return ((WebRTCPeerNative *)user)->was_string_packet();
}

godot_int get_connection_state_wp(const void *user) {
	return ((WebRTCPeerNative *)user)->get_connection_state();
}

godot_error create_offer_wp(void *user) {
	return ((WebRTCPeerNative *)user)->create_offer();
}

godot_error set_remote_description_wp(void *user, const char *type, const char *sdp) {
	return ((WebRTCPeerNative *)user)->set_remote_description(type, sdp);
}

godot_error set_local_description_wp(void *user, const char *type, const char *sdp) {
	return ((WebRTCPeerNative *)user)->set_local_description(type, sdp);
}

godot_error add_ice_candidate_wp(void *user, const char *sdpMidName, int sdpMlineIndexName, const char *sdpName) {
	return ((WebRTCPeerNative *)user)->add_ice_candidate(sdpMidName, sdpMlineIndexName, sdpName);
}

godot_error poll_wp(void *user) {
	return ((WebRTCPeerNative *)user)->poll();
}
