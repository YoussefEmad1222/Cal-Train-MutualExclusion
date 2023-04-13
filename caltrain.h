#include <pthread.h>

struct station {//struct station is a struct that contains the following variables
int seats;//seats is an int that represents the number of seats on the train
int waiting_passengers;//waiting_passengers is an int that represents the number of passengers waiting for the train
int boarded_passengers;//boarded_passengers is an int that represents the number of passengers that have boarded the train
pthread_mutex_t lock;//lock is a mutex that is used to lock the station
pthread_cond_t train_arrived;//train_arrived is a condition variable that is used to signal that the train has arrived
pthread_cond_t train_left;//train_left is a condition variable that is used to signal that the train has left
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);