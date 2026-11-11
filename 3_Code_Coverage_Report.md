# Code Coverage Report

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

Raw output: `raw/coverage_summary.txt`, line-by-line: `raw/test_traffic.c.gcov`.

## 2. Results

```
File 'tests/test_traffic.c'
Lines executed:99.60% of 249
Branches executed:100.00% of 212
Taken at least once:63.68% of 212
Calls executed:65.60% of 218
```

| Metric | Result |
|---|---|
| File measured | tests/test_traffic.c |
| Executable lines | 249 |
| Lines executed | 248 (99.60%) |
| Lines not executed | 1 (line 53) |

Screenshot of the coverage run:

![gcov line coverage](coverage.png)

## 3. Uncovered Code

| Line | Code | Reason |
|---|---|---|
| 53 | `return;` in `compactQueue()` | The invalid-lane guard of `compactQueue()` is never reached, because `addVehicle()` validates the lane before calling it. |

## 4. Observations

- The measured file is the test file, which contains a copy of the queue code. Coverage of `src/traffic.c` (483 lines, includes menu and input handling) is not measured by the automated tests.
- The menu, display and input-reading functions of `src/traffic.c` are verified manually in the System Validation Report.

## 5. Conclusion

Line coverage is **99.60%** for the measured test file; only one defensive line is unexecuted.
