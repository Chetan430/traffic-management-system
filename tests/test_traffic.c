
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

void initializeQueues(void) {
    for (int i = 0; i < MAX_LANES; i++) {
        lanes[i].front = 0;
        lanes[i].rear = 0;
    }

    totalVehiclesAdded = 0;
    totalVehiclesProcessed = 0;
}

int isEmpty(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        return 1;
    }

    return lanes[lane].front == lanes[lane].rear;
}

int isFull(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        return 1;
    }

    return lanes[lane].rear >= MAX_QUEUE;
}

int queueSize(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        return 0;
    }

    return lanes[lane].rear - lanes[lane].front;
}

void compactQueue(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        return;
    }

    int size = queueSize(lane);

    if (lanes[lane].front > 0) {
        for (int i = 0; i < size; i++) {
            lanes[lane].vehicles[i] =
                lanes[lane].vehicles[lanes[lane].front + i];
        }

        lanes[lane].front = 0;
        lanes[lane].rear = size;
    }
}

void addVehicle(int lane, int id, int emergency) {
    if (lane < 0 || lane >= MAX_LANES) {
        return;
    }

    if (id <= 0) {
        return;
    }

    if (emergency != 0 && emergency != 1) {
        return;
    }

    compactQueue(lane);

    if (isFull(lane)) {
        return;
    }

    Vehicle vehicle;
    vehicle.id = id;
    vehicle.emergency = emergency;

    if (emergency == 1) {
        int position = lanes[lane].front;

        for (int i = lanes[lane].rear; i > position; i--) {
            lanes[lane].vehicles[i] =
                lanes[lane].vehicles[i - 1];
        }

        lanes[lane].vehicles[position] = vehicle;
        lanes[lane].rear++;
    } else {
        lanes[lane].vehicles[lanes[lane].rear++] = vehicle;
    }

    totalVehiclesAdded++;
}

int processVehicle(int lane) {
    if (lane < 0 || lane >= MAX_LANES) {
        return -1;
    }

    if (isEmpty(lane)) {
        return -1;
    }

    Vehicle vehicle =
        lanes[lane].vehicles[lanes[lane].front++];

    totalVehiclesProcessed++;

    if (lanes[lane].front == lanes[lane].rear) {
        lanes[lane].front = 0;
        lanes[lane].rear = 0;
    }

    return vehicle.id;
}

void testQueueFIFO(void) {
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

void testEmergencyPriority(void) {
    initializeQueues();

    addVehicle(0, 201, 0);
    addVehicle(0, 202, 0);
    addVehicle(0, 999, 1);

    assert(processVehicle(0) == 999);
    assert(processVehicle(0) == 201);
    assert(processVehicle(0) == 202);
}

void testMultipleLanes(void) {
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

void testEmptyQueue(void) {
    initializeQueues();

    assert(isEmpty(0));
    assert(queueSize(0) == 0);
    assert(processVehicle(0) == -1);
}

void testStatistics(void) {
    initializeQueues();

    addVehicle(0, 501, 0);
    addVehicle(0, 502, 0);
    addVehicle(1, 601, 0);

    assert(totalVehiclesAdded == 3);

    processVehicle(0);
    processVehicle(1);

    assert(totalVehiclesProcessed == 2);
}

void testQueueLimit(void) {
    initializeQueues();

    for (int i = 0; i < MAX_QUEUE; i++) {
        addVehicle(0, i + 1, 0);
    }

    assert(queueSize(0) == MAX_QUEUE);

    addVehicle(0, 999, 0);

    assert(queueSize(0) == MAX_QUEUE);
    assert(totalVehiclesAdded == MAX_QUEUE);
}

void testQueueCompaction(void) {
    initializeQueues();

    for (int i = 0; i < MAX_QUEUE; i++) {
        addVehicle(0, i + 1, 0);
    }

    for (int i = 0; i < 10; i++) {
        assert(processVehicle(0) == i + 1);
    }

    addVehicle(0, 100, 0);

    assert(queueSize(0) == MAX_QUEUE - 9);
    assert(lanes[0].vehicles[lanes[0].front].id == 11);
    assert(processVehicle(0) == 11);
}

void testDensityCounts(void) {
    initializeQueues();

    assert(queueSize(0) == 0);

    addVehicle(0, 1001, 0);
    assert(queueSize(0) == 1);

    for (int i = 0; i < 9; i++) {
        addVehicle(0, 1002 + i, 0);
    }

    assert(queueSize(0) == 10);

    addVehicle(0, 2000, 0);
    assert(queueSize(0) == 11);
}

void testInvalidInputs(void) {
    initializeQueues();

    /* Invalid lane numbers */
    addVehicle(-1, 101, 0);
    addVehicle(MAX_LANES, 102, 0);
    assert(totalVehiclesAdded == 0);

    /* Invalid vehicle IDs */
    addVehicle(0, 0, 0);
    addVehicle(0, -5, 0);
    assert(queueSize(0) == 0);
    assert(totalVehiclesAdded == 0);

    /* Invalid emergency flags */
    addVehicle(0, 103, -1);
    addVehicle(0, 104, 2);
    assert(queueSize(0) == 0);
    assert(totalVehiclesAdded == 0);

    /* Invalid lane operations */
    assert(processVehicle(-1) == -1);
    assert(processVehicle(MAX_LANES) == -1);
    assert(queueSize(-1) == 0);
    assert(queueSize(MAX_LANES) == 0);
    assert(isEmpty(-1));
    assert(isEmpty(MAX_LANES));
    assert(isFull(-1));
    assert(isFull(MAX_LANES));

    /* Valid input still works */
    addVehicle(0, 105, 0);

    assert(queueSize(0) == 1);
    assert(totalVehiclesAdded == 1);
    assert(processVehicle(0) == 105);
}

void testResetCounters(void) {
    initializeQueues();
    addVehicle(0, 701, 0);
    addVehicle(1, 702, 0);
    processVehicle(0);
    assert(totalVehiclesAdded == 2);
    assert(totalVehiclesProcessed == 1);
    initializeQueues();
    assert(totalVehiclesAdded == 0);
    assert(totalVehiclesProcessed == 0);
    assert(queueSize(0) == 0);
    assert(queueSize(1) == 0);
}

int main(void) {
    testQueueFIFO();
    testEmergencyPriority();
    testMultipleLanes();
    testEmptyQueue();
    testStatistics();
    testQueueLimit();
    testQueueCompaction();
    testDensityCounts();
    testInvalidInputs();
    testResetCounters();

    printf("====================================\n");
    printf("All automated tests passed!\n");
    printf("====================================\n");

    return 0;
}
