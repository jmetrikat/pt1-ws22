#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

# Just execute this script in the directory where your solution resides.
# (Version: pt1ws22/exercise4/validator/v1)

import operator
import os
import subprocess
import sys

# -------------------------------------------------------------------------------

Test_cwd = None
output_lines = []


def log(msg="", newLine=True, okay=False):
    output_lines.append((okay, "%s\n" % msg if newLine else msg))


def silent_atoi(s):
    try:
        return int(s)
    except ValueError:
        return None

# -------------------------------------------------------------------------------


class Test(object):

    def exec_(self, input_text, *cmd_and_args, env=None):
        if type(input_text) == str:
            input_text = input_text.encode('utf8')
        p = subprocess.Popen(cmd_and_args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=Test_cwd, env=env)
        return tuple(map(lambda s: s.strip(), p.communicate(input=input_text)[:2])) + (p.returncode, )

    def run_prog(self, *cmd_and_args):
        return self.exec_("", *cmd_and_args)[0].decode('utf8')

    def test(self):
        self.run()
        okay = self.okay()
        log(self.what(), okay=okay)
        return okay

    def run(self):
        raise NotImplementedError

    def what(self):
        raise NotImplementedError

    def okay(self):
        raise NotImplementedError


class TestGroup(Test):
    """A group of tests, where all tests are executed"""

    def __init__(self, *tests):
        self.tests = tests
        self.all_okay = False

    def test(self):
        self.all_okay = all([t.test() for t in self.tests])
        return self.all_okay

    def okay(self):
        return self.all_okay


class AbortingTestGroup(TestGroup):
    """A group of tests, where the first failed test stops the entire group"""

    def test(self):
        self.all_okay = all(t.test() for t in self.tests)
        return self.all_okay


class FileMimeTest(Test):
    """Is the specified file existant of a given mimetype?"""

    def __init__(self, fname, expected_mime_toplevel):
        self.fname = fname
        self.expected_mime_toplevel = expected_mime_toplevel

    def run(self):
        self.exists = os.path.exists(os.path.join(Test_cwd or '', self.fname))
        self.mimetype = self.run_prog("file", "--mime-type", "-b", self.fname)
        self.ttype = self.mimetype.split('/', 1)[0]

    def what(self):
        if not self.exists:
            return 'file "%s" does not exist' % self.fname
        return 'file "%s" exists and is "%s" (expected "%s/plain")' % (self.fname, self.mimetype, self.expected_mime_toplevel)

    def okay(self):
        return self.exists and self.ttype == self.expected_mime_toplevel


class ReturnCodeTest(Test):

    def __init__(self, progname, args=None, retcode=0, showstdout=False, showstderr=False, inputText="", truncateLines=None, env=None):
        self.progname = progname
        self.inputText = inputText
        self.cmdline = [progname] + list(map(str, args or []))
        self.expected = retcode
        self.exception = None
        self.env = env
        self.showstdout = showstdout
        self.showstderr = showstderr
        self.output = None
        self.truncateLines = truncateLines
        self.stdout = ""
        self.stderr = ""

    def _truncate(self, text):
        # Hoping for PEP 572 to fix this mess
        #    https://www.python.org/dev/peps/pep-0572/
        # Okay, hoping for submit-exec to support Python 3.8

        lines = text.split("\n")
        if self.truncateLines is None or len(lines) <= self.truncateLines:
            return text

        return "\n".join(lines[:self.truncateLines] + ["", "[OUTPUT TRUNCATED]"])

    def _get_output(self, tpl):
        self.stdout = tpl[0].decode()
        self.stderr = tpl[1].decode()
        return tpl[2]

    def run(self):
        try:
            self.output = self._get_output(self.exec_(self.inputText, *self.cmdline, env=self.env))
        except Exception as e:
            self.exception = e
            self.exc_info = sys.exc_info()

    def _s(self, a):
        return " ".join(map(str, a))

    def _formatCall(self):
        if self.inputText:
            return "echo -ne %r | %s" % (self.inputText, self._s(self.cmdline))
        return self._s(self.cmdline)

    def what(self):
        return "$ %s #- exited with %s (expected %d)%s%s" % (
                    self._formatCall(),
                    str(self.output) if self.exception is None else repr(str(self.exception)),
                    self.expected,
                    "" if not (self.showstdout and self.stdout) else ("\n%s" % self._truncate(self.stdout)),
                    "" if not (self.showstderr and self.stderr) else ("\n%s" % self._truncate(self.stderr)),
                )

    def okay(self):
        return self.output == self.expected


class ExecutionTest(ReturnCodeTest):
    """Run a programm and compare the lines of stdout to a list of expected output."""

    def __init__(self, progname, args, expected, compare=operator.eq, key=lambda x: x, inputText="", showstderr=False):
        super(ExecutionTest, self).__init__(progname, args, expected, inputText=inputText, showstderr=showstderr)
        self.compare = compare
        self.key = key

    def _get_output(self, tpl):
        super(ExecutionTest, self)._get_output(tpl)
        return self.stdout.split("\n")

    def what(self):
        _r = repr
        return "$ " + self._formatCall() + "\n" + \
                ("" if not (self.showstderr and self.stderr) else ("%s\n" % self.stderr)) + \
                (("received: " + _r(self.output))
                        if self.exception is None
                        else str(self.exception)) + "\n" + \
               "expected: " + _r(self.expected)

    def okay(self):
        return self.exception is None and self.compare(self.key(self.output), self.key(self.expected))


class WcTestWithInput(Test):

    def __init__(self, input_text, expected):
        self.input_text = input_text
        self.expected = expected
        self.exception = None
        self.output = None

    def run(self):
        try:
            output = self.exec_(self.input_text, "./wc")[0]
            self.output = list(map(silent_atoi, output.split()))
        except Exception as e:
            self.exception = e

    def okay(self):
        return self.expected == self.output

    def what(self):
        return "$ echo -ne %r | ./wc\n%s\nexpected: %s" % (self.input_text,
                "received: " + str(self.output) if self.exception is None else str(self.exception),
                str(self.expected))


# -------------------------------------------------------------------------------


def main(cd=None):
    tests = TestGroup(
        AbortingTestGroup(
            ExecutionTest("./cap_rev", ["Guten", "Tag"],       ["GAT",   "NETUG"]),
            ExecutionTest("./cap_rev", ["Wie", "geht", "es?"], ["?SE", "THEG", "EIW"]),
        ),
        AbortingTestGroup(
            ExecutionTest("./is_palindrome",  ["rentner", "regallager"], ["YES", "YES"]),
            ExecutionTest("./is_palindrome",  ["kanu",         "kajak"], ["NO",  "YES"]),
        ),
        AbortingTestGroup(
            ExecutionTest("./eratosthenes_sieve",  [15], list(map(str, [2, 3, 5, 7, 11, 13]))),
            ExecutionTest("./eratosthenes_sieve",  [30], list(map(str, [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]))),
        ),
        AbortingTestGroup(
            WcTestWithInput("Hallo Welt",                    [0, 2, 10]),
            WcTestWithInput("Hallo       Welt",              [0, 2, 16]),
            WcTestWithInput("Lag er im Kajak?\nMir egal.\n", [2, 6, 27]),
        ),
        AbortingTestGroup(
            ExecutionTest("./fib",  [0],                   ['0']),
            ExecutionTest("./fib",  [1],                   ['1']),
            ExecutionTest("./fib", [10],                  ['55']),
            ExecutionTest("./fib", [90], ['2880067194370816120']),
        ),
    )

    return tests.test()

# -------------------------------------------------------------------------------


def fetch_git_repo(job, repo_file="repo.txt", branch="main"):
    log("Checking {} for git repository ...".format(repo_file))

    try:
        repo = open(os.path.join(job.working_dir, repo_file)).read().strip()
    except FileNotFoundError:
        log("[ERROR] {} not found.".format(repo_file))
        return False

    return TestGroup(
        ReturnCodeTest("git", ["clone", "--bare", repo, ".git"], showstderr=True),
        ReturnCodeTest("git", ["checkout", "-f", branch], env={"GIT_WORK_TREE": job.working_dir}, showstderr=True),
    ).test()


def validate(job):
    global Test_cwd
    Test_cwd = job.working_dir
    valid = False

    if fetch_git_repo(job):
        job.run_make(mandatory=True)
        valid = main()
    output = "\n".join(msg for _, msg in output_lines)
    if valid:
        job.send_pass_result(output)
    else:
        job.send_fail_result(output)


if __name__ == "__main__":
    valid = main()
    for okay, msg in output_lines:
        f = sys.stdout if okay else sys.stderr
        f.write("%s\n" % msg)
        f.flush()

    sys.exit(0 if valid else 1)

