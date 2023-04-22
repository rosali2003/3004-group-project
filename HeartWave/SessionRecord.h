#ifndef SESSIONRECORD_H
#define SESSIONRECORD_H

#include <QDateTime>

class SessionRecord{
public:
    SessionRecord(QDateTime date, float duration, float avg_coherence, float achievement_score) {this->date = date; this->duration = duration; this->avg_coherence = avg_coherence; this->achievement_score= achievement_score;}
    QDateTime getDate(){return date;}
    float getDuration(){return duration;}
    float getAvgCoherence(){return avg_coherence;}
    float getAchievementScore(){return achievement_score;}
private:
    QDateTime date;
    float duration;
    float avg_coherence;
    float achievement_score;
};

#endif // SESSIONRECORD_H
