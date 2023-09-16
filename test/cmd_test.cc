#include "cmd.h"
#include <gtest/gtest.h>

TEST(CmdTest, TestErrorCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with argc = 0
  const char *argv0[] = {"neon"};
  std::variant<std::string, CmdFlag> result0 =
      cmdLine.ParseArgvForExprAndSetFlags(1, argv0);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(result0));

  // Test with argc > 1
  const char *argv2[] = {"neon", "arg1"};
  std::variant<std::string, CmdFlag> result2 =
      cmdLine.ParseArgvForExprAndSetFlags(7, argv2);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(result2));
}

TEST(CmdTest, TestFlagCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with --version flag
  const char *argvVersion[] = {"program", "--version"};
  std::variant<std::string, CmdFlag> resultVersion =
      cmdLine.ParseArgvForExprAndSetFlags(2, argvVersion);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(resultVersion));
  ASSERT_EQ(std::get<CmdFlag>(resultVersion), CmdFlag::Version);

  // Test with --help flag
  const char *argvHelp[] = {"program", "--help"};
  std::variant<std::string, CmdFlag> resultHelp =
      cmdLine.ParseArgvForExprAndSetFlags(2, argvHelp);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(resultHelp));
  ASSERT_EQ(std::get<CmdFlag>(resultHelp), CmdFlag::Help);
}

TEST(CmdTest, TestValidExprCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with a valid expression
  const char *argvExpr[] = {"program", "2+2"};
  std::variant<std::string, CmdFlag> resultExpr =
      cmdLine.ParseArgvForExprAndSetFlags(2, argvExpr);
  ASSERT_TRUE(std::holds_alternative<std::string>(resultExpr));
  ASSERT_EQ(std::get<std::string>(resultExpr), "2+2");
}
