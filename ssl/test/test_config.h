/* Copyright (c) 2014, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

#ifndef HEADER_TEST_CONFIG
#define HEADER_TEST_CONFIG

#include <string>


struct TestConfig {
  TestConfig();

  bool is_server;
  bool is_dtls;
  bool resume;
  bool fallback_scsv;
  std::string key_file;
  std::string cert_file;
  std::string expected_server_name;
  std::string expected_certificate_types;
  bool require_any_client_certificate;
  std::string advertise_npn;
  std::string expected_next_proto;
  bool false_start;
  std::string select_next_proto;
  bool async;
  bool write_different_record_sizes;
  bool cbc_record_splitting;
  bool partial_write;
  bool no_tls12;
  bool no_tls11;
  bool no_tls1;
  bool no_ssl3;
  bool cookie_exchange;
};

bool ParseConfig(int argc, char **argv, TestConfig *out_config);


#endif  // HEADER_TEST_CONFIG
