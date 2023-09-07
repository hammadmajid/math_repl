#include "cmd/cmd.h"
#include <gtest/gtest.h>

TEST(CmdTest, TestErrorCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with argc = 0
  const char *argv0[] = {"neon"};
  CmdInput result0 = cmdLine.ParseArgvForExprAndSetFlags(1, argv0);
  ASSERT_TRUE(std::holds_alternative<CmdError>(result0.input));

  // Test with argc > 5
  const char *argv6[] = {"neon", "arg1", "arg2", "arg3",
                         "arg4",    "arg5", "arg6"};
  CmdInput result6 = cmdLine.ParseArgvForExprAndSetFlags(7, argv6);
  ASSERT_TRUE(std::holds_alternative<CmdError>(result6.input));
}

TEST(CmdTest, TestFlagCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with --version flag
  const char *argvVersion[] = {"program", "--version"};
  CmdInput resultVersion = cmdLine.ParseArgvForExprAndSetFlags(2, argvVersion);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(resultVersion.input));
  ASSERT_EQ(std::get<CmdFlag>(resultVersion.input), CmdFlag::VersionFlag);

  // Test with --help flag
  const char *argvHelp[] = {"program", "--help"};
  CmdInput resultHelp = cmdLine.ParseArgvForExprAndSetFlags(2, argvHelp);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(resultHelp.input));
  ASSERT_EQ(std::get<CmdFlag>(resultHelp.input), CmdFlag::HelpFlag);
}

TEST(CmdTest, TestValidExprCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with a valid expression
  const char *argvExpr[] = {"program", "2+2"};
  CmdInput resultExpr = cmdLine.ParseArgvForExprAndSetFlags(2, argvExpr);
  ASSERT_TRUE(std::holds_alternative<std::string>(resultExpr.input));
  ASSERT_EQ(std::get<std::string>(resultExpr.input), "2+2");
}
