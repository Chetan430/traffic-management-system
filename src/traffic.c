#include <stdio.h>

#define MAX_QUEUE 100

int queue[MAX_QUEUE];
int front = 0;
int rear = 0;

void enqueue(int vehicle) {
    if (rear < MAX_QUEUE) {
        queue[rear++] = vehicle;
        printf("Vehicle %d added to traffic queue.\n", vehicle);
    } else {
        printf("Traffic queue is full.\n");
    }
}

int dequeue() {
    if (front < rear) {
        return queue[front++];
    }
    return -1;
}

void displayQueue() {
    if (front == rear) {
        printf("Traffic queue is empty.\n");
        return;
    }

    printf("Vehicles in queue: ");

    for (int i = front; i < rear; i++) {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

int main() {
    int choice;
    int vehicle;

    printf("====================================\n");
    printf(" Traffic Management System\n");
    printf("====================================\n");

    while (1) {
        printf("\n1. Add Vehicle\n");
        printf("2. Process Vehicle\n");
        printf("3. Display Traffic Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter vehicle ID: ");
                scanf("%d", &vehicle);
                enqueue(vehicle);
                break;

            case 2:
                vehicle = dequeue();

                if (vehicle == -1) {
                    printf("No vehicles waiting.\n");
                } else {
                    printf("Vehicle %d has passed through the intersection.\n",
                           vehicle);
                }
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                printf("Exiting Traffic Management System.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}