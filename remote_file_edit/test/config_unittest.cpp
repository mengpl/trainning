#include "gtest/gtest.h"
#include "config.h"

using namespace remote_file_edit;

TEST(CReadConfig,read_config)
{
    CReadConfig c("../remote_file_edit.cfg");

    EXPECT_EQ("test.txt",c.read_config("filename"));
}

TEST(CReadConfig,read_config_01)
{
    CReadConfig c("../remote_file_edit.cfg");

    EXPECT_EQ("test.txt",c.read_config("filename"));
}