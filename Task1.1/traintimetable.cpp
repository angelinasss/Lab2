#include "traintimetable.h"

TrainTimetable::TrainTimetable()
{
    availableSeats = 0;
}

TrainTimetable::TrainTimetable(int seats, QString number, QString date, QString time, QString Destination) :
    availableSeats(seats), departureDate(date), departureTime(time), destination(Destination), trainNumber(number) {}

void TrainTimetable::setInfoAboutDeparture(int seats, QString number, QString date, QString time, QString destination) {
    this->availableSeats = seats;
    this->departureDate = date;
    this->destination = destination;
    this->departureTime = time;
    this->trainNumber = number;
}

QString TrainTimetable::getDestination() const {
    return destination;
}

QString TrainTimetable::getDepartureDate() const {
    return departureDate;
}

QString TrainTimetable::getDepartureTime() const {
    return departureTime;
}

int TrainTimetable::getAvailableSeats() const {
    return availableSeats;
}

QString TrainTimetable::getTrainNumber() const {
    return trainNumber;
}
