include_directories(. .. ../../include)

add_library(
	cipher

	OBJECT

	cipher.c
	cipher_error.c
	derive_key.c
	aead.c

	e_null.c
	e_rc4.c
	e_des.c
	e_aes.c
	e_chacha20poly1305.c
)

add_executable(
	cipher_test

	cipher_test.c
)

add_executable(
	aead_test

	aead_test.c
)

target_link_libraries(cipher_test crypto)
target_link_libraries(aead_test crypto)
