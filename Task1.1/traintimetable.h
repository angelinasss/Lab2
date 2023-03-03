#ifndef TRAINTIMETABLE_H
#define TRAINTIMETABLE_H
#include <QApplication>

class TrainTimetable
{
    QString departureDate;
    QString destination;
    QString departureTime;
    int availableSeats;
    QString trainNumber;
public:
    TrainTimetable();
    TrainTimetable(int, QString, QString, QString, QString);
    void setInfoAboutDeparture(int, QString, QString, QString, QString);
    QString getDestination() const;
    QString getDepartureDate() const;
    QString getDepartureTime() const;
    int getAvailableSeats() const;
    QString getTrainNumber() const;
};

#endif // TRAINTIMETABLE_H
