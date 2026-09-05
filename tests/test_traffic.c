#include <assert.h>
#include <stdio.h>

#define MAX_QUEUE 100

int queue[MAX_QUEUE];
int front = 0;
int rear = 0;

void enqueue(int vehicle) {
    if (rear < MAX_QUEUE) {
        queue[rear++] = vehicle;
    }
}

int dequeue() {
    if (front < rear) {
        return queue[front++];
    }

    return -1;
}

int main() {
    enqueue(101);
    enqueue(102);
    enqueue(103);

    assert(dequeue() == 101);
    assert(dequeue() == 102);
    assert(dequeue() == 103);
    assert(dequeue() == -1);

    printf("All tests passed successfully.\n");

    return 0;
}