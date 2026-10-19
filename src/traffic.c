#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LANES 4
#define MAX_QUEUE 50

typedef struct {
    int id;
    int emergency;
} Vehicle;

typedef struct {
    Vehicle vehicles[MAX_QUEUE];
    int front;
    int rear;
} Queue;

Queue lanes[MAX_LANES];

int totalVehiclesAdded = 0;
int totalVehiclesProcessed = 0;

void initializeQueues() {
    for (int i = 0; i < MAX_LANES; i++) {
        lanes[i].front = 0;
        lanes[i].rear = 0;
    }
}

int isEmpty(int lane) {
    return lanes[lane].front == lanes[lane].rear;
}

int isFull(int lane) {
    return lanes[lane].rear >= MAX_QUEUE;
}

int queueSize(int lane) {
    return lanes[lane].rear - lanes[lane].front;
}

void addVehicle(int lane, int id, int emergency) {
    if (lane < 0 || lane >= MAX_LANES) {
        printf("Invalid lane.\n");
        return;
    }

    if (isFull(lane)) {
        printf("Lane %d is full.\n", lane + 1);
        return;
    }

    Vehicle vehicle;
    vehicle.id = id;
    vehicle.emergency = emergency;

    if (emergency) {
        int position = lanes[lane].front;

        for (int i = lanes[lane].rear; i > position; i--) {
            lanes[lane].vehicles[i] = lanes[lane].vehicles[i - 1];
        }

        lanes[lane].vehicles[position] = vehicle;
        lanes[lane].rear++;
    } else {
        lanes[lane].vehicles[lanes[lane].rear++] = vehicle;
    }

    totalVehiclesAdded++;

    printf("Vehicle %d added to Lane %d%s.\n",
           id, lane + 1, emergency ? " (Emergency)" : "");
}

void processVehicle(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        printf("Invalid lane.\n");
        return;
    }

    if (isEmpty(lane)) {
        printf("Lane %d is empty.\n", lane + 1);
        return;
    }

    Vehicle vehicle = lanes[lane].vehicles[lanes[lane].front++];

    totalVehiclesProcessed++;

    printf("Vehicle %d%s processed from Lane %d.\n",
           vehicle.id,
           vehicle.emergency ? " (Emergency)" : "",
           lane + 1);

    if (lanes[lane].front == lanes[lane].rear) {
        lanes[lane].front = 0;
        lanes[lane].rear = 0;
    }
}

void displayLane(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        printf("Invalid lane.\n");
        return;
    }

    printf("\nLane %d: ", lane + 1);

    if (isEmpty(lane)) {
        printf("Empty\n");
        return;
    }

    for (int i = lanes[lane].front; i < lanes[lane].rear; i++) {
        printf("%d", lanes[lane].vehicles[i].id);

        if (lanes[lane].vehicles[i].emergency) {
            printf("(E)");
        }

        if (i < lanes[lane].rear - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
}

void displayAllLanes() {
    printf("\n========== TRAFFIC QUEUES ==========\n");

    for (int i = 0; i < MAX_LANES; i++) {
        displayLane(i);
    }

    printf("====================================\n");
}

void displayDensity() {
    printf("\n========== TRAFFIC DENSITY ==========\n");

    for (int i = 0; i < MAX_LANES; i++) {
        int count = queueSize(i);

        printf("Lane %d: %d vehicles - ", i + 1, count);

        if (count == 0) {
            printf("LOW\n");
        } else if (count <= 10) {
            printf("MEDIUM\n");
        } else {
            printf("HIGH\n");
        }
    }

    printf("=====================================\n");
}

void displayStatistics() {
    printf("\n========== STATISTICS ==========\n");
    printf("Total vehicles added     : %d\n", totalVehiclesAdded);
    printf("Total vehicles processed : %d\n", totalVehiclesProcessed);

    int waiting = 0;

    for (int i = 0; i < MAX_LANES; i++) {
        waiting += queueSize(i);
    }

    printf("Vehicles currently waiting: %d\n", waiting);
    printf("================================\n");
}

void displaySignal() {
    int signal;

    printf("\nSelect traffic signal state:\n");
    printf("1. RED\n");
    printf("2. GREEN\n");
    printf("Enter choice: ");
    scanf("%d", &signal);

    if (signal == 1) {
        printf("Traffic signal: RED\n");
        printf("Vehicles must wait.\n");
    } else if (signal == 2) {
        printf("Traffic signal: GREEN\n");
        printf("Vehicles may proceed.\n");
    } else {
        printf("Invalid signal selection.\n");
    }
}

void resetSimulation() {
    initializeQueues();

    totalVehiclesAdded = 0;
    totalVehiclesProcessed = 0;

    printf("Simulation has been reset successfully.\n");
}

void addVehicleMenu() {
    int lane;
    int id;
    int emergency;

    printf("\nEnter lane number (1-%d): ", MAX_LANES);
    scanf("%d", &lane);

    printf("Enter vehicle ID: ");
    scanf("%d", &id);

    if (id <= 0) {
        printf("Vehicle ID must be positive.\n");
        return;
    }

    printf("Is this an emergency vehicle? (1-Yes, 0-No): ");
    scanf("%d", &emergency);

    if (emergency != 0 && emergency != 1) {
        printf("Invalid emergency option.\n");
        return;
    }

    addVehicle(lane - 1, id, emergency);
}

void processVehicleMenu() {
    int lane;

    printf("\nEnter lane number to process (1-%d): ", MAX_LANES);
    scanf("%d", &lane);

    processVehicle(lane - 1);
}

void displayMenu() {
    printf("\n");
    printf("============================================\n");
    printf("       TRAFFIC MANAGEMENT SYSTEM\n");
    printf("              SIMULATION\n");
    printf("============================================\n");
    printf("1. Add Vehicle\n");
    printf("2. Process Vehicle\n");
    printf("3. Display All Queues\n");
    printf("4. Display Traffic Density\n");
    printf("5. Display Statistics\n");
    printf("6. Change Traffic Signal\n");
    printf("7. Reset Simulation\n");
    printf("8. Exit\n");
    printf("============================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    initializeQueues();

    printf("Traffic Management System Simulation started.\n");

    while (1) {
        displayMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n') {
            }

            continue;
        }

        switch (choice) {
            case 1:
                addVehicleMenu();
                break;

            case 2:
                processVehicleMenu();
                break;

            case 3:
                displayAllLanes();
                break;

            case 4:
                displayDensity();
                break;

            case 5:
                displayStatistics();
                break;

            case 6:
                displaySignal();
                break;

            case 7:
                resetSimulation();
                break;

            case 8:
                printf("Exiting Traffic Management System.\n");
                return 0;

            default:
                printf("Invalid choice. Please select 1-8.\n");
        }
    }

    return 0;
}