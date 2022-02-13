
/// @file streambuf_test.cc
/// @brief streambuf_test の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include <gtest/gtest.h>
#include "ym/basic_codec_streambuf.h"
#include "codec_test.h"


BEGIN_NAMESPACE_YM

// テストフィクスチャ
class streambuf_test :
public codec_test
{
  // 実は codec_test の別名
};

TEST_F(streambuf_test, compress)
{
  {
    ofstream ofs{mFileName};
    ASSERT_TRUE( ofs.is_open() );

    // 初期化パラメータ
    ZEngineGen::Param param;
    param.level = 0;

    // エンジン生成器
    ZEngineGen gen{param};

    // 圧縮ストリーム
    codec_ostream cos{ofs, gen};

    cos.write(mTestData, mTestSize);
  }
  {
    ifstream ifs{mFileName};
    ASSERT_TRUE( ifs.is_open() );

    // 初期化パラメータ
    ZEngineGen::Param param;

    // エンジン生成器
    ZEngineGen gen{param};

    // 伸張ストリーム
    codec_istream cis{ifs, gen};

    cis.read(mBuff, mTestSize);
    auto size = cis.gcount();
    EXPECT_EQ( mTestSize, size );
  }
  EXPECT_EQ( 0, memcmp(mTestData, mBuff, mTestSize) );
}


#if defined(ZLIB_FOUND)
TEST_F(streambuf_test, gzip)
{
  {
    ofstream ofs{mFileName};
    ASSERT_TRUE( ofs.is_open() );

    // 初期化パラメータ
    GzEngineGen::Param param;
    param.level = Z_BEST_COMPRESSION;
    param.alloc_func = nullptr;
    param.free_func = nullptr;
    param.opaque = nullptr;

    // エンジン生成器
    GzEngineGen gen{param};

    // 圧縮ストリーム
    codec_ostream cos{ofs, gen};

    cos.write(mTestData, mTestSize);
  }
  {
    ifstream ifs{mFileName};
    ASSERT_TRUE( ifs.is_open() );

    // 初期化パラメータ
    GzEngineGen::Param param;
    param.alloc_func = nullptr;
    param.free_func = nullptr;
    param.opaque = nullptr;

    // エンジン生成器
    GzEngineGen gen{param};

    // 伸張ストリーム
    codec_istream cis{ifs, gen};

    cis.read(mBuff, mTestSize);
    auto size = cis.gcount();
    EXPECT_EQ( mTestSize, size );
  }
  EXPECT_EQ( 0, memcmp(mTestData, mBuff, mTestSize) );
}
#endif // defined(ZLIB_FOUND)


#if defined(BZIP2_FOUND)
TEST_F(streambuf_test, bzip2)
{
  {
    ofstream ofs{mFileName};
    ASSERT_TRUE( ofs.is_open() );

    // 初期化パラメータ
    BzEngineGen::Param param;
    param.verbosity = 0;
    param.work_factor = 0;
    param.alloc_func = nullptr;
    param.free_func = nullptr;
    param.opaque = nullptr;

    // エンジン生成器
    BzEngineGen gen{param};

    // 圧縮ストリーム
    codec_ostream cos{ofs, gen};

    cos.write(mTestData, mTestSize);
  }
  {
    ifstream ifs{mFileName};
    ASSERT_TRUE( ifs.is_open() );

    // 初期化パラメータ
    BzEngineGen::Param param;
    param.verbosity = 0;
    param.small = 0;
    param.block_size_100k = 9;
    param.alloc_func = nullptr;
    param.free_func = nullptr;
    param.opaque = nullptr;

    // エンジン生成器
    BzEngineGen gen{param};

    // 伸張ストリーム
    codec_istream cis{ifs, gen};

    cis.read(mBuff, mTestSize);
    auto size = cis.gcount();
    EXPECT_EQ( mTestSize, size );
  }
  EXPECT_EQ( 0, memcmp(mTestData, mBuff, mTestSize) );
}
#endif // defined(BZIP2_FOUND)


#if defined(LIBLZMA_FOUND)
TEST_F(streambuf_test, xz)
{
  {
    ofstream ofs{mFileName};
    ASSERT_TRUE( ofs.is_open() );

    // 初期化パラメータ
    XzEngineGen::Param param;
    param.preset = 6;
    param.check = LZMA_CHECK_CRC64;
    param.allocator = nullptr;

    // エンジン生成器
    XzEngineGen gen{param};

    // 圧縮ストリーム
    codec_ostream cos{ofs, gen};

    cos.write(mTestData, mTestSize);
  }
  {
    ifstream ifs{mFileName};
    ASSERT_TRUE( ifs.is_open() );

    // 初期化パラメータ
    XzEngineGen::Param param;
    param.memlimit = 128 * 1024 * 1024;
    param.flags = 0;
    param.allocator = nullptr;

    // エンジン生成器
    XzEngineGen gen{param};

    // 伸張ストリーム
    codec_istream cis{ifs, gen};

    cis.read(mBuff, mTestSize);
    auto size = cis.gcount();
    EXPECT_EQ( mTestSize, size );
  }
  EXPECT_EQ( 0, memcmp(mTestData, mBuff, mTestSize) );
}
#endif // defined(LIBLZMA_FOUND)

END_NAMESPACE_YM
