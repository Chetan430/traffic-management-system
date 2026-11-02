# Traffic Management System — safer manual signal update

This package preserves the existing browser dashboard and C queue engine while correcting signal control.

## Signal behaviour
- Only one lane can be GREEN at a time; all other lanes are RED.
- Selecting a lane and choosing **Set Lane GREEN** makes that lane GREEN and turns the other lanes RED.
- **Set Lane RED** turns the selected lane RED. The other lane states remain unchanged.
- Processing is allowed only from a GREEN lane.
- Adding an emergency vehicle inserts it at the front of its queue and immediately gives that lane GREEN; all other lanes become RED. This models emergency preemption in the simulation.
- Reset returns the simulation to Lane 1 GREEN and the other lanes RED.
- Signal changes and vehicle processing remain manual; there is no automatic rotation or automatic normal-vehicle processing.

This is a software simulation, not a real traffic-signal controller. Emergency preemption is represented instantly in the simulation; no physical amber/all-red clearance timing is modeled.

## Build and run (Windows PowerShell)
From the extracted project root:

```powershell
gcc ui/tms_ui.c -o tms_ui.exe -lws2_32
.\tms_ui.exe
```

Open `http://127.0.0.1:8080`.

Keep `src/traffic.c`, `ui/tms_ui.c`, and `ui/index.html` in these relative locations because `ui/tms_ui.c` includes `../src/traffic.c`.
