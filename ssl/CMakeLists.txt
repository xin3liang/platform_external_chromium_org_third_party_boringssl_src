include_directories(. .. ../include)

add_subdirectory(pqueue)

add_library(
	ssl
	STATIC

	d1_both.c
	d1_clnt.c
	d1_enc.c
	d1_lib.c
	d1_meth.c
	d1_pkt.c
	d1_srtp.c
	d1_srvr.c
	s23_clnt.c
	s23_lib.c
	s23_meth.c
	s23_pkt.c
	s23_srvr.c
	s3_both.c
	s3_cbc.c
	s3_clnt.c
	s3_enc.c
	s3_lib.c
	s3_meth.c
	s3_pkt.c
	s3_srvr.c
	ssl_algs.c
	ssl_asn1.c
	ssl_cert.c
	ssl_ciph.c
	ssl_error.c
	ssl_lib.c
	ssl_rsa.c
	ssl_sess.c
	ssl_stat.c
	ssl_txt.c
	t1_clnt.c
	t1_enc.c
	t1_lib.c
	t1_meth.c
	t1_reneg.c
	t1_srvr.c

	$<TARGET_OBJECTS:pqueue>
)

add_executable(
	ssl_test

	ssl_test.c
)

target_link_libraries(ssl_test crypto)
