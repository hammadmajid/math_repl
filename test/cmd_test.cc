/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "cmd.h"
#include <gtest/gtest.h>

TEST(CmdTest, TestErrorCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with argc = 0
  const char *argv0[] = {"neon"};
  std::variant<std::string, CmdFlag> result0 =
          cmdLine.ParseArgs(1, argv0);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(result0));

  // Test with argc > 1
  const char *argv2[] = {"neon", "arg1"};
  std::variant<std::string, CmdFlag> result2 =
          cmdLine.ParseArgs(7, argv2);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(result2));
}

TEST(CmdTest, TestFlagCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with --version flag
  const char *argvVersion[] = {"program", "--version"};
  std::variant<std::string, CmdFlag> resultVersion =
          cmdLine.ParseArgs(2, argvVersion);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(resultVersion));
  ASSERT_EQ(std::get<CmdFlag>(resultVersion), CmdFlag::Version);

  // Test with --help flag
  const char *argvHelp[] = {"program", "--help"};
  std::variant<std::string, CmdFlag> resultHelp =
          cmdLine.ParseArgs(2, argvHelp);
  ASSERT_TRUE(std::holds_alternative<CmdFlag>(resultHelp));
  ASSERT_EQ(std::get<CmdFlag>(resultHelp), CmdFlag::Help);
}

TEST(CmdTest, TestValidExprCase) {
  // Create a CmdLine instance
  CmdLine cmdLine;

  // Test with a valid expression
  const char *argvExpr[] = {"program", "2+2"};
  std::variant<std::string, CmdFlag> resultExpr =
          cmdLine.ParseArgs(2, argvExpr);
  ASSERT_TRUE(std::holds_alternative<std::string>(resultExpr));
  ASSERT_EQ(std::get<std::string>(resultExpr), "2+2");
}

/**
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
