# Software Requirements Specification (SRS)

## Project: Traffic Management System (Simulation)

**Version:** 1.0

**Authors:** Team Number: Team 8

**Instructor:** Dr. Pradeep Kumar

### Team Members

- PES2UG24CS131 — Chetan
- PES2UG24CS159 — Dimpal N
- PES2UG24CS176 — Halahally Shivaprasad Deeksha Prasad
- PES2UG25CS816 — Nikitha V

**Date:** 5-9-2026

**Status:** Model Answer / Approved

## Revision history

| Version | Date | Author | Change summary | Approval |
|---|---|---|---|---|
| 1.0 | 18-08-2025 | Instructor | SRS with diagrams embedded | |

## Approvals

| Role | Name | Signature / Email | Date |
|---|---|---|---|
| Course Coordinator | | | |

## Table of Contents

1. Introduction
2. Overall description
3. External interfaces
4. System features (detailed)
5. Non-functional requirements (detailed)
6. Quality attributes & Acceptance tests
7. UML Use-Case Diagram
8. Requirements Traceability Matrix (RTM)

# 1. Introduction

## 1.1 Purpose

The purpose of the Traffic Management System (Simulation) is to simulate and manage traffic flow at a road intersection using queue-based data structures. The system allows vehicles to be added to multiple lanes, processed according to their priority, and monitored through traffic density, queue status, traffic signals, and statistical information. The system is developed in C and is intended to demonstrate the application of data structures and software engineering concepts in traffic management.

## 1.2 Scope

The Traffic Management System (Simulation) provides a simple simulation of traffic flow through multiple lanes. The system allows users to add vehicles to lanes, process vehicles from queues, give priority to emergency vehicles, manage traffic signals, monitor queue sizes, calculate traffic density, and view traffic statistics. The system supports up to four traffic lanes and maintains separate queues for each lane. It also provides input validation, handling of empty and full queues, and an option to reset the simulation. The system is implemented in C using queue-based data structures. The project is intended as a simulation and does not directly control real-world traffic signals, vehicles, or road infrastructure.

## 1.3 Audience

The intended audience for this document includes the project team, faculty members, evaluators, and users interested in understanding the Traffic Management System (Simulation). It also serves as a reference for developers and testers involved in implementing, testing, and evaluating the system.

## 1.4 Definitions

| Term | Definition |
|---|---|
| TMS | Traffic Management System |
| FR | Functional Requirement |
| NFR | Non-Functional Requirement |
| UML | Unified Modeling Language |
| RTM | Requirements Traceability Matrix |
| CI/CD | Continuous Integration / Continuous Delivery |
| Queue | A data structure used to maintain vehicles waiting in a lane. |
| Lane | A separate queue representing a traffic lane in the simulation. |
| Traffic Density | A classification of traffic based on the number of vehicles waiting in a lane. |
| Emergency Vehicle | A vehicle given higher processing priority than normal vehicles. |

# 2. Overall description

## 2.1 Product perspective

The Traffic Management System (Simulation) is a standalone console-based application developed in C. The system simulates traffic flow through multiple lanes using queue-based data structures. Each lane maintains its own queue of vehicles, allowing vehicles to be added and processed while maintaining their priority. The system provides features for vehicle management, multiple-lane traffic handling, traffic signal status, emergency vehicle priority, traffic density monitoring, queue monitoring, statistics, simulation reset, and input validation. The system does not depend on external traffic infrastructure or real-world traffic-control systems. It operates as a software simulation and provides output through a command-line interface.

## 2.2 Major product functions (detailed)

The Traffic Management System provides the following major functions:

1. **Vehicle Addition:** Allows the user to add vehicles to selected traffic lanes.
2. **Vehicle Processing:** Processes vehicles from the lane queues according to their priority.
3. **Multiple Lane Management:** Maintains separate queues for multiple traffic lanes.
4. **Traffic Signal Management:** Displays and manages the traffic signal status.
5. **Emergency Vehicle Priority:** Gives priority to emergency vehicles waiting in a lane.
6. **Traffic Density Monitoring:** Determines the traffic density of each lane based on the number of waiting vehicles.
7. **Queue Monitoring:** Displays the current vehicles and queue status of the lanes.
8. **Statistics:** Maintains and displays the total number of vehicles added and processed.
9. **Simulation Reset:** Allows the user to reset the simulation and clear the current traffic data.
10. **Input Validation:** Validates user input and handles invalid selections and queue conditions.

## 2.3 User roles and characteristics (expanded)

The Traffic Management System has a single primary user role:

**System User:** The system user interacts with the console-based application to manage and monitor the traffic simulation. The user can add vehicles to lanes, process vehicles, view lane queues, manage traffic signals, monitor traffic density, view statistics, reset the simulation, and exit the system.

The system does not require separate administrator or operator accounts because it is designed as a standalone simulation.

## 2.4 Operating environment

The Traffic Management System operates as a standalone console-based C application on a standard computer. The system requires a C compiler such as GCC and a command-line environment for execution. It does not require specialized hardware, network connectivity, a database, or external services.

## 2.5 Constraints

The system is implemented using the C programming language and uses queue-based data structures for traffic management. The simulation supports a maximum of four traffic lanes and a limited queue capacity per lane. The system is designed for simulation purposes and does not interface with real-world traffic signals, sensors, vehicles, or road infrastructure. User interaction is limited to the command-line interface.

# 3. External interface requirements

## 3.1 User interfaces

The Traffic Management System uses a command-line interface (CLI). The main menu provides options for adding vehicles, processing vehicles, displaying queues, managing multiple lanes, viewing traffic signal status, monitoring traffic density, viewing statistics, resetting the simulation, and exiting the system.

The system displays clear prompts and messages to guide the user during interaction. Invalid inputs and queue conditions are handled with appropriate messages.

## 3.2 Hardware interfaces

The system does not require any specialized hardware. It runs on a standard computer capable of compiling and executing a C program.

## 3.3 Software interfaces

The system is developed using the C programming language and can be compiled using a standard C compiler such as GCC. The application runs as a standalone console program and does not require a database or external software service.

## 3.4 Communications

The system does not require network communication or external APIs. All interaction takes place locally through the command-line interface.

> Make sure overall there are at least 15 FRs for overall project, 5 NFRs, 2 security objectives and 5 Security requirements

# 4. System features (detailed)

Each requirement below includes acceptance criteria and a reference test case. IDs follow TMS-F-###.

## 4.1 Authentication

**Description:** Add, process, and display vehicles in the traffic lane queues.

| Req ID | Requirement (shall...) | Type | Priority | Source/Stakeholder | Acceptance criteria / Test case ref | Comments / Dependencies |
|---|---|---|---|---|---|---|
| TMS-F-001 | The system shall allow the user to add a vehicle with a vehicle ID to a selected lane queue. | Functional | High | System User | AC-TMS-F-001: Valid vehicle ID and lane selection add the vehicle to the selected queue. Test: TC-TMS-001 | Requires valid lane and available queue capacity. |
| TMS-F-002 | The system shall process and remove the vehicle at the front of the selected lane queue. | Functional | High | System User | AC-TMS-F-002: The front vehicle is removed and reported as processed; an empty queue is handled correctly. Test: TC-TMS-002 | Depends on a non-empty selected queue. |
| TMS-F-003 | The system shall display the vehicles currently waiting in a selected lane, including vehicle IDs and priority status. | Functional | Medium | System User | AC-TMS-F-003: Queue contents and priority status are displayed correctly; an empty queue produces an appropriate message. Test: TC-TMS-003 | Depends on selected lane and current queue contents. |

## 4.2 Multiple Lane Management

**Description:** Maintain independent queues for the supported traffic lanes and validate lane selection.

| Req ID | Requirement (shall...) | Type | Priority | Source/Stakeholder | Acceptance criteria / Test case ref | Comments / Dependencies |
|---|---|---|---|---|---|---|
| TMS-F-004 | The system shall maintain a separate queue for each supported traffic lane. | Functional | High | System User | AC-TMS-F-004: A vehicle added to one lane remains in that lane and does not appear in another lane. Test: TC-TMS-004 | Supports up to four lanes. |
| TMS-F-005 | The system shall allow the user to select a valid lane before performing lane-specific operations. | Functional | High | System User | AC-TMS-F-005: Valid lane selections are accepted and invalid lane selections are rejected with an error message. Test: TC-TMS-005 | Lane number must be within the supported range. |
| TMS-F-006 | The system shall detect and report empty and full lane queues without corrupting queue data. | Functional | High | System User | AC-TMS-F-006: Processing an empty queue and adding to a full queue produce appropriate messages without invalid memory access. Test: TC-TMS-006 | Depends on finite queue capacity. |

## 4.3 Traffic Signal and Priority

**Description:** Provide traffic signal status and priority handling for emergency vehicles.

| Req ID | Requirement (shall...) | Type | Priority | Source/Stakeholder | Acceptance criteria / Test case ref | Comments / Dependencies |
|---|---|---|---|---|---|---|
| TMS-F-007 | The system shall allow the user to view and set the traffic signal status as Red or Green. | Functional | High | System User | AC-TMS-F-007: The selected signal status is displayed correctly as Red or Green. Test: TC-TMS-007 | Signal status is managed within the simulation. |
| TMS-F-008 | The system shall give emergency vehicles priority over normal waiting vehicles in a lane queue. | Functional | High | System User | AC-TMS-F-008: An emergency vehicle added while normal vehicles are waiting is positioned ahead of normal waiting vehicles. Test: TC-TMS-008 | Uses priority insertion in the queue. |
| TMS-F-009 | The system shall display whether a waiting vehicle is an emergency vehicle when queue information is shown. | Functional | Medium | System User | AC-TMS-F-009: Emergency and normal vehicles are distinguishable in displayed queue information. Test: TC-TMS-009 | Depends on vehicle priority flag. |

## 4.4 Traffic Monitoring and Statistics

**Description:** Monitor traffic density, queue sizes, and simulation statistics.

| Req ID | Requirement (shall...) | Type | Priority | Source/Stakeholder | Acceptance criteria / Test case ref | Comments / Dependencies |
|---|---|---|---|---|---|---|
| TMS-F-010 | The system shall calculate and display traffic density for each lane based on the number of waiting vehicles. | Functional | Medium | System User | AC-TMS-F-010: The system reports Low, Medium, or High density according to the queue size. Test: TC-TMS-010 | Density is derived from current queue size. |
| TMS-F-011 | The system shall display the current number of vehicles waiting in each lane. | Functional | Medium | System User | AC-TMS-F-011: Queue size displayed for each lane matches the number of vehicles stored in that lane. Test: TC-TMS-011 | Depends on queue state. |
| TMS-F-012 | The system shall maintain and display the total number of vehicles added and processed during the simulation. | Functional | Medium | System User | AC-TMS-F-012: Statistics increase when vehicles are added or processed and are displayed correctly. Test: TC-TMS-012 | Counters reset when the simulation is reset. |

## 4.5 Simulation Control and Validation

**Description:** Provide simulation reset, safe input handling, and controlled application exit.

| Req ID | Requirement (shall...) | Type | Priority | Source/Stakeholder | Acceptance criteria / Test case ref | Comments / Dependencies |
|---|---|---|---|---|---|---|
| TMS-F-013 | The system shall allow the user to reset the simulation and clear all lane queues and statistics. | Functional | High | System User | AC-TMS-F-013: After reset, all queues are empty and vehicle counters return to their initial state. Test: TC-TMS-013 | Reset affects the current simulation state only. |
| TMS-F-014 | The system shall validate menu, lane, vehicle ID, and queue-related inputs and shall reject invalid values. | Functional | High | System User | AC-TMS-F-014: Invalid input is rejected and the user receives an appropriate error message without terminating the application unexpectedly. Test: TC-TMS-014 | Input validation is required for safe operation. |
| TMS-F-015 | The system shall provide an option for the user to exit the simulation and terminate the application normally. | Functional | Medium | System User | AC-TMS-F-015: Selecting Exit terminates the simulation without errors. Test: TC-TMS-015 | No external resources need to be released. |

# 5. Non-functional requirements (detailed)

NFRs below are measurable and tied to test plans. IDs follow TMS-NF-###.

| Req ID | Requirement | Category | Priority | Acceptance criteria / Measurement |
|---|---|---|---|---|
| TMS-NF-001 | The system shall respond to normal menu operations within 2 seconds on a standard development computer. | Performance | High | At least 95% of 30 measured operations complete within 2 seconds. Test: TC-NF-001 |
| TMS-NF-002 | The system shall maintain correct queue ordering and counters throughout normal simulation use. | Reliability | High | 100 consecutive add/process operations produce no queue corruption or counter mismatch. Test: TC-NF-002 |
| TMS-NF-003 | The system shall handle invalid user input without crashing or accessing data outside defined queue bounds. | Security / Robustness | High | Invalid menu, lane, and boundary inputs are rejected safely. Test: TC-NF-003 |
| TMS-NF-004 | The system shall provide clear and understandable command-line messages for all supported operations and errors. | Usability | Medium | User evaluation confirms all menu options and error states are understandable. Test: TC-NF-004 |
| TMS-NF-005 | The system shall be maintainable through modular functions for queue operations, vehicle processing, monitoring, statistics, and simulation control. | Maintainability | Medium | Static analysis passes and each major function can be tested independently. Test: TC-NF-005 |

## 5.1 Security

### 5.1.1 Security Objectives

**TMS-SO-001:** Preserve the integrity of simulation and queue data by preventing invalid inputs and out-of-bounds queue operations.

**TMS-SO-002:** Ensure predictable and safe application behavior by rejecting malformed or unsupported user input without exposing sensitive system information.

### 5.1.2 Security Requirements

| Req ID | Requirement (shall...) | Type | Priority | Acceptance criteria / Test case ref |
|---|---|---|---|---|
| TMS-SR-001 | The system shall validate lane numbers before accessing a lane queue. | Security | High | AC-TMS-SR-001: Out-of-range lane values are rejected. Test: TC-SEC-001 |
| TMS-SR-002 | The system shall enforce the maximum queue capacity before inserting a vehicle. | Security | High | AC-TMS-SR-002: Insertion is refused when the queue is full and existing data remains unchanged. Test: TC-SEC-002 |
| TMS-SR-003 | The system shall validate vehicle IDs and reject invalid or unsupported values. | Security | Medium | AC-TMS-SR-003: Invalid vehicle IDs do not enter the queue. Test: TC-SEC-003 |
| TMS-SR-004 | The system shall not execute operating-system commands or accept executable input from the user. | Security | High | AC-TMS-SR-004: User input is treated only as simulation data and no system command is executed. Test: TC-SEC-004 |
| TMS-SR-005 | The system shall avoid storing or displaying confidential personal information because the simulation does not require such information. | Security | Medium | AC-TMS-SR-005: Output and stored vehicle data contain only simulation fields such as ID and priority. Test: TC-SEC-005 |

# 6. Quality attributes & Acceptance tests

- **Exit criteria for acceptance:** All high-priority functional requirements are implemented and verified, all five NFRs meet their stated measurements, no critical security requirement fails, and the RTM has corresponding test cases.

- **Acceptance test suites:** Vehicle Management, Multiple Lane Management, Traffic Signal and Priority, Traffic Monitoring and Statistics, Simulation Control, Performance, Robustness, Usability, and Security tests.

- **Quality attributes evaluated:** performance, reliability, security/robustness, usability, and maintainability.

# 7. System models and diagrams

## 7.1 UML Use-Case Diagram 1 – Vehicle and Lane Management

Actors and use cases for vehicle and lane operations are shown below.

**UML Use-Case Diagram 1**

- Actor: System User
- System: Traffic Management System
- Use cases:
  - Add Vehicle
  - Process Vehicle
  - Display Queue
  - Select Lane
  - Reset Simulation

## 7.2 UML Use-Case Diagram 2 – Monitoring and Control

Actors and use cases for monitoring, signal, priority, and statistics are shown below.

**UML Use-Case Diagram 2**

- Actor: System User
- System: Traffic Management System
- Use cases:
  - Manage Signal
  - Prioritize Emergency Vehicle
  - Monitor Density
  - View Statistics
  - Exit Simulation

# 8. Requirements Traceability Matrix (RTM)

| Req ID | Requirement short | Section ref / Design Spec | Module | Test case(s) | Status (N/P/A) | Comments |
|---|---|---|---|---|---|---|
| TMS-F-001 | Add vehicle | 4.1 / DS-TMS-001 | VehicleModule | TC-TMS-001 | N | Planned / to be verified |
| TMS-F-002 | Process vehicle | 4.1 / DS-TMS-002 | VehicleModule | TC-TMS-002 | N | Planned / to be verified |
| TMS-F-003 | Display queue | 4.1 / DS-TMS-003 | DisplayModule | TC-TMS-003 | N | Planned / to be verified |
| TMS-F-004 | Multiple lanes | 4.2 / DS-TMS-004 | LaneModule | TC-TMS-004 | N | Planned / to be verified |
| TMS-F-005 | Lane selection | 4.2 / DS-TMS-005 | ValidationModule | TC-TMS-005 | N | Planned / to be verified |
| TMS-F-006 | Queue boundary handling | 4.2 / DS-TMS-006 | QueueModule | TC-TMS-006 | N | Planned / to be verified |
| TMS-F-007 | Traffic signal | 4.3 / DS-TMS-007 | SignalModule | TC-TMS-007 | N | Planned / to be verified |
| TMS-F-008 | Emergency priority | 4.3 / DS-TMS-008 | PriorityModule | TC-TMS-008 | N | Planned / to be verified |
| TMS-F-009 | Priority display | 4.3 / DS-TMS-009 | DisplayModule | TC-TMS-009 | N | Planned / to be verified |
| TMS-F-010 | Traffic density | 4.4 / DS-TMS-010 | MonitoringModule | TC-TMS-010 | N | Planned / to be verified |
| TMS-F-011 | Queue monitoring | 4.4 / DS-TMS-011 | MonitoringModule | TC-TMS-011 | N | Planned / to be verified |
| TMS-F-012 | Statistics | 4.4 / DS-TMS-012 | StatisticsModule | TC-TMS-012 | N | Planned / to be verified |
| TMS-F-013 | Simulation reset | 4.5 / DS-TMS-013 | SimulationModule | TC-TMS-013 | N | Planned / to be verified |
| TMS-F-014 | Input validation | 4.5 / DS-TMS-014 | ValidationModule | TC-TMS-014 | N | Planned / to be verified |
| TMS-F-015 | Exit simulation | 4.5 / DS-TMS-015 | SimulationModule | TC-TMS-015 | N | Planned / to be verified |
| TMS-NF-001 | Response time | 5 / DS-NF-001 | QualityModule | TC-NF-001 | N | Planned / to be verified |
| TMS-NF-002 | Queue reliability | 5 / DS-NF-002 | QualityModule | TC-NF-002 | N | Planned / to be verified |
| TMS-NF-003 | Input robustness | 5 / DS-NF-003 | QualityModule | TC-NF-003 | N | Planned / to be verified |
| TMS-NF-004 | CLI usability | 5 / DS-NF-004 | QualityModule | TC-NF-004 | N | Planned / to be verified |
| TMS-NF-005 | Maintainability | 5 / DS-NF-005 | QualityModule | TC-NF-005 | N | Planned / to be verified |
| TMS-SR-001 | Lane validation | 5.1.2 / DS-SEC-001 | SecurityModule | TC-SEC-001 | N | Planned / to be verified |
| TMS-SR-002 | Queue capacity | 5.1.2 / DS-SEC-002 | SecurityModule | TC-SEC-002 | N | Planned / to be verified |
| TMS-SR-003 | Vehicle ID validation | 5.1.2 / DS-SEC-003 | SecurityModule | TC-SEC-003 | N | Planned / to be verified |
| TMS-SR-004 | No command execution | 5.1.2 / DS-SEC-004 | SecurityModule | TC-SEC-004 | N | Planned / to be verified |
| TMS-SR-005 | No confidential data | 5.1.2 / DS-SEC-005 | SecurityModule | TC-SEC-005 | N | Planned / to be verified |
