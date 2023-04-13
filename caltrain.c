#include "caltrain.h"
#include <pthread.h>
void station_init(struct station *station)//
{
  station->seats = 0;
  station->waiting_passengers = 0;
  station->boarded_passengers = 0;
  pthread_mutex_init(&station->lock, NULL);
  pthread_cond_init(&station->train_arrived, NULL);
  pthread_cond_init(&station->train_left, NULL);
}

void station_load_train(struct station *station, int count)
{
  pthread_mutex_lock(&station->lock);// lock the mutex
  station->seats = count;// set the number of seats to the number of passengers on the train
  while (station->seats > 0 && station->waiting_passengers > 0)
  {
    pthread_cond_broadcast(&station->train_arrived);// signal all waiting passengers that the train has arrived
    pthread_cond_wait(&station->train_left, &station->lock);// wait for the train to leave
  }
  station->seats = 0;// reset the number of seats
  pthread_mutex_unlock(&station->lock);// unlock the mutex
}
void station_wait_for_train(struct station *station)
{
  pthread_mutex_lock(&station->lock);// lock the mutex
  station->waiting_passengers++;// increment the number of waiting passengers
  while (station->seats == station->boarded_passengers) // while the train is full
  {
    pthread_cond_wait(&station->train_arrived, &station->lock);// wait for the train to arrive
  }
  station->waiting_passengers--; // decrement the number of waiting passengers
  station->boarded_passengers++; // increment the number of boarded passengers
  pthread_mutex_unlock(&station->lock);
}

void station_on_board(struct station *station)
{
  pthread_mutex_lock(&station->lock);
  station->seats--;// decrement the number of seats
  station->boarded_passengers--;// decrement the number of boarded passengers
  if ((station->boarded_passengers == 0 && station->seats == 0) || (station->waiting_passengers == 0 && station->boarded_passengers == 0))
  {//if there are no more waiting passengers and no more boarded passengers or if there are no more seats available and no more boarded passengers
    pthread_cond_signal(&station->train_left);// signal the train to leave
  }
  pthread_mutex_unlock(&station->lock);// unlock the mutex
}