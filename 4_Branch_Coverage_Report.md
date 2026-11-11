# Branch Coverage Report

| Item | Details |
|---|---|
| Project | Traffic Management System (Simulation) |
| Team | Team 8 |
| Instructor | Dr. Pradeep Kumar |
| Report date | 11-Nov-2026 |
| Environment | gcc, gcov; automated tests in `tests/test_traffic.c` |

## 1. Method

```
gcc --coverage -O0 -g -o build/run_tests tests/test_traffic.c
./build/run_tests
gcov -b -c build/run_tests-test_traffic.gcda
```

## 2. Results

```
File 'tests/test_traffic.c'
Branches executed:100.00% of 212
Taken at least once:63.68% of 212
```

| Metric | Result |
|---|---|
| Total branches | 212 |
| Branches executed | 212 (100.00%) |
| Branches taken at least once | about 135 (63.68%) |
| Branches never taken | 77 |

Screenshot of the branch coverage run (`taken 0` count = branches never taken):

![gcov branch coverage](screenshots/03_branch_coverage.png)

## 3. Analysis

- **Branches executed 100%:** every decision point in the file was reached by the tests.
- **Taken at least once 63.68%:** the 77 branches never taken are the "other direction" of decisions. A large part of these are the failure paths of the `assert()` calls (an assertion only takes that path when a test fails), and the other part are the opposite outcomes of defensive checks such as the invalid-lane guard in `compactQueue()` (line 53).
- Because the suite passes with 0 failures, the assert failure paths are not expected to be taken.

## 4. Recommendations

1. Add a direct test calling `compactQueue(-1)` and `compactQueue(MAX_LANES)` to cover the invalid-lane branch.
2. Move the tests to include `src/traffic.c` so that branch coverage reflects the real program.

## 5. Conclusion

All branches were executed, and **63.68%** were taken in both directions; the remainder are mostly assertion failure paths.
