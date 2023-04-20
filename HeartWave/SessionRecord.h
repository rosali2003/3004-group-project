#ifndef SESSIONRECORD_H
#define SESSIONRECORD_H

#include <QDateTime>

class SessionRecord{
public:
    SessionRecord(QDateTime date, int duration, float avg_coherence) {this->date = date; this->duration = duration; this->avg_coherence = avg_coherence;}
    QDateTime getDate(){return date;}
    int getDuration(){return duration;}
    float getAvgCoherence(){return avg_coherence;}
private:
    QDateTime date;
    int duration;
    float avg_coherence;
};

#endif // SESSIONRECORD_H
