#include <assert.h>
#include <stdio.h>

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

    totalVehiclesAdded = 0;
    totalVehiclesProcessed = 0;
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
    if (lane < 0 || lane >= MAX_LANES)
        return;

    if (isFull(lane))
        return;

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
}

int processVehicle(int lane) {
    if (lane < 0 || lane >= MAX_LANES)
        return -1;

    if (isEmpty(lane))
        return -1;

    Vehicle vehicle = lanes[lane].vehicles[lanes[lane].front++];

    totalVehiclesProcessed++;

    if (lanes[lane].front == lanes[lane].rear) {
        lanes[lane].front = 0;
        lanes[lane].rear = 0;
    }

    return vehicle.id;
}

void testQueueFIFO() {
    initializeQueues();

    addVehicle(0, 101, 0);
    addVehicle(0, 102, 0);
    addVehicle(0, 103, 0);

    assert(queueSize(0) == 3);
    assert(processVehicle(0) == 101);
    assert(processVehicle(0) == 102);
    assert(processVehicle(0) == 103);
    assert(processVehicle(0) == -1);
}

void testEmergencyPriority() {
    initializeQueues();

    addVehicle(0, 201, 0);
    addVehicle(0, 202, 0);
    addVehicle(0, 999, 1);

    assert(processVehicle(0) == 999);
    assert(processVehicle(0) == 201);
    assert(processVehicle(0) == 202);
}

void testMultipleLanes() {
    initializeQueues();

    addVehicle(0, 101, 0);
    addVehicle(1, 201, 0);
    addVehicle(2, 301, 0);
    addVehicle(3, 401, 0);

    assert(queueSize(0) == 1);
    assert(queueSize(1) == 1);
    assert(queueSize(2) == 1);
    assert(queueSize(3) == 1);

    assert(processVehicle(0) == 101);
    assert(processVehicle(1) == 201);
    assert(processVehicle(2) == 301);
    assert(processVehicle(3) == 401);
}

void testEmptyQueue() {
    initializeQueues();

    assert(isEmpty(0));
    assert(queueSize(0) == 0);
    assert(processVehicle(0) == -1);
}

void testStatistics() {
    initializeQueues();

    addVehicle(0, 501, 0);
    addVehicle(0, 502, 0);
    addVehicle(1, 601, 0);

    assert(totalVehiclesAdded == 3);

    processVehicle(0);
    processVehicle(1);

    assert(totalVehiclesProcessed == 2);
}

void testQueueLimit() {
    initializeQueues();

    for (int i = 0; i < MAX_QUEUE; i++) {
        addVehicle(0, i + 1, 0);
    }

    assert(queueSize(0) == MAX_QUEUE);

    addVehicle(0, 999, 0);

    assert(queueSize(0) == MAX_QUEUE);
}

int main() {
    testQueueFIFO();
    testEmergencyPriority();
    testMultipleLanes();
    testEmptyQueue();
    testStatistics();
    testQueueLimit();

    printf("====================================\n");
    printf("All automated tests passed!\n");
    printf("====================================\n");

    return 0;
}