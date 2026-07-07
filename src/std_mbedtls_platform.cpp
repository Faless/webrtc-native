/**************************************************************************/
/*  std_mbedtls_platform.cpp                                              */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include <mbedtls/build_info.h>
#include <mbedtls/threading.h>
#include <psa/crypto.h>

#include <mutex>

#if !defined(MBEDTLS_THREADING_C)
#error "WebRTC-Native require mbedTLS with threading support"
#endif

extern "C" {
#if defined(MBEDTLS_THREADING_ALT)
void std_mbedtls_mutex_init(mbedtls_platform_mutex_t *p_mutex) {
	if (p_mutex == nullptr) {
		return;
	}
	p_mutex->mutex = new std::mutex();
}

void std_mbedtls_mutex_free(mbedtls_platform_mutex_t *p_mutex) {
	if (p_mutex == nullptr || p_mutex->mutex == nullptr) {
		return;
	}
	delete ((std::mutex *)p_mutex->mutex);
}

int std_mbedtls_mutex_lock(mbedtls_platform_mutex_t *p_mutex) {
	if (p_mutex == nullptr || p_mutex->mutex == nullptr) {
		return MBEDTLS_ERR_THREADING_USAGE_ERROR;
	}
	((std::mutex *)p_mutex->mutex)->lock();
	return 0;
}

int std_mbedtls_mutex_unlock(mbedtls_platform_mutex_t *p_mutex) {
	if (p_mutex == nullptr || p_mutex->mutex == nullptr) {
		return MBEDTLS_ERR_THREADING_USAGE_ERROR;
	}
	((std::mutex *)p_mutex->mutex)->unlock();
	return 0;
}
#endif
int std_mbedtls_platform_init() {
#if defined(MBEDTLS_THREADING_ALT)
	mbedtls_threading_set_alt(
			std_mbedtls_mutex_init,
			std_mbedtls_mutex_free,
			std_mbedtls_mutex_lock,
			std_mbedtls_mutex_unlock);
#endif
	printf("Started!");
	return psa_crypto_init();
}
void std_mbedtls_platform_free() {
#if defined(MBEDTLS_THREADING_ALT)
	mbedtls_threading_free_alt();
#endif
}
};
