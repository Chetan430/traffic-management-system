# System Validation Report

| Item | Details |
|---|---|
| Project | Traffic Management System (Simulation) |
| Team | Team 8 |
| Instructor | Dr. Pradeep Kumar |
| Report date | 11-Nov-2026 |
| Item under test | Web dashboard (`ui/index.html`) served by the C backend (`ui/tms_ui.c`, which includes `src/traffic.c`) |
| Build | `gcc ui/tms_ui.c -o tms_ui.exe -lws2_32` on Windows (compiled with no errors; the same file also compiles with gcc on Linux) |
| Run | `.\tms_ui.exe`, then open `http://127.0.0.1:8080` in a browser |
| Method | The dashboard was operated in a browser (Chromium) following the steps below. Messages in the table are the exact responses returned by the C backend. |

## 1. Validation Results

| TC ID | SRS ID | Requirement | Steps on the dashboard | Expected | Actual | Result |
|---|---|---|---|---|---|---|
| TC-TMS-001 | TMS-F-001 | Add vehicle | Select L1, ID 101, click **Add vehicle to lane** | Vehicle added to Lane 1 | "Vehicle 101 added to Lane 1." Lane 1 shows 1 waiting | Pass |
| TC-TMS-002 | TMS-F-002 | Process vehicle | Make Lane 3 GREEN, select L3, click **Process vehicle from selected lane** | Front vehicle removed and reported | "Vehicle 999 (Emergency) processed from Lane 3." | Pass |
| TC-TMS-003 | TMS-F-003 | Display queue | Add vehicles to Lane 1 and Lane 3 | Waiting vehicles and their order shown | Vehicles drawn on each road with their IDs; backend queue text: "Lane 1: 101 -> 102", "Lane 3: 999(E) -> 201 -> 202" | Pass |
| TC-TMS-004 | TMS-F-004 | Separate queue per lane | Add 2 vehicles to Lane 1 and 3 to Lane 3 | Each vehicle stays in its lane | Lane 1 waiting 2, Lane 3 waiting 3, Lanes 2 and 4 waiting 0 | Pass |
| TC-TMS-005 | TMS-F-005 | Lane selection | Use lane buttons L1-L4; send lane 0 and lane 5 to the backend | Valid lanes accepted, invalid rejected | L1-L4 selectable; lanes 0, 5, 8, 9 rejected with "Invalid lane. Choose 1-4." | Pass |
| TC-TMS-006 | TMS-F-006 | Empty / full queue | (a) Process an empty lane; (b) add a 51st vehicle to Lane 1 | (a) message, no crash; (b) rejected | (a) "Lane 2 is empty."; (b) "Lane 1 is full." (Lane 1 stays at 50) | Pass |
| TC-TMS-007 | TMS-F-007 | Traffic signal | Select L2, click **Set Lane GREEN**, then **Set Lane RED** | Signal status shown; only one lane GREEN | "Lane 2 signal: GREEN. Other lanes are RED"; then "Lane 2 signal: RED"; lights update | Pass |
| TC-TMS-008 | TMS-F-008 | Emergency priority | Add 201 and 202 (normal) to Lane 3, then add 999 with Emergency on | 999 placed ahead; lane gets GREEN | Queue "999(E) -> 201 -> 202"; "EMERGENCY PRIORITY: Lane 3 is GREEN; all other lanes are RED." | Pass |
| TC-TMS-009 | TMS-F-009 | Priority display | Look at the queue after adding the emergency vehicle | Emergency vehicle distinguishable | Marked "(E)" in the queue text; "Emergency waiting: 1" in Statistics | Pass |
| TC-TMS-010 | TMS-F-010 | Traffic density | Add 11 vehicles to Lane 1 | LOW / MEDIUM / HIGH by queue size | Lane 1 (11 vehicles) HIGH; Lane 3 (2-3 vehicles) MEDIUM; empty lanes LOW | Pass |
| TC-TMS-011 | TMS-F-011 | Waiting vehicles per lane | Read the Lane management table | Waiting count per lane matches the queue | WAITING, ADDED, PASSED and PEAK columns match the vehicles added/processed | Pass |
| TC-TMS-012 | TMS-F-012 | Statistics | Add 50 vehicles, process 2 | Added 50, processed 2, waiting 48 | "Total vehicles added : 50 / processed : 2 / waiting : 48" | Pass |
| TC-TMS-013 | TMS-F-013 | Reset | Click **Reset simulation** and confirm | Queues and counters cleared | "Simulation has been reset successfully."; Lane 1 GREEN, others RED; counters 0 | Pass |
| TC-TMS-014 | TMS-F-014 | Input validation | Enter vehicle ID `abc`, `-5`, `0`, and leave it blank | Invalid values rejected, page keeps working | `abc` and blank: "Invalid input. Please enter a valid integer vehicle ID."; `-5` and `0`: "Vehicle ID must be positive." | Pass |
| TC-TMS-015 | TMS-F-015 | Exit | Look for an exit control | Simulation can be ended normally | The dashboard has no Exit button. The simulation ends when the server window is closed (Ctrl+C) or the browser tab is closed. | Partial |
| TC-NF-001 | TMS-NF-001 | Response time (< 2 s) | 30 add operations sent to the backend | At least 95% within 2 s | 30 of 30 within 2 s (slowest 0.4 ms at the backend) | Pass |
| TC-NF-002 | TMS-NF-002 | Queue ordering and counters | Add 50, process 2 | No corruption | Added 50 - processed 2 = waiting 48; order 501, 502 processed first | Pass |
| TC-NF-003 | TMS-NF-003 | Robust to invalid input | Bad lane (0, 5, 8, 9), signal 7, 20-digit ID, 5000-character ID | Rejected safely, no crash | All rejected with clear messages; server kept running | Pass |
| TC-NF-004 | TMS-NF-004 | Usability | Review of dashboard | Clear messages | Every action shows a message and an Activity entry; traffic lights, density bars and colours explain the state | Pass (by review) |
| TC-NF-005 | TMS-NF-005 | Maintainability | Code review | Modular functions | Queue, display, signal and reset logic are separate functions in `src/traffic.c`; the UI only calls them | Pass (by review) |
| TC-SEC-001 | TMS-SR-001 | Lane validation | Lane 0, 5, 8, 9 | Rejected | "Invalid lane. Choose 1-4." | Pass |
| TC-SEC-002 | TMS-SR-002 | Queue capacity | 51st vehicle in Lane 1 | Refused, data unchanged | "Lane 1 is full."; Lane 1 stays at 50 vehicles | Pass |
| TC-SEC-003 | TMS-SR-003 | Vehicle ID validation | ID `abc`, `-5`, `0`, 20 digits, `1; rm -rf /` | Not added | Rejected; nothing added | Pass |
| TC-SEC-004 | TMS-SR-004 | No command execution | Source search and input test | No system calls | No `system()`, `popen()` or `exec` calls in `src/traffic.c` or `ui/tms_ui.c`; text such as `1; rm -rf /` is treated only as an invalid number | Pass |
| TC-SEC-005 | TMS-SR-005 | No personal data | Review of dashboard | Only simulation fields | Only vehicle ID, lane and emergency flag are stored and shown; the server listens only on 127.0.0.1 | Pass |

## 2. Summary

| Metric | Value |
|---|---|
| Test cases | 25 |
| Passed | 24 |
| Partial | 1 (TC-TMS-015: no Exit button) |
| Failed | 0 |

## 3. Additional behaviour checked (from the project README)

| Rule | Steps | Actual | Result |
|---|---|---|---|
| Processing is allowed only from a GREEN lane | Select Lane 1 while Lane 3 is GREEN and click Process | "Lane 1 signal is not GREEN. Vehicle cannot be processed." | Pass |
| Only one lane GREEN at a time | Set Lane 2 GREEN | Lane 2 GREEN, all other lanes RED | Pass |
| Reset returns Lane 1 GREEN, others RED | Click Reset | Lane 1 GREEN, Lanes 2-4 RED | Pass |

## 4. Screenshots

**Initial state after reset** (Lane 1 GREEN, all counters 0)

![Initial dashboard](screenshots/10_ui_initial.png)

**Add vehicle** (TC-TMS-001, 004)

![Add vehicle](screenshots/11_ui_add_vehicle.png)

**Emergency priority** (TC-TMS-003, 008, 009): vehicle 999 is first in Lane 3 and Lane 3 turns GREEN.

![Emergency priority](screenshots/12_ui_emergency_priority.png)

**Process from a RED lane is refused**

![Process RED lane](screenshots/13_ui_process_red_lane.png)

**Process from the GREEN lane** (TC-TMS-002)

![Process GREEN lane](screenshots/14_ui_process_green_lane.png)

**Set Lane GREEN** (TC-TMS-007)

![Signal GREEN](screenshots/15_ui_signal_green.png)

**Set Lane RED** (TC-TMS-007)

![Signal RED](screenshots/16_ui_signal_red.png)

**Empty lane** (TC-TMS-006)

![Empty lane](screenshots/17_ui_empty_lane.png)

**Invalid vehicle ID** (TC-TMS-014, TC-SEC-003)

![Invalid ID](screenshots/18_ui_invalid_id.png)

**Traffic density HIGH** (TC-TMS-010, 011)

![Density](screenshots/19_ui_density_high.png)

**Lane full** (TC-TMS-006, TC-SEC-002)

![Lane full](screenshots/20_ui_lane_full.png)

**Statistics** (TC-TMS-012)

![Statistics](screenshots/21_ui_statistics.png)

**Reset** (TC-TMS-013)

![Reset](screenshots/22_ui_reset.png)

## 5. Notes

- Test IDs follow the traceability table in `SAD_AND_TEST_PLAN_TEAM8.md` (section 13).
- The command-line engine alone (`src/traffic.c`) was also run, and its results are in `screenshots/cli_engine/`.
