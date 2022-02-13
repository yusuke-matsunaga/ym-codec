
# ===================================================================
# インクルードパスの設定
# ===================================================================
include_directories(
  ${GTEST_INCLUDE_DIR}
  )


# ===================================================================
# サブディレクトリの設定
# ===================================================================


# ===================================================================
#  ソースファイルの設定
# ===================================================================



# ===================================================================
#  テスト用のターゲットの設定
# ===================================================================


# ===================================================================
# ZFile 関係のテスト
# ===================================================================

set ( TESTDATA_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/testdata
  )

ym_add_gtest ( codec_compress_test
  compress_test.cc
  $<TARGET_OBJECTS:ym_codec_obj_d>
  )

target_include_directories ( codec_compress_test
  PRIVATE
  ../c++-srcs
  )

target_compile_definitions ( codec_compress_test
  PRIVATE
  "-DTESTDATA_DIR=\"${TESTDATA_DIR}\""
  )

target_link_libraries ( codec_compress_test
  )


# ===================================================================
# XzFile 関係のテスト
# ===================================================================
if ( LIBLZMA_FOUND )
  ym_add_gtest ( codec_xz_test
    xz_test.cc
    $<TARGET_OBJECTS:ym_codec_obj_d>
    )

  target_include_directories ( codec_xz_test
    PRIVATE
    ../c++-srcs
    )

  target_compile_definitions ( codec_xz_test
    PRIVATE
    "-DTESTDATA_DIR=\"${TESTDATA_DIR}\""
    )

  target_link_libraries ( codec_xz_test
    ${LIBLZMA_LIBRARIES}
    )

endif ( LIBLZMA_FOUND )


# ===================================================================
# GzFile 関係のテスト
# ===================================================================
if ( ZLIB_FOUND )
  ym_add_gtest ( codec_gzip_test
    gzip_test.cc
    $<TARGET_OBJECTS:ym_codec_obj_d>
    )

  target_include_directories ( codec_gzip_test
    PRIVATE
    ../c++-srcs
    )

  target_compile_definitions ( codec_gzip_test
    PRIVATE
    "-DTESTDATA_DIR=\"${TESTDATA_DIR}\""
    )

  target_link_libraries ( codec_gzip_test
    ${ZLIB_LIBRARIES}
    )

endif ( ZLIB_FOUND )


# ===================================================================
# BzFile 関係のテスト
# ===================================================================
if ( BZIP2_FOUND )
  ym_add_gtest ( codec_bzip2_test
    bzip2_test.cc
    $<TARGET_OBJECTS:ym_codec_obj_d>
    )

  target_include_directories ( codec_bzip2_test
    PRIVATE
    ../c++-srcs
    )

  target_compile_definitions ( codec_bzip2_test
    PRIVATE
    "-DTESTDATA_DIR=\"${TESTDATA_DIR}\""
    )

  target_link_libraries ( codec_bzip2_test
    ${BZIP2_LIBRARIES}
    )

endif ( BZIP2_FOUND )


# ===================================================================
# CodecGen 関係のテスト
# ===================================================================
ym_add_gtest ( codec_codecgen_test
  codecgen_test.cc
  $<TARGET_OBJECTS:ym_codec_obj_d>
  )


# ===================================================================
# basic_codec_streambuf 関係のテスト
# ===================================================================
ym_add_gtest ( codec_streambuf_test
  streambuf_test.cc
  $<TARGET_OBJECTS:ym_codec_obj_d>
  )
