# Synchronization-and-Mutual-Exclusion

* CalTrain (the train running in California, USA) has decided to improve its efficiency by automating
  not just its trains but also its passengers. From now on, passengers will be robots. Each robot and
  each train is controlled by a thread. You have been hired to write synchronization functions that will
  guarantee orderly loading of trains. You must define a structure struct station, plus several
  functions described below.
* When a train arrives in the station and has opened its doors, it invokes the function
  station load train(struct station ? station, int count)
  where count indicates how many seats are available on the train. The function must not return until
  the train is satisfactorily loaded (all passengers are in their seats, and either the train is full or all wait-
  ing passengers have boarded). Note, that the train must leave the station promptly if no passengers
  are waiting at the station or it has no available free seats.
* When a passenger robot arrives in a station, it first invokes the function
  station wait for train(struct station ? station) This function must not return until a
  train is in the station (i.e., a call to station load train is in progress) and there are enough free seats on
  the train for this passenger to sit down. Once this function returns, the passenger robot will move the
  passenger on board the train and into a seat (you do not need to worry about how this mechanism
  works). Once the passenger is seated, it will call the function
  station on board(struct station ? station)
  to let the train know that it’s on board.

## Authors
* **Youssef Emad** 
